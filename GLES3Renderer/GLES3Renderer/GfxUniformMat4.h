#pragma once
#include "gles3/gl3.h"
#include "glm/glm.hpp"


class CGfxUniformBuffer;
class CGfxUniformMat4
{
public:
	CGfxUniformMat4(void);
	virtual ~CGfxUniformMat4(void);


public:
	void SetValue(const float *matrix);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	glm::mat4 m_value;
	CGfxUniformBuffer *m_pUniformBuffer;
};
