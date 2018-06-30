#include "stdio.h"
#include "stdlib.h"
#include "VertexBuffer.h"
#include "VertexAttribute.h"


CVertexBuffer::CVertexBuffer(void)
	: m_vertexCount(0)
	, m_vertexFormat(0)
	, m_vertexBuffer(0)
{

}

CVertexBuffer::~CVertexBuffer(void)
{
	Destroy();
}

bool CVertexBuffer::CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint format)
{
	m_vertexFormat = format;
	m_vertexCount = size / GetVertexStride(format);

	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, pBuffer, bDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CVertexBuffer::Destroy(void)
{
	if (m_vertexBuffer) {
		glDeleteBuffers(1, &m_vertexBuffer);
	}

	m_vertexCount = 0;
	m_vertexFormat = 0;
	m_vertexBuffer = 0;
}

void CVertexBuffer::SetupFormat(void) const
{
	GLuint vertexStride = GetVertexStride(m_vertexFormat);

	for (GLuint indexAttribute = 0; indexAttribute < VERTEX_ATTRIBUTE_COUNT; indexAttribute++) {
		GLuint attribute = (1 << indexAttribute);

		if (m_vertexFormat & attribute) {
			GLuint location = GetVertexAttributeLocation(attribute);
			GLuint components = GetVertexAttributeComponents(attribute);
			GLuint offset = GetVertexAttributeOffset(m_vertexFormat, attribute);

			glEnableVertexAttribArray(location);
			glVertexAttribPointer(location, components, GL_FLOAT, GL_FALSE, vertexStride, (const void *)offset);
			glVertexAttribDivisor(location, 0);
		}
	}
}

GLuint CVertexBuffer::GetVertexCount(void) const
{
	return m_vertexCount;
}

GLuint CVertexBuffer::GetVertexFormat(void) const
{
	return m_vertexFormat;
}

GLuint CVertexBuffer::GetVertexBuffer(void) const
{
	return m_vertexBuffer;
}
