#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "GfxUniformBuffer.h"


class CGfxUniformDirectLight
{
private:
	typedef struct Params {
		glm::vec4 color;
		glm::vec4 direction;
	} Params;


public:
	CGfxUniformDirectLight(void);
	virtual ~CGfxUniformDirectLight(void);


public:
	void SetColor(float red, float green, float blue);
	void SetDirection(float x, float y, float z);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CGfxUniformBuffer m_uniformBuffer;
};
