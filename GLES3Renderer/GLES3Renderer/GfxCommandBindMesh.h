#pragma once
#include "gles3/gl3.h"
#include "GfxRenderer.h"
#include "GfxCommandBuffer.h"


class CGfxCommandBindMesh : public CGfxCommandBase
{
public:
	CGfxCommandBindMesh(CGfxMesh *pMesh)
		: m_pMesh(pMesh)
	{
		m_pMesh->Lock();
	}
	virtual ~CGfxCommandBindMesh(void)
	{
		m_pMesh->Unlock();
	}

public:
	virtual void Execute(void) const
	{
		if (m_pMesh) {
			CGfxRenderer::GetInstance()->BindMesh(m_pMesh);
		}
	}


private:
	CGfxMesh *m_pMesh;
};
