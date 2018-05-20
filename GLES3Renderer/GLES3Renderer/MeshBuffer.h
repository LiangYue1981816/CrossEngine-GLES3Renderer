#pragma once
#include "glew.h"


#define VERTEX_ATTRIBUTE_POSITION  0x00000001
#define VERTEX_ATTRIBUTE_NORMAL    0x00000002
#define VERTEX_ATTRIBUTE_BINORMAL  0x00000004
#define VERTEX_ATTRIBUTE_COLOR     0x00000008
#define VERTEX_ATTRIBUTE_TEXCOORD0 0x00000010
#define VERTEX_ATTRIBUTE_TEXCOORD1 0x00000020
#define VERTEX_ATTRIBUTE_COUNT     6


class CMeshBuffer
{
public:
	CMeshBuffer(void);
	virtual ~CMeshBuffer(void);


public:
	void Bind(void) const;

public:
	bool CreateIndexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLenum type);
	bool CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint format);
	void Destroy(void);

public:
	GLenum GetIndexType(void) const;
	GLuint GetIndexCount(void) const;
	GLuint GetVertexCount(void) const;


private:
	GLenum m_indexType;
	GLuint m_indexCount;
	GLuint m_vertexCount;

private:
	GLuint m_vao;
	GLuint m_indexBuffer;
	GLuint m_vertexBuffer;
};
