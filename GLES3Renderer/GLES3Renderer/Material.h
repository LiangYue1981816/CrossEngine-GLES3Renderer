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
#include "UniformBufferCamera.h"
#include "UniformBufferAmbientLight.h"
#include "UniformBufferPointLight.h"
#include "UniformBufferDirectionLight.h"


class CMaterial
{
public:
	CMaterial(void);
	virtual ~CMaterial(void);


public:
	void Bind(void) const;

private:
	void BindPipeline(void) const;
	void BindTextures(void) const;
	void BindUniforms(void) const;

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
	bool LoadUniform1f(TiXmlNode *pMaterialNode);
	bool LoadUniform2f(TiXmlNode *pMaterialNode);
	bool LoadUniform3f(TiXmlNode *pMaterialNode);
	bool LoadUniform4f(TiXmlNode *pMaterialNode);

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

	CUniformBufferVec1* GetUniform1f(const char *szName);
	CUniformBufferVec2* GetUniform2f(const char *szName);
	CUniformBufferVec3* GetUniform3f(const char *szName);
	CUniformBufferVec4* GetUniform4f(const char *szName);

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

	std::map<GLuint, CUniformBufferVec1*> m_pUniform1fs;
	std::map<GLuint, CUniformBufferVec2*> m_pUniform2fs;
	std::map<GLuint, CUniformBufferVec3*> m_pUniform3fs;
	std::map<GLuint, CUniformBufferVec4*> m_pUniform4fs;

private:
	CProgram *m_pProgram;
};
