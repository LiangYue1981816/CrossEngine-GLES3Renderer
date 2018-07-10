#pragma once
#include "glew.h"
#include "GfxCommandBuffer.h"


class CGfxCommandBindFrameBuffer : public CGfxCommandBase
{
public:
	CGfxCommandBindFrameBuffer(CGfxFrameBuffer *pFrameBuffer)
		: m_pFrameBuffer(pFrameBuffer)
	{

	}
	virtual ~CGfxCommandBindFrameBuffer(void)
	{

	}

public:
	virtual void Execute(void) const
	{
		if (m_pFrameBuffer) {
			m_pFrameBuffer->Bind();
		}
	}


private:
	CGfxFrameBuffer *m_pFrameBuffer;
};
