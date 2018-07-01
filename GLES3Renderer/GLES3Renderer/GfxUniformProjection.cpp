#include "stdio.h"
#include "stdlib.h"
#include "UniformProjection.h"


CUniformProjection::CUniformProjection(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformProjection::~CUniformProjection(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformProjection::SetProjection(float zNear, float zFar)
{
	m_bDirty = true;
	m_params.projection = glm::vec4(1.0f, zNear, zFar, 1.0f / zFar);
}

void CUniformProjection::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformProjection::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformProjection::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
