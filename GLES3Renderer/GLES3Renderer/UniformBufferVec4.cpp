#include "stdio.h"
#include "stdlib.h"
#include "UniformBufferVec4.h"


CUniformBufferVec4::CUniformBufferVec4(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CUniformBufferVec4::~CUniformBufferVec4(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformBufferVec4::SetValue(float x, float y, float z, float w)
{
	m_bDirty = true;
	m_value = glm::vec4(x, y, z, w);
}

void CUniformBufferVec4::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CUniformBufferVec4::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformBufferVec4::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
