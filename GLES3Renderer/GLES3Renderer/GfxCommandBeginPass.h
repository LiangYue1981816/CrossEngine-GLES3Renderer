#pragma once
#include "glew.h"
#include "GfxCommandBuffer.h"


class CGfxCommandBeginPass : public CGfxCommandBase
{
public:
	CGfxCommandBeginPass(CGfxFrameBuffer *pFrameBuffer)
		: m_pFrameBuffer(pFrameBuffer)
	{

	}
	virtual ~CGfxCommandBeginPass(void)
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
