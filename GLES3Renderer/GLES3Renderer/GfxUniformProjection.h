#pragma once
#include "gles/gl3.h"
#include "glm/glm.hpp"


class CGfxUniformBuffer;
class CGfxUniformProjection
{
private:
	typedef struct Params {
		glm::vec4 projection;
	} Params;


public:
	CGfxUniformProjection(void);
	virtual ~CGfxUniformProjection(void);


public:
	void SetProjection(float zNear, float zFar);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CGfxUniformBuffer *m_pUniformBuffer;
};
