#pragma once
#include <map>
#include "glew.h"


class CGfxSampler;
class CGfxTextureBase;
class CGfxTexture2D;
class CGfxTexture2DArray;
class CGfxTextureCubeMap;

class CGfxTextureManager
{
public:
	CGfxTextureManager(void);
	virtual ~CGfxTextureManager(void);


public:
	CGfxSampler* CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode);

public:
	CGfxTexture2D* CreateTexture2D(const char *szFileName);
	CGfxTexture2DArray* CreateTexture2DArray(const char *szFileName);
	CGfxTextureCubeMap* CreateTextureCubeMap(const char *szFileName);
	void DestroyTexture(CGfxTextureBase *pTexture);


private:
	std::map<GLuint64, CGfxSampler*> m_pSamplers;
	std::map<GLuint, CGfxTextureBase*> m_pTextures;
};
