#include "stdio.h"
#include "stdlib.h"
#include "GfxUtils.h"
#include "GfxRenderer.h"
#include "GfxVertexAttribute.h"


CGfxRenderer* CGfxRenderer::pInstance = NULL;
CGfxRenderer* CGfxRenderer::GetInstance(void)
{
	return pInstance;
}

void CGfxRenderer::Create(const char *szShaderPath, const char *szTexturePath, const char *szMaterialPath)
{
	if (pInstance == NULL) {
		pInstance = new CGfxRenderer(szShaderPath, szTexturePath, szMaterialPath);
	}
}

void CGfxRenderer::Destroy(void)
{
	if (pInstance) {
		delete pInstance;
	}

	pInstance = NULL;
}

CGfxRenderer::CGfxRenderer(const char *szShaderPath, const char *szTexturePath, const char *szMaterialPath)
	: m_pGlobalMaterial(NULL)
	, m_pCurrentMaterial(NULL)

	, m_pProgramManager(NULL)
	, m_pTextureManager(NULL)
	, m_pMaterialManager(NULL)
{
	strcpy(m_szShaderPath, szShaderPath);
	strcpy(m_szTexturePath, szTexturePath);
	strcpy(m_szMaterialPath, szMaterialPath);

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

	m_meshScreen.CreateIndexBuffer(sizeof(indices), indices, false, GL_UNSIGNED_INT);
	m_meshScreen.CreateVertexBuffer(sizeof(vertices), vertices, false, VERTEX_ATTRIBUTE_POSITION | VERTEX_ATTRIBUTE_TEXCOORD0);

	m_pGlobalMaterial = new CGfxMaterial(0);

	m_pProgramManager = new CGfxProgramManager;
	m_pTextureManager = new CGfxTextureManager;
	m_pMaterialManager = new CGfxMaterialManager;
}

CGfxRenderer::~CGfxRenderer(void)
{
	m_meshScreen.Destroy();

	delete m_pGlobalMaterial;
	delete m_pMaterialManager;
	delete m_pProgramManager;
	delete m_pTextureManager;
}

const char* CGfxRenderer::GetShaderFullPath(const char *szFileName, char *szFullPath) const
{
	sprintf(szFullPath, "%s/%s", m_szShaderPath, szFileName);
	return szFullPath;
}

const char* CGfxRenderer::GetTextureFullPath(const char *szFileName, char *szFullPath) const
{
	sprintf(szFullPath, "%s/%s", m_szTexturePath, szFileName);
	return szFullPath;
}

const char* CGfxRenderer::GetMaterialFullPath(const char *szFileName, char *szFullPath) const
{
	sprintf(szFullPath, "%s/%s", m_szMaterialPath, szFileName);
	return szFullPath;
}

CGfxProgramManager* CGfxRenderer::GetProgramManager(void) const
{
	return m_pProgramManager;
}

CGfxTextureManager* CGfxRenderer::GetTextureManager(void) const
{
	return m_pTextureManager;
}

CGfxMaterialManager* CGfxRenderer::GetMaterialManager(void) const
{
	return m_pMaterialManager;
}

CGfxMaterial* CGfxRenderer::LoadMaterial(const char *szFileName)
{
	return m_pMaterialManager->LoadMaterial(szFileName);
}

CGfxMaterial* CGfxRenderer::GetMaterial(GLuint name) const
{
	CGfxMaterial *pMaterial = m_pMaterialManager->GetMaterial(name);
	return pMaterial != NULL ? pMaterial : m_pGlobalMaterial;
}

void CGfxRenderer::SetTime(float t, float dt)
{
	m_uniformTime.SetTime(t, dt);
}

void CGfxRenderer::SetCameraPerspective(float fovy, float aspect, float zNear, float zFar)
{
	m_uniformCamera.SetPerspective(fovy, aspect, zNear, zFar);
	m_uniformZBuffer.SetZBuffer(zNear, zFar);
	m_uniformProjection.SetProjection(zNear, zFar);
}

void CGfxRenderer::SetCameraOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_uniformCamera.SetOrtho(left, right, bottom, top, zNear, zFar);
	m_uniformZBuffer.SetZBuffer(zNear, zFar);
	m_uniformProjection.SetProjection(zNear, zFar);
}

void CGfxRenderer::SetCameraLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
	m_uniformCamera.SetLookat(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

void CGfxRenderer::SetCameraProjectionMatrix(const float *mtxProjection)
{
	m_uniformCamera.SetProjectionMatrix(mtxProjection);
}

void CGfxRenderer::SetCameraViewMatrix(const float *mtxView)
{
	m_uniformCamera.SetViewMatrix(mtxView);
}

void CGfxRenderer::SetShadowOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_uniformShadow.SetOrtho(left, right, bottom, top, zNear, zFar);
}

void CGfxRenderer::SetShadowLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
	m_uniformShadow.SetLookat(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

void CGfxRenderer::SetShadowProjectionMatrix(const float *mtxProjection)
{
	m_uniformShadow.SetProjectionMatrix(mtxProjection);
}

void CGfxRenderer::SetShadowViewMatrix(const float *mtxView)
{
	m_uniformShadow.SetViewMatrix(mtxView);
}

void CGfxRenderer::SetShadowClipPlane(float zNear, float zFar)
{
	m_uniformShadow.SetClipPlane(zNear, zFar);
}

void CGfxRenderer::SetShadowDistance(float distance)
{
	m_uniformShadow.SetDistance(distance);
}

void CGfxRenderer::SetShadowResolution(float resolution)
{
	m_uniformShadow.SetResolution(resolution);
}

void CGfxRenderer::SetAmbientLightSH(float shRed[9], float shGreen[9], float shBlue[9])
{
	m_uniformAmbientLight.SetSH(shRed, shGreen, shBlue);
}

void CGfxRenderer::SetAmbientLightRotation(float angle, float axisx, float axisy, float axisz)
{
	m_uniformAmbientLight.SetRotation(angle, axisx, axisy, axisz);
}

void CGfxRenderer::SetPointLightColor(float red, float green, float blue)
{
	m_uniformPointLight.SetColor(red, green, blue);
}

void CGfxRenderer::SetPointLightPosition(float posx, float posy, float posz)
{
	m_uniformPointLight.SetPosition(posx, posy, posz);
}

void CGfxRenderer::SetPointLightAttenuation(float linear, float square, float constant)
{
	m_uniformPointLight.SetAttenuation(linear, square, constant);
}

void CGfxRenderer::SetDirectLightColor(float red, float green, float blue)
{
	m_uniformDirectLight.SetColor(red, green, blue);
}

void CGfxRenderer::SetDirectLightDirection(float dirx, float diry, float dirz)
{
	m_uniformDirectLight.SetDirection(-dirx, -diry, -dirz);
}

void CGfxRenderer::SetFogColor(float red, float green, float blue)
{
	m_uniformFog.SetColor(red, green, blue);
}

void CGfxRenderer::SetFogHeightDensity(float startHeight, float endHeight, float density)
{
	m_uniformFog.SetHeightDensity(startHeight, endHeight, density);
}

void CGfxRenderer::SetFogDistanceDensity(float startDistance, float endDistance, float density)
{
	m_uniformFog.SetDistanceDensity(startDistance, endDistance, density);
}

bool CGfxRenderer::CmdBeginPass(CGfxCommandBuffer *pCommandBuffer, CGfxFrameBuffer *pFrameBuffer)
{
	return pCommandBuffer->BeginPass(pFrameBuffer);
}

bool CGfxRenderer::CmdEndPass(CGfxCommandBuffer *pCommandBuffer)
{
	return pCommandBuffer->EndPass();
}

bool CGfxRenderer::CmdSetScissor(CGfxCommandBuffer *pCommandBuffer, int x, int y, int width, int height)
{
	return pCommandBuffer->SetScissor(x, y, width, height);
}

bool CGfxRenderer::CmdSetViewport(CGfxCommandBuffer *pCommandBuffer, int x, int y, int width, int height)
{
	return pCommandBuffer->SetViewport(x, y, width, height);
}

bool CGfxRenderer::CmdSetMaterial(CGfxCommandBuffer *pCommandBuffer, CGfxMaterial *pMaterial)
{
	return pCommandBuffer->BindMaterial(pMaterial);
}

bool CGfxRenderer::CmdSetInputTexture(CGfxCommandBuffer *pCommandBuffer, const char *szName, GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	return pCommandBuffer->BindInputTexture(szName, texture, minFilter, magFilter, addressMode);
}

bool CGfxRenderer::CmdClearDepth(CGfxCommandBuffer *pCommandBuffer, float depth)
{
	return pCommandBuffer->ClearDepth(depth);
}

bool CGfxRenderer::CmdClearColor(CGfxCommandBuffer *pCommandBuffer, float red, float green, float blue, float alpha)
{
	return pCommandBuffer->ClearColor(red, green, blue, alpha);
}

bool CGfxRenderer::CmdDrawInstance(CGfxCommandBuffer *pCommandBuffer, CGfxMesh *pMesh)
{
	return CmdDrawInstance(pCommandBuffer, pMesh, pMesh->GetIndexCount(), 0);
}

bool CGfxRenderer::CmdDrawInstance(CGfxCommandBuffer *pCommandBuffer, CGfxMesh *pMesh, int indexCount, int indexOffset)
{
	if (pCommandBuffer->BindMesh(pMesh) == false) {
		return false;
	}

	if (pCommandBuffer->DrawInstance(GL_TRIANGLES, indexCount, pMesh->GetIndexType(), (void *)indexOffset, pMesh->GetInstanceCount()) == false) {
		return false;
	}

	return true;
}

bool CGfxRenderer::CmdDrawScreen(CGfxCommandBuffer *pCommandBuffer)
{
	if (pCommandBuffer->BindMesh(&m_meshScreen) == false) {
		return false;
	}

	if (pCommandBuffer->DrawElements(GL_TRIANGLES, m_meshScreen.GetIndexCount(), m_meshScreen.GetIndexType(), NULL) == false) {
		return false;
	}

	return true;
}

bool CGfxRenderer::CmdExecute(CGfxCommandBuffer *pCommandBuffer, CGfxCommandBuffer *pSecondaryCommandBuffer)
{
	return pCommandBuffer->Execute(pSecondaryCommandBuffer);
}

void CGfxRenderer::Update(void)
{
	m_uniformTime.Apply();
	m_uniformZBuffer.Apply();
	m_uniformProjection.Apply();
	m_uniformCamera.Apply();
	m_uniformShadow.Apply();
	m_uniformAmbientLight.Apply();
	m_uniformPointLight.Apply();
	m_uniformDirectLight.Apply();
	m_uniformFog.Apply();
}

void CGfxRenderer::Submit(const CGfxCommandBuffer *pCommandBuffer)
{
	pCommandBuffer->Execute();
}

void CGfxRenderer::BindMaterial(CGfxMaterial *pMaterial)
{
	if (m_pCurrentMaterial != pMaterial) {
		m_pCurrentMaterial = pMaterial;

		m_pCurrentMaterial->Bind();
		m_pCurrentMaterial->GetProgram()->BindUniformBuffer(HashValue(ENGINE_TIME_NAME), m_uniformTime.GetBuffer(), m_uniformTime.GetSize());
		m_pCurrentMaterial->GetProgram()->BindUniformBuffer(HashValue(ENGINE_ZBUFFER_NAME), m_uniformZBuffer.GetBuffer(), m_uniformZBuffer.GetSize());
		m_pCurrentMaterial->GetProgram()->BindUniformBuffer(HashValue(ENGINE_PROJECTION_NAME), m_uniformProjection.GetBuffer(), m_uniformProjection.GetSize());
		m_pCurrentMaterial->GetProgram()->BindUniformBuffer(HashValue(ENGINE_CAMERA_NAME), m_uniformCamera.GetBuffer(), m_uniformCamera.GetSize());
		m_pCurrentMaterial->GetProgram()->BindUniformBuffer(HashValue(ENGINE_SHADOW_NAME), m_uniformShadow.GetBuffer(), m_uniformShadow.GetSize());
		m_pCurrentMaterial->GetProgram()->BindUniformBuffer(HashValue(ENGINE_AMBIENT_LIGHT_NAME), m_uniformAmbientLight.GetBuffer(), m_uniformAmbientLight.GetSize());
		m_pCurrentMaterial->GetProgram()->BindUniformBuffer(HashValue(ENGINE_POINT_LIGHT_NAME), m_uniformPointLight.GetBuffer(), m_uniformPointLight.GetSize());
		m_pCurrentMaterial->GetProgram()->BindUniformBuffer(HashValue(ENGINE_DIRECT_LIGHT_NAME), m_uniformDirectLight.GetBuffer(), m_uniformDirectLight.GetSize());
		m_pCurrentMaterial->GetProgram()->BindUniformBuffer(HashValue(ENGINE_FOG_NAME), m_uniformFog.GetBuffer(), m_uniformFog.GetSize());
	}

	m_pGlobalMaterial->BindUniforms(m_pCurrentMaterial->GetProgram());
	m_pGlobalMaterial->BindTextures(m_pCurrentMaterial->GetProgram(), m_pCurrentMaterial->GetTextureUnits());
}

void CGfxRenderer::BindInputTexture(const char *szName, GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	m_pGlobalMaterial->GetTexture2D(szName)->CreateExtern(texture);
	m_pGlobalMaterial->GetSampler(szName, minFilter, magFilter, addressMode);
}
