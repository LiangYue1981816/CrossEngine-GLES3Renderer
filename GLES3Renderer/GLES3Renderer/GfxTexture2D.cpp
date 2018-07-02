#include "stdio.h"
#include "stdlib.h"
#include "GfxRenderer.h"


CGfxTexture2D::CGfxTexture2D(void)
	: m_texture(0)
	, m_sampler(0)
	, m_external(GL_FALSE)

	, m_format(GL_RGBA)
	, m_internalFormat(GL_RGBA)

	, m_width(0)
	, m_height(0)
	, m_mipLevels(0)
{
	glGenTextures(1, &m_texture);
	glGenSamplers(1, &m_sampler);
}

CGfxTexture2D::~CGfxTexture2D(void)
{
	if (m_external == GL_FALSE) {
		glDeleteTextures(1, &m_texture);
	}

	glDeleteSamplers(1, &m_sampler);
}

bool CGfxTexture2D::Create(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	try {
		printf("\t\tCreate ... ");
		{
			int err = 0;

			char szFullPath[260];
			CGfxRenderer::GetInstance()->GetTextureFullPath(szFileName, szFullPath);
			gli::texture2d texture = (gli::texture2d)gli::load(szFullPath);

			gli::gl GL(gli::gl::PROFILE_ES30);
			gli::gl::format format = GL.translate(texture.format(), texture.swizzles());

			if (texture.target() != gli::TARGET_2D) {
				throw err++;
			}

			if (CreateImage(format.External, format.Internal, texture.extent().x, texture.extent().y, texture.levels()) == false) throw err++;
			if (CreateSampler(minFilter, magFilter, addressMode) == false) throw err++;
			if (TransferTexture2D(texture) == false) throw err++;
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxTexture2D::Create(GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	try {
		printf("\t\tCreate ... ");
		{
			int err = 0;

			if (CreateImage(texture) == false) throw err++;
			if (CreateSampler(minFilter, magFilter, addressMode) == false) throw err++;
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxTexture2D::Create(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	try {
		printf("\t\tCreate ... ");
		{
			int err = 0;

			if (CreateImage(format, internalFormat, width, height, mipLevels) == false) throw err++;
			if (CreateSampler(minFilter, magFilter, addressMode) == false) throw err++;
		}
		printf("OK\n");
		return true;
	}
	catch (int err) {
		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CGfxTexture2D::CreateImage(GLuint texture)
{
	m_texture = texture;
	m_external = GL_TRUE;
	return true;
}

bool CGfxTexture2D::CreateImage(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels)
{
	m_format = format;
	m_internalFormat = internalFormat;

	m_width = width;
	m_height = height;
	m_mipLevels = mipLevels;

	glBindTexture(GL_TEXTURE_2D, m_texture);
	glTexStorage2D(GL_TEXTURE_2D, m_mipLevels, m_internalFormat, m_width, m_height);
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

bool CGfxTexture2D::CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, minFilter);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, magFilter);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, addressMode);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, addressMode);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, addressMode);

	return true;
}

bool CGfxTexture2D::TransferTexture2D(const gli::texture2d &texture)
{
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

bool CGfxTexture2D::TransferTexture2D(GLint level, GLenum format, GLsizei width, GLsizei height, GLenum type, const GLvoid *data)
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
	{
		glTexSubImage2D(GL_TEXTURE_2D, level, 0, 0, width, height, format, type, data);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

bool CGfxTexture2D::TransferTexture2DCompressed(GLint level, GLenum format, GLsizei width, GLsizei height, GLsizei size, const GLvoid *data)
{
	glBindTexture(GL_TEXTURE_2D, m_texture);
	{
		glCompressedTexSubImage2D(GL_TEXTURE_2D, level, 0, 0, width, height, format, size, data);
	}
	glBindTexture(GL_TEXTURE_2D, 0);

	return true;
}

GLuint CGfxTexture2D::GetTexture(void) const
{
	return m_texture;
}

GLuint CGfxTexture2D::GetSampler(void) const
{
	return m_sampler;
}
