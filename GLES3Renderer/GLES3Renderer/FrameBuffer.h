#pragma once
#include <map>
#include <vector>
#include "glew.h"


class CFrameBuffer
{
public:
	CFrameBuffer(GLuint width, GLuint height);
	virtual ~CFrameBuffer(void);


public:
	bool SetRenderTexture(GLuint index, GLenum internalformat, GLenum format, GLenum type, GLenum minFilter, GLenum magFilter, bool invalidation);
	bool CheckFramebufferStatus(void);

	bool Create(void);
	void Destroy(void);

public:
	GLuint GetFBO(void) const;
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
