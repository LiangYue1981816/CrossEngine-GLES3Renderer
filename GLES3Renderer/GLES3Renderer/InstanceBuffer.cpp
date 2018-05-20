#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "InstanceBuffer.h"


struct INSTANCE_ATTRIBUTE {
	GLuint flag;
	GLuint size;
	GLuint offset;
	GLuint location;
	const char *name;
};

static const INSTANCE_ATTRIBUTE instanceAttributes[INSTANCE_ATTRIBUTE_COUNT] = {
	{ INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL0, 4, 0,  8,  "inInstanceTransformMatrixCol0" },
	{ INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL1, 4, 16, 9,  "inInstanceTransformMatrixCol1" },
	{ INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL2, 4, 32, 10, "inInstanceTransformMatrixCol2" },
	{ INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL3, 4, 48, 11, "inInstanceTransformMatrixCol3" },
};

static const int INSTANCE_BUFFER_SIZE = 4 * 1024;


CInstanceBuffer::CInstanceBuffer(void)
	: m_size(0)
	, m_buffer(0)

	, m_bDirty(false)
{
	Create(INSTANCE_BUFFER_SIZE);
}

CInstanceBuffer::~CInstanceBuffer(void)
{
	Destroy();
}

bool CInstanceBuffer::Create(GLuint size)
{
	m_size = size;

	glGenBuffers(1, &m_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);
	glBufferData(GL_ARRAY_BUFFER, m_size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

void CInstanceBuffer::Destroy(void)
{
	if (m_buffer) {
		glDeleteBuffers(1, &m_buffer);
	}

	m_buffer = 0;
}

void CInstanceBuffer::Bind(void)
{
	glBindBuffer(GL_ARRAY_BUFFER, m_buffer);

	if (m_bDirty) {
		m_bDirty = false;

		GLuint size = m_datas.size() * sizeof(InstanceData);

		if (m_size < size) {
			m_size = INSTANCE_BUFFER_SIZE;
			while (m_size < size) m_size <<= 1;

			glBufferData(GL_ARRAY_BUFFER, m_size, NULL, GL_DYNAMIC_DRAW);
		}

		glBufferSubData(GL_ARRAY_BUFFER, 0, size, m_datas.data());
	}

	for (GLuint indexAttribute = 0; indexAttribute < INSTANCE_ATTRIBUTE_COUNT; indexAttribute++) {
		glEnableVertexAttribArray(instanceAttributes[indexAttribute].location);
		glVertexAttribPointer(instanceAttributes[indexAttribute].location, instanceAttributes[indexAttribute].size, GL_FLOAT, GL_FALSE, sizeof(InstanceData), (const void *)instanceAttributes[indexAttribute].offset);
		glVertexAttribDivisor(instanceAttributes[indexAttribute].location, 1);
	}
}

void CInstanceBuffer::Clear(void)
{
	m_bDirty = true;
	m_datas.clear();
}

void CInstanceBuffer::AddInstance(const glm::mat4 &mtxTransform)
{
	m_bDirty = true;

	InstanceData data;
	data.mtxTransform = mtxTransform;
	m_datas.push_back(data);
}

GLuint CInstanceBuffer::GetCount(void) const
{
	return m_datas.size();
}
