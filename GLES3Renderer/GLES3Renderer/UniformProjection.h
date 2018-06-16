#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformProjection
{
private:
	typedef struct Params {
		glm::vec4 projection;
	} Params;


public:
	CUniformProjection(void);
	virtual ~CUniformProjection(void);


public:
	void SetProjection(float zNear, float zFar);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CUniformBuffer m_uniformBuffer;
};
