#include "stdio.h"
#include "stdlib.h"
#include "TextureCubeMap.h"
#include "Renderer.h"


CTextureCubeMap::CTextureCubeMap(void)
	: m_texture(0)
	, m_sampler(0)

	, m_format(GL_RGBA)
	, m_internalFormat(GL_RGBA)

	, m_width(0)
	, m_height(0)
	, m_mipLevels(0)
{

}

CTextureCubeMap::~CTextureCubeMap(void)
{
	Destroy();
}

bool CTextureCubeMap::Create(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	try {
		Destroy();

		printf("\t\tCreate ... ");
		{
			int err = 0;

			char szFullPath[260];
			CRenderer::GetInstance()->GetTextureFullPath(szFileName, szFullPath);
			gli::texture_cube texture = (gli::texture_cube)gli::load(szFullPath);

			gli::gl GL(gli::gl::PROFILE_ES30);
			gli::gl::format format = GL.translate(texture.format(), texture.swizzles());

			if (texture.target() != gli::TARGET_CUBE) {
				throw err++;
			}

			if (CreateImage(format.External, format.Internal, texture.extent().x, texture.extent().y, texture.levels()) == false) throw err++;
			if (CreateSampler(minFilter, magFilter, addressMode) == false) throw err++;
			if (TransferTextureCubeMap(texture) == false) throw err++;
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

bool CTextureCubeMap::Create(GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	try {
		Destroy();

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

bool CTextureCubeMap::Create(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	try {
		Destroy();

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

bool CTextureCubeMap::CreateImage(GLuint texture)
{
	m_texture = texture;
	return true;
}

bool CTextureCubeMap::CreateImage(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels)
{
	m_format = format;
	m_internalFormat = internalFormat;

	m_width = width;
	m_height = height;
	m_mipLevels = mipLevels;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	glTexStorage2D(GL_TEXTURE_CUBE_MAP, m_mipLevels, m_internalFormat, m_width, m_height);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}

bool CTextureCubeMap::CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	glGenSamplers(1, &m_sampler);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, minFilter);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, magFilter);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, addressMode);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, addressMode);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, addressMode);

	return true;
}

void CTextureCubeMap::Destroy(void)
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

bool CTextureCubeMap::TransferTexture2D(const gli::texture2d &texture, GLint face)
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

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	{
		for (int level = 0; level < (int)texture.levels(); level++) {
			if (gli::is_compressed(texture.format())) {
				glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.Internal, texture.size(level), texture.data(0, 0, level));
			}
			else {
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + face, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.External, format.Type, texture.data(0, 0, level));
			}
		}
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}

bool CTextureCubeMap::TransferTextureCubeMap(const gli::texture_cube &texture)
{
	gli::gl GL(gli::gl::PROFILE_ES30);
	gli::gl::format format = GL.translate(texture.format(), texture.swizzles());

	if (texture.target() != gli::TARGET_CUBE) {
		return false;
	}

	if (m_format != format.External) {
		return false;
	}

	if (m_internalFormat != format.Internal) {
		return false;
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, m_texture);
	{
		for (int level = 0; level < (int)texture.levels(); level++) {
			if (gli::is_compressed(texture.format())) {
				glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.Internal, texture.size(level), texture.data(0, 0, level));
				glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.Internal, texture.size(level), texture.data(0, 1, level));
				glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.Internal, texture.size(level), texture.data(0, 2, level));
				glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.Internal, texture.size(level), texture.data(0, 3, level));
				glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.Internal, texture.size(level), texture.data(0, 4, level));
				glCompressedTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.Internal, texture.size(level), texture.data(0, 5, level));
			}
			else {
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.External, format.Type, texture.data(0, 0, level));
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_X, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.External, format.Type, texture.data(0, 1, level));
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Y, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.External, format.Type, texture.data(0, 2, level));
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Y, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.External, format.Type, texture.data(0, 3, level));
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_Z, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.External, format.Type, texture.data(0, 4, level));
				glTexSubImage2D(GL_TEXTURE_CUBE_MAP_NEGATIVE_Z, level, 0, 0, texture.extent(level).x, texture.extent(level).y, format.External, format.Type, texture.data(0, 5, level));
			}
		}
	}
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	return true;
}

GLuint CTextureCubeMap::GetTexture(void) const
{
	return m_texture;
}

GLuint CTextureCubeMap::GetSampler(void) const
{
	return m_sampler;
}
