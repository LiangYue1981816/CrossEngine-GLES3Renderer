#include "stdio.h"
#include "stdlib.h"
#include "GfxInstanceBuffer.h"
#include "GfxVertexAttribute.h"


static const int INSTANCE_BUFFER_SIZE = 1 * 1024;

CGfxInstanceBuffer::CGfxInstanceBuffer(void)
	: m_instanceFormat(0)
	, m_instanceBuffer(0)
	, m_instanceBufferSize(0)

	, m_bDirty(false)
{

}

CGfxInstanceBuffer::~CGfxInstanceBuffer(void)
{
	Destroy();
}

void CGfxInstanceBuffer::Clear(void)
{
	if (m_instanceBuffer) {
		m_bDirty = true;
		m_instanceDatas.clear();
	}
}

void CGfxInstanceBuffer::SetInstance(const glm::mat4 &mtxTransform)
{
	if (m_instanceBuffer) {
		m_bDirty = true;
		m_instanceDatas.clear();
		m_instanceDatas.push_back(mtxTransform);
	}
}

void CGfxInstanceBuffer::AddInstance(const glm::mat4 &mtxTransform)
{
	if (m_instanceBuffer) {
		m_bDirty = true;
		m_instanceDatas.push_back(mtxTransform);
	}
}

void CGfxInstanceBuffer::UpdateInstance(void)
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

bool CGfxInstanceBuffer::CreateInstanceBuffer(GLuint format)
{
	m_instanceFormat = format;
	m_instanceBufferSize = INSTANCE_BUFFER_SIZE;

	glGenBuffers(1, &m_instanceBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
	glBufferData(GL_ARRAY_BUFFER, m_instanceBufferSize, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	return true;
}

void CGfxInstanceBuffer::Destroy(void)
{
	if (m_instanceBuffer) {
		glDeleteBuffers(1, &m_instanceBuffer);
	}

	m_instanceFormat = 0;
	m_instanceBuffer = 0;
	m_instanceBufferSize = 0;
}

void CGfxInstanceBuffer::SetupFormat(void) const
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

GLuint CGfxInstanceBuffer::GetInstanceCount(void) const
{
	return m_instanceDatas.size();
}

GLuint CGfxInstanceBuffer::GetInstanceFormat(void) const
{
	return m_instanceFormat;
}

GLuint CGfxInstanceBuffer::GetInstanceBuffer(void) const
{
	return m_instanceBuffer;
}
