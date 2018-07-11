#include "stdio.h"
#include "stdlib.h"
#include "GfxSampler.h"
#include "GfxTexture2D.h"
#include "GfxTexture2DArray.h"
#include "GfxTextureCubeMap.h"
#include "GfxTextureManager.h"


CGfxTextureManager::CGfxTextureManager(void)
{

}

CGfxTextureManager::~CGfxTextureManager(void)
{

}

CGfxSampler* CGfxTextureManager::CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	return NULL;
}

CGfxTexture2D* CGfxTextureManager::CreateTexture2D(const char *szName)
{
	return NULL;
}

CGfxTexture2DArray* CGfxTextureManager::CreateTexture2DArray(const char *szName)
{
	return NULL;
}

CGfxTextureCubeMap* CGfxTextureManager::CreateTextureCubeMap(const char *szName)
{
	return NULL;
}

void CGfxTextureManager::DestroyTexture(CGfxTextureBase *pTexture)
{

}
