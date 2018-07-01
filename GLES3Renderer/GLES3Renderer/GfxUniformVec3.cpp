#include "stdio.h"
#include "stdlib.h"
#include "UniformVec3.h"


CUniformVec3::CUniformVec3(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CUniformVec3::~CUniformVec3(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformVec3::SetValue(float x, float y, float z)
{
	m_bDirty = true;
	m_value = glm::vec3(x, y, z);
}

void CUniformVec3::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CUniformVec3::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformVec3::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
