#include "stdio.h"
#include "stdlib.h"
#include "UniformBufferCamera.h"


CUniformBufferCamera::CUniformBufferCamera(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CUniformBufferCamera::~CUniformBufferCamera(void)
{
	m_uniformBuffer.Destroy();
}

void CUniformBufferCamera::SetPerspective(float fovy, float aspect, float zNear, float zFar)
{
	m_bDirty = true;
	m_params.mtxProjection = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
}

void CUniformBufferCamera::SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_bDirty = true;
	m_params.mtxProjection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void CUniformBufferCamera::SetLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
	m_bDirty = true;
	m_params.mtxWorldToView = glm::lookAt(glm::vec3(eyex, eyey, eyez), glm::vec3(centerx, centery, centerz), glm::vec3(upx, upy, upz));
	m_params.mtxWorldToViewInverseTranspose = glm::transpose(glm::inverse(m_params.mtxWorldToView));
}

void CUniformBufferCamera::SetProjectionMatrix(const float *mtxProjection)
{
	m_bDirty = true;
	m_params.mtxProjection[0][0] = mtxProjection[0];
	m_params.mtxProjection[0][1] = mtxProjection[1];
	m_params.mtxProjection[0][2] = mtxProjection[2];
	m_params.mtxProjection[0][3] = mtxProjection[3];
	m_params.mtxProjection[1][0] = mtxProjection[4];
	m_params.mtxProjection[1][1] = mtxProjection[5];
	m_params.mtxProjection[1][2] = mtxProjection[6];
	m_params.mtxProjection[1][3] = mtxProjection[7];
	m_params.mtxProjection[2][0] = mtxProjection[8];
	m_params.mtxProjection[2][1] = mtxProjection[9];
	m_params.mtxProjection[2][2] = mtxProjection[10];
	m_params.mtxProjection[2][3] = mtxProjection[11];
	m_params.mtxProjection[3][0] = mtxProjection[12];
	m_params.mtxProjection[3][1] = mtxProjection[13];
	m_params.mtxProjection[3][2] = mtxProjection[14];
	m_params.mtxProjection[3][3] = mtxProjection[15];
}

void CUniformBufferCamera::SetWorldToViewMatrix(const float *mtxWorldToView)
{
	m_bDirty = true;
	m_params.mtxWorldToView[0][0] = mtxWorldToView[0];
	m_params.mtxWorldToView[0][1] = mtxWorldToView[1];
	m_params.mtxWorldToView[0][2] = mtxWorldToView[2];
	m_params.mtxWorldToView[0][3] = mtxWorldToView[3];
	m_params.mtxWorldToView[1][0] = mtxWorldToView[4];
	m_params.mtxWorldToView[1][1] = mtxWorldToView[5];
	m_params.mtxWorldToView[1][2] = mtxWorldToView[6];
	m_params.mtxWorldToView[1][3] = mtxWorldToView[7];
	m_params.mtxWorldToView[2][0] = mtxWorldToView[8];
	m_params.mtxWorldToView[2][1] = mtxWorldToView[9];
	m_params.mtxWorldToView[2][2] = mtxWorldToView[10];
	m_params.mtxWorldToView[2][3] = mtxWorldToView[11];
	m_params.mtxWorldToView[3][0] = mtxWorldToView[12];
	m_params.mtxWorldToView[3][1] = mtxWorldToView[13];
	m_params.mtxWorldToView[3][2] = mtxWorldToView[14];
	m_params.mtxWorldToView[3][3] = mtxWorldToView[15];
	m_params.mtxWorldToViewInverseTranspose = glm::transpose(glm::inverse(m_params.mtxWorldToView));
}

void CUniformBufferCamera::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CUniformBufferCamera::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CUniformBufferCamera::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
