#include "stdio.h"
#include "stdlib.h"
#include "UniformZBuffer.h"


CUniformZBuffer::CUniformZBuffer(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformZBuffer::~CUniformZBuffer(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformZBuffer::SetZBuffer(float zNear, float zFar)
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

void CUniformZBuffer::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformZBuffer::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformZBuffer::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
