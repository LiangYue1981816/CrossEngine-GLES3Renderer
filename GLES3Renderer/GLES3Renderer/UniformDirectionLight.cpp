#include "stdio.h"
#include "stdlib.h"
#include "UniformDirectionLight.h"


CUniformDirectionLight::CUniformDirectionLight(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformDirectionLight::~CUniformDirectionLight(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformDirectionLight::SetDirection(float x, float y, float z)
{
	m_bDirty = true;
	m_params.direction = glm::normalize(glm::vec4(x, y, z, 0.0));
}

void CUniformDirectionLight::SetColor(float r, float g, float b)
{
	m_bDirty = true;
	m_params.color = glm::vec4(r, g, b, 0.0);
}

void CUniformDirectionLight::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformDirectionLight::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformDirectionLight::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
