#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformTime
{
private:
	typedef struct Params {
		glm::vec4 time;
		glm::vec4 sinTime;
		glm::vec4 cosTime;
		glm::vec4 deltaTime;
	} Params;


public:
	CUniformTime(void);
	virtual ~CUniformTime(void);


public:
	void SetTime(float t, float dt);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CUniformBuffer m_uniformBuffer;
};
