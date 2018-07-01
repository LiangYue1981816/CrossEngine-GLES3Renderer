#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "GfxUniformBuffer.h"


class CGfxUniformScreen
{
private:
	typedef struct Params {
		glm::vec4 screen;
	} Params;


public:
	CGfxUniformScreen(void);
	virtual ~CGfxUniformScreen(void);


public:
	void SetScreen(float width, float height);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CGfxUniformBuffer m_uniformBuffer;
};
