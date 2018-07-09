#pragma once
#include <vector>
#include "glew.h"
#include "GfxCommandBuffer.h"


class CGfxCommandClear : public CGfxCommandBase
{
public:
	CGfxCommandClear(float red, float green, float blue, float alpha, float depth)
		: m_red(red)
		, m_green(green)
		, m_blue(blue)
		, m_alpha(alpha)
		, m_depth(depth)
	{

	}
	virtual ~CGfxCommandClear(void)
	{

	}

public:
	virtual void Execute(void) const
	{
		glClearColor(m_red, m_green, m_blue, m_alpha);
		glClearDepthf(m_depth);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}


private:
	float m_red;
	float m_green;
	float m_blue;
	float m_alpha;
	float m_depth;
};
