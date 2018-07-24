#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformBuffer.h"
#include "GfxUniformPointLight.h"


CGfxUniformPointLight::CGfxUniformPointLight(void)
	: m_bDirty(false)
	, m_pUniformBuffer(NULL)
{
	m_pUniformBuffer = new CGfxUniformBuffer;
	m_pUniformBuffer->Create(NULL, sizeof(m_params), true);
}

CGfxUniformPointLight::~CGfxUniformPointLight(void)
{
	m_pUniformBuffer->Destroy();
	delete m_pUniformBuffer;
}

void CGfxUniformPointLight::SetColor(float red, float green, float blue)
{
	m_bDirty = true;
	m_params.color = glm::vec4(red, green, blue, 0.0f);
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
		m_pUniformBuffer->SetData(&m_params, sizeof(m_params));
	}
}

GLuint CGfxUniformPointLight::GetSize(void) const
{
	return m_pUniformBuffer->GetSize();
}

GLuint CGfxUniformPointLight::GetBuffer(void) const
{
	return m_pUniformBuffer->GetBuffer();
}
