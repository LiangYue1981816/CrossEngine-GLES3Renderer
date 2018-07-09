#include "stdio.h"
#include "stdlib.h"
#include "GfxMesh.h"
#include "GfxMaterial.h"
#include "GfxFrameBuffer.h"
#include "GfxCommandBuffer.h"
#include "GfxCommandClear.h"
#include "GfxCommandBindMesh.h"
#include "GfxCommandBindMaterial.h"
#include "GfxCommandBindFrameBuffer.h"
#include "GfxCommandDrawInstance.h"
#include "GfxCommandDrawElements.h"
#include "GfxCommandInvalidateFrameBuffer.h"


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

void CGfxCommandBuffer::Submit(void) const
{
	for (const auto &itCommand : m_commands) {
		itCommand->Execute();
	}
}

void CGfxCommandBuffer::CommandClear(float red, float green, float blue, float alpha, float depth)
{
	m_commands.push_back(new CGfxCommandClear(red, green, blue, alpha, depth));
}

void CGfxCommandBuffer::CommandBindFrameBuffer(CGfxFrameBuffer *pFrameBuffer)
{
	m_commands.push_back(new CGfxCommandBindFrameBuffer(pFrameBuffer));
}

void CGfxCommandBuffer::CommandBindMesh(CGfxMesh *pMesh)
{
	m_commands.push_back(new CGfxCommandBindMesh(pMesh));
}

void CGfxCommandBuffer::CommandBindMaterial(CGfxMaterial *pMaterial)
{
	m_commands.push_back(new CGfxCommandBindMaterial(pMaterial));
}

void CGfxCommandBuffer::CommandDrawInstance(GLenum mode, GLsizei count, GLenum type, void *indices, GLsizei primcount)
{
	m_commands.push_back(new CGfxCommandDrawInstance(mode, count, type, indices, primcount));
}

void CGfxCommandBuffer::CommandDrawElements(GLenum mode, GLsizei count, GLenum type, void *indices)
{
	m_commands.push_back(new CGfxCommandDrawElements(mode, count, type, indices));
}

void CGfxCommandBuffer::CommandInvalidateFramebuffer(CGfxFrameBuffer *pFrameBuffer)
{
	m_commands.push_back(new CGfxCommandInvalidateFrameBuffer(pFrameBuffer));
}
