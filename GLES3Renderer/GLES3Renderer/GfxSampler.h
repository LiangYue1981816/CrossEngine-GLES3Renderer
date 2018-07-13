#pragma once
#include "gles3/gl3.h"


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
