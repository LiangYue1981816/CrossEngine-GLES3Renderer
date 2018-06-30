#pragma once
#include <vector>
#include "glew.h"
#include "glm/glm.hpp"


class CInstanceBuffer
{
public:
	CInstanceBuffer(void);
	virtual ~CInstanceBuffer(void);


public:
	void Clear(void);
	void SetInstance(const glm::mat4 &mtxTransform);
	void AddInstance(const glm::mat4 &mtxTransform);
	void UpdateInstance(void);

public:
	bool CreateInstanceBuffer(GLuint format);
	void Destroy(void);

public:
	void SetupFormat(void) const;

public:
	GLuint GetInstanceCount(void) const;
	GLuint GetInstanceFormat(void) const;
	GLuint GetInstanceBuffer(void) const;


private:
	GLuint m_instanceFormat;
	GLuint m_instanceBuffer;
	GLuint m_instanceBufferSize;

private:
	bool m_bDirty;
	std::vector<glm::mat4> m_instanceDatas;
};