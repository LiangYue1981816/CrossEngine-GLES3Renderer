#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "UniformBuffer.h"


class CUniformBufferAmbientLight
{
private:
	typedef struct Params {
		glm::vec4 shRed0;
		glm::vec4 shRed1;
		glm::vec4 shRed2;

		glm::vec4 shGreen0;
		glm::vec4 shGreen1;
		glm::vec4 shGreen2;

		glm::vec4 shBlue0;
		glm::vec4 shBlue1;
		glm::vec4 shBlue2;

		glm::mat4 rotationMatrix;
	} Params;


public:
	CUniformBufferAmbientLight(void);
	virtual ~CUniformBufferAmbientLight(void);


public:
	void SetSH(float shRed[9], float shGreen[9], float shBlue[9]);
	void SetSH(float shRed[9], float shGreen[9], float shBlue[9], float angle, float axisx, float axisy, float axisz);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CUniformBuffer m_uniformBuffer;
};