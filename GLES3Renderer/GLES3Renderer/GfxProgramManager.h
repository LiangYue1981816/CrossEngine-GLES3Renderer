#pragma once
#include <map>
#include "glew.h"


class CGfxProgram;
class CGfxProgramManager
{
	friend class CGfxRenderer;


private:
	CGfxProgramManager(void);
	virtual ~CGfxProgramManager(void);


public:
	CGfxProgram* Load(const char *szVertexFileName, const char *szFragmentFileName);


private:
	std::map<GLuint64, CGfxProgram*> m_pPrograms;
};
