#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformVec3
{
public:
	CUniformVec3(void);
	virtual ~CUniformVec3(void);


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
