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

bool CGfxMaterialManager::Load(const char *szFileName, GLuint materialid)
{
	try {
		int err = 0;

		if (m_pMaterials[materialid] == NULL) {
			m_pMaterials[materialid] = new CGfxMaterial;
		}

		if (m_pMaterials[materialid] == NULL) {
			throw err++;
		}

		if (m_pMaterials[materialid]->Create(szFileName) == false) {
			throw err++;
		}

		return true;
	}
	catch (int) {
		delete m_pMaterials[materialid];
		m_pMaterials.erase(materialid);

		return false;
	}
}

CGfxMaterial* CGfxMaterialManager::GetMaterial(GLuint materialid) const
{
	const auto &itMaterial = m_pMaterials.find(materialid);
	return itMaterial != m_pMaterials.end() ? itMaterial->second : NULL;
}
