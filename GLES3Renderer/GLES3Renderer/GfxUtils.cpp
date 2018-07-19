#include "stdio.h"
#include "stdlib.h"
#include "windows.h"
#include "GfxUtils.h"


GLuint HashValue(const char *szString)
{
	const char *c = szString;
	GLuint dwHashValue = 0x00000000;

	while (*c) {
		dwHashValue = (dwHashValue << 5) - dwHashValue + (*c == '/' ? '\\' : *c);
		c++;
	}

	return dwHashValue ? dwHashValue : 0xffffffff;
}

void LogOutput(const char *szFormat, ...)
{
	static char szText[128 * 1024];

	va_list vaList;
	va_start(vaList, szFormat);
	vsprintf(szText, szFormat, vaList);
	va_end(vaList);

#ifdef _WIN32

	OutputDebugString(szText);

#else

	printf(szText);

#endif
}
