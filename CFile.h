#pragma once
#include <stdio.h>

class CFileError {
public:
    virtual const char* GetErrorMsg() = 0;
};

class CFileReadWrite :public  CFileError {
public:
    CFileReadWrite(const char* szFile, int nLine)
    {
        snprintf(m_szError, sizeof(m_szError),
            "CFileReadWrite File:%s  Line:%d", szFile, nLine);
    }

    virtual const char* GetErrorMsg() {
        return m_szError;
    }
private:
    char m_szError[1024];
};

class CFileNullPoint :public  CFileError {
public:
    CFileNullPoint(const char* szFile, int nLine)
    {
        snprintf(m_szError, sizeof(m_szError),
            "CFileNullPoint File:%s  Line:%d", szFile, nLine);
    }

    virtual const char* GetErrorMsg() {
        return m_szError;
    }
private:
    char m_szError[1024];
};

class CFileOutofMemory :public  CFileError {
public:
    CFileOutofMemory(const char* szFile, int nLine)
    {
        snprintf(m_szError, sizeof(m_szError),
            "CFileOutofMemory File:%s  Line:%d", szFile, nLine);
    }

    virtual const char* GetErrorMsg() {
        return m_szError;
    }
private:
    char m_szError[1024];
};

class CFileInvalidPath :public  CFileError {
public:
    CFileInvalidPath(const char* szFile, int nLine)
    {
        snprintf(m_szError, sizeof(m_szError),
            "CFileInvalidPath File:%s  Line:%d", szFile, nLine);
    }

    virtual const char* GetErrorMsg() {
        return m_szError;
    }
private:
    char m_szError[1024];
};

class CFile
{
public:
	CFile();
	CFile(const char* str,const char* mode);
	~CFile();
    void Write(void* buf,size_t size,size_t count);
    size_t Read(void* buf, size_t size, size_t count);
    void Seek(int offset,int whence);
    void Close();
    void Flush();
    bool Feof();

private:
	FILE* m_fd;
};

