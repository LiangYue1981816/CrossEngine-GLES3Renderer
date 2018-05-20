#include "stdio.h"
#include "stdlib.h"
#include "UniformBufferVec2.h"


CUniformBufferVec2::CUniformBufferVec2(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CUniformBufferVec2::~CUniformBufferVec2(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformBufferVec2::SetValue(float x, float y)
{
	m_bDirty = true;
	m_value = glm::vec2(x, y);
}

void CUniformBufferVec2::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CUniformBufferVec2::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformBufferVec2::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
