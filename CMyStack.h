#pragma once
#include "MyList.h"

template<typename TYPE>
class CMyStack 
{
public:
    //结点
    struct CMyNode {
        CMyNode() {
            m_pNext = nullptr;
        }
        CMyNode(const TYPE& Data,
            CMyNode* pNext = nullptr)
            :m_Data{ Data }, m_pNext{ pNext }
        {

        }

        TYPE     m_Data;  //数据
        CMyNode* m_pNext; //后继
    };
public:
    CMyStack() {
        m_pHead = new CMyNode();
    }
    ~CMyStack() {
        delete m_pHead;
    }
    CMyNode*& GetHead() {
        return m_pHead;
    }
    void Push(const TYPE& obj) {
        m_pHead->m_pNext = new CMyNode(obj, m_pHead->m_pNext);
    }
    void Pop() {
        CMyNode* pDelNode = m_pHead->m_pNext;
        m_pHead->m_pNext = pDelNode->m_pNext;
        delete pDelNode;
    }
    TYPE& Top() {
        return m_pHead->m_pNext->m_Data;
    }

    bool Empty() {
        return m_pHead->m_pNext == nullptr;
    }
private:
    CMyNode *m_pHead;
};

