#pragma once
#include <vector>
#include "gles3/gl3.h"
#include "glm/glm.hpp"


class CGfxInstanceBuffer
{
	friend class CGfxMesh;


private:
	CGfxInstanceBuffer(GLuint format);
	virtual ~CGfxInstanceBuffer(void);


public:
	void Bind(void) const;

public:
	void Clear(void);
	void SetInstance(const glm::mat4 &mtxTransform);
	void AddInstance(const glm::mat4 &mtxTransform);
	void UpdateInstance(void);

public:
	GLuint GetInstanceCount(void) const;
	GLuint GetInstanceFormat(void) const;
	GLuint GetInstanceBuffer(void) const;
	GLuint GetSize(void) const;


private:
	GLuint m_instanceFormat;
	GLuint m_instanceBuffer;
	GLuint m_size;

private:
	bool m_bDirty;
	std::vector<glm::mat4> m_instanceDatas;
};
