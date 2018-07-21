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
}

CGfxMaterial* CGfxMaterialManager::LoadMaterial(const char *szFileName)
{
	GLuint name = HashValue(szFileName);

	if (m_pMaterials[name] == NULL) {
		m_pMaterials[name] = new CGfxMaterial(name);
		m_pMaterials[name]->Load(szFileName);
	}

	m_pMaterials[name]->refCount++;

	return m_pMaterials[name];
}

void CGfxMaterialManager::FreeMaterial(CGfxMaterial *pMaterial)
{
	if (pMaterial->refCount > 0) {
		pMaterial->refCount--;
	}

	if (pMaterial->refCount == 0) {
		m_pMaterials.erase(pMaterial->GetName());
		delete pMaterial;
	}
}

CGfxMaterial* CGfxMaterialManager::GetMaterial(GLuint name) const
{
	const auto &itMaterial = m_pMaterials.find(name);
	return itMaterial != m_pMaterials.end() ? itMaterial->second : NULL;
}
