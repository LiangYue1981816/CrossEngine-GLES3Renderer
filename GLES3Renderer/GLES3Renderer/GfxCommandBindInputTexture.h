#pragma once
#include "gles3/gl3.h"
#include "GfxCommandBuffer.h"


class CGfxCommandBindInputTexture : public CGfxCommandBase
{
public:
	CGfxCommandBindInputTexture(const char *szName, GLuint texture)
		: m_name(szName)
		, m_texture(texture)
	{

	}
	virtual ~CGfxCommandBindInputTexture(void)
	{

	}

public:
	virtual void Execute(void) const
	{
		CGfxRenderer::GetInstance()->BindInputTexture(m_name.c_str(), m_texture);
	}


private:
	std::string m_name;
	GLuint m_texture;
};
