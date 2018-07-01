#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformProjection.h"


CGfxUniformProjection::CGfxUniformProjection(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CGfxUniformProjection::~CGfxUniformProjection(void)
{
	m_uniformBuffer.Destroy();
}

void CGfxUniformProjection::SetProjection(float zNear, float zFar)
{
	m_bDirty = true;
	m_params.projection = glm::vec4(1.0f, zNear, zFar, 1.0f / zFar);
}

void CGfxUniformProjection::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CGfxUniformProjection::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CGfxUniformProjection::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
