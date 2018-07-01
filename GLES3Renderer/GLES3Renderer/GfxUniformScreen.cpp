#include "stdio.h"
#include "stdlib.h"
#include "UniformScreen.h"


CUniformScreen::CUniformScreen(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformScreen::~CUniformScreen(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformScreen::SetScreen(float width, float height)
{
	m_bDirty = true;
	m_params.screen = glm::vec4(width, height, 1.0f + 1.0f / width, 1.0f + 1.0f / height);
}

void CUniformScreen::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformScreen::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformScreen::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
