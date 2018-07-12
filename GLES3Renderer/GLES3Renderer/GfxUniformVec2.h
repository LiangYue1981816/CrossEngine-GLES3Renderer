#pragma once
#include "glew.h"
#include "glm/glm.hpp"


class CGfxUniformBuffer;
class CGfxUniformVec2
{
public:
	CGfxUniformVec2(void);
	virtual ~CGfxUniformVec2(void);


public:
	void SetValue(float x, float y);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	glm::vec2 m_value;
	CGfxUniformBuffer *m_pUniformBuffer;
};
