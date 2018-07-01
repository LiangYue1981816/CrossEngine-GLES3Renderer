#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformPointLight.h"


CGfxUniformPointLight::CGfxUniformPointLight(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CGfxUniformPointLight::~CGfxUniformPointLight(void)
{
	m_uniformBuffer.Destroy();
}

void CGfxUniformPointLight::SetColor(float r, float g, float b)
{
	m_bDirty = true;
	m_params.color = glm::vec4(r, g, b, 0.0f);
}

void CGfxUniformPointLight::SetPosition(float x, float y, float z)
{
	m_bDirty = true;
	m_params.position = glm::vec4(x, y, z, 0.0f);
}

void CGfxUniformPointLight::SetAttenuation(float linear, float square, float constant)
{
	m_bDirty = true;
	m_params.attenuation = glm::vec4(linear, square, constant, 0.0f);
}

void CGfxUniformPointLight::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CGfxUniformPointLight::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CGfxUniformPointLight::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
