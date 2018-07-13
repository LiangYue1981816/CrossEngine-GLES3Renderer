#pragma once
#include <map>
#include <vector>
#include "gles/gl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GfxMesh.h"
#include "GfxFrameBuffer.h"
#include "GfxCommandBuffer.h"
#include "GfxProgramManager.h"
#include "GfxTextureManager.h"
#include "GfxMaterial.h"
#include "GfxProgram.h"
#include "GfxSampler.h"
#include "GfxTexture2D.h"
#include "GfxTexture2DArray.h"
#include "GfxTextureCubeMap.h"
#include "GfxUniformTime.h"
#include "GfxUniformZBuffer.h"
#include "GfxUniformProjection.h"
#include "GfxUniformCamera.h"
#include "GfxUniformShadow.h"
#include "GfxUniformTransform.h"
#include "GfxUniformAmbientLight.h"
#include "GfxUniformPointLight.h"
#include "GfxUniformDirectLight.h"
#include "GfxUniformFog.h"
#include "GfxUniformVec1.h"
#include "GfxUniformVec2.h"
#include "GfxUniformVec3.h"
#include "GfxUniformVec4.h"
#include "GfxUniformMat4.h"


#define ENGINE_TIME_NAME                "Time"
#define ENGINE_ZBUFFER_NAME             "ZBuffer"
#define ENGINE_PROJECTION_NAME          "Projection"
#define ENGINE_CAMERA_NAME              "Camera"
#define ENGINE_SHADOW_NAME              "Shadow"
#define ENGINE_TRANSFORM_NAME           "Transform"
#define ENGINE_AMBIENT_LIGHT_NAME       "AmbientLight"
#define ENGINE_POINT_LIGHT_NAME         "PointLight"
#define ENGINE_DIRECT_LIGHT_NAME        "DirectLight"
#define ENGINE_FOG_NAME                 "Fog"


class CGfxRenderer
{
	friend class CGfxCommandBindMaterial;
	friend class CGfxCommandBindInputTexture;


public:
	static CGfxRenderer* GetInstance(void);
	static void Create(const char *szShaderPath, const char *szTexturePath, const char *szMaterialPath);
	static void Destroy(void);


private:
	CGfxRenderer(const char *szShaderPath, const char *szTexturePath, const char *szMaterialPath);
	virtual ~CGfxRenderer(void);


public:
	const char* GetShaderFullPath(const char *szFileName, char *szFullPath) const;
	const char* GetTextureFullPath(const char *szFileName, char *szFullPath) const;
	const char* GetMaterialFullPath(const char *szFileName, char *szFullPath) const;

public:
	CGfxProgramManager* GetProgramManager(void) const;
	CGfxTextureManager* GetTextureManager(void) const;

public:
	bool LoadMaterial(const char *szFileName, GLuint materialid);
	CGfxMaterial* GetMaterial(GLuint id) const;

public:
	void SetTime(float t, float dt);

public:
	void SetCameraPerspective(float fovy, float aspect, float zNear, float zFar);
	void SetCameraOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetCameraLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	void SetCameraProjectionMatrix(const float *mtxProjection);
	void SetCameraViewMatrix(const float *mtxView);

public:
	void SetShadowOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetShadowLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	void SetShadowProjectionMatrix(const float *mtxProjection);
	void SetShadowViewMatrix(const float *mtxView);
	void SetShadowClipPlane(float zNear, float zFar);
	void SetShadowDistance(float distance);
	void SetShadowResolution(float resolution);

public:
	void SetAmbientLightSH(float shRed[9], float shGreen[9], float shBlue[9]);
	void SetAmbientLightRotation(float angle, float axisx, float axisy, float axisz);

	void SetPointLightColor(float red, float green, float blue);
	void SetPointLightPosition(float posx, float posy, float posz);
	void SetPointLightAttenuation(float linear, float square, float constant);

	void SetDirectLightColor(float red, float green, float blue);
	void SetDirectLightDirection(float dirx, float diry, float dirz);

public:
	void SetFogColor(float red, float green, float blue);
	void SetFogHeightDensity(float startHeight, float endHeight, float density);
	void SetFogDistanceDensity(float startDistance, float endDistance, float density);

public:
	bool CmdBeginPass(CGfxCommandBuffer *pCommandBuffer, CGfxFrameBuffer *pFrameBuffer);
	bool CmdEndPass(CGfxCommandBuffer *pCommandBuffer);

	bool CmdSetScissor(CGfxCommandBuffer *pCommandBuffer, int x, int y, int width, int height);
	bool CmdSetViewport(CGfxCommandBuffer *pCommandBuffer, int x, int y, int width, int height);

	bool CmdSetMaterial(CGfxCommandBuffer *pCommandBuffer, GLuint material);
	bool CmdSetInputTexture(CGfxCommandBuffer *pCommandBuffer, const char *szName, GLuint texture);

	bool CmdClearDepth(CGfxCommandBuffer *pCommandBuffer, float depth);
	bool CmdClearColor(CGfxCommandBuffer *pCommandBuffer, float red, float green, float blue, float alpha);
	bool CmdDrawInstance(CGfxCommandBuffer *pCommandBuffer, CGfxMesh *pMesh);
	bool CmdDrawInstance(CGfxCommandBuffer *pCommandBuffer, CGfxMesh *pMesh, int indexCount, int indexOffset);
	bool CmdDrawScreen(CGfxCommandBuffer *pCommandBuffer);

	bool CmdExecute(CGfxCommandBuffer *pCommandBuffer, CGfxCommandBuffer *pSecondaryCommandBuffer);

public:
	void Update(void);
	void Submit(const CGfxCommandBuffer *pCommandBuffer);

private:
	void BindMaterial(GLuint material);
	void BindInputTexture(const char *szName, GLuint texture);


private:
	char m_szShaderPath[260];
	char m_szTexturePath[260];
	char m_szMaterialPath[260];

private:
	CGfxMesh m_meshScreen;

private:
	CGfxUniformTime m_uniformTime;
	CGfxUniformZBuffer m_uniformZBuffer;
	CGfxUniformProjection m_uniformProjection;
	CGfxUniformCamera m_uniformCamera;
	CGfxUniformShadow m_uniformShadow;
	CGfxUniformAmbientLight m_uniformAmbientLight;
	CGfxUniformPointLight m_uniformPointLight;
	CGfxUniformDirectLight m_uniformDirectLight;
	CGfxUniformFog m_uniformFog;

private:
	GLuint m_material;
	std::map<GLuint, CGfxMaterial*> m_pMaterials;

private:
	CGfxMaterial *m_pGlobalMaterial;
	CGfxProgramManager *m_pProgramManager;
	CGfxTextureManager *m_pTextureManager;

private:
	static CGfxRenderer *pInstance;
};
