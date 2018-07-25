#pragma once
#include "gles3/gl3.h"


class CGfxIndexBuffer;
class CGfxVertexBuffer;
class CGfxInstanceBuffer;
class CGfxVertexArrayObject
{
	friend class CGfxMesh;


private:
	CGfxVertexArrayObject(void);
	virtual ~CGfxVertexArrayObject(void);


private:
	bool CreateVertexArrayObject(const CGfxIndexBuffer *pIndexBuffer, const CGfxVertexBuffer *pVertexBuffer, const CGfxInstanceBuffer *pInstanceBuffer);
	void Destroy(void);

private:
	GLuint GetVertexArrayObject(void) const;


private:
	GLuint m_vao;
};
