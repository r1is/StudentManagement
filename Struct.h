#pragma once
#include <iostream>
#include "CAVLTree.h"
#include "CString.h"
#include "CFile.h"
#include "CMyStack.h"

//清楚scanf的缓冲区
#define CLEAR_BUFF scanf("%*[^\n]%*c")
//学生信息文件路径
#define STUDENT_FILE_PATH "dat\\student1"
//课程列表文件路径
#define COURSE_FILE_PATH "dat\\course1"
//选课 记录文件路径
#define Course_Selection_Record_FILE_PATH "dat\\record1"

/// <summary>
/// 
/// </summary>
struct CStudent {
    int m_nID;
    int* m_pLink;
    std::string m_szName;
};

struct CCourse {
    int m_nID;
    int* m_pLink;
    std::string m_szName;
};

struct CRecord {
    int m_nStuID;
    int m_nClsID;
    int m_nScore;
};

typedef struct _STSTUDENTSAVEINFO {
    int len;
    struct CStudent _stu;
}STSTUDENTSAVEINFO,*PSTSTUDENTSAVEINFO;

typedef struct _STCLASSSAVEINFO {
    int len;
    struct CCourse _cls;
}STCLASSSAVEINFO, *PSTCLASSSAVEINFO;

std::ostream& operator<< (std::ostream& out, const CStudent& obj) {
    out << "学生姓名:" << obj.m_szName.c_str() << " 学号（ID）:" << obj.m_nID;
    return out;
}

std::ostream& operator<< (std::ostream& out, const CCourse& obj) {
    out << "课程名称:" << obj.m_szName.c_str() << " 课程id:" << obj.m_nID;
    return out;
}

template<typename KEY, typename VALUE>
struct CStudentPair {
    KEY   m_Key; //关键字
    VALUE m_Value; //值

    CStudentPair(const KEY& Key) {
        m_Key = Key;
    }
    CStudentPair(const KEY& Key, const VALUE& value) {
        m_Key = Key;
        m_Value = value;
    }
    bool operator== (const CStudentPair& obj) const {
        return m_Key == obj.m_Key;
    }
    bool operator> (const CStudentPair& obj) const {
        return m_Key > obj.m_Key;
    }
    bool operator< (const CStudentPair& obj) const {
        return m_Key < obj.m_Key;
    }
};

template<typename KEY, typename VALUE>
std::ostream& operator<< (std::ostream& out, const CStudentPair<KEY, VALUE>& obj) {
    out << obj.m_Value;
    return out;
}

typedef CStudentPair<int, CStudent> STUIDPair;
typedef CStudentPair<int, CCourse> CLSIDPair;

//学生id树
CAVLTree<STUIDPair> StuIDTree;
//课程ID树
CAVLTree<CLSIDPair> ClsIDTree;

//删除、修改、查找操作
template<typename T,typename T2,typename TYPE,typename TYPE2>
class CManage {
public:
    //遍历学生ID和课程ID
    void ErgodicStuClsID(T* pRoot, const char* str);
    //通过学生ID或者课程ID查找学生或课程
    void FindStuClsByID(CAVLTree<TYPE>& obj,int id);
    //通过学生名或者课程名查找学生或课程
    void FindStuClsByName(CAVLTree<TYPE>& obj,const char* name);
    //通过学生ID或者课程ID查找选课记录
    void FindSelLogByID(CAVLTree<TYPE>& obj, int id);
    //通过学生ID或者课程ID修改学生名或课程名
    void ModifyStuClsByID(CAVLTree<TYPE>& obj, int id , const char* name);
    //通过学生ID或者课程ID删除学生或课程
    void DeleteStuClsByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int id);
};

//学生和课程文件操作(更新，读取，写入)
template<typename T, typename T2, typename TYPE>
class CFileAct {
public:
    //文件末尾插入更新学生或课程
    void InsertStuClsToFile(const T2& Element, const char* path);
    //初始化学生ID树或课程ID树
    void InitStuClsIDTree(CAVLTree<TYPE>& obj, const char* path);
    //有修改或删除，则遍历树，重新更新写到文件
    void UpdateStuClsToFile(CAVLTree<TYPE>& obj, const char* path);
};

//选课记录文件操作
template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
class CSelRecord {
public:
    //有选课记录被修改，则更新写到文件
    void UpdateSelLogToFile(CAVLTree<TYPE2>& obj, const char* path);
    //新增选课记录，直接文件末尾新增
    void InsertSelLogToFile(const TYPE3& Element, const char* path);

    void ModifySelLogByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuID, int nClsID, int nScore);
    void DeleteSelLogByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuID, int nClsID);
    //新增选课记录，插入到学生ID树和课程ID树
    void AddSelLog(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuId, int nClsID, int nScore);
    void InitSelLogTree(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, const char* path);
};
CSelRecord<CAVLTree<STUIDPair>::CAVLNode, CAVLTree<CLSIDPair>::CAVLNode, STUIDPair, CLSIDPair, CRecord> selRecord;

CFileAct<CAVLTree<CLSIDPair>::CAVLNode, CCourse, CLSIDPair> clsFileAct;
CFileAct<CAVLTree<STUIDPair>::CAVLNode, CStudent, STUIDPair> stuFileAct;

CManage<CAVLTree<STUIDPair>::CAVLNode, CAVLTree<CLSIDPair>::CAVLNode, STUIDPair, CLSIDPair> stuManage;
CManage<CAVLTree<CLSIDPair>::CAVLNode, CAVLTree<STUIDPair>::CAVLNode, CLSIDPair, STUIDPair> clsManage;

template<typename T,typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2,TYPE, TYPE2>::FindStuClsByID(CAVLTree<TYPE>& obj, int id) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    
    T* pNode = obj.Find(id);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "通过ID查找到:>>>" << pNode->m_Element << std::endl;
        pNode = pNode->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "查找用时:>>>" << end - start << "毫秒" << endl;
        std::cout << "数据总数:>>>" << obj.Size() << endl;
    }
    else {
        std::cout << "未查找到" << endl;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2, TYPE, TYPE2>::DeleteStuClsByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int id) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    T* pNode = obj.Find(id);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "通过ID查找到:>>>" << pNode->m_Element << std::endl;
        if (pNode->m_Element.m_Value.m_pLink != NULL) {
            CMyList<struct CRecord>* plist = ((CMyList<struct CRecord>*)(pNode->m_Element.m_Value.m_pLink));
            //CMyList<struct CRecord>::iterator it = plist->begin();
            for (CMyList<struct CRecord>::iterator it = (--plist->end()); it != (--plist->begin()); it--) {
                //std::cout << "学生ID：" << e.m_nStuID << " 课程ID：" << e.m_nClsID << " 成绩：" << e.m_nScore << endl;
                T2* pClsNode = obj2.Find((*it).m_nClsID);
                while (pClsNode != nullptr) {
                    std::cout << "通过ID查找到:>>>" << pClsNode->m_Element << std::endl;
                    if (pClsNode->m_Element.m_Value.m_pLink != NULL) {
                        CMyList<struct CRecord>* pSelList = ((CMyList<struct CRecord>*)(pClsNode->m_Element.m_Value.m_pLink));
                        //CMyList<struct CRecord>::iterator itSel = pSelList->end();
                        for (CMyList<struct CRecord>::iterator itSel = (--pSelList->end()); itSel != (--pSelList->begin()); itSel--) {
                            cout << (*itSel).m_nStuID << ' ' << endl;
                            if ((*itSel).m_nStuID == (*it).m_nStuID) {
                                cout << "删除:>>>" << (*itSel).m_nStuID << endl;
                                pSelList->Erase(itSel);
                            }
                        }
                    }
                    pClsNode = pClsNode->m_pNext;
                }
            }

            plist->Clear();
            pNode->m_Element.m_Value.m_pLink = nullptr;
            delete pNode->m_Element.m_Value.m_pLink;
        }
        obj.Remove(id);
        pNode = pNode->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "删除用时:>>>" << end - start << "毫秒" << endl;
        std::cout << "数据总数:>>>" << StuIDTree.Size() << endl;
    }
    else {
        std::cout << "未查找到" << std::endl;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2, TYPE, TYPE2>::ModifyStuClsByID(CAVLTree<TYPE>& obj, int id,const char* name) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    T* pNode = obj.Find(id);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "通过ID查找到:>>>" << pNode->m_Element << std::endl;
        pNode->m_Element.m_Value.m_szName = name;
        pNode = pNode->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "查找用时:>>>" << end - start << "毫秒" << endl;
        std::cout << "数据总数:>>>" << obj.Size() << endl;
    }
    else {
        std::cout << "未查找到" << end;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2, TYPE, TYPE2>::FindSelLogByID(CAVLTree<TYPE>& obj, int id) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    T* pNode = obj.Find(id);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "通过ID查找到:>>>" << pNode->m_Element << std::endl;
        CMyList<struct CRecord>* pList = ((CMyList<struct CRecord>*)(pNode->m_Element.m_Value.m_pLink));
        if (pList == nullptr)
        {
            nFlag = 0;
            break;
        }
        CMyList<struct CRecord>::iterator it = pList->begin();
        for (auto& e : *pList) {
            std::cout << "学生ID：" << e.m_nStuID << " 课程ID：" << e.m_nClsID << " 成绩：" << e.m_nScore << endl;
        }
        pNode = pNode->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "查找用时:>>>" << end - start << "毫秒" << endl;
        std::cout << "数据总数:>>>" << obj.Size() << endl;
    }
    else {
        std::cout << "未查找到" << std::endl;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2, TYPE, TYPE2>::FindStuClsByName(CAVLTree<TYPE>& obj, const char* name) {
    clock_t start, end;
    start = clock();
    CManage<T, T2, TYPE, TYPE2> manage1;
    manage1.ErgodicStuClsID(obj.GetRoot(), name);
    end = clock();
    std::cout << "查找用时:>>>" << end - start << "毫秒" << endl;
    std::cout << "数据总数:>>>" << endl;
}

template<typename T, typename T2, typename TYPE, typename TYPE2>
inline void CManage<T,T2,TYPE, TYPE2>::ErgodicStuClsID(T* pRoot, const char* str)
{
    if (pRoot != nullptr) {
        ErgodicStuClsID(pRoot->m_pLeft, str);
        //if (strcmp((char*)pRoot->m_Element.m_Value.m_szName.c_str(), str) == 0) {
        //包含汉字，并且去除部分不对齐的char
        if (pRoot->m_Element.m_Value.m_szName.find(str) != std::string::npos) {
            for (int i = 0; i < pRoot->m_Element.m_Value.m_szName.length(); i = i + 2) {
                if (pRoot->m_Element.m_Value.m_szName[i] == str[0] && pRoot->m_Element.m_Value.m_szName[i + 1] == str[1]) {
                    std::cout << "查找到:>>>" << pRoot->m_Element << std::endl;
                    break;
                }
            }
        }
        //显示链表
        T* pNext = pRoot->m_pNext;
        while (pNext != nullptr) {
            pNext = pNext->m_pNext;
        }
        ErgodicStuClsID(pRoot->m_pRight, str);
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::InitSelLogTree(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, const char* path) {
    CFile cFileStu;
    try {
        cFileStu = CFile(path, "rb+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    struct CRecord rec = { 0 };
    while (!cFileStu.Feof()) {
        try {
            size_t size = cFileStu.Read(&rec.m_nStuID, 1, 4);
            if (size <= 0)break;
            size = cFileStu.Read(&rec.m_nClsID, 1, 4);
            if (size <= 0)break;
            cFileStu.Read(&rec.m_nScore, 1, 4);
        }
        catch (CFileError& e) {
            std::cout << e.GetErrorMsg() << endl;
        }
        T* pStuNode = obj.Find(rec.m_nStuID);
        if (pStuNode != nullptr) {
            if (pStuNode->m_Element.m_Value.m_pLink == NULL) {
                CMyList<struct CRecord>* plist = new CMyList<struct CRecord>;
                plist->PushBack(rec);
                pStuNode->m_Element.m_Value.m_pLink = (int*)plist;
            }
            else {
                ((CMyList<struct CRecord>*)(pStuNode->m_Element.m_Value.m_pLink))->PushBack(rec);
            }
        }
        T2* pClsNode = obj2.Find(rec.m_nClsID);
        if (pClsNode != nullptr) {
            if (pClsNode->m_Element.m_Value.m_pLink == NULL) {
                CMyList<struct CRecord>* plist = new CMyList<struct CRecord>;
                plist->PushBack(rec);
                pClsNode->m_Element.m_Value.m_pLink = (int*)plist;
            }
            else {
                ((CMyList<struct CRecord>*)(pClsNode->m_Element.m_Value.m_pLink))->PushBack(rec);
            }
        }
    }
    cFileStu.Close();
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::AddSelLog(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuId, int nClsID, int nScore) {
    clock_t start, end;
    struct CRecord rec = { nStuId ,nClsID ,nScore };
    start = clock();
    int nFlag = 0;
    T2* pClsNode = obj2.Find(nClsID);
    while (pClsNode != nullptr) {
        nFlag = 1;
        if (pClsNode->m_Element.m_Value.m_pLink == NULL) {
            CMyList<struct CRecord>* plist = new CMyList<struct CRecord>;
            plist->PushBack(rec);
            pClsNode->m_Element.m_Value.m_pLink = (int*)plist;
        }
        else {
            ((CMyList<struct CRecord>*)(pClsNode->m_Element.m_Value.m_pLink))->PushBack(rec);
        }
        pClsNode = pClsNode->m_pNext;
    }
    if (nFlag == 0) {
        cout << "没有该课程" << endl;
        return;
    }
    T* pStuNode = obj.Find(nStuId);
    while (pStuNode != nullptr) {
        //std::cout << "通过学生ID查找到:>>>" << pNode->m_Element << std::endl;
        if (pStuNode->m_Element.m_Value.m_pLink == NULL) {
            CMyList<struct CRecord>* plist = new CMyList<struct CRecord>;
            plist->PushBack(rec);
            pStuNode->m_Element.m_Value.m_pLink = (int*)plist;
        }
        else {
            ((CMyList<struct CRecord>*)(pStuNode->m_Element.m_Value.m_pLink))->PushBack(rec);
        }
        pStuNode = pStuNode->m_pNext;
    }
    selRecord.InsertSelLogToFile({ nStuId, nClsID, nScore }, Course_Selection_Record_FILE_PATH);
    end = clock();
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::DeleteSelLogByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuID, int nClsID) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    T* pNode = obj.Find(nStuID);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "通过学生ID查找到:>>>" << pNode->m_Element << std::endl;
        if (pNode->m_Element.m_Value.m_pLink != NULL) {
            CMyList<struct CRecord>* plist = ((CMyList<struct CRecord>*)(pNode->m_Element.m_Value.m_pLink));
            //CMyList<struct CRecord>::iterator it = plist->begin();
            for (CMyList<struct CRecord>::iterator it = (--plist->end()); it != (--plist->begin()); it--) {
                //std::cout << "学生ID：" << e.m_nStuID << " 课程ID：" << e.m_nClsID << " 成绩：" << e.m_nScore << endl;
                if ((*it).m_nClsID == nClsID) {
                    cout << "删除:>>>" << (*it).m_nStuID << (*it).m_nClsID << endl;
                    plist->Erase(it);
                }
            }
        }
        pNode = pNode->m_pNext;
    }

    T2* pClsNode = obj2.Find(nClsID);
    while (pClsNode != nullptr) {
        nFlag = 1;
        std::cout << "通过课程ID查找到:>>>" << pClsNode->m_Element << std::endl;
        if (pClsNode->m_Element.m_Value.m_pLink != NULL) {
            CMyList<struct CRecord>* plist = ((CMyList<struct CRecord>*)(pClsNode->m_Element.m_Value.m_pLink));
            //CMyList<struct CRecord>::iterator it = plist->begin();
            for (CMyList<struct CRecord>::iterator it = (--plist->end()); it != (--plist->begin()); it--) {
                //std::cout << "学生ID：" << e.m_nStuID << " 课程ID：" << e.m_nClsID << " 成绩：" << e.m_nScore << endl;
                if ((*it).m_nStuID == nStuID) {
                    cout << "删除:>>>" << (*it).m_nStuID << (*it).m_nClsID << endl;
                    plist->Erase(it);
                }
            }
        }
        pClsNode = pClsNode->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "删除用时:>>>" << end - start << "毫秒" << endl;
        std::cout << "数据总数:>>>" << obj.Size() << endl;
    }
    else {
        std::cout << "未查找到" << std::endl;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::ModifySelLogByID(CAVLTree<TYPE>& obj, CAVLTree<TYPE2>& obj2, int nStuID, int nClsID, int nScore) {
    clock_t start, end;
    int nFlag = 0;
    start = clock();
    T* pNode = obj.Find(nStuID);
    while (pNode != nullptr) {
        nFlag = 1;
        std::cout << "通过学生ID查找到:>>>" << pNode->m_Element << std::endl;
        CMyList<struct CRecord>* plist = ((CMyList<struct CRecord>*)(pNode->m_Element.m_Value.m_pLink));
        if (plist == nullptr) {
            nFlag = 0;
            break;
        }
        for (CMyList<struct CRecord>::iterator it = (--plist->end()); it != (--plist->begin()); it--) {
            if ((*it).m_nClsID == nClsID) {
                (*it).m_nScore = nScore;
            }
        }
        pNode = pNode->m_pNext;
    }

    T2* pNode2 = obj2.Find(nClsID);
    while (pNode2 != nullptr) {
        nFlag = 1;
        std::cout << "通过课程ID查找到:>>>" << pNode2->m_Element << std::endl;
        CMyList<struct CRecord>* plist = ((CMyList<struct CRecord>*)(pNode2->m_Element.m_Value.m_pLink));
        if (plist == nullptr) {
            nFlag = 0;
            break;
        }
        for (CMyList<struct CRecord>::iterator it = (--plist->end()); it != (--plist->begin()); it--) {
            if ((*it).m_nStuID == nStuID) {
                (*it).m_nScore = nScore;
            }
        }
        pNode2 = pNode2->m_pNext;
    }
    end = clock();
    if (nFlag == 1) {
        std::cout << "查找用时:>>>" << end - start << "毫秒" << endl;
        std::cout << "数据总数:>>>" << obj.Size() << endl;
    }
    else {
        std::cout << "未查找到" << std::endl;
    }
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::InsertSelLogToFile(const TYPE3& Element, const char* path) {
    CFile cFileSel;
    try {
        cFileSel = CFile(path, "ab+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    try {
        cFileSel.Write((void*)&Element.m_nStuID, 1, sizeof(Element.m_nStuID));
        cFileSel.Flush();
        cFileSel.Write((void*)&Element.m_nClsID, 1, sizeof(Element.m_nClsID));
        cFileSel.Flush();
        cFileSel.Write((void*)&Element.m_nScore, 1, sizeof(Element.m_nScore));
        cFileSel.Flush();
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    cFileSel.Close();
}

template<typename T, typename T2, typename TYPE, typename TYPE2, typename TYPE3>
inline void CSelRecord<T, T2, TYPE, TYPE2, TYPE3>::UpdateSelLogToFile(CAVLTree<TYPE2>& obj,const char* path)
{
    CFile cFileSel;
    try {
        cFileSel = CFile(path, "wb+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    CMyStack<T2*> stack;
    T2* pRoot = obj.GetRoot();
    //先序遍历
    while (true) {
        while (pRoot != nullptr) {
            CMyList<struct CRecord>* pList = ((CMyList<struct CRecord>*)(pRoot->m_Element.m_Value.m_pLink));
            if (pList == nullptr) {
                pRoot = pRoot->m_pLeft;
                continue;
            }
            //CMyList<struct CRecord>::iterator it = pList->begin();
                struct CRecord* rec = new struct CRecord[pList->Size()];
                struct CRecord* pRec = rec;
                for (auto& e : *pList) {
                    
                    pRec->m_nStuID = e.m_nStuID;
                    pRec->m_nClsID = e.m_nClsID;
                    pRec->m_nScore = e.m_nScore;
                    pRec++;
                
                }
                try {
                    cFileSel.Write(rec, 1, pList->Size()*12);
                    cFileSel.Flush();
                }
                catch (CFileError& e) {

                }
                delete[] rec;
            stack.Push(pRoot);
            pRoot = pRoot->m_pLeft;
        }
        if (stack.Empty()) {
            break;
        }
        pRoot = stack.Top();
        stack.Pop();
        pRoot = pRoot->m_pRight;
    }
    cFileSel.Close();
}

template<typename T, typename T2, typename TYPE>
inline void CFileAct<T, T2, TYPE>::UpdateStuClsToFile(CAVLTree<TYPE>& obj, const char* path) {
    CFile cFileCls;
    try {
        cFileCls = CFile(path, "wb+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    CMyStack<T*> stack;
    T* pRoot = obj.GetRoot();

    //先序遍历
    while (true) {
        while (pRoot != nullptr) {
            int nLength = sizeof(pRoot->m_Element.m_Value.m_nID) + pRoot->m_Element.m_Value.m_szName.length() + 1;
            try {
                cFileCls.Write(&nLength, 1, sizeof(nLength));
                cFileCls.Flush();
                cFileCls.Write(&pRoot->m_Element.m_Value.m_nID, 1, sizeof(pRoot->m_Element.m_Value.m_nID));
                cFileCls.Flush();
                cFileCls.Write((char*)pRoot->m_Element.m_Value.m_szName.c_str(), 1, pRoot->m_Element.m_Value.m_szName.length() + 1);
                cFileCls.Flush();
            }
            catch (CFileError& e) {
                std::cout << e.GetErrorMsg() << endl;
            }
            stack.Push(pRoot);
            pRoot = pRoot->m_pLeft;
        }
        if (stack.Empty()) {
            break;
        }
        pRoot = stack.Top();
        stack.Pop();
        pRoot = pRoot->m_pRight;
    }
    cFileCls.Close();
}

template<typename T , typename T2, typename TYPE>
inline void CFileAct<T, T2, TYPE>::InitStuClsIDTree(CAVLTree<TYPE>& obj, const char* path) {
    CFile cFile;
    try {
        cFile = CFile(path, "rb+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    int nLength = 0;
    //struct CClass cls = { 0 };
    int nID;
    std::string str(1000, '\0');
    while (!cFile.Feof()) {
        try {
            size_t size = cFile.Read(&nLength, 1, 4);
            if (size <= 0)
                break;
            size = cFile.Read(&nID, 1, 4);
            if (size <= 0)
                break;
            cFile.Read((char*)str.c_str(), 1, nLength - 4);
        }
        catch (CFileError& e) {
            std::cout << e.GetErrorMsg() << endl;
        }
        obj.Insert({ nID, {nID,NULL,str.c_str() } });
    }
    cFile.Close();
}

template<typename T , typename T2, typename TYPE>
inline void CFileAct<T, T2, TYPE>::InsertStuClsToFile(const T2& Element, const char* path)
{
    CFile cFile;
    try {
        cFile = CFile(path, "ab+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    int nLength = sizeof(Element.m_nID) + Element.m_szName.length() + 1;
    try {
        //cFileStu.Seek(0, SEEK_END);
        cFile.Write(&nLength, 1, sizeof(nLength));
        cFile.Flush();
        cFile.Write((int*)&Element.m_nID, 1, sizeof(Element.m_nID));
        cFile.Flush();
        cFile.Write((char*)Element.m_szName.c_str(), 1, Element.m_szName.length() + 1);
        cFile.Flush();
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    cFile.Close();
}

void CoutCText(const char* str) {
    cout << str << endl;
}





const char* LASTNAME[444] = { "赵", "钱", "孙", "李", "周", "吴", "郑", "王", "冯", "陈", "褚", "卫", "蒋", "沈", "韩", "杨", "朱", "秦", "尤", "许", "何", "吕", "施", "张", "孔", "曹", "严", "华", "金", "魏", "陶", "姜", "戚", "谢", "邹", "喻", "柏", "水", "窦", "章", "云", "苏", "潘", "葛", "奚", "范", "彭", "郎", "鲁", "韦", "昌", "马", "苗", "凤", "花", "方", "俞", "任", "袁", "柳", "酆", "鲍", "史", "唐", "费", "廉", "岑", "薛", "雷", "贺", "倪", "汤", "滕", "殷", "罗", "毕", "郝", "邬", "安", "常", "乐", "于", "时", "傅", "皮", "卞", "齐", "康", "伍", "余", "元", "卜", "顾", "孟", "平", "黄", "和", "穆", "萧", "尹", "姚", "邵", "湛", "汪", "祁", "毛", "禹", "狄", "米", "贝", "明", "臧", "计", "伏", "成", "戴", "谈", "宋", "茅", "庞", "熊", "纪", "舒", "屈", "项", "祝", "董", "梁", "杜", "阮", "蓝", "闵", "席", "季", "麻", "强", "贾", "路", "娄", "危", "江", "童", "颜", "郭", "梅", "盛", "林", "刁", "钟", "徐", "邱", "骆", "高", "夏", "蔡", "田", "樊", "胡", "凌", "霍", "虞", "万", "支", "柯", "昝", "管", "卢", "莫", "经", "房", "裘", "缪", "干", "解", "应", "宗", "丁", "宣", "贲", "邓", "郁", "单", "杭", "洪", "包", "诸", "左", "石", "崔", "吉", "钮", "龚", "程", "嵇", "邢", "滑", "裴", "陆", "荣", "翁", "荀", "羊", "於", "惠", "甄", "麴", "家", "封", "芮", "羿", "储", "靳", "汲", "邴", "糜", "松", "井", "段", "富", "巫", "乌", "焦", "巴", "弓", "牧", "隗", "山", "谷", "车", "侯", "宓", "蓬", "全", "郗", "班", "仰", "秋", "仲", "伊", "宫", "宁", "仇", "栾", "暴", "甘", "钭", "厉", "戎", "祖", "武", "符", "刘", "景", "詹", "束", "龙", "叶", "幸", "司", "韶", "郜", "黎", "蓟", "薄", "印", "宿", "白", "怀", "蒲", "邰", "从", "鄂", "索", "咸", "籍", "赖", "卓", "蔺", "屠", "蒙", "池", "乔", "阴", "郁", "胥", "能", "苍", "双", "闻", "莘", "党", "翟", "谭", "贡", "劳", "逄", "姬", "申", "扶", "堵", "冉", "宰", "郦", "雍", "舄", "璩", "桑", "桂", "濮", "牛", "寿", "通", "边", "扈", "燕", "冀", "郏", "浦", "尚", "农", "温", "别", "庄", "晏", "柴", "瞿", "阎", "充", "慕", "连", "茹", "习", "宦", "艾", "鱼", "容", "向", "古", "易", "慎", "戈", "廖", "庾", "终", "暨", "居", "衡", "步", "都", "耿", "满", "弘", "匡", "国", "文", "寇", "广", "禄", "阙", "东", "殴", "殳", "沃", "利", "蔚", "越", "夔", "隆", "师", "巩", "厍", "聂", "晁", "勾", "敖", "融", "冷", "訾", "辛", "阚", "那", "简", "饶", "空", "曾", "毋", "沙", "乜", "养", "鞠", "须", "丰", "巢", "关", "蒯", "相", "查", "後", "荆", "红", "游", "竺", "权", "逯", "盖", "益", "桓", "公", "仉", "督", "晋", "楚", "闫", "法", "汝", "鄢", "涂", "钦", "归", "海", "岳", "帅", "缑", "亢", "况", "后", "有", "琴", "商", "牟", "佘", "佴", "伯", "赏", "墨", "哈", "谯", "笪", "年", "爱", "阳", "佟", "言", "福" };

const char* NAME[305] = { "伟", "刚", "勇", "毅", "俊", "峰", "强", "军", "平", "保", "东", "文", "辉", "力", "明", "永", "健", "世", "广", "志", "义", "兴", "良", "海", "山", "仁", "波", "宁", "贵", "福", "生", "龙", "元", "全", "国", "胜", "学", "祥", "才", "发", "武", "新", "利", "清", "飞", "彬", "富", "顺", "信", "子", "杰", "涛", "昌", "成", "康", "星", "光", "天", "达", "安", "岩", "中", "茂", "进", "林", "有", "坚", "和", "彪", "博", "诚", "先", "敬", "震", "振", "壮", "会", "思", "群", "豪", "心", "邦", "承", "乐", "绍", "功", "松", "善", "厚", "庆", "磊", "民", "友", "裕", "河", "哲", "江", "超", "浩", "亮", "政", "谦", "亨", "奇", "固", "之", "轮", "翰", "朗", "伯", "宏", "言", "若", "鸣", "朋", "斌", "梁", "栋", "维", "启", "克", "伦", "翔", "旭", "鹏", "泽", "晨", "辰", "士", "以", "建", "家", "致", "树", "炎", "德", "行", "时", "泰", "盛", "秀", "娟", "英", "华", "慧", "巧", "美", "娜", "静", "淑", "惠", "珠", "翠", "雅", "芝", "玉", "萍", "红", "娥", "玲", "芬", "芳", "燕", "彩", "春", "菊", "兰", "凤", "洁", "梅", "琳", "素", "云", "莲", "真", "环", "雪", "荣", "爱", "妹", "霞", "香", "月", "莺", "媛", "艳", "瑞", "凡", "佳", "嘉", "琼", "勤", "珍", "贞", "莉", "桂", "娣", "叶", "璧", "璐", "娅", "琦", "晶", "妍", "茜", "秋", "珊", "莎", "锦", "黛", "青", "倩", "婷", "姣", "婉", "娴", "瑾", "颖", "露", "瑶", "怡", "婵", "雁", "蓓", "纨", "仪", "荷", "丹", "蓉", "眉", "君", "琴", "蕊", "薇", "菁", "梦", "岚", "苑", "筠", "柔", "竹", "霭", "凝", "晓", "欢", "霄", "枫", "芸", "菲", "寒", "欣", "滢", "伊", "亚", "宜", "可", "姬", "舒", "影", "荔", "枝", "思", "丽", "秀", "飘", "育", "馥", "琦", "晶", "妍", "茜", "秋", "珊", "莎", "锦", "黛", "青", "倩", "婷", "宁", "蓓", "纨", "苑", "婕", "馨", "瑗", "琰", "韵", "融", "园", "艺", "咏", "卿", "聪", "澜", "纯", "毓", "悦", "昭", "冰", "爽", "琬", "茗", "羽", "希" };

const char* course[741] = {
    "专业名称",
    "哲学",
    "逻辑学",
    "宗教学",
    "伦理学",
    "经济学",
    "经济统计学",
    "国民经济管理",
    "资源与环境经济学",
    "商务经济学",
    "能源经济",
    "劳动经济学",
    "经济工程",
    "数字经济",
    "财政学",
    "税收学",
    "金融学",
    "金融工程",
    "保险学",
    "投资学",
    "金融数学",
    "信用管理",
    "经济与金融",
    "精算学",
    "互联网金融",
    "金融科技",
    "国际经济与贸易",
    "贸易经济",
    "法学",
    "知识产权",
    "监狱学",
    "信用风险管理与法律防控",
    "国际经贸规则",
    "司法警察学",
    "社区矫正",
    "政治学与行政学",
    "国际政治",
    "外交学",
    "国际事务与国际关系",
    "政治学、经济学与哲学",
    "国际组织与全球治理",
    "社会学",
    "社会工作",
    "人类学",
    "女性学",
    "家政学",
    "老年学",
    "社会政策",
    "民族学",
    "科学社会主义",
    "中国共产党历史",
    "思想政治教育",
    "马克思主义理论",
    "治安学",
    "侦査学",
    "边防管理",
    "禁毒学",
    "警犬技术",
    "经济犯罪侦査",
    "边防指挥",
    "消防指挥",
    "警卫学",
    "公安情报学",
    "犯罪学",
    "公安管理学",
    "涉外警务",
    "国内安全保卫",
    "警务指挥与战术",
    "技术侦查学",
    "海警执法",
    "公安政治工作",
    "移民管理",
    "出入境管理",
    "反恐警务",
    "消防政治工作",
    "教育学",
    "科学教育",
    "人文教育",
    "教育技术学",
    "艺术教育",
    "学前教育",
    "小学教育",
    "特殊教育",
    "华文教育",
    "教育康复学",
    "卫生教育",
    "认知科学与技术",
    "融合教育",
    "体育教育",
    "运动训练",
    "社会体育指导与管理",
    "武术与民族传统体育",
    "运动人体科学",
    "运动康复",
    "休闲体育",
    "体能训练",
    "冰雪运动",
    "电子竞技运动与管理",
    "智能体育工程",
    "体育旅游",
    "运动能力开发",
    "汉语言文学",
    "汉语言",
    "汉语国际教育",
    "中国少数民族语言文学",
    "古典文献学",
    "应用语言学",
    "秘书学",
    "中国语言与文化",
    "手语翻译",
    "桑戈语",
    "英语",
    "俄语",
    "徳语",
    "法语",
    "西班牙语",
    "阿拉伯语",
    "日语",
    "波斯语",
    "朝鲜语",
    "菲律宾语",
    "语言学",
    "塔玛齐格特语",
    "爪哇语",
    "旁遮普语",
    "梵语巴利语",
    "印度尼西亚语",
    "印地语",
    "柬埔寨语",
    "老挝语",
    "缅甸语",
    "马来语",
    "蒙古语",
    "僧伽罗语",
    "泰语",
    "乌尔都语",
    "希伯来语",
    "越南语",
    "豪萨语",
    "斯瓦希里语",
    "阿尔巴尼亚语",
    "保加利亚语",
    "波兰语",
    "捷克语",
    "斯洛伐克语",
    "罗马尼亚语",
    "葡萄牙语",
    "瑞典语",
    "塞尔维亚语",
    "土耳其语",
    "希腊语",
    "匈牙利语",
    "意大利语",
    "泰米尔语",
    "普什图语",
    "世界语",
    "孟加拉语",
    "尼泊尔语",
    "克罗地亚语",
    "荷兰语",
    "芬兰语",
    "乌克兰语",
    "挪威语",
    "丹麦语",
    "冰岛语",
    "爱尔兰语",
    "拉脱维亚语",
    "立陶宛语",
    "斯洛文尼亚语",
    "爱沙尼亚语",
    "马耳他语",
    "哈萨克语",
    "乌兹别克语",
    "祖鲁语",
    "拉丁语",
    "翻译",
    "商务英语",
    "阿姆哈拉语",
    "吉尔吉斯语",
    "索马里语",
    "土库曼语",
    "加泰罗尼亚语",
    "约鲁巴语",
    "亚美尼亚语",
    "马达加斯加语",
    "格鲁吉亚语",
    "阿塞拜疆语",
    "阿非利卡语",
    "马其顿语",
    "塔吉克语",
    "茨瓦纳语",
    "恩徳贝莱语",
    "科摩罗语",
    "克里奥尔语",
    "绍纳语",
    "提格雷尼亚语",
    "白俄罗斯语",
    "毛利语",
    "汤加语",
    "萨摩亚语",
    "库尔德语",
    "比斯拉马语",
    "达里语",
    "德顿语",
    "迪维希语",
    "斐济语",
    "库克群岛毛利语",
    "隆迪语",
    "卢森堡语",
    "卢旺达语",
    "纽埃语",
    "皮金语",
    "切瓦语",
    "塞苏陀语",
    "新闻学",
    "广播电视学",
    "广告学",
    "传播学",
    "编辑出版学",
    "网络与新媒体",
    "数字出版",
    "时尚传播",
    "国际新闻与传播",
    "会展",
    "历史学",
    "世界史",
    "考古学",
    "文物与博物馆学",
    "文物保护技术",
    "外国语言与外国历史",
    "文化遗产",
    "古文字学",
    "数学与应用数学",
    "信息与计算科学",
    "数理基础科学",
    "数据计算及应用",
    "物理学",
    "应用物理学",
    "核物理",
    "声学",
    "系统科学与工程",
    "量子信息科学",
    "化学",
    "应用化学",
    "化学生物学",
    "分子科学与工程",
    "能源化学",
    "化学测量学与技术",
    "天文学",
    "地理科学",
    "自然地理与资源环境",
    "人文地理与城乡规划",
    "地理信息科学",
    "大气科学",
    "应用气象学",
    "气象技术与工程",
    "海洋科学",
    "海洋技术",
    "海洋资源与环境",
    "军事海洋学",
    "地球物理学",
    "空间科学与技术",
    "防灾减灾科学与工程",
    "地质学",
    "地球化学",
    "地球信息科学与技术",
    "古生物学",
    "生物科学",
    "生物技术",
    "生物信息学",
    "生态学",
    "整合科学",
    "神经科学",
    "心理学",
    "应用心理学",
    "统计学",
    "应用统计学",
    "理论与应用力学",
    "工程力学",
    "机械工程",
    "机械设计制造及其自动化",
    "材料成型及控制工程",
    "机械电子工程",
    "工业设计",
    "过程装备与控制工程",
    "车辆工程",
    "汽车服务工程",
    "机械工艺技术",
    "微机电系统工程",
    "机电技术教育",
    "汽车维修工程教育",
    "智能制造工程",
    "智能车辆工程",
    "仿生科学与工程",
    "新能源汽车工程",
    "增材制造工程",
    "智能交互设计",
    "应急装备技术与工程",
    "测控技术与仪器",
    "精密仪器",
    "智能感知工程",
    "材料科学与工程",
    "材料物理",
    "材料化学",
    "冶金工程",
    "金属材料工程",
    "无机非金属材料工程",
    "高分子材料与工程",
    "复合材料与工程",
    "粉体材料科学与工程",
    "宝石及材料工艺学",
    "焊接技术与工程",
    "功能材料",
    "纳米材料与技术",
    "新能源材料与器件",
    "材料设计科学与工程",
    "复合材料成型工程",
    "智能材料与结构",
    "能源与动力工程",
    "能源与环境系统工程",
    "新能源科学与工程",
    "储能科学与工程",
    "能源服务工程",
    "电气工程及其自动化",
    "智能电网信息工程",
    "光源与照明",
    "电气工程与智能控制",
    "电机电器智能化",
    "电缆工程",
    "能源互联网工程",
    "电子信息工程",
    "电子科学与技术",
    "通信工程",
    "微电子科学与工程",
    "光电信息科学与工程",
    "信息工程",
    "广播电视工程",
    "水声工程",
    "电子封装技术",
    "集成电路设计与集成系统",
    "医学信息工程",
    "电磁场与无线技术",
    "电波传播与天线",
    "电子信息科学与技术",
    "电信工程及管理",
    "应用电子技术教育",
    "人工智能",
    "海洋信息工程",
    "柔性电子学",
    "智能测控工程",
    "自动化",
    "轨道交通信号与控制",
    "机器人工程",
    "邮政工程",
    "核电技术与控制工程",
    "智能装备与系统",
    "工业智能",
    "智能工程与创意设计",
    "计算机科学与技术",
    "软件工程",
    "网络工程",
    "信息安全",
    "物联网工程",
    "数字媒体技术",
    "智能科学与技术",
    "空间信息与数字技术",
    "电子与计算机工程",
    "数据科学与大数据技术",
    "网络空间安全",
    "新媒体技术",
    "电影制作",
    "保密技术",
    "服务科学与工程",
    "虚拟现实技术",
    "区块链工程",
    "密码科学与技术",
    "土木工程",
    "建筑环境与能源应用工程",
    "给排水科学与工程",
    "建筑电气与智能化",
    "城市地下空间工程",
    "道路桥梁与渡河工程",
    "铁道工程",
    "智能建造",
    "土木、水利与海洋工程",
    "土木、水利与交通工程",
    "城市水系统工程",
    "水利水电工程",
    "水文与水资源工程",
    "港口航道与海岸工程",
    "水务工程",
    "水利科学与工程",
    "测绘工程",
    "遥感科学与技术",
    "导航工程",
    "地理国情监测",
    "地理空间信息工程",
    "化学工程与工艺",
    "制药工程",
    "资源循环科学与工程",
    "能源化学工程",
    "化学工程与工业生物工程",
    "化工安全工程",
    "涂料工程",
    "精细化工",
    "地质工程",
    "勘查技术与工程",
    "资源勘查工程",
    "地下水科学与工程",
    "旅游地学与规划工程",
    "釆矿工程",
    "石油工程",
    "矿物加工工程",
    "油气储运工程",
    "矿物资源工程",
    "海洋油气工程",
    "智能采矿工程",
    "纺织工程",
    "服装设计与工程",
    "非织造材料与工程",
    "服装设计与工艺教育",
    "丝绸设计与工程",
    "轻化工程",
    "包装工程",
    "印刷工程",
    "香料香精技术与工程",
    "化妆品技术与工程",
    "交通运输",
    "交通工程",
    "航海技术",
    "轮机工程",
    "飞行技术",
    "交通设备与控制工程",
    "救助与打捞工程",
    "船舶电子电气工程",
    "轨道交通电气与控制",
    "邮轮工程与管理",
    "智慧交通",
    "船舶与海洋工程",
    "海洋工程与技术",
    "海洋资源开发技术",
    "海洋机器人",
    "航空航天工程",
    "飞行器设计与工程",
    "飞行器制造工程",
    "飞行器动力工程",
    "飞行器环境与生命保障工程",
    "飞行器质量与可靠性",
    "飞行器适航技术",
    "飞行器控制与信息工程",
    "无人驾驶航空器系统工程",
    "智能飞行器技术",
    "武器系统与工程",
    "武器发射工程",
    "探测制导与控制技术",
    "弹药工程与爆炸技术",
    "特种能源技术与工程",
    "装甲车辆工程",
    "信息对抗技术",
    "智能无人系统技术",
    "核工程与核技术",
    "辐射防护与核安全",
    "工程物理",
    "核化工与核燃料工程",
    "农业工程",
    "农业机械化及其自动化",
    "农业电气化",
    "农业建筑环境与能源工程",
    "农业水利工程",
    "土地整治工程",
    "农业智能装备工程",
    "森林工程",
    "木材科学与工程",
    "林产化工",
    "家具设计与工程",
    "环境科学与工程",
    "环境工程",
    "环境科学",
    "环境生态工程",
    "环保设备工程",
    "资源环境科学",
    "水质科学与技术",
    "生物医学工程",
    "假肢矫形工程",
    "临床工程技术",
    "康复工程",
    "食品科学与工程",
    "食品质量与安全",
    "粮食工程",
    "乳品工程",
    "酿酒工程",
    "葡萄与葡萄酒工程",
    "食品营养与检验教育",
    "烹饪与营养教育",
    "食品安全与检测",
    "食品营养与健康",
    "食用菌科学与工程",
    "白酒酿造工程",
    "建筑学",
    "城乡规划",
    "风景园林",
    "历史建筑保护工程",
    "人居环境科学与技术",
    "城市设计",
    "智慧建筑与建造",
    "安全工程",
    "应急技术与管理",
    "职业卫生工程",
    "生物工程",
    "生物制药",
    "合成生物学",
    "刑事科学技术",
    "消防工程",
    "交通管理工程",
    "安全防范工程",
    "公安视听技术",
    "抢险救援指挥与技术",
    "火灾勘查",
    "网络安全与执法",
    "核生化消防",
    "海警舰艇指挥与技术",
    "数据警务技术",
    "食品药品环境犯罪侦查技术",
    "农学",
    "园艺",
    "植物保护",
    "植物科学与技术",
    "种子科学与工程",
    "设施农业科学与工程",
    "茶学",
    "烟草",
    "应用生物科学",
    "农艺教育",
    "园艺教育",
    "智慧农业",
    "菌物科学与工程",
    "农药化肥",
    "生物农药科学与工程",
    "农业资源与环境",
    "野生动物与自然保护区管理",
    "水土保持与荒漠化防治",
    "生物质科学与工程",
    "土地科学与技术",
    "动物科学",
    "蚕学",
    "蜂学",
    "经济动物学",
    "马业科学",
    "饲料工程",
    "智慧牧业科学与工程",
    "动物医学",
    "动物药学",
    "动植物检疫",
    "实验动物学",
    "中兽医学",
    "兽医公共卫生",
    "林学",
    "园林",
    "森林保护",
    "经济林",
    "水产养殖学",
    "海洋渔业科学与技术",
    "水族科学与技术",
    "水生动物医学",
    "草业科学",
    "草坪科学与工程",
    "基础医学",
    "生物医学",
    "生物医学科学",
    "临床医学",
    "麻醉学",
    "医学影像学",
    "眼视光医学",
    "精神医学",
    "放射医学",
    "儿科学",
    "口腔医学",
    "预防医学",
    "食品卫生与营养学",
    "妇幼保健医学",
    "卫生监督",
    "全球健康学",
    "运动与公共健康",
    "中医学",
    "针灸推拿学",
    "藏医学",
    "蒙医学",
    "维医学",
    "壮医学",
    "哈医学",
    "傣医学",
    "回医学",
    "中医康复学",
    "中医养生学",
    "中医儿科学",
    "中医骨伤科学",
    "中西医临床医学",
    "药学",
    "药物制剂",
    "临床药学",
    "药事管理",
    "药物分析",
    "药物化学",
    "海洋药学",
    "化妆品科学与技术",
    "中药学",
    "中药资源与开发",
    "藏药学",
    "蒙药学",
    "中药制药",
    "中草药栽培与鉴定",
    "法医学",
    "医学检验技术",
    "医学实验技术",
    "医学影像技术",
    "眼视光学",
    "康复治疗学",
    "口腔医学技术",
    "卫生检验与检疫",
    "听力与言语康复学",
    "康复物理治疗",
    "康复作业治疗",
    "智能医学工程",
    "生物医药数据科学",
    "智能影像工程",
    "护理学",
    "助产学",
    "管理科学",
    "信息管理与信息系统",
    "工程管理",
    "房地产开发与管理",
    "工程造价",
    "保密管理",
    "邮政管理",
    "大数据管理与应用",
    "工程审计",
    "计算金融",
    "应急管理",
    "工商管理",
    "市场营销",
    "会计学",
    "财务管理",
    "国际商务",
    "人力资源管理",
    "审计学",
    "资产评估",
    "物业管理",
    "文化产业管理",
    "劳动关系",
    "体育经济与管理",
    "财务会计教育",
    "市场营销教育",
    "零售业管理",
    "创业管理",
    "农林经济管理",
    "农村区域发展",
    "公共事业管理",
    "行政管理",
    "劳动与社会保障",
    "土地资源管理",
    "城市管理",
    "海关管理",
    "交通管理",
    "海事管理",
    "公共关系学",
    "健康服务与管理",
    "海警后勤管理",
    "医疗产品管理",
    "医疗保险",
    "养老服务管理",
    "海关检验检疫安全",
    "海外安全管理",
    "自然资源登记与管理",
    "图书馆学",
    "档案学",
    "信息资源管理",
    "物流管理",
    "物流工程",
    "釆购管理",
    "供应链管理",
    "工业工程",
    "标准化工程",
    "质量管理工程",
    "电子商务",
    "电子商务及法律",
    "跨境电子商务",
    "旅游管理",
    "酒店管理",
    "会展经济与管理",
    "旅游管理与服务教育",
    "艺术史论",
    "艺术管理",
    "非物质文化遗产保护",
    "音乐表演",
    "音乐学",
    "作曲与作曲技术理论",
    "舞蹈表演",
    "舞蹈学",
    "舞蹈编导",
    "舞蹈教育",
    "航空服务艺术与管理",
    "流行音乐",
    "音乐治疗",
    "流行舞蹈",
    "音乐教育",
    "表演",
    "戏剧学",
    "电影学",
    "戏剧影视文学",
    "广播电视编导",
    "戏剧影视导演",
    "戏剧影视美术设计",
    "录音艺术",
    "播音与主持艺术",
    "动画",
    "影视摄影与制作",
    "影视技术",
    "戏剧教育",
    "美术学",
    "绘画",
    "雕塑",
    "摄影",
    "书法学",
    "中国画",
    "实验艺术",
    "跨媒体艺术",
    "文物保护与修复",
    "漫画",
    "纤维艺术",
    "艺术设计学",
    "视觉传达设计",
    "环境设计",
    "产品设计",
    "服装与服饰设计",
    "公共艺术",
    "工艺美术",
    "数字媒体艺术",
    "艺术与科技",
    "陶瓷艺术设计",
    "新媒体艺术",
    "包装设计"
};

