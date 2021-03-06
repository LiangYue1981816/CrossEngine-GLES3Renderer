#pragma once
#include "gles3/gl3.h"
#include "GfxCommandBuffer.h"


class CGfxCommandDrawInstance : public CGfxCommandBase
{
public:
	CGfxCommandDrawInstance(GLenum mode, GLsizei count, GLenum type, void *indices, GLsizei primcount)
		: m_mode(mode)
		, m_count(count)
		, m_type(type)
		, m_indices(indices)
		, m_primcount(primcount)
	{

	}
	virtual ~CGfxCommandDrawInstance(void)
	{

	}

public:
	virtual void Execute(void) const
	{
		glDrawElementsInstanced(m_mode, m_count, m_type, m_indices, m_primcount);
	}


private:
	GLenum m_mode;
	GLsizei m_count;
	GLenum m_type;
	void *m_indices;
	GLsizei m_primcount;
};
