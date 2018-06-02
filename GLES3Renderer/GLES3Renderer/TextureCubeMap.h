#pragma once
#include "glew.h"
#include "gli/gli.hpp"


class CTextureCubeMap
{
public:
	CTextureCubeMap(void);
	virtual ~CTextureCubeMap(void);


public:
	bool Create(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum addressMode);
	bool Create(GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode);
	bool Create(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels, GLenum minFilter, GLenum magFilter, GLenum addressMode);
	void Destroy(void);

private:
	bool CreateImage(GLuint texture);
	bool CreateImage(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels);
	bool CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode);

public:
	bool TransferTextureCubeMap(const gli::texture_cube &texture);
	bool TransferTexture2D(const gli::texture2d &texture, GLint face);
	bool TransferTexture2D(GLint face, GLint level, GLenum format, GLsizei width, GLsizei height, GLenum type, const GLvoid *data);
	bool TransferTexture2DCompressed(GLint face, GLint level, GLenum format, GLsizei width, GLsizei height, GLsizei size, const GLvoid *data);

public:
	GLuint GetTexture(void) const;
	GLuint GetSampler(void) const;


private:
	GLenum m_format;
	GLenum m_internalFormat;

	GLuint m_width;
	GLuint m_height;
	GLuint m_mipLevels;

private:
	GLuint m_texture;
	GLuint m_sampler;
};
