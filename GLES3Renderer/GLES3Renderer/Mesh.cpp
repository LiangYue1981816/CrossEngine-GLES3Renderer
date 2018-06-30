#include "stdio.h"
#include "stdlib.h"
#include "Mesh.h"
#include "VertexAttribute.h"


CMesh::CMesh(void)
	: m_pIndexBuffer(NULL)
	, m_pVertexBuffer(NULL)
	, m_pInstanceBuffer(NULL)
	, m_pVertexArrayObject(NULL)
{
	m_pIndexBuffer = new CIndexBuffer;
	m_pVertexBuffer = new CVertexBuffer;
	m_pInstanceBuffer = new CInstanceBuffer;
	m_pVertexArrayObject = new CVertexArrayObject;
}

CMesh::~CMesh(void)
{
	delete m_pIndexBuffer;
	delete m_pVertexBuffer;
	delete m_pInstanceBuffer;
	delete m_pVertexArrayObject;
}

void CMesh::Bind(void) const
{
	if (m_pIndexBuffer->GetIndexBuffer() == 0 || m_pVertexBuffer->GetVertexBuffer() == 0) {
		return;
	}

	if (m_pInstanceBuffer->GetInstanceBuffer() == 0) {
		m_pInstanceBuffer->CreateInstanceBuffer(INSTANCE_ATTRIBUTE_TRANSFORM);
	}

	if (m_pVertexArrayObject->GetVertexArrayObject() == 0) {
		m_pVertexArrayObject->CreateVertexArrayObject(m_pIndexBuffer, m_pVertexBuffer, m_pInstanceBuffer);
	}

	m_pInstanceBuffer->UpdateInstance();
	glBindVertexArray(m_pVertexArrayObject->GetVertexArrayObject());
}

bool CMesh::CreateIndexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLenum type)
{
	return m_pIndexBuffer->CreateIndexBuffer(size, pBuffer, bDynamic, type);
}

bool CMesh::CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint format)
{
	return m_pVertexBuffer->CreateVertexBuffer(size, pBuffer, bDynamic, format);
}

void CMesh::Destroy(void)
{
	m_pIndexBuffer->Destroy();
	m_pVertexBuffer->Destroy();
	m_pInstanceBuffer->Destroy();
	m_pVertexArrayObject->Destroy();
}

void CMesh::ClearInstance(void)
{
	m_pInstanceBuffer->Clear();
}

void CMesh::SetInstance(const glm::mat4 &mtxTransform)
{
	m_pInstanceBuffer->SetInstance(mtxTransform);
}

void CMesh::AddInstance(const glm::mat4 &mtxTransform)
{
	m_pInstanceBuffer->AddInstance(mtxTransform);
}
