#pragma once
#include <vector>
#include "glew.h"
#include "glm/glm.hpp"


class CIndexBuffer
{
public:
	CIndexBuffer(void);
	virtual ~CIndexBuffer(void);


public:
	void Bind(void);

public:
	bool CreateIndexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLenum type);
	void Destroy(void);

public:
	GLenum GetIndexType(void) const;
	GLuint GetIndexCount(void) const;


private:
	GLenum m_indexType;
	GLuint m_indexCount;
	GLuint m_indexBuffer;
};
