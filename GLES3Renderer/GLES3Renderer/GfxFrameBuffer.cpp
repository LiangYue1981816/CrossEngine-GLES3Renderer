#include "stdio.h"
#include "stdlib.h"
#include "GfxRenderer.h"


static void glReadBuffers(GLsizei n, const GLenum *bufs)
{
	for (int index = 0; index < n; index++) {
		glReadBuffer(bufs[index]);
	}
}

CGfxFrameBuffer::CGfxFrameBuffer(GLuint width, GLuint height)
	: m_width(width)
	, m_height(height)

	, m_fbo(0)
	, m_rbo(0)

	, refCount(0)
{
	glGenRenderbuffers(1, &m_rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, m_width, m_height);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_rbo);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

CGfxFrameBuffer::~CGfxFrameBuffer(void)
{
	glDeleteFramebuffers(1, &m_fbo);
	glDeleteRenderbuffers(1, &m_rbo);

	for (const auto &itTexture : m_textures) {
		glDeleteTextures(1, &itTexture.second);
	}

	m_textures.clear();
	m_invalidations.clear();
}

void CGfxFrameBuffer::Lock(void)
{
	refCount++;
}

void CGfxFrameBuffer::Unlock(bool bFree)
{
	if (refCount > 0) {
		refCount--;
	}

	if (refCount == 0 && bFree) {
		CGfxRenderer::GetInstance()->DestroyFrameBuffer(this);
	}
}

void CGfxFrameBuffer::Bind(void)
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void CGfxFrameBuffer::InvalidateFramebuffer(void)
{
	std::vector<GLenum> discardBuffers;

	for (const auto &itInvalidation : m_invalidations) {
		if (itInvalidation.second) {
			discardBuffers.push_back(GL_COLOR_ATTACHMENT0 + itInvalidation.first);
		}
	}

	glInvalidateFramebuffer(GL_FRAMEBUFFER, discardBuffers.size(), discardBuffers.data());
}

bool CGfxFrameBuffer::SetRenderTexture(GLuint index, GLenum internalformat, GLenum format, GLenum type, bool invalidation)
{
	if (m_textures.find(index) != m_textures.end()) {
		return false;
	}

	GLuint texture;
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, internalformat, m_width, m_height, 0, format, type, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_textures[index] = texture;
	m_invalidations[index] = invalidation;

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	{
		std::vector<GLenum> drawBuffers;

		for (const auto &itTexture : m_textures) {
			drawBuffers.push_back(GL_COLOR_ATTACHMENT0 + itTexture.first);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + itTexture.first, GL_TEXTURE_2D, itTexture.second, 0);
		}

		glReadBuffers(drawBuffers.size(), drawBuffers.data());
		glDrawBuffers(drawBuffers.size(), drawBuffers.data());
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return CheckFramebufferStatus();
}

bool CGfxFrameBuffer::CheckFramebufferStatus(void)
{
	GLenum status;

	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
	status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	return status == GL_FRAMEBUFFER_COMPLETE;
}

GLuint CGfxFrameBuffer::GetWidth(void) const
{
	return m_width;
}

GLuint CGfxFrameBuffer::GetHeight(void) const
{
	return m_height;
}

GLuint CGfxFrameBuffer::GetTexture(GLuint index) const
{
	const auto &itTexture = m_textures.find(index);
	return itTexture != m_textures.end() ? itTexture->second : 0;
}
