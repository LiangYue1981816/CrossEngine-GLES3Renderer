#include "stdio.h"
#include "stdlib.h"
#include "UniformFog.h"


CUniformFog::CUniformFog(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformFog::~CUniformFog(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformFog::SetColor(float r, float g, float b)
{
	m_bDirty = true;
	m_params.color = glm::vec4(r, g, b, 0.0f);
}

void CUniformFog::SetHeightDensity(float startHeight, float endHeight, float density)
{
	m_bDirty = true;
	m_params.heightDensity = glm::vec4(startHeight, endHeight, density, 0.0f);
}

void CUniformFog::SetDistanceDensity(float startDistance, float endDistance, float density)
{
	m_bDirty = true;
	m_params.distanceDensity = glm::vec4(startDistance, endDistance, density, 0.0f);
}

void CUniformFog::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformFog::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformFog::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
