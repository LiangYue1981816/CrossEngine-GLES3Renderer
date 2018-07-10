#pragma once
#include <vector>
#include "glew.h"


class CGfxMesh;
class CGfxMaterial;
class CGfxFrameBuffer;

class CGfxCommandBase
{
public:
	CGfxCommandBase(void)
	{

	}
	virtual ~CGfxCommandBase(void)
	{

	}

public:
	virtual void Execute(void) const = 0;
};

class CGfxCommandBuffer
{
public:
	CGfxCommandBuffer(void);
	virtual ~CGfxCommandBuffer(void);


public:
	void Clearup(void);
	void Execute(void) const;

public:
	void SetScissor(int x, int y, int width, int height);
	void SetViewport(int x, int y, int width, int height);

	void BindFrameBuffer(CGfxFrameBuffer *pFrameBuffer);
	void BindInputTexture(const char *szName, GLuint texture);
	void BindMesh(CGfxMesh *pMesh);
	void BindMaterial(CGfxMaterial *pMaterial);

	void Clear(float red, float green, float blue, float alpha, float depth);
	void DrawInstance(GLenum mode, GLsizei count, GLenum type, void *indices, GLsizei primcount);
	void DrawElements(GLenum mode, GLsizei count, GLenum type, void *indices);
	void InvalidateFramebuffer(CGfxFrameBuffer *pFrameBuffer);

	void Execute(CGfxCommandBuffer *pCommandBuffer);


private:
	std::vector<CGfxCommandBase*> m_commands;
};
