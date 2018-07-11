#pragma once
#include "glew.h"


class CGfxSampler
{
public:
	CGfxSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode);
	virtual ~CGfxSampler(void);


public:
	GLuint GetSampler(void) const;


private:
	GLuint m_sampler;
};
