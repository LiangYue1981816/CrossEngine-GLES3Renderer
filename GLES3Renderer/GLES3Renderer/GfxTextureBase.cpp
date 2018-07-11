#include "stdio.h"
#include "stdlib.h"
#include "GfxTextureBase.h"


CGfxTextureBase::CGfxTextureBase(void)
	: m_texture(0)
	, m_refCount(0)

	, m_format(GL_INVALID_ENUM)
	, m_internalFormat(GL_INVALID_ENUM)

	, m_width(0)
	, m_height(0)

	, m_mipLevels(0)
	, m_arrayLayers(0)
{
	glGenTextures(1, &m_texture);
}

CGfxTextureBase::~CGfxTextureBase(void)
{
	glDeleteTextures(1, &m_texture);
}

GLuint CGfxTextureBase::GetTexture(void) const
{
	return m_texture;
}

GLenum CGfxTextureBase::GetFormat(void) const
{
	return m_format;
}

GLenum CGfxTextureBase::GetInternalFormat(void) const
{
	return m_internalFormat;
}

GLuint CGfxTextureBase::GetWidth(void) const
{
	return m_width;
}

GLuint CGfxTextureBase::GetHeight(void) const
{
	return m_height;
}
