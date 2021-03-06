#pragma once
#include "gles3/gl3.h"


class CGfxIndexBuffer
{
	friend class CGfxMesh;
	friend class CGfxVertexArrayObject;


private:
	CGfxIndexBuffer(GLenum type);
	virtual ~CGfxIndexBuffer(void);


private:
	void Bind(void) const;
	bool BufferData(size_t size, const void *pBuffer, bool bDynamic);

private:
	GLenum GetIndexType(void) const;
	GLuint GetIndexCount(void) const;
	GLuint GetIndexBuffer(void) const;
	GLuint GetSize(void) const;


private:
	GLenum m_indexType;
	GLuint m_indexBuffer;
	GLuint m_size;
};
