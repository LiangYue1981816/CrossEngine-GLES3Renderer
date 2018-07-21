#pragma once
#include <map>
#include "gles3/gl3.h"


class CGfxMaterial;
class CGfxMaterialManager
{
	friend class CGfxRenderer;


private:
	CGfxMaterialManager(void);
	virtual ~CGfxMaterialManager(void);


public:
	CGfxMaterial* LoadMaterial(const char *szFileName);
	void FreeMaterial(CGfxMaterial *pMaterial);

	CGfxMaterial* GetMaterial(GLuint name) const;


private:
	std::map<GLuint, CGfxMaterial*> m_pMaterials;
};
