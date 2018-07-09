#pragma once
#include <vector>
#include "glew.h"
#include "GfxCommandBuffer.h"


class CGfxCommandInvalidateFrameBuffer : public CGfxCommandBase
{
public:
	CGfxCommandInvalidateFrameBuffer(CGfxFrameBuffer *pFrameBuffer)
		: m_pFrameBuffer(pFrameBuffer)
	{

	}
	virtual ~CGfxCommandInvalidateFrameBuffer(void)
	{

	}

public:
	virtual void Execute(void) const
	{
		if (m_pFrameBuffer) {
			m_pFrameBuffer->InvalidateFramebuffer();
		}
	}


private:
	CGfxFrameBuffer *m_pFrameBuffer;
};
