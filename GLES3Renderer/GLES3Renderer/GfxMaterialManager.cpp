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

bool CGfxMaterialManager::LoadMaterial(const char *szFileName, GLuint material)
{
	try {
		if (m_pMaterials[material] == NULL) {
			m_pMaterials[material] = new CGfxMaterial;
		}

		if (m_pMaterials[material] == NULL) {
			throw 0;
		}

		if (m_pMaterials[material]->Load(szFileName) == false) {
			throw 1;
		}

		return true;
	}
	catch (int) {
		delete m_pMaterials[material];
		m_pMaterials.erase(material);

		return false;
	}
}

CGfxMaterial* CGfxMaterialManager::GetMaterial(GLuint material) const
{
	const auto &itMaterial = m_pMaterials.find(material);
	return itMaterial != m_pMaterials.end() ? itMaterial->second : NULL;
}
