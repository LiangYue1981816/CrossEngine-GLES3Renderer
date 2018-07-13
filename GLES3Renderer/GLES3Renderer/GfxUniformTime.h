#pragma once
#include "gles/gl3.h"
#include "glm/glm.hpp"


class CGfxUniformBuffer;
class CGfxUniformTime
{
private:
	typedef struct Params {
		glm::vec4 time;
		glm::vec4 sinTime;
		glm::vec4 cosTime;
		glm::vec4 deltaTime;
	} Params;


public:
	CGfxUniformTime(void);
	virtual ~CGfxUniformTime(void);


public:
	void SetTime(float t, float dt);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CGfxUniformBuffer *m_pUniformBuffer;
};
