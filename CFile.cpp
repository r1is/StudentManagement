#define _CRT_SECURE_NO_WARNINGS
#include "CFile.h"

CFile::CFile()
{
}

CFile::CFile(const char* str, const char* mode)
{
	m_fd = fopen(str, mode);
	if(m_fd == NULL)
		throw CFileInvalidPath(__FILE__, __LINE__);
}

CFile::~CFile()
{
}

void CFile::Write(void* buf,size_t size, size_t count)
{
	size_t sSize = fwrite(buf, size, count, m_fd);
	if (sSize <= 0)
		throw CFileReadWrite(__FILE__, __LINE__);
}

size_t CFile::Read(void* buf, size_t size, size_t count)
{
	size_t sSize = fread(buf, size, count, m_fd);
	return sSize;
	//if (sSize <= 0)
		//throw CFileReadWrite(__FILE__, __LINE__);
}

void CFile::Seek(int offset, int whence)
{
	fseek(m_fd, offset, whence);
}

void CFile::Close() {
	if (m_fd != NULL) {
		fclose(m_fd);
	}
}

void CFile::Flush() {
	fflush(m_fd);
}

bool CFile::Feof() {
	if (feof(m_fd))
		return true;
	else
		return false;

}