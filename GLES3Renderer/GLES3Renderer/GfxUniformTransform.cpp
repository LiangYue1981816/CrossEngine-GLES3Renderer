#include "stdio.h"
#include "stdlib.h"
#include "UniformTransform.h"


CUniformTransform::CUniformTransform(void)
	: m_bDirty(false)
{
	Identity();
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformTransform::~CUniformTransform(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformTransform::Identity(void)
{
	m_bDirty = true;
	m_mtxScale = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
	m_mtxRotate = glm::rotate(glm::mat4(), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	m_mtxTranslate = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	m_params.mtxWorld = glm::mat4();
	m_params.mtxWorldInverse = glm::mat4();
	m_params.mtxWorldInverseTranspose = glm::mat4();
}

void CUniformTransform::SetScale(float x, float y, float z)
{
	m_bDirty = true;
	m_mtxScale = glm::scale(glm::mat4(), glm::vec3(x, y, z));
	m_params.mtxWorld = m_mtxTranslate * m_mtxRotate * m_mtxScale;
	m_params.mtxWorldInverse = glm::inverse(m_params.mtxWorld);
	m_params.mtxWorldInverseTranspose = glm::transpose(m_params.mtxWorldInverse);
}

void CUniformTransform::SetRotate(float angle, float x, float y, float z)
{
	m_bDirty = true;
	m_mtxRotate = glm::rotate(glm::mat4(), angle, glm::vec3(x, y, z));
	m_params.mtxWorld = m_mtxTranslate * m_mtxRotate * m_mtxScale;
	m_params.mtxWorldInverse = glm::inverse(m_params.mtxWorld);
	m_params.mtxWorldInverseTranspose = glm::transpose(m_params.mtxWorldInverse);
}

void CUniformTransform::SetTranslate(float x, float y, float z)
{
	m_bDirty = true;
	m_mtxTranslate = glm::translate(glm::mat4(), glm::vec3(x, y, z));
	m_params.mtxWorld = m_mtxTranslate * m_mtxRotate * m_mtxScale;
	m_params.mtxWorldInverse = glm::inverse(m_params.mtxWorld);
	m_params.mtxWorldInverseTranspose = glm::transpose(m_params.mtxWorldInverse);
}

void CUniformTransform::SetTransform(const glm::mat4 &mtxTransform)
{
	m_bDirty = true;
	m_params.mtxWorld = mtxTransform;
	m_params.mtxWorldInverse = glm::inverse(m_params.mtxWorld);
	m_params.mtxWorldInverseTranspose = glm::transpose(m_params.mtxWorldInverse);
}

void CUniformTransform::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformTransform::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformTransform::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
