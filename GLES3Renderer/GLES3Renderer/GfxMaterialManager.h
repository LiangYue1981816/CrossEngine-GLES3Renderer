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
	bool LoadMaterial(const char *szFileName, GLuint material);
	CGfxMaterial* GetMaterial(GLuint material) const;


private:
	std::map<GLuint, CGfxMaterial*> m_pMaterials;
};
