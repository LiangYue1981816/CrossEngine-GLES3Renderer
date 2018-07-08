#include "stdio.h"
#include "stdlib.h"
#include "GfxCommandBuffer.h"
#include "GfxCommandBindVertexArray.h"
#include "GfxCommandBindFrameBuffer.h"
#include "GfxCommandDrawInstance.h"
#include "GfxCommandDrawElements.h"
#include "GfxCommandInvalidateFramebuffer.h"
#include "GfxMesh.h"
#include "GfxMaterial.h"
#include "GfxFrameBuffer.h"
#include "GfxCommandBindMaterial.h"


CGfxCommandBuffer::CGfxCommandBuffer(void)
{

}

CGfxCommandBuffer::~CGfxCommandBuffer(void)
{

}

void CGfxCommandBuffer::Clearup(void)
{
	for (const auto &itCommand : m_commands) {
		delete itCommand;
	}

	m_commands.clear();
}

void CGfxCommandBuffer::Submit(void)
{
	for (const auto &itCommand : m_commands) {
		itCommand->Execute();
	}
}

void CGfxCommandBuffer::CommandBindFrameBuffer(CGfxFrameBuffer *pFrameBuffer)
{

}

void CGfxCommandBuffer::CommandBindMesh(CGfxMesh *pMesh)
{

}

void CGfxCommandBuffer::CommandBindMaterial(CGfxMaterial *pMaterial)
{

}

void CGfxCommandBuffer::CommandDrawInstance(GLenum mode, GLsizei count, GLenum type, const void *indices, GLsizei primcount)
{

}

void CGfxCommandBuffer::CommandDrawElements(GLenum mode, GLsizei count, GLenum type, const void *indices)
{

}

void CGfxCommandBuffer::CommandInvalidateFramebuffer(CGfxFrameBuffer *pFrameBuffer)
{

}
