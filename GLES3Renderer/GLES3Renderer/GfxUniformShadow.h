#pragma once
#include "glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "GfxUniformBuffer.h"


class CGfxUniformShadow
{
private:
	typedef struct Params {
		glm::mat4 mtxProjection;
		glm::mat4 mtxView;
		glm::vec2 clip;
	} Params;


public:
	CGfxUniformShadow(void);
	virtual ~CGfxUniformShadow(void);


public:
	void SetOrtho(float left, float right, float bottom, float top, float zNear, float zFar);
	void SetLookat(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	void SetProjectionMatrix(const float *mtxProjection);
	void SetViewMatrix(const float *mtxView);
	void Apply(void);

public:
	GLuint GetSize(void) const;
	GLuint GetBuffer(void) const;


private:
	bool m_bDirty;
	Params m_params;
	CGfxUniformBuffer m_uniformBuffer;
};
