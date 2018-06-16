#include "stdio.h"
#include "stdlib.h"
#include "UniformVec4.h"


CUniformVec4::CUniformVec4(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CUniformVec4::~CUniformVec4(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformVec4::SetValue(float x, float y, float z, float w)
{
	m_bDirty = true;
	m_value = glm::vec4(x, y, z, w);
}

void CUniformVec4::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CUniformVec4::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformVec4::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
