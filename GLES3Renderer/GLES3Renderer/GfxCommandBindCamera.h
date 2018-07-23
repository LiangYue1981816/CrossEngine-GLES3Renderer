#pragma once
#include "gles3/gl3.h"
#include "GfxRenderer.h"
#include "GfxCommandBuffer.h"


class CGfxCommandBindCamera : public CGfxCommandBase
{
public:
	CGfxCommandBindCamera(CGfxCamera *pCamera)
		: m_pCamera(pCamera)
	{

	}
	virtual ~CGfxCommandBindCamera(void)
	{

	}

public:
	virtual void Execute(void) const
	{
		CGfxRenderer::GetInstance()->BindCamera(m_pCamera);
	}


private:
	CGfxCamera *m_pCamera;
};
