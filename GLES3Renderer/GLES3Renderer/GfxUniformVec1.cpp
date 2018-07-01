#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformVec1.h"


CGfxUniformVec1::CGfxUniformVec1(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CGfxUniformVec1::~CGfxUniformVec1(void)
{
	m_uniformBuffer.Destroy();
}

void CGfxUniformVec1::SetValue(float value)
{
	m_bDirty = true;
	m_value = value;
}

void CGfxUniformVec1::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CGfxUniformVec1::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CGfxUniformVec1::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
