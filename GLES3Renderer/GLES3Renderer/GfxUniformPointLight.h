#pragma once
#include "gles/gl3.h"
#include "glm/glm.hpp"


class CGfxUniformBuffer;
class CGfxUniformPointLight
{
private:
	typedef struct Params {
		glm::vec4 color;
		glm::vec4 position;
		glm::vec4 attenuation;
	} Params;


public:
	CGfxUniformPointLight(void);
	virtual ~CGfxUniformPointLight(void);


public:
	void SetColor(float red, float green, float blue);
	void SetPosition(float x, float y, float z);
	void SetAttenuation(float linear, float square, float constant);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CGfxUniformBuffer *m_pUniformBuffer;
};
