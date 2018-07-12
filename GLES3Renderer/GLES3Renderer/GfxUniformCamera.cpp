#include "stdio.h"
#include "stdlib.h"
#include "glm/gtc/matrix_transform.hpp"
#include "GfxUniformCamera.h"


CGfxUniformCamera::CGfxUniformCamera(void)
	: m_bDirty(false)
{
	m_uniformBuffer.Create(NULL, sizeof(m_params), true);
}

CGfxUniformCamera::~CGfxUniformCamera(void)
{
	m_uniformBuffer.Destroy();
}

void CGfxUniformCamera::SetPerspective(float fovy, float aspect, float zNear, float zFar)
{
	m_bDirty = true;
	m_params.mtxProjection = glm::perspective(glm::radians(fovy), aspect, zNear, zFar);
}

void CGfxUniformCamera::SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	m_bDirty = true;
	m_params.mtxProjection = glm::ortho(left, right, bottom, top, zNear, zFar);
}

void CGfxUniformCamera::SetLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
	m_bDirty = true;
	m_params.mtxView = glm::lookAt(glm::vec3(eyex, eyey, eyez), glm::vec3(centerx, centery, centerz), glm::vec3(upx, upy, upz));
	m_params.mtxViewInverse = glm::inverse(m_params.mtxView);
	m_params.mtxViewInverseTranspose = glm::transpose(m_params.mtxViewInverse);
}

void CGfxUniformCamera::SetProjectionMatrix(const float *mtxProjection)
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

void CGfxUniformCamera::SetViewMatrix(const float *mtxView)
{
	m_bDirty = true;
	m_params.mtxView[0][0] = mtxView[0];
	m_params.mtxView[0][1] = mtxView[1];
	m_params.mtxView[0][2] = mtxView[2];
	m_params.mtxView[0][3] = mtxView[3];
	m_params.mtxView[1][0] = mtxView[4];
	m_params.mtxView[1][1] = mtxView[5];
	m_params.mtxView[1][2] = mtxView[6];
	m_params.mtxView[1][3] = mtxView[7];
	m_params.mtxView[2][0] = mtxView[8];
	m_params.mtxView[2][1] = mtxView[9];
	m_params.mtxView[2][2] = mtxView[10];
	m_params.mtxView[2][3] = mtxView[11];
	m_params.mtxView[3][0] = mtxView[12];
	m_params.mtxView[3][1] = mtxView[13];
	m_params.mtxView[3][2] = mtxView[14];
	m_params.mtxView[3][3] = mtxView[15];
	m_params.mtxViewInverse = glm::inverse(m_params.mtxView);
	m_params.mtxViewInverseTranspose = glm::transpose(m_params.mtxViewInverse);
}

void CGfxUniformCamera::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_uniformBuffer.SetData(&m_params, sizeof(m_params));
	}
}

GLuint CGfxUniformCamera::GetSize(void) const
{
	return m_uniformBuffer.GetSize();
}

GLuint CGfxUniformCamera::GetBuffer(void) const
{
	return m_uniformBuffer.GetBuffer();
}
