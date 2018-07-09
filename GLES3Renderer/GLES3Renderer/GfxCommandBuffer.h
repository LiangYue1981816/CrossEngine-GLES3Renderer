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
	void Submit(void) const;

public:
	void CommandBindFrameBuffer(CGfxFrameBuffer *pFrameBuffer);
	void CommandBindMesh(CGfxMesh *pMesh);
	void CommandBindMaterial(CGfxMaterial *pMaterial);
	void CommandDrawInstance(GLenum mode, GLsizei count, GLenum type, void *indices, GLsizei primcount);
	void CommandDrawElements(GLenum mode, GLsizei count, GLenum type, void *indices);
	void CommandInvalidateFramebuffer(CGfxFrameBuffer *pFrameBuffer);


private:
	std::vector<CGfxCommandBase*> m_commands;
};
