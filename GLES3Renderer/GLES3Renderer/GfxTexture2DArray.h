#pragma once
#include "gles3/gl3.h"
#include "gli/gli.hpp"
#include "GfxTextureBase.h"


class CGfxTexture2DArray : public CGfxTextureBase
{
	friend class CGfxMaterial;
	friend class CGfxTextureManager;


private:
	CGfxTexture2DArray(GLuint name);
	virtual ~CGfxTexture2DArray(void);


private:
	bool Load(const char *szFileName);
	bool Create(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLuint mipLevels, GLuint arrayLayers);

private:
	bool TransferTexture2DArray(const gli::texture2d_array &texture);
	bool TransferTexture2D(GLuint layer, const gli::texture2d &texture);
	bool TransferTexture2D(GLuint layer, GLuint level, GLenum format, GLsizei width, GLsizei height, GLenum type, const GLvoid *data);
	bool TransferTexture2DCompressed(GLuint layer, GLuint level, GLenum format, GLsizei width, GLsizei height, GLsizei size, const GLvoid *data);
};
