#pragma once
#include <map>
#include "glew.h"
#include "Material.h"
#include "FrameBuffer.h"
#include "MeshBufferInstance.h"
#include "UniformBufferCamera.h"
#include "UniformBufferTransform.h"
#include "UniformBufferAmbientLight.h"
#include "UniformBufferPointLight.h"
#include "UniformBufferDirectionLight.h"


class CRenderer
{
public:
	static CRenderer* GetInstance(void);
	static void Create(const char *szShaderPath, const char *szTexturePath, const char *szMaterialPath);
	static void Destroy(void);


private:
	CRenderer(const char *szShaderPath, const char *szTexturePath, const char *szMaterialPath);
	virtual ~CRenderer(void);


public:
	const char* GetShaderFullPath(const char *szFileName, char *szFullPath) const;
	const char* GetTextureFullPath(const char *szFileName, char *szFullPath) const;
	const char* GetMaterialFullPath(const char *szFileName, char *szFullPath) const;

public:
	void SetScissor(int x, int y, int width, int height);
	void SetViewport(int x, int y, int width, int height);
	void SetFrameBuffer(GLuint fbo);

public:
	void SetCameraPerspective(float fovy, float aspect, float zNear, float zFar);
	void SetCameraOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetCameraLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	void SetCameraProjectionMatrix(const float *mtxProjection);
	void SetCameraWorldToViewMatrix(const float *mtxWorldToView);

public:
	void SetAmbientLight(float shRed[9], float shGreen[9], float shBlue[9]);
	void SetAmbientLight(float shRed[9], float shGreen[9], float shBlue[9], float angle, float axisx, float axisy, float axisz);
	void SetPointLight(float posx, float posy, float posz, float red, float green, float blue);
	void SetDirectionLight(float dirx, float diry, float dirz, float red, float green, float blue);

public:
	bool LoadMaterial(const char *szFileName, GLuint materialid = 0xffffffff);
	CMaterial* GetMaterial(GLuint id) const;

public:
	void Clear(float red, float green, float blue, float alpha, float depth);
	void DrawInstance(GLuint material, CMeshBufferInstance *pMesh);
	void DrawElements(GLuint material, CMeshBufferInstance *pMesh, const CUniformBufferTransform *pUniformTransform);
	void DrawScreen(GLuint material, GLsizei numTextures, GLuint *textures, GLchar names[][260]);


private:
	char m_szShaderPath[260];
	char m_szTexturePath[260];
	char m_szMaterialPath[260];

private:
	CMeshBufferInstance m_screenMesh;

private:
	CUniformBufferCamera m_uniformCamera;
	CUniformBufferAmbientLight m_uniformAmbientLight;
	CUniformBufferPointLight m_uniformPointLight;
	CUniformBufferDirectionLight m_uniformDirectionLight;

private:
	GLuint m_material;
	std::map<GLuint, CMaterial*> m_pMaterials;

private:
	static CRenderer *pInstance;
};
