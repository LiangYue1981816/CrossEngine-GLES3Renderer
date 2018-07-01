#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformVec1
{
public:
	CUniformVec1(void);
	virtual ~CUniformVec1(void);


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
