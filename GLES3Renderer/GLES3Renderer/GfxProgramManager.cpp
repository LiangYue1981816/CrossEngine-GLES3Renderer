#include "stdio.h"
#include "stdlib.h"
#include "GfxUtils.h"
#include "GfxProgram.h"
#include "GfxProgramManager.h"


CGfxProgramManager::CGfxProgramManager(void)
{

}

CGfxProgramManager::~CGfxProgramManager(void)
{
	for (const auto &itProgram : m_pPrograms) {
		delete itProgram.second;
	}

	m_pPrograms.clear();
}

CGfxProgram* CGfxProgramManager::Create(const char *szVertexFileName, const char *szFragmentFileName)
{
	GLuint64 hashVertex = HashValue(szVertexFileName);
	GLuint64 hashFragment = HashValue(szFragmentFileName);
	GLuint64 hash = hashVertex << 32 | hashFragment;

	if (m_pPrograms[hash] == NULL) {
		m_pPrograms[hash] = new CGfxProgram;
		m_pPrograms[hash]->Create(szVertexFileName, szFragmentFileName);
	}

	return m_pPrograms[hash];
}
