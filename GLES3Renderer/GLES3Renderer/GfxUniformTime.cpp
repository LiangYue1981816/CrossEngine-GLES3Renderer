#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformBuffer.h"
#include "GfxUniformTime.h"


CGfxUniformTime::CGfxUniformTime(void)
	: m_bDirty(false)
	, m_pUniformBuffer(NULL)
{
	m_pUniformBuffer = new CGfxUniformBuffer;
	m_pUniformBuffer->Create(NULL, sizeof(m_params), true);
}

CGfxUniformTime::~CGfxUniformTime(void)
{
	m_pUniformBuffer->Destroy();
	delete m_pUniformBuffer;
}

void CGfxUniformTime::SetTime(float t, float dt)
{
	m_bDirty = true;
	m_params.time = glm::vec4(t / 20.0f, t * 1.0f, t * 2.0f, t * 3.0f);
	m_params.sinTime = glm::vec4(sinf(t / 8.0f), sinf(t / 4.0f), sinf(t / 2.0f), t);
	m_params.cosTime = glm::vec4(cosf(t / 8.0f), cosf(t / 4.0f), cosf(t / 2.0f), t);
	m_params.deltaTime = glm::vec4(dt, 1.0f / dt, 1.0f, 1.0f);
}

void CGfxUniformTime::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_pUniformBuffer->SetData(&m_params, sizeof(m_params));
	}
}

GLuint CGfxUniformTime::GetSize(void) const
{
	return m_pUniformBuffer->GetSize();
}

GLuint CGfxUniformTime::GetBuffer(void) const
{
	return m_pUniformBuffer->GetBuffer();
}
