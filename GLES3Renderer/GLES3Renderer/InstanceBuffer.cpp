#include "stdio.h"
#include "stdlib.h"
#include "InstanceBuffer.h"
#include "VertexAttribute.h"


static const int INSTANCE_BUFFER_SIZE = 4 * 1024;

CInstanceBuffer::CInstanceBuffer(void)
	: m_instanceFormat(0)
	, m_instanceBuffer(0)
	, m_instanceBufferSize(0)

	, m_bDirty(false)
{

}

CInstanceBuffer::~CInstanceBuffer(void)
{
	Destroy();
}

void CInstanceBuffer::Clear(void)
{
	if (m_instanceBuffer) {
		m_bDirty = true;
		m_instanceDatas.clear();
	}
}

void CInstanceBuffer::SetInstance(const glm::mat4 &mtxTransform)
{
	if (m_instanceBuffer) {
		m_bDirty = true;
		m_instanceDatas.clear();
		m_instanceDatas.push_back(mtxTransform);
	}
}

void CInstanceBuffer::AddInstance(const glm::mat4 &mtxTransform)
{
	if (m_instanceBuffer) {
		m_bDirty = true;
		m_instanceDatas.push_back(mtxTransform);
	}
}

void CInstanceBuffer::UpdateInstance(void)
{
	if (m_bDirty && m_instanceBuffer) {
		m_bDirty = false;

		GLuint size = m_instanceDatas.size() * sizeof(glm::mat4);

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
}

bool CInstanceBuffer::CreateInstanceBuffer(GLuint format)
{
	m_instanceFormat = format;
	m_instanceBufferSize = INSTANCE_BUFFER_SIZE;

	glGenBuffers(1, &m_instanceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_instanceBufferSize, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CInstanceBuffer::Destroy(void)
{
	if (m_instanceBuffer) {
		glDeleteBuffers(1, &m_instanceBuffer);
	}

	m_instanceFormat = 0;
	m_instanceBuffer = 0;
	m_instanceBufferSize = 0;
}

void CInstanceBuffer::SetupFormat(void) const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
	{
		GLuint instanceStride = GetInstanceStride(m_instanceFormat);

		for (GLuint indexAttribute = 0; indexAttribute < INSTANCE_ATTRIBUTE_COUNT; indexAttribute++) {
			GLuint attribute = (1 << indexAttribute);

			if (m_instanceFormat & attribute) {
				GLuint location = GetInstanceAttributeLocation(attribute);
				GLuint components = GetInstanceAttributeComponents(attribute);
				GLuint offset = GetInstanceAttributeOffset(m_instanceFormat, attribute);

				glEnableVertexAttribArray(location);
				glVertexAttribPointer(location, components, GL_FLOAT, GL_FALSE, instanceStride, (const void *)offset);
				glVertexAttribDivisor(location, 1);
			}
		}
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

GLuint CInstanceBuffer::GetInstanceCount(void) const
{
	return m_instanceDatas.size();
}

GLuint CInstanceBuffer::GetInstanceFormat(void) const
{
	return m_instanceFormat;
}

GLuint CInstanceBuffer::GetInstanceBuffer(void) const
{
	return m_instanceBuffer;
}
