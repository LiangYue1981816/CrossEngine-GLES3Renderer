#pragma once
#include "glew.h"
#include "glm/glm.hpp"


class CGfxUniformBuffer;
class CGfxUniformFog
{
private:
	typedef struct Params {
		glm::vec4 color;
		glm::vec4 heightDensity;
		glm::vec4 distanceDensity;
	} Params;


public:
	CGfxUniformFog(void);
	virtual ~CGfxUniformFog(void);


public:
	void SetColor(float red, float green, float blue);
	void SetHeightDensity(float startHeight, float endHeight, float density);
	void SetDistanceDensity(float startDistance, float endDistance, float density);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CGfxUniformBuffer *m_pUniformBuffer;
};
