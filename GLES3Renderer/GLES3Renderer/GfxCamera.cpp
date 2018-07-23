#include "stdio.h"
#include "stdlib.h"
#include "GfxCamera.h"
#include "GfxRenderer.h"


CGfxCamera::CGfxCamera(void)
	: m_pFrameBuffer(NULL)
	, m_pCommandBuffer(NULL)

	, m_pUniformCamera(NULL)
	, m_pUniformZBuffer(NULL)
	, m_pUniformProjection(NULL)

	, m_bEnableClearDepth(true)
	, m_bEnableClearColor(true)
	, m_clearDepth(1.0f)
	, m_clearColorRed(0.0f)
	, m_clearColorGreen(0.0f)
	, m_clearColorBlue(0.0f)
	, m_clearColorAlpha(0.0f)
{
	m_pCommandBuffer = new CGfxCommandBuffer(true);
	m_pUniformCamera = new CGfxUniformCamera;
	m_pUniformZBuffer = new CGfxUniformZBuffer;
	m_pUniformProjection = new CGfxUniformProjection;
}

CGfxCamera::~CGfxCamera(void)
{
	ClearQueue();

	delete m_pCommandBuffer;
	delete m_pUniformCamera;
	delete m_pUniformZBuffer;
	delete m_pUniformProjection;
}

void CGfxCamera::SetFrameBuffer(CGfxFrameBuffer *pFrameBuffer)
{
	m_pFrameBuffer = pFrameBuffer;
}

const CGfxFrameBuffer* CGfxCamera::GetFrameBuffer(void) const
{
	return m_pFrameBuffer;
}

void CGfxCamera::SetEnableClearDepth(bool bEnable)
{
	m_bEnableClearDepth = bEnable;
}

void CGfxCamera::SetEnableClearColor(bool bEnable)
{
	m_bEnableClearColor = bEnable;
}

void CGfxCamera::SetClearDepth(float depth)
{
	m_clearDepth = depth;
}

void CGfxCamera::SetClearColor(float red, float green, float blue, float alpha)
{
	m_clearColorRed = red;
	m_clearColorGreen = green;
	m_clearColorBlue = blue;
	m_clearColorAlpha = alpha;
}

void CGfxCamera::SetScissor(float x, float y, float width, float height)
{
	m_camera.setScissor(x, y, width, height);
}

void CGfxCamera::SetViewport(float x, float y, float width, float height)
{
	m_camera.setViewport(x, y, width, height);
}

void CGfxCamera::SetPerspective(float fovy, float aspect, float zNear, float zFar)
{
	m_camera.setPerspective(fovy, aspect, zNear, zFar);
	m_pUniformCamera->SetPerspective(fovy, aspect, zNear, zFar);
	m_pUniformZBuffer->SetZBuffer(zNear, zFar);
	m_pUniformProjection->SetProjection(zNear, zFar);
}

void CGfxCamera::SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_camera.setOrtho(left, right, bottom, top, zNear, zFar);
	m_pUniformCamera->SetOrtho(left, right, bottom, top, zNear, zFar);
	m_pUniformZBuffer->SetZBuffer(zNear, zFar);
	m_pUniformProjection->SetProjection(zNear, zFar);
}

void CGfxCamera::SetLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
	m_camera.setLookat(glm::vec3(eyex, eyey, eyez), glm::vec3(centerx, centery, centerz), glm::vec3(upx, upy, upz));
	m_pUniformCamera->SetLookat(eyex, eyey, eyez, centerx, centery, centerz, upx, upy, upz);
}

const float* CGfxCamera::GetProjectionMatrix(void) const
{
	return (float *)&m_camera.mtxProjection;
}

const float* CGfxCamera::GetViewMatrix(void) const
{
	return (float *)&m_camera.mtxView;
}

glm::vec3 CGfxCamera::WorldToScreen(const glm::vec3 &world)
{
	return m_camera.worldToScreen(world);
}

glm::vec3 CGfxCamera::ScreenToWorld(const glm::vec3 &screen)
{
	return m_camera.screenToWorld(screen);
}

bool CGfxCamera::IsVisible(const glm::vec3 &vertex)
{
	return m_camera.visible(vertex);
}

bool CGfxCamera::IsVisible(const glm::aabb &aabb)
{
	return m_camera.visible(aabb);
}

bool CGfxCamera::IsVisible(const glm::sphere &sphere)
{
	return m_camera.visible(sphere);
}

void CGfxCamera::AddQueue(CGfxMaterial *pMaterial, CGfxMesh *pMesh, const glm::mat4 &mtxTransform)
{
	if (m_meshs[pMesh] == NULL) {
		m_meshs[pMesh] = pMesh;

		glm::vec4 position = mtxTransform * glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
		glm::vec3 distance = glm::vec3(position.x - m_camera.position.x, position.y - m_camera.position.y, position.z - m_camera.position.z);
		GLuint length = (GLuint)glm::length(distance);

		if (pMaterial->IsEnableBlend()) {
			m_queueTransparent[pMaterial][UINT_MAX - length].push_back(pMesh);
		}
		else {
			m_queueOpaque[pMaterial][length].push_back(pMesh);
		}
	}

	pMesh->AddInstance(mtxTransform);
}

void CGfxCamera::ClearQueue(void)
{
	for (const auto &itMesh : m_meshs) {
		itMesh.second->ClearInstance();
	}

	m_meshs.clear();
	m_queueOpaque.clear();
	m_queueTransparent.clear();

	m_pCommandBuffer->Clearup();
}

void CGfxCamera::CmdDraw(void)
{
	m_pCommandBuffer->Clearup();

	CGfxRenderer::GetInstance()->CmdBeginPass(m_pCommandBuffer, m_pFrameBuffer);
	{
		CGfxRenderer::GetInstance()->CmdSetScissor(m_pCommandBuffer, (int)m_camera.scissor.x, (int)m_camera.scissor.y, (int)m_camera.scissor.z, (int)m_camera.scissor.w);
		CGfxRenderer::GetInstance()->CmdSetViewport(m_pCommandBuffer, (int)m_camera.viewport.x, (int)m_camera.viewport.y, (int)m_camera.viewport.z, (int)m_camera.viewport.w);

		if (m_bEnableClearDepth) {
			CGfxRenderer::GetInstance()->CmdClearDepth(m_pCommandBuffer, m_clearDepth);
		}

		if (m_bEnableClearColor) {
			CGfxRenderer::GetInstance()->CmdClearColor(m_pCommandBuffer, m_clearColorRed, m_clearColorGreen, m_clearColorBlue, m_clearColorAlpha);
		}

		for (const auto &itMaterialQueue : m_queueOpaque) {
			CGfxRenderer::GetInstance()->CmdSetMaterial(m_pCommandBuffer, itMaterialQueue.first);

			for (const auto &itDistanceQueue : itMaterialQueue.second) {
				for (size_t index = 0; index < itDistanceQueue.second.size(); index++) {
					CGfxRenderer::GetInstance()->CmdDrawInstance(m_pCommandBuffer, itDistanceQueue.second[index], itDistanceQueue.second[index]->GetIndexCount(), 0);
				}
			}
		}
	}
	CGfxRenderer::GetInstance()->CmdEndPass(m_pCommandBuffer);
}

void CGfxCamera::Submit(void)
{
	CGfxRenderer::GetInstance()->SetCameraProjectionMatrix((float *)&m_camera.mtxProjection);
	CGfxRenderer::GetInstance()->SetCameraViewMatrix((float *)&m_camera.mtxView);

	CGfxRenderer::GetInstance()->Update();
	CGfxRenderer::GetInstance()->Submit(m_pCommandBuffer);
}

const CGfxUniformCamera* CGfxCamera::GetUniformCamera(void) const
{
	return m_pUniformCamera;
}

const CGfxUniformZBuffer* CGfxCamera::GetUniformZBuffer(void) const
{
	return m_pUniformZBuffer;
}

const CGfxUniformProjection* CGfxCamera::GetUniformProjection(void) const
{
	return m_pUniformProjection;
}
