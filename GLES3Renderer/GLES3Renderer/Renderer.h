#pragma once
#include <map>
#include "glew.h"
#include "Material.h"
#include "FrameBuffer.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "UniformTime.h"
#include "UniformScreen.h"
#include "UniformZBuffer.h"
#include "UniformProjection.h"
#include "UniformCamera.h"
#include "UniformTransform.h"
#include "UniformAmbientLight.h"
#include "UniformPointLight.h"
#include "UniformDirectLight.h"
#include "UniformShadowLight.h"
#include "UniformFog.h"


#define ENGINE_TIME_NAME                "Time"
#define ENGINE_SCREEN_NAME              "Screen"
#define ENGINE_ZBUFFER_NAME             "ZBuffer"
#define ENGINE_PROJECTION_NAME          "Projection"
#define ENGINE_CAMERA_NAME              "Camera"
#define ENGINE_TRANSFORM_NAME           "Transform"
#define ENGINE_AMBIENT_LIGHT_NAME       "AmbientLight"
#define ENGINE_POINT_LIGHT_NAME         "PointLight"
#define ENGINE_DIRECT_LIGHT_NAME        "DirectLight"
#define ENGINE_SHADOW_LIGHT_NAME        "ShadowLight"
#define ENGINE_FOG_NAME                 "Fog"


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
	void SetInputTexture(const char *szName, GLuint texture);

public:
	void SetTime(float t, float dt);

public:
	void SetCameraPerspective(float fovy, float aspect, float zNear, float zFar);
	void SetCameraOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetCameraLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	void SetProjectionMatrix(const float *mtxProjection);
	void SetViewMatrix(const float *mtxView);

public:
	void SetShadowLightOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetShadowLightLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);

public:
	void SetAmbientLightSH(float shRed[9], float shGreen[9], float shBlue[9]);
	void SetAmbientLightRotation(float angle, float axisx, float axisy, float axisz);

	void SetPointLightColor(float red, float green, float blue);
	void SetPointLightPosition(float posx, float posy, float posz);
	void SetPointLightAttenuation(float linear, float square, float constant);

	void SetDirectLightColor(float red, float green, float blue);
	void SetDirectLightDirection(float dirx, float diry, float dirz);

	void SetFogColor(float r, float g, float b);
	void SetFogHeightDensity(float startHeight, float endHeight, float density);
	void SetFogDistanceDensity(float startDistance, float endDistance, float density);

public:
	bool LoadMaterial(const char *szFileName, GLuint materialid);
	CMaterial* GetMaterial(GLuint id) const;

public:
	void Clear(float red, float green, float blue, float alpha, float depth);
	void DrawInstance(GLuint material, CVertexBuffer *pVertexBuffer, CIndexBuffer *pIndexBuffer);
	void DrawElements(GLuint material, CVertexBuffer *pVertexBuffer, CIndexBuffer *pIndexBuffer, const CUniformTransform *pUniformTransform);
	void DrawScreen(GLuint material);

private:
	void BindMaterial(CMaterial *pMaterial);


private:
	char m_szShaderPath[260];
	char m_szTexturePath[260];
	char m_szMaterialPath[260];

private:
	CIndexBuffer m_screenIndexBuffer;
	CVertexBuffer m_screenVertexBuffer;

private:
	CUniformTime m_uniformTime;
	CUniformScreen m_uniformScreen;
	CUniformZBuffer m_uniformZBuffer;
	CUniformProjection m_uniformProjection;
	CUniformCamera m_uniformCamera;
	CUniformAmbientLight m_uniformAmbientLight;
	CUniformPointLight m_uniformPointLight;
	CUniformDirectLight m_uniformDirectLight;
	CUniformShadowLight m_uniformShadowLight;
	CUniformFog m_uniformFog;

private:
	GLuint m_material;
	std::map<GLuint, CMaterial*> m_pMaterials;

private:
	CMaterial *m_pGlobalMaterial;

private:
	static CRenderer *pInstance;
};
