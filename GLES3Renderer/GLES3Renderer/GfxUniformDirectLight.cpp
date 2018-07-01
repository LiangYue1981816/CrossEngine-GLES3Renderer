#include "stdio.h"
#include "stdlib.h"
#include "UniformDirectLight.h"


CUniformDirectLight::CUniformDirectLight(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformDirectLight::~CUniformDirectLight(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformDirectLight::SetColor(float r, float g, float b)
{
	m_bDirty = true;
	m_params.color = glm::vec4(r, g, b, 0.0);
}

void CUniformDirectLight::SetDirection(float x, float y, float z)
{
	m_bDirty = true;
	m_params.direction = glm::normalize(glm::vec4(x, y, z, 0.0));
}

void CUniformDirectLight::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformDirectLight::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformDirectLight::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
