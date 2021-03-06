#include "stdio.h"
#include "stdlib.h"
#include "GfxUtils.h"
#include "GfxMaterial.h"
#include "GfxMaterialManager.h"


CGfxMaterialManager::CGfxMaterialManager(void)
{

}

CGfxMaterialManager::~CGfxMaterialManager(void)
{
	for (const auto &itMaterial : m_pMaterials) {
		delete itMaterial.second;
	}

	m_pMaterials.clear();
}

CGfxMaterial* CGfxMaterialManager::LoadMaterial(const char *szFileName)
{
	GLuint name = HashValue(szFileName);

	if (m_pMaterials[name] == NULL) {
		m_pMaterials[name] = new CGfxMaterial(name);
		m_pMaterials[name]->Load(szFileName);
	}

	return m_pMaterials[name];
}

void CGfxMaterialManager::FreeMaterial(CGfxMaterial *pMaterial)
{
	if (pMaterial && pMaterial->refCount == 0) {
		m_pMaterials.erase(pMaterial->GetName());
		delete pMaterial;
	}
}
