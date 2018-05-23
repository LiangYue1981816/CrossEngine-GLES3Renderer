#include "stdafx.h"
#include "Renderer.h"


class CMesh
{
public:
	CMesh(void);
	virtual ~CMesh(void);


public:
	CIndexBuffer* GetIndexBuffer(void);
	CVertexBuffer* GetVertexBuffer(void);

public:
	bool Load(const char *szFileName);
	void Free(void);

public:
	void SetTransform(const glm::mat4 &mtxTransform);


private:
	CIndexBuffer m_indexBuffer;
	CVertexBuffer m_vertexBuffer;
};