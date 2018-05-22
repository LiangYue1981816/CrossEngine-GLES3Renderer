#include "stdio.h"
#include "stdlib.h"
#include "Texture2D.h"
#include "Renderer.h"


CTexture2D::CTexture2D(void)
	: m_texture(0)
	, m_sampler(0)

	, m_format(GL_RGBA)
	, m_internalFormat(GL_RGBA)

	, m_width(0)
	, m_height(0)
	, m_mipLevels(0)
{

}

CTexture2D::~CTexture2D(void)
{
	Destroy();
}

bool CTexture2D::Create(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	try {
		printf("\t\tCreate ... ");
		{
			int err = 0;

			char szFullPath[260];
			CRenderer::GetInstance()->GetTextureFullPath(szFileName, szFullPath);
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
		Destroy();

		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CTexture2D::Create(GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode)
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
		Destroy();

		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CTexture2D::Create(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels, GLenum minFilter, GLenum magFilter, GLenum addressMode)
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
		Destroy();
		
		printf("Fail(%d)\n", err);
		return false;
	}
}

bool CTexture2D::CreateImage(GLuint texture)
{
	m_texture = texture;
	return true;
}

bool CTexture2D::CreateImage(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels)
{
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

bool CTexture2D::CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	glGenSamplers(1, &m_sampler);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, minFilter);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, magFilter);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, addressMode);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, addressMode);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, addressMode);

	return true;
}

void CTexture2D::Destroy(void)
{
	if (m_texture) {
		glDeleteTextures(1, &m_texture);
	}

	if (m_sampler) {
		glDeleteSamplers(1, &m_sampler);
	}

	m_texture = 0;
	m_sampler = 0;
}

bool CTexture2D::TransferTexture2D(const gli::texture2d &texture)
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

GLuint CTexture2D::GetTexture(void) const
{
	return m_texture;
}

GLuint CTexture2D::GetSampler(void) const
{
	return m_sampler;
}