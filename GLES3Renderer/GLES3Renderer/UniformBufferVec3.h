#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformBufferVec3
{
public:
	CUniformBufferVec3(void);
	virtual ~CUniformBufferVec3(void);


public:
	void SetValue(float x, float y, float z);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	glm::vec3 m_value;
	CUniformBuffer m_uniformBuffer;
};
