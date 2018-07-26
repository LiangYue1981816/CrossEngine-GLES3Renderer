#pragma once
#include <map>
#include "gles3/gl3.h"


class CGfxMesh;
class CGfxMeshManager
{
	friend class CGfxRenderer;


private:
	CGfxMeshManager(void);
	virtual ~CGfxMeshManager(void);


private:
	CGfxMesh* LoadMesh(const char *szFileName);
	void FreeMesh(CGfxMesh *pMesh);


private:
	std::map<GLuint, CGfxMesh*> m_pMeshs;
};
