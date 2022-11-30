#include <cstdio>

#ifndef FileService_H
#define FileService_H

class FileService
{
public:
	static char* read_file(const char *file_name)
	{
		FILE* file;
		long file_length;
		char* buffer;
		size_t result;

		file = fopen(file_name, "r");
		if (file == NULL) 
		{
			return NULL;
		}

		fseek(file, 0, SEEK_END);
		file_length = ftell(file);
		rewind(file);

		buffer = new char[file_length+1];

		if (buffer == NULL)
		{
			return NULL;
		}

		result = fread(buffer, 1, file_length, file);
		buffer[result] = '\0';
		fclose(file);
		return buffer;
	}


};

#endif

