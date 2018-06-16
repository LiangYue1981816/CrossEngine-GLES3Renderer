#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformVec2
{
public:
	CUniformVec2(void);
	virtual ~CUniformVec2(void);


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
