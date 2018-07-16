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

bool CGfxMaterialManager::Load(const char *szFileName, GLuint material)
{
	try {
		int err = 0;

		if (m_pMaterials[material] == NULL) {
			m_pMaterials[material] = new CGfxMaterial;
		}

		if (m_pMaterials[material] == NULL) {
			throw err++;
		}

		if (m_pMaterials[material]->Create(szFileName) == false) {
			throw err++;
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
