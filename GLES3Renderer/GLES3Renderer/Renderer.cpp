#include "stdio.h"
#include "stdlib.h"
#include "Renderer.h"


CRenderer* CRenderer::pInstance = NULL;
CRenderer* CRenderer::GetInstance(void)
{
	return pInstance;
}

void CRenderer::Create(const char *szShaderPath, const char *szTexturePath, const char *szMaterialPath)
{
	if (pInstance == NULL) {
		pInstance = new CRenderer(szShaderPath, szTexturePath, szMaterialPath);
	}
}

void CRenderer::Destroy(void)
{
	if (pInstance) {
		delete pInstance;
	}

	pInstance = NULL;
}

CRenderer::CRenderer(const char *szShaderPath, const char *szTexturePath, const char *szMaterialPath)
{
	struct Vertex {
		glm::vec3 position;
		glm::vec2 texcoord;
	};

	const static Vertex vertices[] = {
		{ glm::vec3(-1.0f, -1.0f, 0.0f), glm::vec2(0.0f, 0.0f) },
		{ glm::vec3( 1.0f, -1.0f, 0.0f), glm::vec2(1.0f, 0.0f) },
		{ glm::vec3( 1.0f,  1.0f, 0.0f), glm::vec2(1.0f, 1.0f) },
		{ glm::vec3(-1.0f,  1.0f, 0.0f), glm::vec2(0.0f, 1.0f) },
	};

	const static GLuint indices[] = {
		0, 1, 2, 2, 3, 0
	};

	m_screenIndexBuffer.CreateIndexBuffer(sizeof(indices), indices, false, GL_UNSIGNED_INT);
	m_screenVertexBuffer.CreateVertexBuffer(sizeof(vertices), vertices, false, VERTEX_ATTRIBUTE_POSITION | VERTEX_ATTRIBUTE_TEXCOORD0, 0);

	strcpy(m_szShaderPath, szShaderPath);
	strcpy(m_szTexturePath, szTexturePath);
	strcpy(m_szMaterialPath, szMaterialPath);

	m_material = -1;
}

CRenderer::~CRenderer(void)
{
	m_screenIndexBuffer.Destroy();
	m_screenVertexBuffer.Destroy();
}

const char* CRenderer::GetShaderFullPath(const char *szFileName, char *szFullPath) const
{
	sprintf(szFullPath, "%s/%s", m_szShaderPath, szFileName);
	return szFullPath;
}

const char* CRenderer::GetTextureFullPath(const char *szFileName, char *szFullPath) const
{
	sprintf(szFullPath, "%s/%s", m_szTexturePath, szFileName);
	return szFullPath;
}

const char* CRenderer::GetMaterialFullPath(const char *szFileName, char *szFullPath) const
{
	sprintf(szFullPath, "%s/%s", m_szMaterialPath, szFileName);
	return szFullPath;
}

void CRenderer::SetScissor(int x, int y, int width, int height)
{
	glEnable(GL_SCISSOR_TEST);
	glScissor(x, y, width, height);
}

void CRenderer::SetViewport(int x, int y, int width, int height)
{
	glViewport(x, y, width, height);
}

void CRenderer::SetFrameBuffer(GLuint fbo)
{
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);
}

void CRenderer::SetCameraPerspective(float fovy, float aspect, float zNear, float zFar)
{
	m_uniformCamera.SetPerspective(fovy, aspect, zNear, zFar);
	m_uniformCamera.Apply();
}

void CRenderer::SetCameraOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_uniformCamera.SetOrtho(left, right, bottom, top, zNear, zFar);
	m_uniformCamera.Apply();
}

void CRenderer::SetCameraLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
	m_uniformCamera.SetLookat(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
	m_uniformCamera.Apply();
}

void CRenderer::SetProjectionMatrix(const float *mtxProjection)
{
	m_uniformCamera.SetProjectionMatrix(mtxProjection);
	m_uniformCamera.Apply();
}

void CRenderer::SetViewMatrix(const float *mtxView)
{
	m_uniformCamera.SetViewMatrix(mtxView);
	m_uniformCamera.Apply();
}

void CRenderer::SetAmbientLight(float shRed[9], float shGreen[9], float shBlue[9])
{
	m_uniformAmbientLight.SetSH(shRed, shGreen, shBlue);
	m_uniformAmbientLight.Apply();
}

void CRenderer::SetAmbientLight(float shRed[9], float shGreen[9], float shBlue[9], float angle, float axisx, float axisy, float axisz)
{
	m_uniformAmbientLight.SetSH(shRed, shGreen, shBlue, angle, axisx, axisy, axisz);
	m_uniformAmbientLight.Apply();
}

void CRenderer::SetPointLight(float posx, float posy, float posz, float red, float green, float blue)
{
	m_uniformPointLight.SetPosition(posx, posy, posz);
	m_uniformPointLight.SetColor(red, green, blue);
	m_uniformPointLight.Apply();
}

void CRenderer::SetDirectionLight(float dirx, float diry, float dirz, float red, float green, float blue)
{
	m_uniformDirectionLight.SetDirection(-dirx, -diry, -dirz);
	m_uniformDirectionLight.SetColor(red, green, blue);
	m_uniformDirectionLight.Apply();
}

bool CRenderer::LoadMaterial(const char *szFileName, GLuint materialid)
{
	CMaterial *pMaterial = NULL;

	try {
		pMaterial = new CMaterial;
		{
			int err = 0;

			if (pMaterial == NULL) {
				throw err++;
			}

			if (pMaterial->Create(szFileName, &m_uniformCamera, &m_uniformAmbientLight, &m_uniformPointLight, &m_uniformDirectionLight) == false) {
				throw err++;
			}

			if (materialid == 0xffffffff) {
				materialid = pMaterial->GetID();
			}

			if (m_pMaterials.find(materialid) != m_pMaterials.end()) {
				throw err++;
			}

			m_pMaterials[materialid] = pMaterial;
		}
		return true;
	}
	catch (int) {
		if (pMaterial) {
			delete pMaterial;
		}

		return false;
	}
}

CMaterial* CRenderer::GetMaterial(GLuint id) const
{
	const auto &itMaterial = m_pMaterials.find(id);
	return itMaterial != m_pMaterials.end() ? itMaterial->second : NULL;
}

void CRenderer::Clear(float red, float green, float blue, float alpha, float depth)
{
	glClearColor(red, green, blue, alpha);
	glClearDepthf(depth);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void CRenderer::DrawInstance(GLuint material, CVertexBuffer *pVertexBuffer, CIndexBuffer *pIndexBuffer)
{
	if (m_pMaterials.find(material) == m_pMaterials.end()) {
		return;
	}

	if (m_material != material) {
		m_material  = material;
		m_pMaterials[material]->Bind();
	}

	pVertexBuffer->Bind();
	pIndexBuffer->Bind();

	glDrawElementsInstanced(GL_TRIANGLES, pIndexBuffer->GetIndexCount(), pIndexBuffer->GetIndexType(), NULL, pVertexBuffer->GetInstanceCount());
}

void CRenderer::DrawElements(GLuint material, CVertexBuffer *pVertexBuffer, CIndexBuffer *pIndexBuffer, const CUniformBufferTransform *pUniformTransform)
{
	if (m_pMaterials.find(material) == m_pMaterials.end()) {
		return;
	}

	if (m_material != material) {
		m_material  = material;
		m_pMaterials[material]->Bind();
	}

	m_pMaterials[material]->GetProgram()->BindUniformBuffer(HashValue(ENGINE_TRANSFORM_NAME), pUniformTransform->GetBuffer(), pUniformTransform->GetSize());

	pVertexBuffer->Bind();
	pIndexBuffer->Bind();

	glDrawElements(GL_TRIANGLES, pIndexBuffer->GetIndexCount(), pIndexBuffer->GetIndexType(), NULL);
}

void CRenderer::DrawScreen(GLuint material, GLsizei numTextures, GLuint *textures, GLchar names[][260])
{
	if (m_pMaterials.find(material) == m_pMaterials.end()) {
		return;
	}

	if (m_material != material) {
		m_material  = material;
		m_pMaterials[material]->Bind();
	}

	for (GLint index = 0; index < numTextures; index++) {
		m_pMaterials[material]->GetProgram()->BindTexture2D(HashValue(names[index]), textures[index], 0, m_pMaterials[material]->GetInUseTextureUnits() + index);
	}

	glDisable(GL_DEPTH_TEST);
	glDepthMask(GL_FALSE);

	m_screenVertexBuffer.Bind();
	m_screenIndexBuffer.Bind();

	glDrawElements(GL_TRIANGLES, m_screenIndexBuffer.GetIndexCount(), m_screenIndexBuffer.GetIndexType(), NULL);
}
