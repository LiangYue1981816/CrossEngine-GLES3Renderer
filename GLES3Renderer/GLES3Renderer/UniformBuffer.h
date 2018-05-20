#pragma once
#include "glew.h"


class CUniformBuffer
{
public:
	CUniformBuffer(void);
	virtual ~CUniformBuffer(void);


public:
	bool Create(const void *pBuffer, size_t size, bool bDynamic);
	void Destroy(void);
	bool SetData(const void *pBuffer, size_t size, size_t offset = 0);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	GLuint m_size;
	GLuint m_buffer;
};
