#include "stdio.h"
#include "stdlib.h"
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
