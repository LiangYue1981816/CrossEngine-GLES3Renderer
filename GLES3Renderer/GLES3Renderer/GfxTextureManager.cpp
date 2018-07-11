#include "stdio.h"
#include "stdlib.h"
#include "GfxTextureManager.h"


CGfxTextureBase::CGfxTextureBase(void)
	: m_texture(0)
	, m_sampler(0)
	, m_external(GL_FALSE)

	, m_format(GL_RGBA)
	, m_internalFormat(GL_RGBA)

	, m_width(0)
	, m_height(0)

	, m_refCount(0)
{

}

CGfxTextureBase::~CGfxTextureBase(void)
{

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

GLuint CGfxTextureBase::GetTexture(void) const
{
	return m_texture;
}

GLuint CGfxTextureBase::GetSampler(void) const
{
	return m_sampler;
}
