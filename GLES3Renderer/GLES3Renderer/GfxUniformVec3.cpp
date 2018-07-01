#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformVec3.h"


CGfxUniformVec3::CGfxUniformVec3(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CGfxUniformVec3::~CGfxUniformVec3(void)
{
	m_uniformBuffer.Destroy();
}

void CGfxUniformVec3::SetValue(float x, float y, float z)
{
	m_bDirty = true;
	m_value = glm::vec3(x, y, z);
}

void CGfxUniformVec3::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CGfxUniformVec3::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CGfxUniformVec3::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
