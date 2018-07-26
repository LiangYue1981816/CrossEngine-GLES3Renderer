#pragma once
#include "gles3/gl3.h"
#include "GfxRenderer.h"
#include "GfxCommandBuffer.h"


class CGfxCommandBeginPass : public CGfxCommandBase
{
public:
	CGfxCommandBeginPass(CGfxFrameBuffer *pFrameBuffer)
		: m_pFrameBuffer(pFrameBuffer)
	{
		if (m_pFrameBuffer) {
			m_pFrameBuffer->Lock();
		}
	}
	virtual ~CGfxCommandBeginPass(void)
	{
		if (m_pFrameBuffer) {
			m_pFrameBuffer->Unlock(true);
		}
	}

public:
	virtual void Execute(void) const
	{
		if (m_pFrameBuffer) {
			CGfxRenderer::GetInstance()->BindFrameBuffer(m_pFrameBuffer);
		}
		else {
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}


private:
	CGfxFrameBuffer *m_pFrameBuffer;
};
