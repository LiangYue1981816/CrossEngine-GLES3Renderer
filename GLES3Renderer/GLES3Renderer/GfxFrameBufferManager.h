#pragma once
#include <map>
#include "gles3/gl3.h"


class CGfxFrameBuffer;
class CGfxFrameBufferManager
{
	friend class CGfxRenderer;


private:
	CGfxFrameBufferManager(void);
	virtual ~CGfxFrameBufferManager(void);


private:
	CGfxFrameBuffer* CreateFrameBuffer(GLuint width, GLuint height);
	void DestroyFrameBuffer(CGfxFrameBuffer *pFrameBuffer);


private:
	std::map<CGfxFrameBuffer*, CGfxFrameBuffer*> m_pFrameBuffers;
};
