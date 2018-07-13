#pragma once
#include "gles/gl3.h"


class CGfxIndexBuffer
{
public:
	CGfxIndexBuffer(void);
	virtual ~CGfxIndexBuffer(void);


public:
	void Bind(void);

public:
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
