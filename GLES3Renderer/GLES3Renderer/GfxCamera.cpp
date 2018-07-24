#include "stdio.h"
#include "stdlib.h"
#include "GfxCamera.h"
#include "GfxRenderer.h"


CGfxCamera::CGfxCamera(void)
	: m_index(0)
	, m_pCommandBuffer{ NULL }

	, m_pUniformCamera(NULL)
	, m_pUniformZBuffer(NULL)
	, m_pUniformProjection(NULL)

	, m_pFrameBuffer(NULL)

	, m_bEnableClearDepth(true)
	, m_bEnableClearColor(true)
	, m_clearDepth(1.0f)
	, m_clearColorRed(0.0f)
	, m_clearColorGreen(0.0f)
	, m_clearColorBlue(0.0f)
	, m_clearColorAlpha(0.0f)
{
	m_pCommandBuffer[0] = new CGfxCommandBuffer(true);
	m_pCommandBuffer[1] = new CGfxCommandBuffer(true);

	m_pUniformCamera = new CGfxUniformCamera;
	m_pUniformZBuffer = new CGfxUniformZBuffer;
	m_pUniformProjection = new CGfxUniformProjection;
}

CGfxCamera::~CGfxCamera(void)
{
	ClearQueue();
	{
		m_index = 1 - m_index;
	}
	ClearQueue();

	delete m_pCommandBuffer[0];
	delete m_pCommandBuffer[1];

	delete m_pUniformCamera;
	delete m_pUniformZBuffer;
	delete m_pUniformProjection;
}

void CGfxCamera::SetFrameBuffer(CGfxFrameBuffer *pFrameBuffer)
{
	m_pFrameBuffer = pFrameBuffer;
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
	if (pMaterial->IsEnableBlend()) {
		if (m_queueTransparent[m_index].find(pMaterial) == m_queueTransparent[m_index].end()) {
			pMaterial->Lock();
		}

		if (m_queueTransparent[m_index][pMaterial].find(pMesh) == m_queueTransparent[m_index][pMaterial].end()) {
			pMesh->Lock();
		}

		m_queueTransparent[m_index][pMaterial][pMesh].push_back(mtxTransform);
	}
	else {
		if (m_queueOpaque[m_index].find(pMaterial) == m_queueOpaque[m_index].end()) {
			pMaterial->Lock();
		}

		if (m_queueOpaque[m_index][pMaterial].find(pMesh) == m_queueOpaque[m_index][pMaterial].end()) {
			pMesh->Lock();
		}

		m_queueOpaque[m_index][pMaterial][pMesh].push_back(mtxTransform);
	}
}

void CGfxCamera::ClearQueue(void)
{
	for (const auto &itMaterialQueue : m_queueOpaque[m_index]) {
		for (const auto itMeshQueue : itMaterialQueue.second) {
			itMeshQueue.first->Unlock();
		}

		itMaterialQueue.first->Unlock();
	}

	for (const auto &itMaterialQueue : m_queueTransparent[m_index]) {
		for (const auto itMeshQueue : itMaterialQueue.second) {
			itMeshQueue.first->Unlock();
		}

		itMaterialQueue.first->Unlock();
	}

	m_queueOpaque[m_index].clear();
	m_queueTransparent[m_index].clear();
	m_pCommandBuffer[m_index]->Clearup();
}

void CGfxCamera::CmdDraw(void)
{
	m_pCommandBuffer[m_index]->Clearup();

	CGfxRenderer::GetInstance()->CmdBeginPass(m_pCommandBuffer[m_index], m_pFrameBuffer);
	{
		CGfxRenderer::GetInstance()->CmdSetScissor(m_pCommandBuffer[m_index], (int)m_camera.scissor.x, (int)m_camera.scissor.y, (int)m_camera.scissor.z, (int)m_camera.scissor.w);
		CGfxRenderer::GetInstance()->CmdSetViewport(m_pCommandBuffer[m_index], (int)m_camera.viewport.x, (int)m_camera.viewport.y, (int)m_camera.viewport.z, (int)m_camera.viewport.w);

		if (m_bEnableClearDepth) {
			CGfxRenderer::GetInstance()->CmdClearDepth(m_pCommandBuffer[m_index], m_clearDepth);
		}

		if (m_bEnableClearColor) {
			CGfxRenderer::GetInstance()->CmdClearColor(m_pCommandBuffer[m_index], m_clearColorRed, m_clearColorGreen, m_clearColorBlue, m_clearColorAlpha);
		}
		
		for (auto &itMaterialQueue : m_queueOpaque[m_index]) {
			CGfxRenderer::GetInstance()->CmdBindMaterial(m_pCommandBuffer[m_index], itMaterialQueue.first, m_pUniformCamera, m_pUniformZBuffer, m_pUniformProjection);

			for (auto &itMeshQueue : itMaterialQueue.second) {
				CGfxRenderer::GetInstance()->CmdDrawInstance(m_pCommandBuffer[m_index], itMeshQueue.first, itMeshQueue.first->GetIndexCount(), 0, itMeshQueue.second);
			}
		}

		for (auto &itMaterialQueue : m_queueTransparent[m_index]) {
			CGfxRenderer::GetInstance()->CmdBindMaterial(m_pCommandBuffer[m_index], itMaterialQueue.first, m_pUniformCamera, m_pUniformZBuffer, m_pUniformProjection);

			for (auto &itMeshQueue : itMaterialQueue.second) {
				CGfxRenderer::GetInstance()->CmdDrawInstance(m_pCommandBuffer[m_index], itMeshQueue.first, itMeshQueue.first->GetIndexCount(), 0, itMeshQueue.second);
			}
		}
	}
	CGfxRenderer::GetInstance()->CmdEndPass(m_pCommandBuffer[m_index]);
}

void CGfxCamera::Submit(void)
{
	m_pUniformCamera->Apply();
	m_pUniformZBuffer->Apply();
	m_pUniformProjection->Apply();

	CGfxRenderer::GetInstance()->Update();
	CGfxRenderer::GetInstance()->Submit(m_pCommandBuffer[m_index]);

	m_index = 1 - m_index;
}
