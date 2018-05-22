#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformBufferDirectionLight
{
private:
	typedef struct Params {
		glm::vec4 color;
		glm::vec4 direction;
	} Params;


public:
	CUniformBufferDirectionLight(void);
	virtual ~CUniformBufferDirectionLight(void);


public:
	void SetDirection(float x, float y, float z);
	void SetColor(float r, float g, float b);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CUniformBuffer m_uniformBuffer;
};
