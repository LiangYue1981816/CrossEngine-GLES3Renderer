#pragma once
#include <vector>
#include "glew.h"
#include "glm/glm.hpp"


class CVertexArrayObject
{
public:
	CVertexArrayObject(void);
	virtual ~CVertexArrayObject(void);


public:
	bool CreateVertexArrayObject(const CIndexBuffer *pIndexBuffer, const CVertexBuffer *pVertexBuffer, const CInstanceBuffer *pInstanceBuffer);
	void Destroy(void);

public:
	GLuint GetVertexArrayObject(void) const;


private:
	GLuint m_vao;
};
