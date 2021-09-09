#pragma once
#include <string.h>

class CString  //GBK UTF-8 ANSI UNICODE
{
public:
    CString();
    CString(const CString& obj);
    CString(const char* pStr);
    ~CString();

    static CString ValueOf(int num) {
        CString str;
        str.Foramt("%d", num);
        return str;
    }

    static CString ValueOf(float num) {
        CString str;
        str.Foramt("%f", num);
        return str;
    }

    //增加引用计数
    int AddRef() {
        if (m_pRefCount == nullptr) {
            m_pRefCount = new int(1);
            return *m_pRefCount;
        }

        (*m_pRefCount)++;
        return (*m_pRefCount);
    }

    //减少引用计数
    int Release() {
        if (m_pRefCount == nullptr)
            return 0;
        --(*m_pRefCount);
        if ((*m_pRefCount) == 0) {
            FreeBuffer();
        }

        return (*m_pRefCount);
    }
    void SetAt(int nIndex, char ch) {
        //写时拷贝(数据修改，深拷贝 WriteCopy) 引用计数(RefCount)
        if (*m_pRefCount > 1) {  //多人使用
            char* pNewBuf = new char[m_nBufSize];
            strcpy_s(pNewBuf, m_nBufSize, m_pBuf);
            m_pBuf = pNewBuf;

            //释放原来的计数器
            Release();

            //申请新的计数器
            m_pRefCount = new int;
            *m_pRefCount = 0;

            AddRef();
        }

        m_pBuf[nIndex] = ch;
    }

    bool operator==(const CString& str) {
        if (strcmp(m_pBuf, str.m_pBuf) == 0)
            return true;
        else
            return false;
    }
    bool operator==(const char* str) {
        if (strcmp(m_pBuf, str) == 0)
            return true;
        else
            return false;
    }

    bool operator!=(const CString& str) {
        if (strcmp(m_pBuf, str.m_pBuf) != 0)
            return true;
        else
            return false;
    }
    bool operator!=(const char* str) {
        if (strcmp(m_pBuf, str) != 0)
            return true;
        else
            return false;
    }
    /*CString& operator>>(const CString& str) {
        int nSize = str.m_nLength + 1;
        m_pBuf = new char[nSize];
        strcpy_s(m_pBuf, nSize, str.m_pBuf);
        m_nBufSize = nSize;
        return *this;
    }
    CString& operator>>(const char* str) {
        int nSize = strlen(str) + 1;
        m_pBuf = new char[nSize];
        strcpy_s(m_pBuf, nSize, str);
        m_nBufSize = nSize;
        return *this;
    }*/
    
    bool operator>(const CString& str) {
        if (strcmp(m_pBuf, str.m_pBuf) > 0)
            return true;
        else
            return false;
    }
    bool operator>(const char* str) {
        if (strcmp(m_pBuf, str) > 0)
            return true;
        else
            return false;
    }
    bool operator<(const CString& str) {
        if (strcmp(m_pBuf, str.m_pBuf) < 0)
            return true;
        else
            return false;
    }
    bool operator<(const char* str) {
        if (strcmp(m_pBuf, str) < 0)
            return true;
        else
            return false;
    }
    CString operator+(const char* str) {
        Append(str);
        return *this;
    }
    CString operator+(const CString& obj) {
        Append(obj);
        return *this;
    }
    CString& operator=(const CString& str) {
        int nSize = str.m_nLength + 1;
        m_pBuf = new char[nSize];
        strcpy_s(m_pBuf, nSize, str.m_pBuf);
        m_nBufSize = nSize;
        return *this;
    }
    const char* GetString() const {
        return m_pBuf;
    }
    char& operator[](int nIndex) {
        return m_pBuf[nIndex];
    }
    const char* operator&() {
        return m_pBuf;
    }
    char operator*() {
        return *m_pBuf;
    }
    const char* GetBuffer(int nPos);
    void Copy(const char* pStr);
    void Copy(CString& obj);
    CString& Append(const char* pStr);
    CString& Append(const CString& obj);
    void Append(char ch);
    void Append(int n);
    void Append(float f);
    char GetAt(int nPos);

    int SubString(const char* pStr);
    int Search(const CString& obj);
   
    int Search(const char* pStr);
    int Search(char ch);
    int ReSearch(const CString& obj);
    int ReSearch(const char* pStr);
    int ReSearch(char ch);
    const char* Split(const char* Seps);  //字符串分割
    const char* NextSplit(const char* Seps);  //字符串分割
    int Compare(const char* pStr);
    int Compare(const CString& obj);
    int Compare(CString& obj1, const CString& obj2);
    bool Equal(const char* pStr);
    bool Equal(const CString& obj);
    void Upper();
    void Lower();
    void Foramt(const char* pForamt, ...);
    int Length();
    //void	replace​(char oldChar, char newChar)
   // void	replace​(String regex, String replacement)
    //trim()
private:
    void Init(const char* pStr);
    bool AllocBuffer(size_t nSize);
    bool ReAllocBuffer(size_t nSize);
    bool ReAllocBufferAndCopy(size_t nSize);
    void FreeBuffer();
private:
        //引用计数
        int* m_pRefCount;
private:
    char* m_pBuf;     //字符串缓冲区
    int   m_nBufSize; //缓冲区大小
    int   m_nLength;  //字符串长度
    char* m_Context;
    char* m_pSplitBuf;
    static char g_pDef[];
};

