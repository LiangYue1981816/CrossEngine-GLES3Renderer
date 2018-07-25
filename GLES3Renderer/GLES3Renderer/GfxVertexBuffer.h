#pragma once
#include "gles3/gl3.h"


class CGfxVertexBuffer
{
	friend class CGfxMesh;
	friend class CGfxVertexArrayObject;


private:
	CGfxVertexBuffer(void);
	virtual ~CGfxVertexBuffer(void);


private:
	void Bind(void) const;
	void SetupFormat(void) const;

private:
	bool CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint format);
	void Destroy(void);

public:
	GLuint GetVertexCount(void) const;
	GLuint GetVertexFormat(void) const;
	GLuint GetVertexBuffer(void) const;


private:
	GLuint m_vertexCount;
	GLuint m_vertexFormat;
	GLuint m_vertexBuffer;
};
