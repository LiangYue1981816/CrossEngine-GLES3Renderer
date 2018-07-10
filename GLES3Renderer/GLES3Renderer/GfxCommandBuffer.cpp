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
	, m_pFrameBuffer(NULL)
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

void CGfxCommandBuffer::Clearup(void)
{
	for (const auto &itCommand : m_commands) {
		delete itCommand;
	}

	m_commands.clear();
	m_bInPassScope = false;
	m_pFrameBuffer = NULL;
}

bool CGfxCommandBuffer::Execute(void) const
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == false)) {
		for (const auto &itCommand : m_commands) {
			itCommand->Execute();
		}
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::BeginPass(CGfxFrameBuffer *pFrameBuffer)
{
	if (m_bMainCommandBuffer == true && m_bInPassScope == false) {
		m_bInPassScope = true;
		m_pFrameBuffer = pFrameBuffer;
		m_commands.push_back(new CGfxCommandBeginPass(m_pFrameBuffer));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::EndPass(void)
{
	if (m_bMainCommandBuffer == true && m_bInPassScope == true) {
		m_commands.push_back(new CGfxCommandEndPass(m_pFrameBuffer));
		m_bInPassScope = false;
		m_pFrameBuffer = NULL;
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::SetScissor(int x, int y, int width, int height)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandSetScissor(x, y, width, height));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::SetViewport(int x, int y, int width, int height)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandSetViewport(x, y, width, height));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::BindMesh(CGfxMesh *pMesh)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandBindMesh(pMesh));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::BindMaterial(GLuint material)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandBindMaterial(material));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::BindInputTexture(const char *szName, GLuint texture)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandBindInputTexture(szName, texture));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::ClearDepth(float depth)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandClearDepth(depth));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::ClearColor(float red, float green, float blue, float alpha)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandClearColor(red, green, blue, alpha));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::DrawInstance(GLenum mode, GLsizei count, GLenum type, void *indices, GLsizei primcount)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandDrawInstance(mode, count, type, indices, primcount));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::DrawElements(GLenum mode, GLsizei count, GLenum type, void *indices)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandDrawElements(mode, count, type, indices));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::Execute(CGfxCommandBuffer *pCommandBuffer)
{
	if (m_bMainCommandBuffer == true && m_bInPassScope == true && pCommandBuffer->IsMainCommandBuffer() == false) {
		m_commands.push_back(new CGfxCommandExecute(pCommandBuffer));
		return true;
	}

	return false;
}
