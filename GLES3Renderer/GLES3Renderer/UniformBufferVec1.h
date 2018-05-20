#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformBufferVec1
{
public:
	CUniformBufferVec1(void);
	virtual ~CUniformBufferVec1(void);


public:
	void SetValue(float value);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	float m_value;
	CUniformBuffer m_uniformBuffer;
};
