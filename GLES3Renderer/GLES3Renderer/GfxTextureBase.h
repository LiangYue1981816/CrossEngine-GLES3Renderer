#pragma once
#include <map>
#include "glew.h"


class CGfxTextureBase
{
public:
	CGfxTextureBase(void);
	virtual ~CGfxTextureBase(void);


public:
	virtual bool Create(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum addressMode) = 0;
	virtual bool Create(GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode) = 0;

public:
	GLenum GetFormat(void) const;
	GLenum GetInternalFormat(void) const;

	GLuint GetWidth(void) const;
	GLuint GetHeight(void) const;

	GLuint GetTexture(void) const;
	GLuint GetSampler(void) const;


protected:
	GLenum m_format;
	GLenum m_internalFormat;

	GLuint m_width;
	GLuint m_height;

protected:
	GLuint m_texture;
	GLuint m_sampler;
	GLboolean m_external;

private:
	GLuint m_refCount;
};
