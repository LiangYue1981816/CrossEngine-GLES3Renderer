#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformBuffer.h"
#include "GfxUniformDirectLight.h"


CGfxUniformDirectLight::CGfxUniformDirectLight(void)
	: m_bDirty(false)
	, m_pUniformBuffer(NULL)
{
	m_pUniformBuffer = new CGfxUniformBuffer;
	m_pUniformBuffer->Create(NULL, sizeof(m_params), true);
}

CGfxUniformDirectLight::~CGfxUniformDirectLight(void)
{
	m_pUniformBuffer->Destroy();
	delete m_pUniformBuffer;
}

void CGfxUniformDirectLight::SetColor(float red, float green, float blue)
{
	m_bDirty = true;
	m_params.color = glm::vec4(red, green, blue, 0.0);
}

void CGfxUniformDirectLight::SetDirection(float x, float y, float z)
{
	m_bDirty = true;
	m_params.direction = glm::normalize(glm::vec4(x, y, z, 0.0));
}

void CGfxUniformDirectLight::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_pUniformBuffer->SetData(&m_params, sizeof(m_params));
	}
}

GLuint CGfxUniformDirectLight::GetSize(void) const
{
	return m_pUniformBuffer->GetSize();
}

GLuint CGfxUniformDirectLight::GetBuffer(void) const
{
	return m_pUniformBuffer->GetBuffer();
}
