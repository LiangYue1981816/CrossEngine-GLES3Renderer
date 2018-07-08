#pragma once
#include <vector>
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

	}


private:
	CGfxFrameBuffer *m_pFrameBuffer;
};
