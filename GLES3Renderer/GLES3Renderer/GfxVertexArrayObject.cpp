#include "stdio.h"
#include "stdlib.h"
#include "GfxIndexBuffer.h"
#include "GfxVertexBuffer.h"
#include "GfxInstanceBuffer.h"
#include "GfxVertexArrayObject.h"


CGfxVertexArrayObject::CGfxVertexArrayObject(void)
	: m_vao(0)
{

}

CGfxVertexArrayObject::~CGfxVertexArrayObject(void)
{
	Destroy();
}

bool CGfxVertexArrayObject::CreateVertexArrayObject(const CGfxIndexBuffer *pIndexBuffer, const CGfxVertexBuffer *pVertexBuffer, const CGfxInstanceBuffer *pInstanceBuffer)
{
	glGenVertexArrays(1, &m_vao);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindVertexArray(m_vao);
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, pIndexBuffer->GetIndexBuffer());

		glBindBuffer(GL_ARRAY_BUFFER, pVertexBuffer->GetVertexBuffer());
		pVertexBuffer->SetupFormat();

		glBindBuffer(GL_ARRAY_BUFFER, pInstanceBuffer->GetInstanceBuffer());
		pInstanceBuffer->SetupFormat();
	}
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

void CGfxVertexArrayObject::Destroy(void)
{
	if (m_vao) {
		glDeleteVertexArrays(1, &m_vao);
	}

	m_vao = 0;
}

GLuint CGfxVertexArrayObject::GetVertexArrayObject(void) const
{
	return m_vao;
}
