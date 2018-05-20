#include "stdio.h"
#include "stdlib.h"
#include "UniformBufferVec3.h"


CUniformBufferVec3::CUniformBufferVec3(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CUniformBufferVec3::~CUniformBufferVec3(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformBufferVec3::SetValue(float x, float y, float z)
{
	m_bDirty = true;
	m_value = glm::vec3(x, y, z);
}

void CUniformBufferVec3::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CUniformBufferVec3::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformBufferVec3::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
