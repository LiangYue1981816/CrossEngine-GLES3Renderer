#pragma once
#include "glew.h"


class CGfxVertexBuffer
{
public:
	CGfxVertexBuffer(void);
	virtual ~CGfxVertexBuffer(void);


public:
	void Bind(void);

public:
	bool CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint format);
	void Destroy(void);

public:
	void SetupFormat(void) const;

public:
	GLuint GetVertexCount(void) const;
	GLuint GetVertexFormat(void) const;
	GLuint GetVertexBuffer(void) const;


private:
	GLuint m_vertexCount;
	GLuint m_vertexFormat;
	GLuint m_vertexBuffer;
};
