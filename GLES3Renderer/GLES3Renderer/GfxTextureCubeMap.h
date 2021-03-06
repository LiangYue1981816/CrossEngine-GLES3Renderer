#pragma once
#include "gles3/gl3.h"
#include "gli/gli.hpp"
#include "GfxTextureBase.h"


class CGfxTextureCubeMap : public CGfxTextureBase
{
	friend class CGfxMaterial;
	friend class CGfxTextureManager;


private:
	CGfxTextureCubeMap(GLuint name);
	virtual ~CGfxTextureCubeMap(void);


private:
	bool Load(const char *szFileName);
	bool Create(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLuint mipLevels);

private:
	bool TransferTextureCubeMap(const gli::texture_cube &texture);
	bool TransferTexture2D(GLuint face, const gli::texture2d &texture);
	bool TransferTexture2D(GLuint face, GLuint level, GLenum format, GLsizei width, GLsizei height, GLenum type, const GLvoid *data);
	bool TransferTexture2DCompressed(GLuint face, GLuint level, GLenum format, GLsizei width, GLsizei height, GLsizei size, const GLvoid *data);
};
