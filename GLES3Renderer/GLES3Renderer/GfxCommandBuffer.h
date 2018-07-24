#pragma once
#include <vector>
#include "gles3/gl3.h"


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

class CGfxMesh;
class CGfxMaterial;
class CGfxFrameBuffer;
class CGfxUniformCamera;
class CGfxUniformZBuffer;
class CGfxUniformProjection;
class CGfxCommandBuffer
{
	friend class CGfxRenderer;


public:
	CGfxCommandBuffer(bool bMainCommandBuffer);
	virtual ~CGfxCommandBuffer(void);


public:
	void Clearup(void);
	bool Execute(void) const;

private:
	bool CmdBeginPass(CGfxFrameBuffer *pFrameBuffer);
	bool CmdEndPass(void);

	bool CmdSetScissor(int x, int y, int width, int height);
	bool CmdSetViewport(int x, int y, int width, int height);

	bool CmdBindMesh(CGfxMesh *pMesh);
	bool CmdBindMesh(CGfxMesh *pMesh, std::vector<glm::mat4> &mtxTransforms);
	bool CmdBindMaterial(CGfxMaterial *pMaterial, CGfxUniformCamera *pUniformCamera, CGfxUniformZBuffer *pUniformZBuffer, CGfxUniformProjection *pUniformProjection);
	bool CmdBindInputTexture(const char *szName, GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode);

	bool CmdClearDepth(float depth);
	bool CmdClearColor(float red, float green, float blue, float alpha);
	bool CmdDrawInstance(GLenum mode, GLsizei count, GLenum type, void *indices, GLsizei primcount);
	bool CmdDrawElements(GLenum mode, GLsizei count, GLenum type, void *indices);

	bool CmdExecute(CGfxCommandBuffer *pCommandBuffer);


private:
	bool m_bMainCommandBuffer;
	bool m_bInPassScope;

private:
	CGfxFrameBuffer *m_pFrameBuffer;
	std::vector<CGfxCommandBase*> m_commands;
};
