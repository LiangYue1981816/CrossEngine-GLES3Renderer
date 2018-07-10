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
	CGfxCommandBuffer(bool bMainCommandBuffer);
	virtual ~CGfxCommandBuffer(void);


public:
	bool IsMainCommandBuffer(void) const;

public:
	void Clearup(void);
	void Execute(void) const;

public:
	void BeginPass(CGfxFrameBuffer *pFrameBuffer);
	void EndPass(CGfxFrameBuffer *pFrameBuffer);

	void SetScissor(int x, int y, int width, int height);
	void SetViewport(int x, int y, int width, int height);

	void BindMesh(CGfxMesh *pMesh);
	void BindMaterial(GLuint material);
	void BindInputTexture(const char *szName, GLuint texture);

	void ClearDepth(float depth);
	void ClearColor(float red, float green, float blue, float alpha);
	void DrawInstance(GLenum mode, GLsizei count, GLenum type, void *indices, GLsizei primcount);
	void DrawElements(GLenum mode, GLsizei count, GLenum type, void *indices);

	void Execute(CGfxCommandBuffer *pCommandBuffer);


private:
	bool m_bMainCommandBuffer;
	bool m_bInPassScope;
	std::vector<CGfxCommandBase*> m_commands;
};
