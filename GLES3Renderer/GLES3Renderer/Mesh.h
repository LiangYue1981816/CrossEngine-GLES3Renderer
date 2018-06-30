#pragma once
#include <vector>
#include "glew.h"
#include "glm/glm.hpp"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "InstanceBuffer.h"
#include "VertexArrayObject.h"


class CMesh
{
public:
	CMesh(void);
	virtual ~CMesh(void);


public:
	void Bind(void) const;

public:
	bool CreateIndexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLenum type);
	bool CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint format);
	void Destroy(void);

public:
	void ClearInstance(void);
	void SetInstance(const glm::mat4 &mtxTransform);
	void AddInstance(const glm::mat4 &mtxTransform);


private:
	CIndexBuffer *m_pIndexBuffer;
	CVertexBuffer *m_pVertexBuffer;
	CInstanceBuffer *m_pInstanceBuffer;
	CVertexArrayObject *m_pVertexArrayObject;
};
