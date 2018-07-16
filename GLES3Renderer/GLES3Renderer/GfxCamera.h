#pragma once
#include <map>
#include <vector>
#include "gles3/gl3.h"
#include "GfxGLM.h"


class CGfxFrameBuffer;
class CGfxMesh;
class CGfxCamera
{
public:
	CGfxCamera(void);
	virtual ~CGfxCamera(void);


public:
	void SetFrameBuffer(CGfxFrameBuffer *pFrameBuffer);
	const CGfxFrameBuffer* GetFrameBuffer(void) const;

public:
	void SetViewport(float x, float y, float width, float height);
	void SetPerspective(float fovy, float aspect, float zNear, float zFar);
	void SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetLookat(const glm::vec3 &position, const glm::vec3 &direction, const glm::vec3 &up);

public:
	glm::vec3 WorldToScreen(const glm::vec3 &world);
	glm::vec3 ScreenToWorld(const glm::vec3 &screen);

public:
	bool IsVisible(const glm::vec3 &vertex);
	bool IsVisible(const glm::aabb &aabb);
	bool IsVisible(const glm::sphere &sphere);

public:
	void AddQueue(GLuint material, CGfxMesh *pMesh);
	void ClearQueue(void);


private:
	CGfxFrameBuffer *m_pFrameBuffer;

private:
	glm::camera m_camera;
	std::map<GLuint, std::vector<CGfxMesh*>> m_queue;
};
