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
	CGfxCommandBindMesh(CGfxMesh *pMesh, std::vector<glm::mat4> &mtxTransforms)
		: m_pMesh(pMesh)
		, m_mtxTransforms(mtxTransforms)
	{
		m_pMesh->Lock();
	}
	virtual ~CGfxCommandBindMesh(void)
	{
		m_pMesh->Unlock(true);
	}

public:
	virtual void Execute(void) const
	{
		if (m_mtxTransforms.size()) {
			m_pMesh->ClearInstance();

			for (GLuint index = 0; index < m_mtxTransforms.size(); index++) {
				m_pMesh->AddInstance(m_mtxTransforms[index]);
			}
		}

		if (m_pMesh) {
			CGfxRenderer::GetInstance()->BindMesh(m_pMesh);
		}
	}


private:
	CGfxMesh *m_pMesh;
	std::vector<glm::mat4> m_mtxTransforms;
};
