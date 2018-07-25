#pragma once
#include <vector>
#include "gles3/gl3.h"
#include "glm/glm.hpp"


class CGfxInstanceBuffer
{
	friend class CGfxMesh;
	friend class CGfxVertexArrayObject;


private:
	CGfxInstanceBuffer(void);
	virtual ~CGfxInstanceBuffer(void);


private:
	void Bind(void) const;
	void SetupFormat(void) const;

private:
	bool CreateInstanceBuffer(GLuint format);
	void Destroy(void);

public:
	void Clear(void);
	void SetInstance(const glm::mat4 &mtxTransform);
	void AddInstance(const glm::mat4 &mtxTransform);
	void UpdateInstance(void);

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
