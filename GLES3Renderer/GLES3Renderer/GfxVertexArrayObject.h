#pragma once
#include "glew.h"


class CGfxIndexBuffer;
class CGfxVertexBuffer;
class CGfxInstanceBuffer;
class CGfxVertexArrayObject
{
public:
	CGfxVertexArrayObject(void);
	virtual ~CGfxVertexArrayObject(void);


public:
	bool CreateVertexArrayObject(const CGfxIndexBuffer *pIndexBuffer, const CGfxVertexBuffer *pVertexBuffer, const CGfxInstanceBuffer *pInstanceBuffer);
	void Destroy(void);

public:
	GLuint GetVertexArrayObject(void) const;


private:
	GLuint m_vao;
};
