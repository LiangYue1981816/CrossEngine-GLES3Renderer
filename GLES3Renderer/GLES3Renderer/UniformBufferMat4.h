#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformBufferMat4
{
public:
	CUniformBufferMat4(void);
	virtual ~CUniformBufferMat4(void);


public:
	void SetValue(const float *matrix);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	glm::mat4 m_value;
	CUniformBuffer m_uniformBuffer;
};
