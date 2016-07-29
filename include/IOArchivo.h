
#pragma warning(disable:4514)

#include <stdio.h>

#ifndef  __IOARCHIVO_H__
#define  __IOARCHIVO_H__

namespace IOArchivo{

	typedef FILE* File;

	File OpenFile(File& file, const char* fileName, const char* mode);

	int CloseFile(File file);

	unsigned int ReadFile(File file, char* buffer, unsigned int n);

	unsigned int WriteFile(File file, const char* buffer, unsigned int n);
}

#endif 