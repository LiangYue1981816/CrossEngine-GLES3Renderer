#include "stdio.h"
#include "stdlib.h"
#include "UniformBufferDirectionLight.h"


CUniformBufferDirectionLight::CUniformBufferDirectionLight(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformBufferDirectionLight::~CUniformBufferDirectionLight(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformBufferDirectionLight::SetDirection(float x, float y, float z)
{
	m_bDirty = true;
	m_params.direction = glm::normalize(glm::vec4(x, y, z, 0.0));
}

void CUniformBufferDirectionLight::SetColor(float r, float g, float b)
{
	m_bDirty = true;
	m_params.color = glm::vec4(r, g, b, 0.0);
}

void CUniformBufferDirectionLight::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformBufferDirectionLight::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformBufferDirectionLight::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
