#pragma once
#include "gles3/gl3.h"
#include "GfxRenderer.h"
#include "GfxCommandBuffer.h"


class CGfxCommandBindMaterial : public CGfxCommandBase
{
public:
	CGfxCommandBindMaterial(CGfxMaterial *pMaterial, CGfxUniformCamera *pUniformCamera, CGfxUniformZBuffer *pUniformZBuffer, CGfxUniformProjection *pUniformProjection)
		: m_pMaterial(pMaterial)
		, m_pUniformCamera(pUniformCamera)
		, m_pUniformZBuffer(pUniformZBuffer)
		, m_pUniformProjection(pUniformProjection)
	{
		if (m_pMaterial) {
			m_pMaterial->Lock();
		}
	}
	virtual ~CGfxCommandBindMaterial(void)
	{
		if (m_pMaterial) {
			m_pMaterial->Unlock(true);
		}
	}

public:
	virtual void Execute(void) const
	{
		if (m_pMaterial) {
			CGfxRenderer::GetInstance()->BindMaterial(m_pMaterial, m_pUniformCamera, m_pUniformZBuffer, m_pUniformProjection);
		}
		else {
			glUseProgram(0);
		}
	}


private:
	CGfxMaterial *m_pMaterial;
	CGfxUniformCamera *m_pUniformCamera;
	CGfxUniformZBuffer *m_pUniformZBuffer;
	CGfxUniformProjection *m_pUniformProjection;
};
