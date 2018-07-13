#pragma once
#include "gles/gl3.h"
#include "GfxCommandBuffer.h"


class CGfxCommandEndPass : public CGfxCommandBase
{
public:
	CGfxCommandEndPass(CGfxFrameBuffer *pFrameBuffer)
		: m_pFrameBuffer(pFrameBuffer)
	{

	}
	virtual ~CGfxCommandEndPass(void)
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
