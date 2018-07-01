#include "stdafx.h"
#include "GfxRenderer.h"


class CMesh
{
public:
	CMesh(void);
	virtual ~CMesh(void);


public:
	CGfxMesh* GetMesh(void);

public:
	bool Load(const char *szFileName);
	void Free(void);

public:
	void SetTransform(const glm::mat4 &mtxTransform);


private:
	CGfxMesh m_mesh;
};