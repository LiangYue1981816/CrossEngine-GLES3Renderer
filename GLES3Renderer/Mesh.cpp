#include "stdafx.h"


CMesh::CMesh(void)
{

}

CMesh::~CMesh(void)
{
	Free();
}

CIndexBuffer* CMesh::GetIndexBuffer(void)
{
	return &m_indexBuffer;
}

CVertexBuffer* CMesh::GetVertexBuffer(void)
{
	return &m_vertexBuffer;
}

bool CMesh::Load(const char *szFileName)
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

	if (FILE *pFile = fopen(szFileName, "rb")) {
		MeshHeader header;
		fread(&header, sizeof(header), 1, pFile);

		unsigned int format = 0;
		unsigned int rawFormat = 0;
		fread(&rawFormat, sizeof(rawFormat), 1, pFile);
		if (rawFormat & RAW_VERTEX_ATTRIBUTE_POSITION) format |= VERTEX_ATTRIBUTE_POSITION;
		if (rawFormat & RAW_VERTEX_ATTRIBUTE_NORMAL) format |= VERTEX_ATTRIBUTE_NORMAL;
		if (rawFormat & RAW_VERTEX_ATTRIBUTE_BINORMAL) format |= VERTEX_ATTRIBUTE_BINORMAL;
		if (rawFormat & RAW_VERTEX_ATTRIBUTE_COLOR) format |= VERTEX_ATTRIBUTE_COLOR;
		if (rawFormat & RAW_VERTEX_ATTRIBUTE_UV0) format |= VERTEX_ATTRIBUTE_TEXCOORD0;
		if (rawFormat & RAW_VERTEX_ATTRIBUTE_UV1) format |= VERTEX_ATTRIBUTE_TEXCOORD1;

		void *pIndexBuffer = malloc(header.indexBufferSize);
		void *pVertexBuffer = malloc(header.vertexBufferSize);

		fseek(pFile, header.indexBufferOffset, SEEK_SET);
		fread(pIndexBuffer, header.indexBufferSize, 1, pFile);

		fseek(pFile, header.vertexBufferOffset, SEEK_SET);
		fread(pVertexBuffer, header.vertexBufferSize, 1, pFile);

		m_indexBuffer.CreateIndexBuffer(header.indexBufferSize, pIndexBuffer, false, GL_UNSIGNED_INT);
		m_vertexBuffer.CreateVertexBuffer(header.vertexBufferSize, pVertexBuffer, false, format, INSTANCE_ATTRIBUTE_TRANSFORM);

		free(pIndexBuffer);
		free(pVertexBuffer);

		fclose(pFile);

		return true;
	}

	return false;
}

void CMesh::Free(void)
{
	m_indexBuffer.Destroy();
	m_vertexBuffer.Destroy();
}

void CMesh::SetTransform(const glm::mat4 &mtxTransform)
{
	m_vertexBuffer.SetInstance(mtxTransform);
}
