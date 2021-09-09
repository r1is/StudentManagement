#include "CString.h"

#include <stdio.h>
#include <stdarg.h>


char CString::g_pDef[] = { "null" };

CString::CString()
{
    Init(nullptr);
    AddRef();
}

CString::CString(const CString& obj)
{
    //Init(obj.m_pBuf);
    m_pBuf = obj.m_pBuf;
    m_nBufSize = obj.m_nBufSize;
    m_pRefCount = obj.m_pRefCount;
    AddRef();
    //AllocBuffer(obj.m_nLength + 1);
    //strcpy_s(m_pBuf, m_nBufSize, obj.m_pBuf);
    //m_nLength = obj.m_nLength;
    //CString::CString(obj.m_pBuf); //直接调用构造函数
}

CString::CString(const char* pStr)
{
    Init(pStr);
    AddRef();
}

CString::~CString()
{
    Release();
    //FreeBuffer();
}

const char* CString::GetBuffer(int nPos)
{
    if (m_pBuf == nullptr)
        return g_pDef;

    return m_pBuf + nPos;
}

void CString::Copy(const char* pStr)
{
    //申请空间
    int nLen = strlen(pStr);
    int nNeedSapce = nLen + 1; //需要的空间

    //1.空间不够
    if (m_nBufSize < nNeedSapce) {
        ReAllocBuffer(nNeedSapce);
    }

    //拷贝数据
    strcpy_s(m_pBuf, m_nBufSize, pStr);
    m_nLength = nLen;
}

void CString::Copy(CString& obj)
{
    Copy(obj.GetBuffer(0));
}

CString& CString::Append(const char* pStr)
{
    //申请空间
    int nLen = strlen(pStr);
    int nNeedSapce = nLen + 1 + Length(); //需要的空间

    //1.空间不够
    if (m_nBufSize < nNeedSapce) {
        ReAllocBufferAndCopy(nNeedSapce);
    }

    //拷贝数据
    strcat_s(m_pBuf, m_nBufSize, pStr);
    m_nLength = nNeedSapce - 1;
    return *this;
}

CString& CString::Append(const CString& obj)
{
    Append(obj.GetString());
    return *this;
}


void CString::Append(char ch)
{
    char buf[2] = { ch, '\0' };
    Append(buf);
}

void CString::Append(int n)
{
    CString str;
    str.Foramt("%d", n);
    Append(str);
}

void CString::Append(float f)
{
    CString str;
    str.Foramt("%f", f);
    Append(str);
}

char CString::GetAt(int nPos)
{
    return m_pBuf[nPos];
}


int CString::SubString(const char* pStr)
{
    return strstr(m_pBuf, pStr) - m_pBuf;
}

int CString::Search(const CString& obj)
{
    return 0;
}

int CString::Search(const char* pStr)
{
    return 0;
}

int CString::Search(char ch)
{
    return 0;
}

int CString::ReSearch(const CString& obj)
{
    return 0;
}

int CString::ReSearch(const char* pStr)
{
    return 0;
}

int CString::ReSearch(char ch)
{
    return 0;
}

const char* CString::Split(const char* Seps)
{
    m_pSplitBuf = new char[m_nLength + 1];
    strcpy_s(m_pSplitBuf, m_nLength + 1, m_pBuf);
    const char* token = strtok_s(m_pSplitBuf, Seps, &m_Context);
    return token;
}
const char* CString::NextSplit(const char* Seps) {
    const char*  token = strtok_s(NULL, Seps, &m_Context);
    if (token == nullptr)
        delete[] m_pSplitBuf;

    return token;
}


int CString::Compare(const char* pStr)
{
    return strcmp(pStr, m_pBuf);
}

int CString::Compare(const CString& obj)
{
    return strcmp(obj.m_pBuf, m_pBuf);
}

int CString::Compare(CString& obj1, const CString& obj2) {
    return obj1.Compare(obj2);
    
}

bool CString::Equal(const char* pStr)
{
    return strcmp(pStr, m_pBuf) == 0;
}

bool CString::Equal(const CString& obj)
{
    return strcmp(obj.m_pBuf, m_pBuf) == 0;
}

void CString::Upper()
{
}

void CString::Lower()
{
}

void CString::Foramt(const char* pForamt, ...)
{
    AllocBuffer(1024);

    va_list argList;
    va_start(argList, pForamt);
    vsnprintf_s(m_pBuf, m_nBufSize - 1, m_nBufSize, pForamt, argList);
    va_end(argList);
}

int CString::Length()
{
    return m_nLength;
}

void CString::Init(const char* pStr)
{
    m_pBuf = nullptr;
    m_nBufSize = 0;
    m_Context = nullptr;
    m_pSplitBuf = nullptr;
    m_pRefCount = new int;
    *m_pRefCount = 0;

    if (pStr != nullptr) {
        //申请空间
        int nLen = strlen(pStr);
        int nBufSize = nLen + 1;
        AllocBuffer(nBufSize);

        //拷贝数据
        strcpy_s(m_pBuf, m_nBufSize, pStr);
        m_nLength = nLen;
    }
}

bool CString::AllocBuffer(size_t nSize)
{
    m_pBuf = new char[nSize];
    if (m_pBuf == nullptr)
        return false;

    m_nBufSize = nSize;
    
    return true;
}

bool CString::ReAllocBuffer(size_t nSize)
{
    FreeBuffer();

    return AllocBuffer(nSize);
}

bool CString::ReAllocBufferAndCopy(size_t nSize)
{
    //保存旧的地址
    char* pBuf = m_pBuf;

    //申请新的空间
    if (!AllocBuffer(nSize))
        return false;

    //拷贝旧的数据到新的空间
    strcpy_s(m_pBuf, m_nBufSize, pBuf);

    //释放原来的空间
    delete[] pBuf;

    return true;
}

void CString::FreeBuffer()
{
    if (m_pBuf != nullptr)
        delete[] m_pBuf;
    m_nBufSize = 0;
}
