#pragma once
#include "gles3/gl3.h"
#include "glm/glm.hpp"


class CGfxIndexBuffer;
class CGfxVertexBuffer;
class CGfxInstanceBuffer;
class CGfxVertexArrayObject;
class CGfxMesh
{
	friend class CGfxRenderer;
	friend class CGfxCamera;
	friend class CGfxMeshManager;


private:
	CGfxMesh(GLuint name);
	virtual ~CGfxMesh(void);


public:
	GLuint GetName(void) const;

private:
	void Bind(void) const;

private:
	bool Load(const char *szFileName);
	void Free(void);

	bool CreateIndexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLenum type);
	bool CreateVertexBuffer(size_t size, const void *pBuffer, bool bDynamic, GLuint format);

private:
	void ClearInstance(void);
	void SetInstance(const glm::mat4 &mtxTransform);
	void AddInstance(const glm::mat4 &mtxTransform);

public:
	GLuint GetVertexFormat(void) const;
	GLuint GetVertexCount(void) const;

	GLenum GetIndexType(void) const;
	GLuint GetIndexCount(void) const;

	GLuint GetInstanceCount(void) const;


private:
	GLuint m_name;

private:
	CGfxIndexBuffer *m_pIndexBuffer;
	CGfxVertexBuffer *m_pVertexBuffer;
	CGfxInstanceBuffer *m_pInstanceBuffer;
	CGfxVertexArrayObject *m_pVertexArrayObject;

private:
	GLuint refCount;
};
