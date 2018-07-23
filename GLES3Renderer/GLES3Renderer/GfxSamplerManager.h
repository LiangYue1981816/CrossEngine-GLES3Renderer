#pragma once
#include <map>
#include "gles3/gl3.h"


class CGfxSampler;
class CGfxSamplerManager
{
	friend class CGfxRenderer;


private:
	CGfxSamplerManager(void);
	virtual ~CGfxSamplerManager(void);


public:
	CGfxSampler* CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode);


private:
	std::map<GLuint64, CGfxSampler*> m_pSamplers;
};
