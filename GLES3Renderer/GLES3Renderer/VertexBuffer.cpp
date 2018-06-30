#include "stdio.h"
#include "stdlib.h"
#include "VertexBuffer.h"
#include "VertexAttribute.h"


static const int INSTANCE_BUFFER_SIZE = 1 * 1024;

CVertexBuffer::CVertexBuffer(void)
	: m_vao(0)

	, m_vertexFormat(0)
	, m_vertexBuffer(0)
	, m_vertexCount(0)

	, m_instanceFormat(0)
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
	CreateVertexBuffer(size, pBuffer, bDynamic, vertexFormat);
	CreateInstanceBuffer(instanceFormat);
	CreateVertexArrayObject(vertexFormat, instanceFormat);
	return true;
}

void CVertexBuffer::CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint vertexFormat)
{
	if (vertexFormat) {
		m_vertexFormat = vertexFormat;
		m_vertexCount = size / GetVertexStride(vertexFormat);

		glGenBuffers(1, &m_vertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, size, pBuffer, bDynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void CVertexBuffer::CreateInstanceBuffer(GLuint instanceFormat)
{
	if (instanceFormat) {
		m_instanceFormat = instanceFormat;
		m_instanceBufferSize = INSTANCE_BUFFER_SIZE;

		glGenBuffers(1, &m_instanceBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_instanceBuffer);
		glBufferData(GL_ARRAY_BUFFER, m_instanceBufferSize, NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}

void CVertexBuffer::CreateVertexArrayObject(GLuint vertexFormat, GLuint instanceFormat)
{
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);
	{
		SetupFormate(vertexFormat, instanceFormat);
	}
	glBindVertexArray(0);
}

void CVertexBuffer::SetupFormate(GLuint vertexFormat, GLuint instanceFormat)
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
	m_vertexFormat = 0;
	m_vertexBuffer = 0;
	m_instanceFormat = 0;
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

GLuint CVertexBuffer::GetVertexFormat(void) const
{
	return m_vertexFormat;
}

GLuint CVertexBuffer::GetInstanceFormat(void) const
{
	return m_instanceFormat;
}
