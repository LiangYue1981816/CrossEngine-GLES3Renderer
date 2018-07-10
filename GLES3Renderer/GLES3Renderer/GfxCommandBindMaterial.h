#pragma once
#include "glew.h"
#include "GfxRenderer.h"
#include "GfxCommandBuffer.h"


class CGfxCommandBindMaterial : public CGfxCommandBase
{
public:
	CGfxCommandBindMaterial(CGfxMaterial *pMaterial)
		: m_pMaterial(pMaterial)
	{

	}
	virtual ~CGfxCommandBindMaterial(void)
	{

	}

public:
	virtual void Execute(void) const
	{
		if (m_pMaterial) {
			CGfxRenderer::GetInstance()->BindMaterial(m_pMaterial);
		}
	}


private:
	CGfxMaterial *m_pMaterial;
};
