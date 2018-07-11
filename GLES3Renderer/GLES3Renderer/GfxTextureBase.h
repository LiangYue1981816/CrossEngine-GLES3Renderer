#pragma once
#include <map>
#include "glew.h"


class CGfxTextureBase
{
public:
	CGfxTextureBase(void);
	virtual ~CGfxTextureBase(void);


public:
	virtual bool Create(const char *szFileName) = 0;

public:
	GLuint GetTexture(void) const;

	GLenum GetFormat(void) const;
	GLenum GetInternalFormat(void) const;

	GLuint GetWidth(void) const;
	GLuint GetHeight(void) const;


protected:
	GLuint m_texture;

protected:
	GLenum m_format;
	GLenum m_internalFormat;

	GLuint m_width;
	GLuint m_height;

private:
	GLuint m_refCount;
};
