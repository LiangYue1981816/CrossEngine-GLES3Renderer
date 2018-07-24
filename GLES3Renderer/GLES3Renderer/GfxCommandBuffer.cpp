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

bool CGfxCommandBuffer::CmdBeginPass(CGfxFrameBuffer *pFrameBuffer)
{
	if (m_bMainCommandBuffer == true && m_bInPassScope == false) {
		m_bInPassScope = true;
		m_pFrameBuffer = pFrameBuffer;
		m_commands.push_back(new CGfxCommandBeginPass(m_pFrameBuffer));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdEndPass(void)
{
	if (m_bMainCommandBuffer == true && m_bInPassScope == true) {
		m_commands.push_back(new CGfxCommandEndPass(m_pFrameBuffer));
		m_bInPassScope = false;
		m_pFrameBuffer = NULL;
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdSetScissor(int x, int y, int width, int height)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandSetScissor(x, y, width, height));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdSetViewport(int x, int y, int width, int height)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandSetViewport(x, y, width, height));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdBindMesh(CGfxMesh *pMesh)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandBindMesh(pMesh));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdBindMesh(CGfxMesh *pMesh, std::vector<glm::mat4> &mtxTransforms)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandBindMesh(pMesh, mtxTransforms));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdBindMaterial(CGfxMaterial *pMaterial, CGfxUniformCamera *pUniformCamera, CGfxUniformZBuffer *pUniformZBuffer, CGfxUniformProjection *pUniformProjection)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandBindMaterial(pMaterial, pUniformCamera, pUniformZBuffer, pUniformProjection));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdBindInputTexture(const char *szName, GLuint texture, GLenum minFilter, GLenum magFilter, GLenum addressMode)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandBindInputTexture(szName, texture, minFilter, magFilter, addressMode));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdClearDepth(float depth)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandClearDepth(depth));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdClearColor(float red, float green, float blue, float alpha)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandClearColor(red, green, blue, alpha));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdDrawInstance(GLenum mode, GLsizei count, GLenum type, void *indices, GLsizei primcount)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandDrawInstance(mode, count, type, indices, primcount));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdDrawElements(GLenum mode, GLsizei count, GLenum type, void *indices)
{
	if ((m_bMainCommandBuffer == false) || (m_bMainCommandBuffer == true && m_bInPassScope == true)) {
		m_commands.push_back(new CGfxCommandDrawElements(mode, count, type, indices));
		return true;
	}

	return false;
}

bool CGfxCommandBuffer::CmdExecute(CGfxCommandBuffer *pCommandBuffer)
{
	if (m_bMainCommandBuffer == true && m_bInPassScope == true && pCommandBuffer->m_bMainCommandBuffer == false) {
		m_commands.push_back(new CGfxCommandExecute(pCommandBuffer));
		return true;
	}

	return false;
}
