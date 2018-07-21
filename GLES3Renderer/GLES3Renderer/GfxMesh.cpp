#include "stdio.h"
#include "stdlib.h"
#include "GfxUtils.h"
#include "GfxIndexBuffer.h"
#include "GfxVertexBuffer.h"
#include "GfxInstanceBuffer.h"
#include "GfxVertexAttribute.h"
#include "GfxVertexArrayObject.h"
#include "GfxRenderer.h"


CGfxMesh::CGfxMesh(GLuint name)
	: m_name(name)

	, m_pIndexBuffer(NULL)
	, m_pVertexBuffer(NULL)
	, m_pInstanceBuffer(NULL)
	, m_pVertexArrayObject(NULL)

	, refCount(0)
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

GLuint CGfxMesh::GetName(void) const
{
	return m_name;
}

void CGfxMesh::Bind(void) const
{
	if (m_pIndexBuffer->GetIndexBuffer() == 0 || m_pVertexBuffer->GetVertexBuffer() == 0) {
		return;
	}

	glBindVertexArray(0);
	{
		if (m_pInstanceBuffer->GetInstanceBuffer() == 0) {
			m_pInstanceBuffer->CreateInstanceBuffer(INSTANCE_ATTRIBUTE_TRANSFORM);
		}

		if (m_pVertexArrayObject->GetVertexArrayObject() == 0) {
			m_pVertexArrayObject->CreateVertexArrayObject(m_pIndexBuffer, m_pVertexBuffer, m_pInstanceBuffer);
		}

		m_pInstanceBuffer->UpdateInstance();
	}
	glBindVertexArray(m_pVertexArrayObject->GetVertexArrayObject());
}

bool CGfxMesh::Load(const char *szFileName)
{
	enum RawVertexAttribute
	{
		RAW_VERTEX_ATTRIBUTE_POSITION = 1 << 0,
		RAW_VERTEX_ATTRIBUTE_NORMAL = 1 << 1,
		RAW_VERTEX_ATTRIBUTE_BINORMAL = 1 << 3,
		RAW_VERTEX_ATTRIBUTE_COLOR = 1 << 4,
		RAW_VERTEX_ATTRIBUTE_UV0 = 1 << 5,
		RAW_VERTEX_ATTRIBUTE_UV1 = 1 << 6,
	};

	typedef struct MeshHeader
	{
		unsigned int indexBufferSize;
		unsigned int indexBufferOffset;

		unsigned int vertexBufferSize;
		unsigned int vertexBufferOffset;

	} MeshHeader;

	FILE *pFile = NULL;
	void *pIndexBuffer = NULL;
	void *pVertexBuffer = NULL;

	try {
		Free();

		char szFullPath[260];
		CGfxRenderer::GetInstance()->GetMeshFullPath(szFileName, szFullPath);

		pFile = fopen(szFullPath, "rb");
		if (pFile == NULL) throw 0;

		MeshHeader header;
		fread(&header, sizeof(header), 1, pFile);

		unsigned int format = 0;
		fread(&format, sizeof(format), 1, pFile);

		pIndexBuffer = malloc(header.indexBufferSize);
		pVertexBuffer = malloc(header.vertexBufferSize);

		fseek(pFile, header.indexBufferOffset, SEEK_SET);
		fread(pIndexBuffer, header.indexBufferSize, 1, pFile);

		fseek(pFile, header.vertexBufferOffset, SEEK_SET);
		fread(pVertexBuffer, header.vertexBufferSize, 1, pFile);

		if (CreateIndexBuffer(header.indexBufferSize, pIndexBuffer, false, GL_UNSIGNED_INT) == false) throw 1;
		if (CreateVertexBuffer(header.vertexBufferSize, pVertexBuffer, false, format) == false) throw 2;

		free(pVertexBuffer);
		free(pIndexBuffer);
		fclose(pFile);

		return true;
	}
	catch (int) {
		Free();

		if (pVertexBuffer) free(pVertexBuffer);
		if (pIndexBuffer) free(pIndexBuffer);
		if (pFile) fclose(pFile);

		return false;
	}
}

void CGfxMesh::Free(void)
{
	m_pIndexBuffer->Destroy();
	m_pVertexBuffer->Destroy();
	m_pInstanceBuffer->Destroy();
	m_pVertexArrayObject->Destroy();
}

bool CGfxMesh::CreateIndexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLenum type)
{
	return m_pIndexBuffer->CreateIndexBuffer(size, pBuffer, bDynamic, type);
}

bool CGfxMesh::CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint format)
{
	return m_pVertexBuffer->CreateVertexBuffer(size, pBuffer, bDynamic, format);
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

GLuint CGfxMesh::GetVertexFormat(void) const
{
	return m_pVertexBuffer->GetVertexFormat();
}

GLuint CGfxMesh::GetVertexCount(void) const
{
	return m_pVertexBuffer->GetVertexCount();
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
