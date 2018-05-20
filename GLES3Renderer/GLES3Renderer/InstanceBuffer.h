#pragma once
#include <vector>
#include "glew.h"
#include "glm/glm.hpp"


#define INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL0 0x00000001
#define INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL1 0x00000002
#define INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL2 0x00000004
#define INSTANCE_ATTRIBUTE_TRANSFORM_MATRIX_COL3 0x00000008
#define INSTANCE_ATTRIBUTE_COUNT   4


class CInstanceBuffer
{
private:
	typedef struct InstanceData {
		glm::mat4 mtxTransform;
	} InstanceData;


public:
	CInstanceBuffer(void);
	virtual ~CInstanceBuffer(void);


private:
	bool Create(GLuint size);
	void Destroy(void);

public:
	void Bind(void);

public:
	void Clear(void);
	void AddInstance(const glm::mat4 &mtxTransform);

public:
	GLuint GetCount(void) const;


private:
	bool m_bDirty;
	std::vector<InstanceData> m_datas;

private:
	GLuint m_size;
	GLuint m_buffer;
};
