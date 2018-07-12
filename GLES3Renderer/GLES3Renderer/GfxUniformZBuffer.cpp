#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformBuffer.h"
#include "GfxUniformZBuffer.h"


CGfxUniformZBuffer::CGfxUniformZBuffer(void)
	: m_bDirty(false)
	, m_pUniformBuffer(NULL)
{
	m_pUniformBuffer = new CGfxUniformBuffer;
	m_pUniformBuffer->Create(NULL, sizeof(m_params), true);
}

CGfxUniformZBuffer::~CGfxUniformZBuffer(void)
{
	delete m_pUniformBuffer;
}

void CGfxUniformZBuffer::SetZBuffer(float zNear, float zFar)
{
	// OpenGL
	float x = (1.0f - zFar / zNear) / 2.0f;
	float y = (1.0f + zFar / zNear) / 2.0f;

	// D3D
	//float x = 1.0f - zFar / zNear;
	//float y = zFar / zNear;

	m_bDirty = true;
	m_params.zbuffer = glm::vec4(x, y, x / zFar, y / zFar);
}

void CGfxUniformZBuffer::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_pUniformBuffer->SetData(&m_params, sizeof(m_params));
	}
}

GLuint CGfxUniformZBuffer::GetSize(void) const
{
	return m_pUniformBuffer->GetSize();
}

GLuint CGfxUniformZBuffer::GetBuffer(void) const
{
	return m_pUniformBuffer->GetBuffer();
}
