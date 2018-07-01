#pragma once
#include <map>
#include "glew.h"
#include "Mesh.h"
#include "Material.h"
#include "FrameBuffer.h"
#include "UniformTime.h"
#include "UniformScreen.h"
#include "UniformZBuffer.h"
#include "UniformProjection.h"
#include "UniformCamera.h"
#include "UniformFog.h"
#include "UniformTransform.h"
#include "UniformAmbientLight.h"
#include "UniformPointLight.h"
#include "UniformDirectLight.h"
#include "UniformShadowLight.h"


#define ENGINE_TIME_NAME                "Time"
#define ENGINE_SCREEN_NAME              "Screen"
#define ENGINE_ZBUFFER_NAME             "ZBuffer"
#define ENGINE_PROJECTION_NAME          "Projection"
#define ENGINE_CAMERA_NAME              "Camera"
#define ENGINE_TRANSFORM_NAME           "Transform"
#define ENGINE_FOG_NAME                 "Fog"
#define ENGINE_AMBIENT_LIGHT_NAME       "AmbientLight"
#define ENGINE_POINT_LIGHT_NAME         "PointLight"
#define ENGINE_DIRECT_LIGHT_NAME        "DirectLight"
#define ENGINE_SHADOW_LIGHT_NAME        "ShadowLight"


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
	void SetCameraProjectionMatrix(const float *mtxProjection);
	void SetCameraViewMatrix(const float *mtxView);

public:
	void SetFogColor(float r, float g, float b);
	void SetFogHeightDensity(float startHeight, float endHeight, float density);
	void SetFogDistanceDensity(float startDistance, float endDistance, float density);

public:
	void SetAmbientLightSH(float shRed[9], float shGreen[9], float shBlue[9]);
	void SetAmbientLightRotation(float angle, float axisx, float axisy, float axisz);

	void SetPointLightColor(float red, float green, float blue);
	void SetPointLightPosition(float posx, float posy, float posz);
	void SetPointLightAttenuation(float linear, float square, float constant);

	void SetDirectLightColor(float red, float green, float blue);
	void SetDirectLightDirection(float dirx, float diry, float dirz);

public:
	void SetShadowLightOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetShadowLightLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);

public:
	bool LoadMaterial(const char *szFileName, GLuint materialid);
	CMaterial* GetMaterial(GLuint id) const;

public:
	void Clear(float red, float green, float blue, float alpha, float depth);
	void DrawInstance(GLuint material, CMesh *pMesh);
	void DrawElements(GLuint material, CMesh *pMesh, const CUniformTransform *pUniformTransform);
	void DrawScreen(GLuint material);

private:
	void BindMaterial(CMaterial *pMaterial);


private:
	char m_szShaderPath[260];
	char m_szTexturePath[260];
	char m_szMaterialPath[260];

private:
	CMesh m_meshScreen;

private:
	CUniformTime m_uniformTime;
	CUniformScreen m_uniformScreen;
	CUniformZBuffer m_uniformZBuffer;
	CUniformProjection m_uniformProjection;
	CUniformCamera m_uniformCamera;
	CUniformFog m_uniformFog;
	CUniformAmbientLight m_uniformAmbientLight;
	CUniformPointLight m_uniformPointLight;
	CUniformDirectLight m_uniformDirectLight;
	CUniformShadowLight m_uniformShadowLight;

private:
	GLuint m_material;
	std::map<GLuint, CMaterial*> m_pMaterials;

private:
	CMaterial *m_pGlobalMaterial;

private:
	static CRenderer *pInstance;
};
