#include "stdio.h"
#include "stdlib.h"
#include "IndexBuffer.h"
#include "InstanceBuffer.h"
#include "VertexBuffer.h"
#include "VertexArrayObject.h"


CVertexArrayObject::CVertexArrayObject(void)
	: m_vao(0)
{

}

CVertexArrayObject::~CVertexArrayObject(void)
{
	Destroy();
}

void CVertexArrayObject::Bind(void) const
{
	glBindVertexArray(m_vao);
}

bool CVertexArrayObject::CreateVertexArrayObject(const CIndexBuffer *pIndexBuffer, const CVertexBuffer *pVertexBuffer, const CInstanceBuffer *pInstanceBuffer)
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
}

void CVertexArrayObject::Destroy(void)
{
	if (m_vao) {
		glDeleteVertexArrays(1, &m_vao);
	}

	m_vao = 0;
}
