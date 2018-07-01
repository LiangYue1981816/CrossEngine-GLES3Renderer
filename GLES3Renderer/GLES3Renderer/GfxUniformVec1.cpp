#include "stdio.h"
#include "stdlib.h"
#include "UniformVec1.h"


CUniformVec1::CUniformVec1(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CUniformVec1::~CUniformVec1(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformVec1::SetValue(float value)
{
	m_bDirty = true;
	m_value = value;
}

void CUniformVec1::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CUniformVec1::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformVec1::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
