#include "stdio.h"
#include "stdlib.h"
#include "UniformBufferVec1.h"


CUniformBufferVec1::CUniformBufferVec1(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_value), true);
}

CUniformBufferVec1::~CUniformBufferVec1(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformBufferVec1::SetValue(float value)
{
	m_bDirty = true;
	m_value = value;
}

void CUniformBufferVec1::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_value, sizeof(m_value));
	}
}

GLuint CUniformBufferVec1::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformBufferVec1::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
