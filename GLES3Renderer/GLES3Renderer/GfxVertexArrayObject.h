#pragma once
#include "gles3/gl3.h"


class CGfxIndexBuffer;
class CGfxVertexBuffer;
class CGfxInstanceBuffer;
class CGfxVertexArrayObject
{
	friend class CGfxMesh;


private:
	CGfxVertexArrayObject(const CGfxIndexBuffer *pIndexBuffer, const CGfxVertexBuffer *pVertexBuffer, const CGfxInstanceBuffer *pInstanceBuffer);
	virtual ~CGfxVertexArrayObject(void);


public:
	void Bind(void) const;


private:
	GLuint m_vao;
};
