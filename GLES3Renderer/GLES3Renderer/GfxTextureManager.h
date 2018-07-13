#pragma once
#include <map>
#include "gles/gl3.h"


class CGfxSampler;
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


public:
	CGfxSampler* CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode);

public:
	CGfxTexture2D* CreateTexture2D(const char *szName);
	CGfxTexture2DArray* CreateTexture2DArray(const char *szName);
	CGfxTextureCubeMap* CreateTextureCubeMap(const char *szName);

	CGfxTexture2D* LoadTexture2D(const char *szFileName);
	CGfxTexture2DArray* LoadTexture2DArray(const char *szFileName);
	CGfxTextureCubeMap* LoadTextureCubeMap(const char *szFileName);

	void DestroyTexture(CGfxTextureBase *pTexture);


private:
	std::map<GLuint64, CGfxSampler*> m_pSamplers;
	std::map<GLuint, CGfxTextureBase*> m_pTextures;
};
