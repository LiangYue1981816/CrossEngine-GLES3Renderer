#pragma once
#include "gles3/gl3.h"


class CGfxTextureBase
{
	friend class CGfxRenderer;
	friend class CGfxMaterial;
	friend class CGfxTextureManager;


protected:
	CGfxTextureBase(GLuint name);
	virtual ~CGfxTextureBase(void);


public:
	GLuint GetName(void) const;

public:
	void Lock(void);
	void Unlock(bool bFree);

protected:
	virtual bool CreateExtern(GLuint texture);
	virtual bool Load(const char *szFileName) = 0;
	virtual void Free(void);

public:
	bool IsValid(void) const;

	GLenum GetFormat(void) const;
	GLenum GetInternalFormat(void) const;

	GLuint GetWidth(void) const;
	GLuint GetHeight(void) const;

protected:
	GLuint GetTexture(void) const;


protected:
	GLuint m_name;

protected:
	GLuint m_texture;
	GLboolean m_extern;

protected:
	GLenum m_format;
	GLenum m_internalFormat;

	GLuint m_width;
	GLuint m_height;

	GLuint m_mipLevels;
	GLuint m_arrayLayers;

private:
	GLuint refCount;
};
