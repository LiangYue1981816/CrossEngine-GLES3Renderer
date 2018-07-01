#include "stdio.h"
#include "stdlib.h"
#include "GfxMesh.h"


CGfxMesh::CGfxMesh(void)
	: m_pIndexBuffer(NULL)
	, m_pVertexBuffer(NULL)
	, m_pInstanceBuffer(NULL)
	, m_pVertexArrayObject(NULL)
{
	m_pIndexBuffer = new CGfxIndexBuffer;
	m_pVertexBuffer = new CGfxVertexBuffer;
	m_pInstanceBuffer = new CGfxInstanceBuffer;
	m_pVertexArrayObject = new CGfxVertexArrayObject;
}

CGfxMesh::~CGfxMesh(void)
{
	delete m_pIndexBuffer;
	delete m_pVertexBuffer;
	delete m_pInstanceBuffer;
	delete m_pVertexArrayObject;
}

void CGfxMesh::Bind(void) const
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

bool CGfxMesh::CreateIndexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLenum type)
{
	return m_pIndexBuffer->CreateIndexBuffer(size, pBuffer, bDynamic, type);
}

bool CGfxMesh::CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint format)
{
	return m_pVertexBuffer->CreateVertexBuffer(size, pBuffer, bDynamic, format);
}

void CGfxMesh::Destroy(void)
{
	m_pIndexBuffer->Destroy();
	m_pVertexBuffer->Destroy();
	m_pInstanceBuffer->Destroy();
	m_pVertexArrayObject->Destroy();
}

void CGfxMesh::ClearInstance(void)
{
	m_pInstanceBuffer->Clear();
}

void CGfxMesh::SetInstance(const glm::mat4 &mtxTransform)
{
	m_pInstanceBuffer->SetInstance(mtxTransform);
}

void CGfxMesh::AddInstance(const glm::mat4 &mtxTransform)
{
	m_pInstanceBuffer->AddInstance(mtxTransform);
}

GLenum CGfxMesh::GetIndexType(void) const
{
	return m_pIndexBuffer->GetIndexType();
}

GLuint CGfxMesh::GetIndexCount(void) const
{
	return m_pIndexBuffer->GetIndexCount();
}

GLuint CGfxMesh::GetInstanceCount(void) const
{
	return m_pInstanceBuffer->GetInstanceCount();
}
