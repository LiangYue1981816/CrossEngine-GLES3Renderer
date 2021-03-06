#include "stdio.h"
#include "stdlib.h"
#include "GfxUniformBuffer.h"
#include "GfxUniformMat4.h"


CGfxUniformMat4::CGfxUniformMat4(void)
	: m_bDirty(false)
	, m_pUniformBuffer(NULL)
{
	m_pUniformBuffer = new CGfxUniformBuffer;
	m_pUniformBuffer->Create(NULL, sizeof(m_value), true);
}

CGfxUniformMat4::~CGfxUniformMat4(void)
{
	m_pUniformBuffer->Destroy();
	delete m_pUniformBuffer;
}

void CGfxUniformMat4::SetValue(const float *matrix)
{
	m_bDirty = true;
	m_value[0][0] = matrix[0];
	m_value[0][1] = matrix[1];
	m_value[0][2] = matrix[2];
	m_value[0][3] = matrix[3];
	m_value[1][0] = matrix[4];
	m_value[1][1] = matrix[5];
	m_value[1][2] = matrix[6];
	m_value[1][3] = matrix[7];
	m_value[2][0] = matrix[8];
	m_value[2][1] = matrix[9];
	m_value[2][2] = matrix[10];
	m_value[2][3] = matrix[11];
	m_value[3][0] = matrix[12];
	m_value[3][1] = matrix[13];
	m_value[3][2] = matrix[14];
	m_value[3][3] = matrix[15];
}

void CGfxUniformMat4::Apply(void)
{
	if (m_bDirty) {
		m_bDirty = false;
		m_pUniformBuffer->SetData(&m_value, sizeof(m_value));
	}
}

GLuint CGfxUniformMat4::GetSize(void) const
{
	return m_pUniformBuffer->GetSize();
}

GLuint CGfxUniformMat4::GetBuffer(void) const
{
	return m_pUniformBuffer->GetBuffer();
}
