#pragma once
#include <vector>
#include "gles/gl3.h"


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
	bool Execute(void) const;

public:
	bool BeginPass(CGfxFrameBuffer *pFrameBuffer);
	bool EndPass(void);

	bool SetScissor(int x, int y, int width, int height);
	bool SetViewport(int x, int y, int width, int height);

	bool BindMesh(CGfxMesh *pMesh);
	bool BindMaterial(GLuint material);
	bool BindInputTexture(const char *szName, GLuint texture);

	bool ClearDepth(float depth);
	bool ClearColor(float red, float green, float blue, float alpha);
	bool DrawInstance(GLenum mode, GLsizei count, GLenum type, void *indices, GLsizei primcount);
	bool DrawElements(GLenum mode, GLsizei count, GLenum type, void *indices);

	bool Execute(CGfxCommandBuffer *pCommandBuffer);


private:
	bool m_bMainCommandBuffer;
	bool m_bInPassScope;

private:
	CGfxFrameBuffer *m_pFrameBuffer;
	std::vector<CGfxCommandBase*> m_commands;
};
