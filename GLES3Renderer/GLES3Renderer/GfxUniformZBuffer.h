#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "UniformBuffer.h"


class CUniformZBuffer
{
private:
	typedef struct Params {
		glm::vec4 zbuffer;
	} Params;


public:
	CUniformZBuffer(void);
	virtual ~CUniformZBuffer(void);


public:
	void SetZBuffer(float zNear, float zFar);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CUniformBuffer m_uniformBuffer;
};
