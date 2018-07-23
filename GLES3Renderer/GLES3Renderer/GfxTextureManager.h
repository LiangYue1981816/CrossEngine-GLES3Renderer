#pragma once
#include <map>
#include "gles3/gl3.h"


class CGfxTextureBase;
class CGfxTexture2D;
class CGfxTexture2DArray;
class CGfxTextureCubeMap;
class CGfxTextureManager
{
	friend class CGfxRenderer;


private:
	CGfxTextureManager(void);
	virtual ~CGfxTextureManager(void);


private:
	CGfxTexture2D* LoadTexture2D(const char *szFileName);
	CGfxTexture2DArray* LoadTexture2DArray(const char *szFileName);
	CGfxTextureCubeMap* LoadTextureCubeMap(const char *szFileName);
	void FreeTexture(CGfxTextureBase *pTexture);


private:
	std::map<GLuint, CGfxTextureBase*> m_pTextures;
};
