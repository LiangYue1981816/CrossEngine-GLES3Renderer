#pragma once
#include <map>
#include <vector>
#include "gles/gl3.h"


class CGfxFrameBuffer
{
public:
	CGfxFrameBuffer(GLuint width, GLuint height);
	virtual ~CGfxFrameBuffer(void);


public:
	void Bind(void);

public:
	bool SetRenderTexture(GLuint index, GLenum internalformat, GLenum format, GLenum type, GLenum minFilter, GLenum magFilter, bool invalidation);
	bool CheckFramebufferStatus(void);

	bool Create(void);
	void Destroy(void);

	void InvalidateFramebuffer(void);

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
};
