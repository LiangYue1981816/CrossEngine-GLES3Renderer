#include "stdio.h"
#include "stdlib.h"
#include "UniformVec2.h"


CUniformVec2::CUniformVec2(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CUniformVec2::~CUniformVec2(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformVec2::SetValue(float x, float y)
{
	m_bDirty = true;
	m_value = glm::vec2(x, y);
}

void CUniformVec2::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CUniformVec2::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformVec2::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
