#pragma once
#include "gles3/gl3.h"


class CGfxIndexBuffer
{
	friend class CGfxMesh;


private:
	CGfxIndexBuffer(GLenum type);
	virtual ~CGfxIndexBuffer(void);


public:
	void Bind(void) const;
	bool BufferData(size_t size, const void *pBuffer, bool bDynamic);

public:
	GLenum GetIndexType(void) const;
	GLuint GetIndexCount(void) const;
	GLuint GetIndexBuffer(void) const;
	GLuint GetSize(void) const;


private:
	GLenum m_indexType;
	GLuint m_indexBuffer;
	GLuint m_size;
};
