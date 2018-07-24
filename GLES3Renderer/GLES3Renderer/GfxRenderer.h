#pragma once
#include <map>
#include <vector>
#include "gles3/gl3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GfxUtils.h"
#include "GfxCamera.h"
#include "GfxFrameBuffer.h"
#include "GfxCommandBuffer.h"
#include "GfxMeshManager.h"
#include "GfxProgramManager.h"
#include "GfxSamplerManager.h"
#include "GfxTextureManager.h"
#include "GfxMaterialManager.h"
#include "GfxMesh.h"
#include "GfxMaterial.h"
#include "GfxProgram.h"
#include "GfxSampler.h"
#include "GfxTexture2D.h"
#include "GfxTexture2DArray.h"
#include "GfxTextureCubeMap.h"
#include "GfxUniformTime.h"
#include "GfxUniformCamera.h"
#include "GfxUniformZBuffer.h"
#include "GfxUniformProjection.h"
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
#define ENGINE_CAMERA_NAME              "Camera"
#define ENGINE_ZBUFFER_NAME             "ZBuffer"
#define ENGINE_PROJECTION_NAME          "Projection"
#define ENGINE_SHADOW_NAME              "Shadow"
#define ENGINE_TRANSFORM_NAME           "Transform"
#define ENGINE_AMBIENT_LIGHT_NAME       "AmbientLight"
#define ENGINE_POINT_LIGHT_NAME         "PointLight"
#define ENGINE_DIRECT_LIGHT_NAME        "DirectLight"
#define ENGINE_FOG_NAME                 "Fog"


class CGfxRenderer
{
	friend class CGfxCommandBindMesh;
	friend class CGfxCommandBindCamera;
	friend class CGfxCommandBindMaterial;
	friend class CGfxCommandBindInputTexture;


public:
	static CGfxRenderer* GetInstance(void);
	static void Create(const char *szShaderPath, const char *szTexturePath, const char *szMaterialPath, const char *szMeshPath);
	static void Destroy(void);


private:
	CGfxRenderer(const char *szShaderPath, const char *szTexturePath, const char *szMaterialPath, const char *szMeshPath);
	virtual ~CGfxRenderer(void);


public:
	const char* GetShaderFullPath(const char *szFileName, char *szFullPath) const;
	const char* GetTextureFullPath(const char *szFileName, char *szFullPath) const;
	const char* GetMaterialFullPath(const char *szFileName, char *szFullPath) const;
	const char* GetMeshFullPath(const char *szFileName, char *szFullPath) const;

public:
	CGfxProgram* CreateProgram(const char *szVertexFileName, const char *szFragmentFileName);
	CGfxSampler* CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode);

	CGfxTexture2D* LoadTexture2D(const char *szFileName);
	CGfxTexture2DArray* LoadTexture2DArray(const char *szFileName);
	CGfxTextureCubeMap* LoadTextureCubeMap(const char *szFileName);
	void FreeTexture(CGfxTextureBase *pTexture);

	CGfxMaterial* LoadMaterial(const char *szFileName);
	void FreeMaterial(CGfxMaterial *pMaterial);

	CGfxMesh* LoadMesh(const char *szFileName);
	void FreeMesh(CGfxMesh *pMesh);

public:
	void SetTime(float t, float dt);

	void SetCameraPerspective(float fovy, float aspect, float zNear, float zFar);
	void SetCameraOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetCameraLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	void SetCameraProjectionMatrix(const float *mtxProjection);
	void SetCameraViewMatrix(const float *mtxView);

	void SetShadowOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetShadowLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	void SetShadowProjectionMatrix(const float *mtxProjection);
	void SetShadowViewMatrix(const float *mtxView);
	void SetShadowClipPlane(float zNear, float zFar);
	void SetShadowDistance(float distance);
	void SetShadowResolution(float resolution);

	void SetAmbientLightSH(float shRed[9], float shGreen[9], float shBlue[9]);
	void SetAmbientLightRotation(float angle, float axisx, float axisy, float axisz);

	void SetPointLightColor(float red, float green, float blue);
	void SetPointLightPosition(float posx, float posy, float posz);
	void SetPointLightAttenuation(float linear, float square, float constant);

	void SetDirectLightColor(float red, float green, float blue);
	void SetDirectLightDirection(float dirx, float diry, float dirz);

	void SetFogColor(float red, float green, float blue);
	void SetFogHeightDensity(float startHeight, float endHeight, float density);
	void SetFogDistanceDensity(float startDistance, float endDistance, float density);

public:
	bool CmdBeginPass(CGfxCommandBuffer *pCommandBuffer, CGfxFrameBuffer *pFrameBuffer);
	bool CmdEndPass(CGfxCommandBuffer *pCommandBuffer);

	bool CmdSetScissor(CGfxCommandBuffer *pCommandBuffer, int x, int y, int width, int height);
	bool CmdSetViewport(CGfxCommandBuffer *pCommandBuffer, int x, int y, int width, int height);

	bool CmdBindMaterial(CGfxCommandBuffer *pCommandBuffer, CGfxMaterial *pMaterial, CGfxUniformCamera *pUniformCamera = NULL, CGfxUniformZBuffer *pUniformZBuffer = NULL, CGfxUniformProjection *pUniformProjection = NULL);
	bool CmdBindInputTexture(CGfxCommandBuffer *pCommandBuffer, const char *szName, GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode);

	bool CmdClearDepth(CGfxCommandBuffer *pCommandBuffer, float depth);
	bool CmdClearColor(CGfxCommandBuffer *pCommandBuffer, float red, float green, float blue, float alpha);
	bool CmdDrawInstance(CGfxCommandBuffer *pCommandBuffer, CGfxMesh *pMesh, int indexCount, int indexOffset);
	bool CmdDrawInstance(CGfxCommandBuffer *pCommandBuffer, CGfxMesh *pMesh, int indexCount, int indexOffset, std::vector<glm::mat4> &mtxTransforms);
	bool CmdDrawScreen(CGfxCommandBuffer *pCommandBuffer);

	bool CmdExecute(CGfxCommandBuffer *pCommandBuffer, CGfxCommandBuffer *pSecondaryCommandBuffer);

public:
	void Update(void);
	void Submit(const CGfxCommandBuffer *pCommandBuffer);

private:
	void BindMesh(CGfxMesh *pMesh);
	void BindMaterial(CGfxMaterial *pMaterial, CGfxUniformCamera *pUniformCamera, CGfxUniformZBuffer *pUniformZBuffer, CGfxUniformProjection *pUniformProjection);
	void BindInputTexture(const char *szName, GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode);


private:
	char m_szShaderPath[260];
	char m_szTexturePath[260];
	char m_szMaterialPath[260];
	char m_szMeshPath[260];

private:
	CGfxMesh m_meshScreen;

private:
	CGfxMaterial *m_pGlobalMaterial;
	CGfxMaterial *m_pCurrentMaterial;

private:
	CGfxProgramManager *m_pProgramManager;
	CGfxSamplerManager *m_pSamplerManager;
	CGfxTextureManager *m_pTextureManager;
	CGfxMaterialManager *m_pMaterialManager;
	CGfxMeshManager *m_pMeshManager;

private:
	CGfxUniformTime m_uniformTime;
	CGfxUniformCamera m_uniformCamera;
	CGfxUniformZBuffer m_uniformZBuffer;
	CGfxUniformProjection m_uniformProjection;
	CGfxUniformShadow m_uniformShadow;
	CGfxUniformAmbientLight m_uniformAmbientLight;
	CGfxUniformPointLight m_uniformPointLight;
	CGfxUniformDirectLight m_uniformDirectLight;
	CGfxUniformFog m_uniformFog;

private:
	static CGfxRenderer *pInstance;
};
