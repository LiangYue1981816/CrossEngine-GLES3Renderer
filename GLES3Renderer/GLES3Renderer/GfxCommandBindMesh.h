#pragma once
#include <vector>
#include "glew.h"
#include "GfxCommandBuffer.h"


class CGfxCommandBindMesh : public CGfxCommandBase
{
public:
	CGfxCommandBindMesh(CGfxMesh *pMesh)
		: m_pMesh(pMesh)
	{

	}
	virtual ~CGfxCommandBindMesh(void)
	{

	}

public:
	virtual void Execute(void) const
	{

	}


private:
	CGfxMesh *m_pMesh;
};
