#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformBufferVec2
{
public:
	CUniformBufferVec2(void);
	virtual ~CUniformBufferVec2(void);


public:
	void SetValue(float x, float y);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	glm::vec2 m_value;
	CUniformBuffer m_uniformBuffer;
};
