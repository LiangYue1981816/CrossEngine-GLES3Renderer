#pragma once
#include <map>
#include <vector>
#include "tinyxml/tinyxml.h"
#include "tinyxml/tinystr.h"
#include "Program.h"
#include "Texture2D.h"
#include "Texture2DArray.h"
#include "TextureCubeMap.h"
#include "UniformBufferVec1.h"
#include "UniformBufferVec2.h"
#include "UniformBufferVec3.h"
#include "UniformBufferVec4.h"
#include "UniformBufferMat4.h"
#include "UniformBufferCamera.h"
#include "UniformBufferAmbientLight.h"
#include "UniformBufferPointLight.h"
#include "UniformBufferDirectionLight.h"


class CMaterial
{
	friend class CRenderer;


public:
	CMaterial(void);
	virtual ~CMaterial(void);


public:
	void Bind(void) const;

private:
	void BindPipeline(void) const;
	void BindUniforms(CProgram *pProgram) const;
	void BindTextures(CProgram *pProgram, GLuint indexUnit) const;

public:
	bool Create(const char *szFileName);
	void Destroy(void);

private:
	bool Load(const char *szFileName);
	bool LoadBase(TiXmlNode *pMaterialNode);
	bool LoadProgram(TiXmlNode *pMaterialNode);
	bool LoadTexture2D(TiXmlNode *pMaterialNode);
	bool LoadTexture2DArray(TiXmlNode *pMaterialNode);
	bool LoadTextureCubeMap(TiXmlNode *pMaterialNode);
	bool LoadUniformVec1(TiXmlNode *pMaterialNode);
	bool LoadUniformVec2(TiXmlNode *pMaterialNode);
	bool LoadUniformVec3(TiXmlNode *pMaterialNode);
	bool LoadUniformVec4(TiXmlNode *pMaterialNode);

public:
	void SetEnableCullFace(bool bEnable, GLenum frontFace);
	void SetEnableDepthTest(bool bEnable, GLenum depthFunc);
	void SetEnableDepthWrite(bool bEnable);
	void SetEnableBlend(bool bEnable, GLenum srcFactor, GLenum dstFactor);
	void SetEnablePolygonOffset(bool bEnable, GLfloat factor, GLfloat units);

public:
	CProgram* GetProgram(void);

	CTexture2D* GetTexture2D(const char *szName);
	CTexture2DArray* GetTexture2DArray(const char *szName);
	CTextureCubeMap* GetTextureCubeMap(const char *szName);

	CUniformBufferVec1* GetUniformVec1(const char *szName);
	CUniformBufferVec2* GetUniformVec2(const char *szName);
	CUniformBufferVec3* GetUniformVec3(const char *szName);
	CUniformBufferVec4* GetUniformVec4(const char *szName);
	CUniformBufferMat4* GetUniformMat4(const char *szName);

	GLuint GetTextureUnits(void) const;


private:
	bool m_bEnableCullFace;
	bool m_bEnableDepthTest;
	bool m_bEnableDepthWrite;
	bool m_bEnableBlend;
	bool m_bEnablePolygonOffset;
	GLenum m_frontFace;
	GLenum m_depthFunc;
	GLenum m_srcBlendFactor;
	GLenum m_dstBlendFactor;
	GLfloat m_polygonOffsetFactor;
	GLfloat m_polygonOffsetUnits;

private:
	std::map<GLuint, CTexture2D*> m_pTexture2ds;
	std::map<GLuint, CTexture2DArray*> m_pTexture2dArrays;
	std::map<GLuint, CTextureCubeMap*> m_pTextureCubeMaps;

	std::map<GLuint, CUniformBufferVec1*> m_pUniformVec1s;
	std::map<GLuint, CUniformBufferVec2*> m_pUniformVec2s;
	std::map<GLuint, CUniformBufferVec3*> m_pUniformVec3s;
	std::map<GLuint, CUniformBufferVec4*> m_pUniformVec4s;
	std::map<GLuint, CUniformBufferMat4*> m_pUniformMat4s;

private:
	CProgram *m_pProgram;
};
