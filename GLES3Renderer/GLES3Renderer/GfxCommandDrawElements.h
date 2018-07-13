#pragma once
#include "gles/gl3.h"
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
		glDrawElements(m_mode, m_count, m_type, m_indices);
	}


private:
	GLenum m_mode;
	GLsizei m_count;
	GLenum m_type;
	void *m_indices;
};
