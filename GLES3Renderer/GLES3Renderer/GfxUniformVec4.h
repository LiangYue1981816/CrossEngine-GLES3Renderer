#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformVec4
{
public:
	CUniformVec4(void);
	virtual ~CUniformVec4(void);


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
