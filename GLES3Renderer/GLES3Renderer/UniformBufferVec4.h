#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformBufferVec4
{
public:
	CUniformBufferVec4(void);
	virtual ~CUniformBufferVec4(void);


public:
	void SetValue(float x, float y, float z, float w);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	glm::vec4 m_value;
	CUniformBuffer m_uniformBuffer;
};
