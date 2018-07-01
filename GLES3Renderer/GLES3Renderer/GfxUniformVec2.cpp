#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformVec2.h"


CGfxUniformVec2::CGfxUniformVec2(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CGfxUniformVec2::~CGfxUniformVec2(void)
{
	m_uniformBuffer.Destroy();
}

void CGfxUniformVec2::SetValue(float x, float y)
{
	m_bDirty = true;
	m_value = glm::vec2(x, y);
}

void CGfxUniformVec2::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CGfxUniformVec2::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CGfxUniformVec2::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
