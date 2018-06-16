#include "stdio.h"
#include "stdlib.h"
#include "UniformTime.h"


CUniformTime::CUniformTime(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformTime::~CUniformTime(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformTime::SetTime(float t, float dt)
{
	m_bDirty = true;
	m_params.time = glm::vec4(t / 20.0f, t * 1.0f, t * 2.0f, t * 3.0f);
	m_params.sinTime = glm::vec4(sinf(t / 8.0f), sinf(t / 4.0f), sinf(t / 2.0f), t);
	m_params.cosTime = glm::vec4(cosf(t / 8.0f), cosf(t / 4.0f), cosf(t / 2.0f), t);
	m_params.deltaTime = glm::vec4(dt, 1.0f / dt, 1.0f, 1.0f);
}

void CUniformTime::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformTime::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformTime::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
