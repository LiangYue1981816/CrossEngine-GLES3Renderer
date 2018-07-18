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
	bool LoadMesh(const char *szFileName, GLuint mesh);
	void DestroyMesh(CGfxMesh *pMesh);

	CGfxMesh* GetMesh(GLuint mesh);


private:
	std::map<GLuint, CGfxMesh*> m_pMeshs;
};
