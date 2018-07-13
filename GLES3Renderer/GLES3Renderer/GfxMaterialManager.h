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
	bool Load(const char *szFileName, GLuint materialid);
	CGfxMaterial* GetMaterial(GLuint materialid) const;


private:
	std::map<GLuint, CGfxMaterial*> m_pMaterials;
};
