#pragma once
#include "glew.h"
#include "glm/glm.hpp"


class CGfxUniformBuffer;
class CGfxUniformZBuffer
{
private:
	typedef struct Params {
		glm::vec4 zbuffer;
	} Params;


public:
	CGfxUniformZBuffer(void);
	virtual ~CGfxUniformZBuffer(void);


public:
	void SetZBuffer(float zNear, float zFar);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CGfxUniformBuffer *m_pUniformBuffer;
};
