#pragma once
#include <map>
#include <vector>
#include "gles3/gl3.h"


class CGfxFrameBuffer
{
	friend class CGfxRenderer;
	friend class CGfxFrameBufferManager;


private:
	CGfxFrameBuffer(GLuint width, GLuint height);
	virtual ~CGfxFrameBuffer(void);


public:
	void Lock(void);
	void Unlock(bool bFree);

private:
	void Bind(void);
	void InvalidateFramebuffer(void);

public:
	bool SetRenderTexture(GLuint index, GLenum internalformat, GLenum format, GLenum type, bool invalidation);
	bool CheckFramebufferStatus(void);

public:
	GLuint GetWidth(void) const;
	GLuint GetHeight(void) const;
	GLuint GetTexture(GLuint index) const;


private:
	GLuint m_width;
	GLuint m_height;

private:
	GLuint m_fbo;
	GLuint m_rbo;
	std::map<GLuint, GLuint> m_textures;
	std::map<GLuint, bool> m_invalidations;

private:
	GLuint refCount;
};
