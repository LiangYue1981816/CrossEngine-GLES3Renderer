#pragma once
#include "gles3/gl3.h"


class CGfxIndexBuffer
{
	friend class CGfxMesh;
	friend class CGfxVertexArrayObject;


private:
	CGfxIndexBuffer(void);
	virtual ~CGfxIndexBuffer(void);


private:
	void Bind(void) const;

private:
	bool CreateIndexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLenum type);
	void Destroy(void);

public:
	GLenum GetIndexType(void) const;
	GLuint GetIndexCount(void) const;
	GLuint GetIndexBuffer(void) const;


private:
	GLenum m_indexType;
	GLuint m_indexCount;
	GLuint m_indexBuffer;
};
