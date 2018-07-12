#include "stdio.h"
#include "stdlib.h"
#include "GfxUtils.h"
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
	for (const auto &itSampler : m_pSamplers) {
		delete itSampler.second;
	}

	for (const auto &itTexture : m_pTextures) {
		delete itTexture.second;
	}

	m_pSamplers.clear();
	m_pTextures.clear();
}

CGfxSampler* CGfxTextureManager::CreateSampler(GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	GLuint64 hash = (((GLuint64)minFilter) << 32) | (((GLuint64)magFilter) << 16) | ((GLuint64)addressMode);

	if (m_pSamplers[hash] == NULL) {
		m_pSamplers[hash] = new CGfxSampler(minFilter, magFilter, addressMode);
	}

	return m_pSamplers[hash];
}

CGfxTexture2D* CGfxTextureManager::CreateTexture2D(const char *szFileName)
{
	GLuint hash = HashValue(szFileName);

	if (m_pTextures[hash] == NULL) {
		m_pTextures[hash] = new CGfxTexture2D(hash);
		m_pTextures[hash]->Create(szFileName);
	}

	m_pTextures[hash]->refCount++;

	return (CGfxTexture2D *)m_pTextures[hash];
}

CGfxTexture2DArray* CGfxTextureManager::CreateTexture2DArray(const char *szFileName)
{
	GLuint hash = HashValue(szFileName);

	if (m_pTextures[hash] == NULL) {
		m_pTextures[hash] = new CGfxTexture2DArray(hash);
		m_pTextures[hash]->Create(szFileName);
	}

	m_pTextures[hash]->refCount++;

	return (CGfxTexture2DArray *)m_pTextures[hash];
}

CGfxTextureCubeMap* CGfxTextureManager::CreateTextureCubeMap(const char *szFileName)
{
	GLuint hash = HashValue(szFileName);

	if (m_pTextures[hash] == NULL) {
		m_pTextures[hash] = new CGfxTextureCubeMap(hash);
		m_pTextures[hash]->Create(szFileName);
	}

	m_pTextures[hash]->refCount++;

	return (CGfxTextureCubeMap *)m_pTextures[hash];
}

void CGfxTextureManager::DestroyTexture(CGfxTextureBase *pTexture)
{
	if (pTexture->refCount > 0) {
		pTexture->refCount--;
	}

	if (pTexture->refCount == 0) {
		m_pTextures.erase(pTexture->GetName());
		delete pTexture;
	}
}
