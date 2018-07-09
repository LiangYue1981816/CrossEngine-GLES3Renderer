#pragma once
#include <vector>
#include "glew.h"
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
			m_pMaterial->Bind();
		}
	}


private:
	CGfxMaterial *m_pMaterial;
};
