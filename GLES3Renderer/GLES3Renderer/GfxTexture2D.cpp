#include "stdio.h"
#include "stdlib.h"
#include "GfxRenderer.h"


CGfxTexture2D::CGfxTexture2D(GLuint name)
	: CGfxTextureBase(name)
{

}

CGfxTexture2D::~CGfxTexture2D(void)
{

}

bool CGfxTexture2D::Load(const char *szFileName)
{
	try {
		Free();

		char szFullPath[260];
		CGfxRenderer::GetInstance()->GetTextureFullPath(szFileName, szFullPath);

		gli::gl GL(gli::gl::PROFILE_ES30);
		gli::texture2d texture = (gli::texture2d)gli::load(szFullPath);
		gli::gl::format format = GL.translate(texture.format(), texture.swizzles());

		if (texture.target() != gli::TARGET_2D) throw 0;
		if (Create(format.External, format.Internal, texture.extent().x, texture.extent().y, texture.levels()) == false) throw 1;
		if (TransferTexture2D(texture) == false) throw 2;

		return true;
	}
	catch (int) {
		Free();
		return false;
	}
}

bool CGfxTexture2D::Create(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLuint mipLevels)
{
	Free();

	m_format = format;
	m_internalFormat = internalFormat;

	m_width = width;
	m_height = height;

	m_mipLevels = mipLevels;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexStorage2D(GL_TEXTURE_2D, m_mipLevels, m_internalFormat, m_width, m_height);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

bool CGfxTexture2D::TransferTexture2D(const gli::texture2d &texture)
{
	if (m_texture == 0) {
		return false;
	}

	if (m_extern == GL_TRUE) {
		return false;
	}

	gli::gl GL(gli::gl::PROFILE_ES30);
	gli::gl::format format = GL.translate(texture.format(), texture.swizzles());

	if (texture.target() != gli::TARGET_2D) {
		return false;
	}

	if (m_format != format.External) {
		return false;
	}

	if (m_internalFormat != format.Internal) {
		return false;
	}

	if (m_mipLevels != texture.levels()) {
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, m_texture);
	{
		for (int level = 0; level < (int)texture.levels(); level++) {
			if (gli::is_compressed(texture.format())) {
				glCompressedTexSubImage2D(GL_TEXTURE_2D, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.Internal, texture.size(level), texture.data(0, 0, level));
			}
			else {
				glTexSubImage2D(GL_TEXTURE_2D, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.External, format.Type, texture.data(0, 0, level));
			}
		}
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

bool CGfxTexture2D::TransferTexture2D(GLuint level, GLenum format, GLsizei width, GLsizei height, GLenum type, const GLvoid *data)
{
	if (m_texture == 0) {
		return false;
	}

	if (m_extern == GL_TRUE) {
		return false;
	}

	if (m_mipLevels < level) {
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, m_texture);
	{
		glTexSubImage2D(GL_TEXTURE_2D, level, 0, 0, width, height, format, type, data);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

bool CGfxTexture2D::TransferTexture2DCompressed(GLuint level, GLenum format, GLsizei width, GLsizei height, GLsizei size, const GLvoid *data)
{
	if (m_texture == 0) {
		return false;
	}

	if (m_extern == GL_TRUE) {
		return false;
	}

	if (m_mipLevels < level) {
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, m_texture);
	{
		glCompressedTexSubImage2D(GL_TEXTURE_2D, level, 0, 0, width, height, format, size, data);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}
