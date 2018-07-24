#include "stdio.h"
#include "stdlib.h"
#include "GfxTextureBase.h"


CGfxTextureBase::CGfxTextureBase(GLuint name)
	: m_name(name)

	, m_texture(0)
	, m_extern(GL_FALSE)

	, m_format(GL_INVALID_ENUM)
	, m_internalFormat(GL_INVALID_ENUM)

	, m_width(0)
	, m_height(0)

	, m_mipLevels(0)
	, m_arrayLayers(0)

	, refCount(0)
{

}

CGfxTextureBase::~CGfxTextureBase(void)
{
	Free();
}

void CGfxTextureBase::Lock(void)
{
	refCount++;
}

void CGfxTextureBase::Unlock(void)
{
	if (refCount > 0) {
		refCount--;
	}
}

GLuint CGfxTextureBase::GetName(void) const
{
	return m_name;
}

bool CGfxTextureBase::CreateExtern(GLuint texture)
{
	Free();

	m_texture = texture;
	m_extern = GL_TRUE;

	return true;
}

void CGfxTextureBase::Free(void)
{
	if (m_extern == GL_FALSE) {
		if (m_texture) {
			glDeleteTextures(1, &m_texture);
		}
	}

	m_texture = 0;
	m_extern = GL_FALSE;

	m_format = GL_INVALID_ENUM;
	m_internalFormat = GL_INVALID_ENUM;

	m_width = 0;
	m_height = 0;

	m_mipLevels = 0;
	m_arrayLayers = 0;
}

bool CGfxTextureBase::IsValid(void) const
{
	return m_texture != 0;
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
