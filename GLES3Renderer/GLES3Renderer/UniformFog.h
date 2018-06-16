#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "UniformBuffer.h"


class CUniformFog
{
private:
	typedef struct Params {
		glm::vec4 color;
		glm::vec4 heightDensity;
		glm::vec4 distanceDensity;
	} Params;


public:
	CUniformFog(void);
	virtual ~CUniformFog(void);


public:
	void SetColor(float r, float g, float b);
	void SetHeightDensity(float startHeight, float endHeight, float density);
	void SetDistanceDensity(float startDistance, float endDistance, float density);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CUniformBuffer m_uniformBuffer;
};
