#include "stdio.h"
#include "stdlib.h"
#include "Texture2DArray.h"
#include "Renderer.h"


CTexture2DArray::CTexture2DArray(void)
	: m_texture(0)
	, m_sampler(0)

	, m_format(GL_RGBA)
	, m_internalFormat(GL_RGBA)

	, m_width(0)
	, m_height(0)
	, m_mipLevels(0)
	, m_arrayLayers(0)
{

}

CTexture2DArray::~CTexture2DArray(void)
{
	Destroy();
}

bool CTexture2DArray::Create(const char *szFileName, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	try {
		printf("\t\tCreate ... ");
		{
			int err = 0;

			char szFullPath[260];
			CRenderer::GetInstance()->GetTextureFullPath(szFileName, szFullPath);
			gli::texture2d_array texture = (gli::texture2d_array)gli::load(szFullPath);

			gli::gl GL(gli::gl::PROFILE_ES30);
			gli::gl::format format = GL.translate(texture.format(), texture.swizzles());

			if (texture.target() != gli::TARGET_2D_ARRAY) {
				throw err++;
			}

			if (CreateImage(format.External, format.Internal, texture.extent().x, texture.extent().y, texture.levels(), texture.layers()) == false) throw err++;
			if (CreateSampler(minFilter, magFilter, addressMode) == false) throw err++;
			if (TransferTexture2DArray(texture) == false) throw err++;
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

bool CTexture2DArray::Create(GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode)
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

bool CTexture2DArray::Create(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels, GLint arrayLayers, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	try {
		printf("\t\tCreate ... ");
		{
			int err = 0;

			if (CreateImage(format, internalFormat, width, height, mipLevels, arrayLayers) == false) throw err++;
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

bool CTexture2DArray::CreateImage(GLuint texture)
{
	m_texture = texture;
	return true;
}

bool CTexture2DArray::CreateImage(GLenum format, GLenum internalFormat, GLsizei width, GLsizei height, GLint mipLevels, GLint arrayLayers)
{
	m_format = format;
	m_internalFormat = internalFormat;

	m_width = width;
	m_height = height;
	m_mipLevels = mipLevels;
	m_arrayLayers = arrayLayers;

	glGenTextures(1, &m_texture);
	glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture);
	glTexStorage3D(GL_TEXTURE_2D_ARRAY, m_mipLevels, m_internalFormat, m_width, m_height, m_arrayLayers);
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	return true;
}

bool CTexture2DArray::CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	glGenSamplers(1, &m_sampler);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, minFilter);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, magFilter);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, addressMode);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, addressMode);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, addressMode);

	return true;
}

void CTexture2DArray::Destroy(void)
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

bool CTexture2DArray::TransferTexture2D(const gli::texture2d &texture, GLint layer)
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

	glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture);
	{
		for (int level = 0; level < (int)texture.levels(); level++) {
			if (gli::is_compressed(texture.format())) {
				glCompressedTexSubImage3D(GL_TEXTURE_2D_ARRAY, level, 0, 0, 0, texture.extent(level).x, texture.extent(level).y, layer, format.Internal, texture.size(level), texture.data(layer, 0, level));
			}
			else {
				glTexSubImage3D(GL_TEXTURE_2D_ARRAY, level, 0, 0, 0, texture.extent(level).x, texture.extent(level).y, layer, format.External, format.Type, texture.data(layer, 0, level));
			}
		}
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	return true;
}

bool CTexture2DArray::TransferTexture2DArray(const gli::texture2d_array &texture)
{
	gli::gl GL(gli::gl::PROFILE_ES30);
	gli::gl::format format = GL.translate(texture.format(), texture.swizzles());

	if (texture.target() != gli::TARGET_2D_ARRAY) {
		return false;
	}

	if (m_format != format.External) {
		return false;
	}

	if (m_internalFormat != format.Internal) {
		return false;
	}

	glBindTexture(GL_TEXTURE_2D_ARRAY, m_texture);
	{
		for (int layer = 0; layer < (int)texture.layers(); layer++) {
			for (int level = 0; level < (int)texture.levels(); level++) {
				if (gli::is_compressed(texture.format())) {
					glCompressedTexSubImage3D(GL_TEXTURE_2D_ARRAY, level, 0, 0, 0, texture.extent(level).x, texture.extent(level).y, layer, format.Internal, texture.size(level), texture.data(layer, 0, level));
				}
				else {
					glTexSubImage3D(GL_TEXTURE_2D_ARRAY, level, 0, 0, 0, texture.extent(level).x, texture.extent(level).y, layer, format.External, format.Type, texture.data(layer, 0, level));
				}
			}
		}
	}
	glBindTexture(GL_TEXTURE_2D_ARRAY, 0);

	return true;
}

GLuint CTexture2DArray::GetTexture(void) const
{
	return m_texture;
}

GLuint CTexture2DArray::GetSampler(void) const
{
	return m_sampler;
}
