#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "UniformBuffer.h"


class CUniformBufferCamera
{
private:
	typedef struct Params {
		glm::mat4 mtxProjection;
		glm::mat4 mtxView;
		glm::mat4 mtxViewInverse;
		glm::mat4 mtxViewInverseTranspose;
	} Params;


public:
	CUniformBufferCamera(void);
	virtual ~CUniformBufferCamera(void);


public:
	void SetPerspective(float fovy, float aspect, float zNear, float zFar);
	void SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	void SetProjectionMatrix(const float *mtxProjection);
	void SetWorldToViewMatrix(const float *mtxWorldToView);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CUniformBuffer m_uniformBuffer;
};
