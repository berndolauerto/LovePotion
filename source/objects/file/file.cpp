#include "runtime.h"
#include <sys/stat.h>

#include "file.h"

File::File(const char * path)
{
	this->path = path;
	this->open = false;
}

long File::GetSize()
{
	long size = 0;
	
	fseek(this->fileHandle, 0, SEEK_END);
	size = ftell(this->fileHandle);
	rewind(this->fileHandle);

	return size;
}

const char * File::GetMode()
{
	return this->mode;
}

bool File::IsOpen()
{
	return this->open;
}

bool File::Open(const char * mode)
{
	printf("%s: %s\n", this->path, mode);
	this->fileHandle = fopen(this->path, mode);

	if (!this->fileHandle)
	{
		fclose(this->fileHandle);
		return false;
	}

	this->mode = mode;
	this->open = true;

	return true;
}

void File::Write(const char * data, size_t length)
{
	if (!this->open || (strncmp(this->mode, "w", 1) != 0))
		return;

	fwrite(data, 1, length, this->fileHandle);
}

void File::Flush()
{
	fflush(this->fileHandle);
}

void File::Close()
{
	
	fclose(this->fileHandle);
}

char * File::Read()
{
	if (!this->open || (strncmp(this->mode, "r", 1) != 0))
		return NULL;

	char * buffer;

	long size = this->GetSize();

	buffer = (char *)malloc(size * sizeof(char));

	fread(buffer, 1, size, this->fileHandle);

	buffer[size] = '\0';

	return buffer;
}