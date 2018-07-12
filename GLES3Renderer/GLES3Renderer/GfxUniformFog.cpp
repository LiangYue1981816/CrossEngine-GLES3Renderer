#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformBuffer.h"
#include "GfxUniformFog.h"


CGfxUniformFog::CGfxUniformFog(void)
	: m_bDirty(false)
	, m_pUniformBuffer(NULL)
{
	m_pUniformBuffer = new CGfxUniformBuffer;
	m_pUniformBuffer->Create(NULL, sizeof(m_params), true);
}

CGfxUniformFog::~CGfxUniformFog(void)
{
	delete m_pUniformBuffer;
}

void CGfxUniformFog::SetColor(float red, float green, float blue)
{
	m_bDirty = true;
	m_params.color = glm::vec4(red, green, blue, 0.0f);
}

void CGfxUniformFog::SetHeightDensity(float startHeight, float endHeight, float density)
{
	m_bDirty = true;
	m_params.heightDensity = glm::vec4(startHeight, endHeight, density, 0.0f);
}

void CGfxUniformFog::SetDistanceDensity(float startDistance, float endDistance, float density)
{
	m_bDirty = true;
	m_params.distanceDensity = glm::vec4(startDistance, endDistance, density, 0.0f);
}

void CGfxUniformFog::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_pUniformBuffer->SetData(&m_params, sizeof(m_params));
	}
}

GLuint CGfxUniformFog::GetSize(void) const
{
	return m_pUniformBuffer->GetSize();
}

GLuint CGfxUniformFog::GetBuffer(void) const
{
	return m_pUniformBuffer->GetBuffer();
}
