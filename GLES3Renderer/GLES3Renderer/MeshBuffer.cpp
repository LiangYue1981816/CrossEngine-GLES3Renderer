#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "MeshBuffer.h"


struct VERTEX_ATTRIBUTE {
	GLuint flag;
	GLuint size;
	GLuint location;
	const char *name;
};

static const VERTEX_ATTRIBUTE vertexAttributes[VERTEX_ATTRIBUTE_COUNT] = {
	{ VERTEX_ATTRIBUTE_POSITION,  3, 0, "inPosition"  },
	{ VERTEX_ATTRIBUTE_NORMAL,    3, 1, "inNormal"    },
	{ VERTEX_ATTRIBUTE_BINORMAL,  3, 2, "inBinormal"  },
	{ VERTEX_ATTRIBUTE_COLOR,     3, 3, "inColor"     },
	{ VERTEX_ATTRIBUTE_TEXCOORD0, 2, 4, "inTexcoord0" },
	{ VERTEX_ATTRIBUTE_TEXCOORD1, 2, 5, "inTexcoord1" },
};

static GLuint GetVertexStride(GLuint format)
{
	GLuint stride = 0;

	for (GLuint indexAttribute = 0; indexAttribute < VERTEX_ATTRIBUTE_COUNT; indexAttribute++) {
		if (format & vertexAttributes[indexAttribute].flag) {
			stride += vertexAttributes[indexAttribute].size * 4;
		}
	}

	return stride;
}

static GLuint GetVertexAttributeOffset(GLuint format, GLuint attribute)
{
	GLuint offset = 0;

	for (GLuint indexAttribute = 0; indexAttribute < VERTEX_ATTRIBUTE_COUNT; indexAttribute++) {
		if (attribute == vertexAttributes[indexAttribute].flag) return offset;
		if (format & vertexAttributes[indexAttribute].flag) offset += vertexAttributes[indexAttribute].size * 4;
	}

	return -1;
}

static GLuint GetVertexAttributeSize(GLuint attribute)
{
	for (GLuint indexAttribute = 0; indexAttribute < VERTEX_ATTRIBUTE_COUNT; indexAttribute++) {
		if (attribute == vertexAttributes[indexAttribute].flag) {
			return vertexAttributes[indexAttribute].size;
		}
	}

	return 0;
}

static GLuint GetVertexAttributeLocation(GLuint attribute)
{
	for (GLuint indexAttribute = 0; indexAttribute < VERTEX_ATTRIBUTE_COUNT; indexAttribute++) {
		if (attribute == vertexAttributes[indexAttribute].flag) {
			return vertexAttributes[indexAttribute].location;
		}
	}

	return -1;
}


CMeshBuffer::CMeshBuffer(void)
	: m_vao(0)
	, m_indexBuffer(0)
	, m_vertexBuffer(0)

	, m_indexType(GL_UNSIGNED_SHORT)
	, m_indexCount(0)
	, m_vertexCount(0)
{

}

CMeshBuffer::~CMeshBuffer(void)
{
	Destroy();
}

void CMeshBuffer::Bind(void) const
{
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
}

bool CMeshBuffer::CreateIndexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLenum type)
{
	m_indexType = type;
	m_indexCount = size / (m_indexType == GL_UNSIGNED_SHORT ? 2 : 4);

	glGenBuffers(1, &m_indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, pBuffer, bDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

bool CMeshBuffer::CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint format)
{
	glGenBuffers(1, &m_vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, pBuffer, bDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	GLsizei stride = GetVertexStride(format);
	m_vertexCount = size / stride;

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
	{
		for (GLuint indexAttribute = 0; indexAttribute < VERTEX_ATTRIBUTE_COUNT; indexAttribute++) {
			GLuint attribute = (1 << indexAttribute);

			if (format & attribute) {
				GLuint location = GetVertexAttributeLocation(attribute);
				GLuint size = GetVertexAttributeSize(attribute);
				GLuint offset = GetVertexAttributeOffset(format, attribute);

				glEnableVertexAttribArray(location);
				glVertexAttribPointer(location, size, GL_FLOAT, GL_FALSE, stride, (const void *)offset);
			}
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	return true;
}

void CMeshBuffer::Destroy(void)
{
	if (m_vao) {
		glDeleteVertexArrays(1, &m_vao);
	}

	if (m_indexBuffer) {
		glDeleteBuffers(1, &m_indexBuffer);
	}

	if (m_vertexBuffer) {
		glDeleteBuffers(1, &m_vertexBuffer);
	}

	m_vao = 0;
	m_indexBuffer = 0;
	m_vertexBuffer = 0;
}

GLenum CMeshBuffer::GetIndexType(void) const
{
	return m_indexType;
}

GLuint CMeshBuffer::GetIndexCount(void) const
{
	return m_indexCount;
}

GLuint CMeshBuffer::GetVertexCount(void) const
{
	return m_vertexCount;
}
