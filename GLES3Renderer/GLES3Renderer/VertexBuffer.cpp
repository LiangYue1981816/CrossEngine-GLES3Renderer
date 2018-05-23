#include "stdio.h"
#include "stdlib.h"
#include "VertexBuffer.h"


struct ATTRIBUTE {
	GLuint flag;
	GLuint size;
	GLuint components;
	GLuint location;
	const char *name;
};

static const ATTRIBUTE vertexAttributes[VERTEX_ATTRIBUTE_COUNT] = {
	{ VERTEX_ATTRIBUTE_POSITION,  4, 3, 0, "inPosition"  },
	{ VERTEX_ATTRIBUTE_NORMAL,    4, 3, 1, "inNormal"    },
	{ VERTEX_ATTRIBUTE_BINORMAL,  4, 3, 2, "inBinormal"  },
	{ VERTEX_ATTRIBUTE_COLOR,     4, 3, 3, "inColor"     },
	{ VERTEX_ATTRIBUTE_TEXCOORD0, 4, 2, 4, "inTexcoord0" },
	{ VERTEX_ATTRIBUTE_TEXCOORD1, 4, 2, 5, "inTexcoord1" },
};

static const ATTRIBUTE instanceAttributes[INSTANCE_ATTRIBUTE_COUNT] = {
	{ INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL0, 4, 4, 8,  "inInstanceTransformMatrixCol0" },
	{ INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL1, 4, 4, 9,  "inInstanceTransformMatrixCol1" },
	{ INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL2, 4, 4, 10, "inInstanceTransformMatrixCol2" },
	{ INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL3, 4, 4, 11, "inInstanceTransformMatrixCol3" },
};

static GLuint GetStride(GLuint format, const ATTRIBUTE *attributes, GLuint count)
{
	GLuint stride = 0;

	for (GLuint indexAttribute = 0; indexAttribute < count; indexAttribute++) {
		if (format & attributes[indexAttribute].flag) {
			stride += attributes[indexAttribute].components * attributes[indexAttribute].size;
		}
	}

	return stride;
}

static GLuint GetAttributeOffset(GLuint format, GLuint attribute, const ATTRIBUTE *attributes, GLuint count)
{
	GLuint offset = 0;

	for (GLuint indexAttribute = 0; indexAttribute < count; indexAttribute++) {
		if (attribute == attributes[indexAttribute].flag) return offset;
		if (format & attributes[indexAttribute].flag) offset += attributes[indexAttribute].components * attributes[indexAttribute].size;
	}

	return -1;
}

static GLuint GetAttributeComponents(GLuint attribute, const ATTRIBUTE *attributes, GLuint count)
{
	for (GLuint indexAttribute = 0; indexAttribute < count; indexAttribute++) {
		if (attribute == attributes[indexAttribute].flag) {
			return attributes[indexAttribute].components;
		}
	}

	return 0;
}

static GLuint GetAttributeLocation(GLuint attribute, const ATTRIBUTE *attributes, GLuint count)
{
	for (GLuint indexAttribute = 0; indexAttribute < count; indexAttribute++) {
		if (attribute == attributes[indexAttribute].flag) {
			return attributes[indexAttribute].location;
		}
	}

	return -1;
}

static GLuint GetVertexStride(GLuint format)
{
	return GetStride(format, vertexAttributes, VERTEX_ATTRIBUTE_COUNT);
}

static GLuint GetVertexAttributeOffset(GLuint format, GLuint attribute)
{
	return GetAttributeOffset(format, attribute, vertexAttributes, VERTEX_ATTRIBUTE_COUNT);
}

static GLuint GetVertexAttributeComponents(GLuint attribute)
{
	return GetAttributeComponents(attribute, vertexAttributes, VERTEX_ATTRIBUTE_COUNT);
}

static GLuint GetVertexAttributeLocation(GLuint attribute)
{
	return GetAttributeLocation(attribute, vertexAttributes, VERTEX_ATTRIBUTE_COUNT);
}

static GLuint GetInstanceStride(GLuint format)
{
	return GetStride(format, instanceAttributes, INSTANCE_ATTRIBUTE_COUNT);
}

static GLuint GetInstanceAttributeOffset(GLuint format, GLuint attribute)
{
	return GetAttributeOffset(format, attribute, instanceAttributes, INSTANCE_ATTRIBUTE_COUNT);
}

static GLuint GetInstanceAttributeComponents(GLuint attribute)
{
	return GetAttributeComponents(attribute, instanceAttributes, INSTANCE_ATTRIBUTE_COUNT);
}

static GLuint GetInstanceAttributeLocation(GLuint attribute)
{
	return GetAttributeLocation(attribute, instanceAttributes, INSTANCE_ATTRIBUTE_COUNT);
}


static const int INSTANCE_BUFFER_SIZE = 4 * 1024;

CVertexBuffer::CVertexBuffer(void)
	: m_vao(0)
	, m_vertexCount(0)
	, m_vertexBuffer(0)
	, m_instanceBuffer(0)
	, m_instanceBufferSize(0)
	, m_bDirty(false)
{

}

CVertexBuffer::~CVertexBuffer(void)
{
	Destroy();
}

void CVertexBuffer::Bind(void)
{
	if (m_bDirty && m_instanceBuffer) {
		m_bDirty = false;

		GLuint size = m_instanceDatas.size() * sizeof(InstanceData);

		if (m_instanceBufferSize < size) {
			m_instanceBufferSize = INSTANCE_BUFFER_SIZE;
			while (m_instanceBufferSize < size) m_instanceBufferSize <<= 1;

			glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
			glBufferData(GL_ARRAY_BUFFER, m_instanceBufferSize, NULL, GL_DYNAMIC_DRAW);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
		glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_instanceDatas.data());
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glBindVertexArray(m_vao);
}

void CVertexBuffer::Clear(void)
{
	if (m_instanceBuffer) {
		m_bDirty = true;
		m_instanceDatas.clear();
	}
}

void CVertexBuffer::SetInstance(const glm::mat4 &mtxTransform)
{
	if (m_instanceBuffer) {
		m_bDirty = true;
		m_instanceDatas.clear();

		InstanceData data;
		data.mtxTransform = mtxTransform;
		m_instanceDatas.push_back(data);
	}
}

void CVertexBuffer::AddInstance(const glm::mat4 &mtxTransform)
{
	if (m_instanceBuffer) {
		m_bDirty = true;

		InstanceData data;
		data.mtxTransform = mtxTransform;
		m_instanceDatas.push_back(data);
	}
}

bool CVertexBuffer::CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint vertexFormat, GLuint instanceFormat)
{
	if (vertexFormat) {
		m_vertexCount = size / GetVertexStride(vertexFormat);

		glGenBuffers(1, &m_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, pBuffer, bDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	if (instanceFormat) {
		m_instanceBufferSize = INSTANCE_BUFFER_SIZE;

		glGenBuffers(1, &m_instanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_instanceBufferSize, NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	{
		if (vertexFormat) {
			glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
			{
				GLuint vertexStride = GetVertexStride(vertexFormat);

				for (GLuint indexAttribute = 0; indexAttribute < VERTEX_ATTRIBUTE_COUNT; indexAttribute++) {
					GLuint attribute = (1 << indexAttribute);

					if (vertexFormat & attribute) {
						GLuint location = GetVertexAttributeLocation(attribute);
						GLuint components = GetVertexAttributeComponents(attribute);
						GLuint offset = GetVertexAttributeOffset(vertexFormat, attribute);

						glEnableVertexAttribArray(location);
						glVertexAttribPointer(location, components, GL_FLOAT, GL_FALSE, vertexStride, (const void *)offset);
						glVertexAttribDivisor(location, 0);
					}
				}
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		if (instanceFormat) {
			glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
			{
				GLuint instanceStride = GetInstanceStride(instanceFormat);

				for (GLuint indexAttribute = 0; indexAttribute < INSTANCE_ATTRIBUTE_COUNT; indexAttribute++) {
					GLuint attribute = (1 << indexAttribute);

					if (instanceFormat & attribute) {
						GLuint location = GetInstanceAttributeLocation(attribute);
						GLuint components = GetInstanceAttributeComponents(attribute);
						GLuint offset = GetInstanceAttributeOffset(instanceFormat, attribute);

						glEnableVertexAttribArray(location);
						glVertexAttribPointer(location, components, GL_FLOAT, GL_FALSE, instanceStride, (const void *)offset);
						glVertexAttribDivisor(location, 1);
					}
				}
			}
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
	glBindVertexArray(0);

	return true;
}

void CVertexBuffer::Destroy(void)
{
	if (m_vao) {
		glDeleteVertexArrays(1, &m_vao);
	}

	if (m_vertexBuffer) {
		glDeleteBuffers(1, &m_vertexBuffer);
	}

	if (m_instanceBuffer) {
		glDeleteBuffers(1, &m_instanceBuffer);
	}

	m_vao = 0;
	m_vertexBuffer = 0;
	m_instanceBuffer = 0;
}

GLuint CVertexBuffer::GetVertexCount(void) const
{
	return m_vertexCount;
}

GLuint CVertexBuffer::GetInstanceCount(void) const
{
	return m_instanceDatas.size();
}
