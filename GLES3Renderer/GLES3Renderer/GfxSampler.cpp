#include "stdio.h"
#include "stdlib.h"
#include "GfxSampler.h"


CGfxSampler::CGfxSampler(void)
	: m_sampler(0)
{
	glGenSamplers(1, &m_sampler);
}

CGfxSampler::~CGfxSampler(void)
{
	glDeleteSamplers(1, &m_sampler);
}

GLvoid CGfxSampler::SetSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	glSamplerParameteri(m_sampler, GL_TEXTURE_MIN_FILTER, minFilter);
	glSamplerParameteri(m_sampler, GL_TEXTURE_MAG_FILTER, magFilter);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_S, addressMode);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_T, addressMode);
	glSamplerParameteri(m_sampler, GL_TEXTURE_WRAP_R, addressMode);
}

GLuint CGfxSampler::GetSampler(void) const
{
	return m_sampler;
}
