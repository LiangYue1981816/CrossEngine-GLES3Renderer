#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "GfxInstanceBuffer.h"
#include "GfxIndexBuffer.h"
#include "GfxVertexBuffer.h"
#include "GfxVertexArrayObject.h"
#include "GfxVertexAttribute.h"


class CGfxMesh
{
public:
	CGfxMesh(void);
	virtual ~CGfxMesh(void);


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

public:
	GLenum GetIndexType(void) const;
	GLuint GetIndexCount(void) const;
	GLuint GetInstanceCount(void) const;


private:
	CGfxIndexBuffer *m_pIndexBuffer;
	CGfxVertexBuffer *m_pVertexBuffer;
	CGfxInstanceBuffer *m_pInstanceBuffer;
	CGfxVertexArrayObject *m_pVertexArrayObject;
};
