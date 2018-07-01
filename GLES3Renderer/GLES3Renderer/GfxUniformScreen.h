#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformScreen
{
private:
	typedef struct Params {
		glm::vec4 screen;
	} Params;


public:
	CUniformScreen(void);
	virtual ~CUniformScreen(void);


public:
	void SetScreen(float width, float height);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CUniformBuffer m_uniformBuffer;
};
