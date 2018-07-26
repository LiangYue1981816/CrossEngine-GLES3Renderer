#pragma once
#include "gles3/gl3.h"


class CGfxVertexBuffer
{
	friend class CGfxMesh;


private:
	CGfxVertexBuffer(GLuint format);
	virtual ~CGfxVertexBuffer(void);


public:
	void Bind(void) const;
	bool BufferData(size_t size, const void *pBuffer, bool bDynamic);

public:
	GLuint GetVertexCount(void) const;
	GLuint GetVertexFormat(void) const;
	GLuint GetVertexBuffer(void) const;
	GLuint GetSize(void) const;


private:
	GLuint m_vertexFormat;
	GLuint m_vertexBuffer;
	GLuint m_size;
};
