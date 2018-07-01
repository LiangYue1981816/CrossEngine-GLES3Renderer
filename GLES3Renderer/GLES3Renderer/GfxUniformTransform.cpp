#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformTransform.h"


CGfxUniformTransform::CGfxUniformTransform(void)
	: m_bDirty(false)
{
	Identity();
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CGfxUniformTransform::~CGfxUniformTransform(void)
{
	m_uniformBuffer.Destroy();
}

void CGfxUniformTransform::Identity(void)
{
	m_bDirty = true;
	m_mtxScale = glm::scale(glm::mat4(), glm::vec3(1.0f, 1.0f, 1.0f));
	m_mtxRotate = glm::rotate(glm::mat4(), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f));
	m_mtxTranslate = glm::translate(glm::mat4(), glm::vec3(0.0f, 0.0f, 0.0f));
	m_params.mtxWorld = glm::mat4();
	m_params.mtxWorldInverse = glm::mat4();
	m_params.mtxWorldInverseTranspose = glm::mat4();
}

void CGfxUniformTransform::SetScale(float x, float y, float z)
{
	m_bDirty = true;
	m_mtxScale = glm::scale(glm::mat4(), glm::vec3(x, y, z));
	m_params.mtxWorld = m_mtxTranslate * m_mtxRotate * m_mtxScale;
	m_params.mtxWorldInverse = glm::inverse(m_params.mtxWorld);
	m_params.mtxWorldInverseTranspose = glm::transpose(m_params.mtxWorldInverse);
}

void CGfxUniformTransform::SetRotate(float angle, float x, float y, float z)
{
	m_bDirty = true;
	m_mtxRotate = glm::rotate(glm::mat4(), angle, glm::vec3(x, y, z));
	m_params.mtxWorld = m_mtxTranslate * m_mtxRotate * m_mtxScale;
	m_params.mtxWorldInverse = glm::inverse(m_params.mtxWorld);
	m_params.mtxWorldInverseTranspose = glm::transpose(m_params.mtxWorldInverse);
}

void CGfxUniformTransform::SetTranslate(float x, float y, float z)
{
	m_bDirty = true;
	m_mtxTranslate = glm::translate(glm::mat4(), glm::vec3(x, y, z));
	m_params.mtxWorld = m_mtxTranslate * m_mtxRotate * m_mtxScale;
	m_params.mtxWorldInverse = glm::inverse(m_params.mtxWorld);
	m_params.mtxWorldInverseTranspose = glm::transpose(m_params.mtxWorldInverse);
}

void CGfxUniformTransform::SetTransform(const glm::mat4 &mtxTransform)
{
	m_bDirty = true;
	m_params.mtxWorld = mtxTransform;
	m_params.mtxWorldInverse = glm::inverse(m_params.mtxWorld);
	m_params.mtxWorldInverseTranspose = glm::transpose(m_params.mtxWorldInverse);
}

void CGfxUniformTransform::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CGfxUniformTransform::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CGfxUniformTransform::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
