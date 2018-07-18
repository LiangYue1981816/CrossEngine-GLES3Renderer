#include "stdio.h"
#include "stdlib.h"
#include "GfxMesh.h"
#include "GfxMeshManager.h"


CGfxMeshManager::CGfxMeshManager(void)
{

}

CGfxMeshManager::~CGfxMeshManager(void)
{

}

bool CGfxMeshManager::LoadMesh(const char *szFileName, GLuint mesh)
{
	return true;
}

void CGfxMeshManager::DestroyMesh(CGfxMesh *pMesh)
{

}

CGfxMesh* CGfxMeshManager::GetMesh(GLuint mesh)
{
	return NULL;
}
