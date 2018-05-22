#pragma once
#include "glew.h"
#include "gli/gli.hpp"


class CTexture2DArray
{
public:
	CTexture2DArray(void);
	virtual ~CTexture2DArray(void);


public:
	bool Create(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum addressMode);
	bool Create(GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode);
	bool Create(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels, GLint arrayLayers, GLenum minFilter, GLenum magFilter, GLenum addressMode);
	void Destroy(void);

private:
	bool CreateImage(GLuint texture);
	bool CreateImage(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels, GLint arrayLayers);
	bool CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode);

public:
	bool TransferTexture2D(const gli::texture2d &texture, GLint layer);
	bool TransferTexture2DArray(const gli::texture2d_array &texture);

public:
	GLuint GetTexture(void) const;
	GLuint GetSampler(void) const;


private:
	GLenum m_format;
	GLenum m_internalFormat;

	GLuint m_width;
	GLuint m_height;
	GLuint m_mipLevels;
	GLuint m_arrayLayers;

private:
	GLuint m_texture;
	GLuint m_sampler;
};