#include "stdio.h"
#include "stdlib.h"
#include "GfxCamera.h"
#include "GfxRenderer.h"


CGfxCamera::CGfxCamera(void)
	: m_pFrameBuffer(NULL)
	, m_pCommandBuffer(NULL)
{
	m_pCommandBuffer = new CGfxCommandBuffer(true);
}

CGfxCamera::~CGfxCamera(void)
{
	ClearQueue();
	delete m_pCommandBuffer;
}

void CGfxCamera::SetFrameBuffer(CGfxFrameBuffer *pFrameBuffer)
{
	m_pFrameBuffer = pFrameBuffer;
}

const CGfxFrameBuffer* CGfxCamera::GetFrameBuffer(void) const
{
	return m_pFrameBuffer;
}

void CGfxCamera::SetViewport(float x, float y, float width, float height)
{
	m_camera.setViewport(x, y, width, height);
}

void CGfxCamera::SetPerspective(float fovy, float aspect, float zNear, float zFar)
{
	m_camera.setPerspective(fovy, aspect, zNear, zFar);
}

void CGfxCamera::SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_camera.setOrtho(left, right, bottom, top, zNear, zFar);
}

void CGfxCamera::SetLookat(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up)
{
	m_camera.setLookat(position, position + direction, up);
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

void CGfxCamera::AddQueue(GLuint material, CGfxMesh *pMesh, const glm::mat4 &mtxTransform)
{
	if (CGfxMaterial *pMaterial = CGfxRenderer::GetInstance()->GetMaterial(material)) {
		if (m_meshs[pMesh] == NULL) {
			m_meshs[pMesh] = pMesh;

			if (pMaterial->IsEnableBlend()) {
				m_queueTransparent[material].push_back(pMesh);
			}
			else {
				m_queueOpaque[material].push_back(pMesh);
			}
		}

		pMesh->AddInstance(mtxTransform);
	}
}

void CGfxCamera::ClearQueue(void)
{
	for (const auto &itMesh : m_meshs) {
		itMesh.second->ClearInstance();
	}

	m_meshs.clear();
	m_queueOpaque.clear();
	m_queueTransparent.clear();
}

void CGfxCamera::CmdDraw(void)
{

}

void CGfxCamera::Submit(void)
{

}

void CGfxCamera::ClearCommandBuffer(void)
{

}
