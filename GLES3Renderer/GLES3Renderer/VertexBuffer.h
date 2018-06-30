#pragma once
#include <vector>
#include "glew.h"
#include "glm/glm.hpp"


class CVertexBuffer
{
private:
	typedef struct InstanceData {
		glm::mat4 mtxTransform;
	} InstanceData;


public:
	CVertexBuffer(void);
	virtual ~CVertexBuffer(void);


public:
	void Bind(void);

public:
	void Clear(void);
	void SetInstance(const glm::mat4 &mtxTransform);
	void AddInstance(const glm::mat4 &mtxTransform);

public:
	bool CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint vertexFormat, GLuint instanceFormat);
	void Destroy(void);

private:
	void CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint vertexFormat);
	void CreateInstanceBuffer(GLuint instanceFormat);
	void CreateVertexArrayObject(GLuint vertexFormat, GLuint instanceFormat);
	void SetupFormate(GLuint vertexFormat, GLuint instanceFormat);

public:
	GLuint GetVertexCount(void) const;
	GLuint GetInstanceCount(void) const;

public:
	GLuint GetVertexFormat(void) const;
	GLuint GetInstanceFormat(void) const;


private:
	GLuint m_vao;
	GLuint m_vertexCount;
	GLuint m_vertexBuffer;
	GLuint m_instanceBuffer;
	GLuint m_instanceBufferSize;

private:
	GLuint m_vertexFormat;
	GLuint m_instanceFormat;

private:
	bool m_bDirty;
	std::vector<InstanceData> m_instanceDatas;
};
