#include "stdio.h"
#include "stdlib.h"
#include "GfxMesh.h"
#include "GfxMaterial.h"
#include "GfxFrameBuffer.h"
#include "GfxCommandBuffer.h"
#include "GfxCommandBeginPass.h"
#include "GfxCommandEndPass.h"
#include "GfxCommandBindMesh.h"
#include "GfxCommandBindMaterial.h"
#include "GfxCommandBindInputTexture.h"
#include "GfxCommandSetScissor.h"
#include "GfxCommandSetViewport.h"
#include "GfxCommandClearDepth.h"
#include "GfxCommandClearColor.h"
#include "GfxCommandDrawInstance.h"
#include "GfxCommandDrawElements.h"
#include "GfxCommandExecute.h"


CGfxCommandBuffer::CGfxCommandBuffer(bool bMainCommandBuffer)
	: m_bMainCommandBuffer(bMainCommandBuffer)
	, m_bInPassScope(false)
{

}

CGfxCommandBuffer::~CGfxCommandBuffer(void)
{
	Clearup();
}

bool CGfxCommandBuffer::IsMainCommandBuffer(void) const
{
	return m_bMainCommandBuffer;
}

bool CGfxCommandBuffer::IsInPassScope(void) const
{
	return m_bInPassScope;
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
	if (m_bMainCommandBuffer) {
		for (const auto &itCommand : m_commands) {
			itCommand->Execute();
		}
	}
}

void CGfxCommandBuffer::BeginPass(CGfxFrameBuffer *pFrameBuffer)
{
	if (m_bMainCommandBuffer) {
		m_bInPassScope = true;
		m_commands.push_back(new CGfxCommandBeginPass(pFrameBuffer));
	}
}

void CGfxCommandBuffer::EndPass(CGfxFrameBuffer *pFrameBuffer)
{
	if (m_bMainCommandBuffer) {
		m_bInPassScope = false;
		m_commands.push_back(new CGfxCommandEndPass(pFrameBuffer));
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

void CGfxCommandBuffer::BindMesh(CGfxMesh *pMesh)
{
	m_commands.push_back(new CGfxCommandBindMesh(pMesh));
}

void CGfxCommandBuffer::BindMaterial(GLuint material)
{
	m_commands.push_back(new CGfxCommandBindMaterial(material));
}

void CGfxCommandBuffer::BindInputTexture(const char *szName, GLuint texture)
{
	m_commands.push_back(new CGfxCommandBindInputTexture(szName, texture));
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

void CGfxCommandBuffer::Execute(CGfxCommandBuffer *pCommandBuffer)
{
	if (m_bMainCommandBuffer) {
		m_commands.push_back(new CGfxCommandExecute(pCommandBuffer));
	}
}
