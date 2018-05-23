#pragma once
#include <vector>
#include "glew.h"
#include "glm/glm.hpp"


#define VERTEX_ATTRIBUTE_POSITION  0x00000001
#define VERTEX_ATTRIBUTE_NORMAL    0x00000002
#define VERTEX_ATTRIBUTE_BINORMAL  0x00000004
#define VERTEX_ATTRIBUTE_COLOR     0x00000008
#define VERTEX_ATTRIBUTE_TEXCOORD0 0x00000010
#define VERTEX_ATTRIBUTE_TEXCOORD1 0x00000020
#define VERTEX_ATTRIBUTE_COUNT     6

#define INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL0 0x00000001
#define INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL1 0x00000002
#define INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL2 0x00000004
#define INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL3 0x00000008
#define INSTANCE_ATTRIBUTE_COUNT   4

#define INSTANCE_ATTRIBUTE_TRANSFORM (INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL0 | INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL1 | INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL2 | INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL3)


class CVertexBufferInstance
{
private:
	typedef struct InstanceData {
		glm::mat4 mtxTransform;
	} InstanceData;


public:
	CVertexBufferInstance(void);
	virtual ~CVertexBufferInstance(void);


public:
	void Bind(void);

public:
	void Clear(void);
	void SetInstance(const glm::mat4 &mtxTransform);
	void AddInstance(const glm::mat4 &mtxTransform);

public:
	bool CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint vertexFormat, GLuint instanceFormat);
	void Destroy(void);

public:
	GLuint GetVertexCount(void) const;
	GLuint GetInstanceCount(void) const;


private:
	GLuint m_vao;
	GLuint m_vertexCount;
	GLuint m_vertexBuffer;
	GLuint m_instanceBuffer;
	GLuint m_instanceBufferSize;

private:
	bool m_bDirty;
	std::vector<InstanceData> m_instanceDatas;
};

class CIndexBuffer
{
public:
	CIndexBuffer(void);
	virtual ~CIndexBuffer(void);


public:
	void Bind(void);

public:
	bool CreateIndexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLenum type);
	void Destroy(void);

public:
	GLenum GetIndexType(void) const;
	GLuint GetIndexCount(void) const;


private:
	GLenum m_indexType;
	GLuint m_indexCount;
	GLuint m_indexBuffer;
};
