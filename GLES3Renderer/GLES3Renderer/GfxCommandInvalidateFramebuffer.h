#pragma once
#include <vector>
#include "glew.h"
#include "GfxCommandBuffer.h"


class CGfxGfxCommandInvalidateFramebuffer : public CGfxCommandBase
{
public:
	CGfxGfxCommandInvalidateFramebuffer(CGfxFrameBuffer *pFrameBuffer)
		: m_pFrameBuffer(pFrameBuffer)
	{

	}
	virtual ~CGfxGfxCommandInvalidateFramebuffer(void)
	{

	}

public:
	virtual void Execute(void) const
	{

	}


private:
	CGfxFrameBuffer *m_pFrameBuffer;
};
