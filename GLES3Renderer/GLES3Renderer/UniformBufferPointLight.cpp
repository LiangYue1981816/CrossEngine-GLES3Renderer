#include "stdio.h"
#include "stdlib.h"
#include "UniformBufferPointLight.h"


CUniformBufferPointLight::CUniformBufferPointLight(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformBufferPointLight::~CUniformBufferPointLight(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformBufferPointLight::SetPosition(float x, float y, float z)
{
	m_bDirty = true;
	m_params.position = glm::vec4(x, y, z, 0.0f);
}

void CUniformBufferPointLight::SetColor(float r, float g, float b)
{
	m_bDirty = true;
	m_params.color = glm::vec4(r, g, b, 0.0f);
}

void CUniformBufferPointLight::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformBufferPointLight::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformBufferPointLight::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
