#include "stdio.h"
#include "stdlib.h"
#include "UniformBufferTransform.h"


CUniformBufferTransform::CUniformBufferTransform(void)
	: m_bDirty(false)
{
	Identity();
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformBufferTransform::~CUniformBufferTransform(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformBufferTransform::Identity(void)
{
	m_bDirty = true;
	m_mtxScale = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
	m_mtxRotate = glm::rotate(glm::mat4(), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	m_mtxTranslate = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	m_params.mtxTransform = glm::mat4();
}

void CUniformBufferTransform::SetScale(float x, float y, float z)
{
	m_bDirty = true;
	m_mtxScale = glm::scale(glm::mat4(), glm::vec3(x, y, z));
	m_params.mtxTransform = m_mtxTranslate * m_mtxRotate * m_mtxScale;
}

void CUniformBufferTransform::SetRotate(float angle, float x, float y, float z)
{
	m_bDirty = true;
	m_mtxRotate = glm::rotate(glm::mat4(), angle, glm::vec3(x, y, z));
	m_params.mtxTransform = m_mtxTranslate * m_mtxRotate * m_mtxScale;
}

void CUniformBufferTransform::SetTranslate(float x, float y, float z)
{
	m_bDirty = true;
	m_mtxTranslate = glm::translate(glm::mat4(), glm::vec3(x, y, z));
	m_params.mtxTransform = m_mtxTranslate * m_mtxRotate * m_mtxScale;
}

void CUniformBufferTransform::SetTransform(const glm::mat4 &mtxTransform)
{
	m_bDirty = true;
	m_params.mtxTransform = mtxTransform;
}

void CUniformBufferTransform::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformBufferTransform::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformBufferTransform::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
