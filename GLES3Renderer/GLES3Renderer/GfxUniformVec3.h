#pragma once
#include "gles3/gl3.h"
#include "glm/glm.hpp"


class CGfxUniformBuffer;
class CGfxUniformVec3
{
public:
	CGfxUniformVec3(void);
	virtual ~CGfxUniformVec3(void);


public:
	void SetValue(float x, float y, float z);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	glm::vec3 m_value;
	CGfxUniformBuffer *m_pUniformBuffer;
};
