#include <cstdio>

#ifndef FileService_H
#define FileService_H

class FileService
{
public:
	static char* read_file(const char* file_name)
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

	static bool save_file(const char* file_name, const char* text_to_save, int text_length)
	{
		FILE* file;
		file = fopen(file_name, "w");

		if (file == NULL)
		{
			return false;
		}

		fwrite(text_to_save, sizeof(char), text_length, file);
		fclose(file);

		return true;
	}

	static bool append_file(const char* file_name, const char* text_to_save, int text_length)
	{
		FILE* file;
		file = fopen(file_name, "a");

		if (file == NULL)
		{
			return false;
		}

		fwrite(text_to_save, sizeof(char), text_length, file);
		fclose(file);

		return true;
	}
};
#endif