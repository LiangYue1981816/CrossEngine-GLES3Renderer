#pragma once
#include "glew.h"


class CGfxSampler
{
public:
	CGfxSampler(void);
	virtual ~CGfxSampler(void);


public:
	GLvoid SetSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode);
	GLuint GetSampler(void) const;


private:
	GLuint m_sampler;
};
