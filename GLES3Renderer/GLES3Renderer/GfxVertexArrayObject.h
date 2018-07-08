#pragma once
#include <vector>
#include "glew.h"
#include "glm/glm.hpp"


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
