#pragma once
#include "gles3/gl3.h"
#include "GfxCommandBuffer.h"


class CGfxCommandEndPass : public CGfxCommandBase
{
public:
	CGfxCommandEndPass(CGfxFrameBuffer *pFrameBuffer)
		: m_pFrameBuffer(pFrameBuffer)
	{
		if (m_pFrameBuffer) {
			m_pFrameBuffer->Lock();
		}
	}
	virtual ~CGfxCommandEndPass(void)
	{
		if (m_pFrameBuffer) {
			m_pFrameBuffer->Unlock(true);
		}
	}

public:
	virtual void Execute(void) const
	{
		if (m_pFrameBuffer) {
			CGfxRenderer::GetInstance()->InvalidateFramebuffer(m_pFrameBuffer);
		}
	}


private:
	CGfxFrameBuffer *m_pFrameBuffer;
};
