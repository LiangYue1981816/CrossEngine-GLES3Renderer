#include "stdio.h"
#include "stdlib.h"
#include "UniformShadowLight.h"


CUniformShadowLight::CUniformShadowLight(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformShadowLight::~CUniformShadowLight(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformShadowLight::SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_bDirty = true;
	m_params.mtxProjection = glm::ortho(left, right, bottom, top, zNear, zFar);
	m_params.clip = glm::vec2(zFar - zNear, 1.0f / (zFar - zNear));
}

void CUniformShadowLight::SetLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
	m_bDirty = true;
	m_params.mtxView = glm::lookAt(glm::vec3(eyex, eyey, eyez), glm::vec3(centerx, centery, centerz), glm::vec3(upx, upy, upz));
}

void CUniformShadowLight::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformShadowLight::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformShadowLight::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
