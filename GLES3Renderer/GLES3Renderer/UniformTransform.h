#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "UniformBuffer.h"


class CUniformTransform
{
private:
	typedef struct Params {
		glm::mat4 mtxWorld;
		glm::mat4 mtxWorldInverse;
		glm::mat4 mtxWorldInverseTranspose;
	} Params;


public:
	CUniformTransform(void);
	virtual ~CUniformTransform(void);


public:
	void Identity(void);
	void SetScale(float x, float y, float z);
	void SetRotate(float angle, float x, float y, float z);
	void SetTranslate(float x, float y, float z);
	void SetTransform(const glm::mat4 &mtxTransform);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	glm::mat4 m_mtxScale;
	glm::mat4 m_mtxRotate;
	glm::mat4 m_mtxTranslate;

private:
	bool m_bDirty;
	Params m_params;
	CUniformBuffer m_uniformBuffer;
};
