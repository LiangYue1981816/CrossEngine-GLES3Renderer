#include "stdio.h"
#include "stdlib.h"
#include "GfxUtils.h"
#include "GfxMesh.h"
#include "GfxMeshManager.h"


CGfxMeshManager::CGfxMeshManager(void)
{

}

CGfxMeshManager::~CGfxMeshManager(void)
{
	for (const auto &itMesh : m_pMeshs) {
		delete itMesh.second;
	}

	m_pMeshs.clear();
}

CGfxMesh* CGfxMeshManager::LoadMesh(const char *szFileName)
{
	GLuint name = HashValue(szFileName);

	if (m_pMeshs[name] == NULL) {
		m_pMeshs[name] = new CGfxMesh(name);
		m_pMeshs[name]->Load(szFileName);
	}

	return m_pMeshs[name];
}

void CGfxMeshManager::FreeMesh(CGfxMesh *pMesh)
{
	if (pMesh && pMesh->refCount == 0) {
		m_pMeshs.erase(pMesh->GetName());
		delete pMesh;
	}
}
