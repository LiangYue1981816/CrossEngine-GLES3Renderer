#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformShadowLight.h"


CGfxUniformShadowLight::CGfxUniformShadowLight(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CGfxUniformShadowLight::~CGfxUniformShadowLight(void)
{
	m_uniformBuffer.Destroy();
}

void CGfxUniformShadowLight::SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_bDirty = true;
	m_params.mtxProjection = glm::ortho(left, right, bottom, top, zNear, zFar);
	m_params.clip = glm::vec2(zFar - zNear, 1.0f / (zFar - zNear));
}

void CGfxUniformShadowLight::SetLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
	m_bDirty = true;
	m_params.mtxView = glm::lookAt(glm::vec3(eyex, eyey, eyez), glm::vec3(centerx, centery, centerz), glm::vec3(upx, upy, upz));
}

void CGfxUniformShadowLight::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CGfxUniformShadowLight::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CGfxUniformShadowLight::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
