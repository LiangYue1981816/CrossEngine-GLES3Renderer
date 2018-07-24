#pragma once
#include <map>
#include <vector>
#include "gles3/gl3.h"
#include "GfxGLM.h"


class CGfxMesh;
class CGfxMaterial;
class CGfxFrameBuffer;
class CGfxCommandBuffer;
class CGfxUniformCamera;
class CGfxUniformZBuffer;
class CGfxUniformProjection;
class CGfxCamera
{
public:
	CGfxCamera(void);
	virtual ~CGfxCamera(void);


public:
	void SetFrameBuffer(CGfxFrameBuffer *pFrameBuffer);

public:
	void SetEnableClearDepth(bool bEnable);
	void SetEnableClearColor(bool bEnable);

	void SetClearDepth(float depth);
	void SetClearColor(float red, float green, float blue, float alpha);

public:
	void SetScissor(float x, float y, float width, float height);
	void SetViewport(float x, float y, float width, float height);
	void SetPerspective(float fovy, float aspect, float zNear, float zFar);
	void SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);

	const float* GetProjectionMatrix(void) const;
	const float* GetViewMatrix(void) const;

public:
	glm::vec3 WorldToScreen(const glm::vec3 &world);
	glm::vec3 ScreenToWorld(const glm::vec3 &screen);

public:
	bool IsVisible(const glm::vec3 &vertex);
	bool IsVisible(const glm::aabb &aabb);
	bool IsVisible(const glm::sphere &sphere);

public:
	void AddQueue(CGfxMaterial *pMaterial, CGfxMesh *pMesh, const glm::mat4 &mtxTransform);
	void ClearQueue(void);

public:
	void CmdDraw(void);
	void Submit(void);


private:
	bool m_bEnableClearDepth;
	bool m_bEnableClearColor;

	float m_clearDepth;
	float m_clearColorRed;
	float m_clearColorGreen;
	float m_clearColorBlue;
	float m_clearColorAlpha;

private:
	glm::camera m_camera;

private:
	std::map<CGfxMaterial*, std::map<CGfxMesh*, std::vector<glm::mat4>>> m_queueOpaque;
	std::map<CGfxMaterial*, std::map<CGfxMesh*, std::vector<glm::mat4>>> m_queueTransparent;

private:
	CGfxFrameBuffer *m_pFrameBuffer;
	CGfxCommandBuffer *m_pCommandBuffer;

private:
	CGfxUniformCamera *m_pUniformCamera;
	CGfxUniformZBuffer *m_pUniformZBuffer;
	CGfxUniformProjection *m_pUniformProjection;
};
