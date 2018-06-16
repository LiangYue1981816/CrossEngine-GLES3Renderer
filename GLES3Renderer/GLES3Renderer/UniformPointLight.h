#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformPointLight
{
private:
	typedef struct Params {
		glm::vec4 color;
		glm::vec4 position;
	} Params;


public:
	CUniformPointLight(void);
	virtual ~CUniformPointLight(void);


public:
	void SetPosition(float x, float y, float z);
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
