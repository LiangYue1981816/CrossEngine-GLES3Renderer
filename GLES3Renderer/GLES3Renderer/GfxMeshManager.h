#pragma once
#include <map>
#include "gles3/gl3.h"


class CGfxMesh;
class CGfxMeshManager
{
private:
	CGfxMeshManager(void);
	virtual ~CGfxMeshManager(void);


public:
	CGfxMesh* LoadMesh(const char *szFileName);
	void FreeMesh(CGfxMesh *pMesh);

	CGfxMesh* GetMesh(GLuint mesh) const;


private:
	std::map<GLuint, CGfxMesh*> m_pMeshs;
};
