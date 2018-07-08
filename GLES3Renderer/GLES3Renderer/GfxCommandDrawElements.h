#pragma once
#include <vector>
#include "glew.h"
#include "GfxCommandBuffer.h"


class CGfxCommandDrawElements : public CGfxCommandBase
{
public:
	CGfxCommandDrawElements(GLenum mode, GLsizei count, GLenum type, void *indices)
		: m_mode(mode)
		, m_count(count)
		, m_type(type)
		, m_indices(indices)
	{

	}
	virtual ~CGfxCommandDrawElements(void)
	{

	}

public:
	virtual void Execute(void) const
	{

	}


private:
	GLenum m_mode;
	GLsizei m_count;
	GLenum m_type;
	void *m_indices;
};
