#pragma once
#include <vector>
#include "gles3/gl3.h"
#include "glm/glm.hpp"


class CGfxInstanceBuffer
{
	friend class CGfxMesh;
	friend class CGfxVertexArrayObject;


private:
	CGfxInstanceBuffer(GLuint format);
	virtual ~CGfxInstanceBuffer(void);


private:
	void Bind(void) const;

private:
	void SetInstance(const glm::mat4 &mtxTransform);
	void AddInstance(const glm::mat4 &mtxTransform);
	void ClearInstance(void);
	void UpdateInstance(void);

private:
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
