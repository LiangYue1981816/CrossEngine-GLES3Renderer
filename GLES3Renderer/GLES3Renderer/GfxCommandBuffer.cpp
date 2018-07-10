#include "stdio.h"
#include "stdlib.h"
#include "GfxMesh.h"
#include "GfxMaterial.h"
#include "GfxFrameBuffer.h"
#include "GfxCommandBuffer.h"
#include "GfxCommandBindMesh.h"
#include "GfxCommandBindMaterial.h"
#include "GfxCommandBindFrameBuffer.h"
#include "GfxCommandBindInputTexture.h"
#include "GfxCommandSetScissor.h"
#include "GfxCommandSetViewport.h"
#include "GfxCommandClearDepth.h"
#include "GfxCommandClearColor.h"
#include "GfxCommandDrawInstance.h"
#include "GfxCommandDrawElements.h"
#include "GfxCommandInvalidateFrameBuffer.h"
#include "GfxCommandExecute.h"


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

void CGfxCommandBuffer::Execute(void) const
{
	for (const auto &itCommand : m_commands) {
		itCommand->Execute();
	}
}

void CGfxCommandBuffer::SetScissor(int x, int y, int width, int height)
{
	m_commands.push_back(new CGfxCommandSetScissor(x, y, width, height));
}

void CGfxCommandBuffer::SetViewport(int x, int y, int width, int height)
{
	m_commands.push_back(new CGfxCommandSetViewport(x, y, width, height));
}

void CGfxCommandBuffer::BindFrameBuffer(CGfxFrameBuffer *pFrameBuffer)
{
	m_commands.push_back(new CGfxCommandBindFrameBuffer(pFrameBuffer));
}

void CGfxCommandBuffer::BindInputTexture(const char *szName, GLuint texture)
{
	m_commands.push_back(new CGfxCommandBindInputTexture(szName, texture));
}

void CGfxCommandBuffer::BindMesh(CGfxMesh *pMesh)
{
	m_commands.push_back(new CGfxCommandBindMesh(pMesh));
}

void CGfxCommandBuffer::BindMaterial(CGfxMaterial *pMaterial)
{
	m_commands.push_back(new CGfxCommandBindMaterial(pMaterial));
}

void CGfxCommandBuffer::ClearDepth(float depth)
{
	m_commands.push_back(new CGfxCommandClearDepth(depth));
}

void CGfxCommandBuffer::ClearColor(float red, float green, float blue, float alpha)
{
	m_commands.push_back(new CGfxCommandClearColor(red, green, blue, alpha));
}

void CGfxCommandBuffer::DrawInstance(GLenum mode, GLsizei count, GLenum type, void *indices, GLsizei primcount)
{
	m_commands.push_back(new CGfxCommandDrawInstance(mode, count, type, indices, primcount));
}

void CGfxCommandBuffer::DrawElements(GLenum mode, GLsizei count, GLenum type, void *indices)
{
	m_commands.push_back(new CGfxCommandDrawElements(mode, count, type, indices));
}

void CGfxCommandBuffer::InvalidateFramebuffer(CGfxFrameBuffer *pFrameBuffer)
{
	m_commands.push_back(new CGfxCommandInvalidateFrameBuffer(pFrameBuffer));
}

void CGfxCommandBuffer::Execute(CGfxCommandBuffer *pCommandBuffer)
{
	m_commands.push_back(new CGfxCommandExecute(pCommandBuffer));
}
