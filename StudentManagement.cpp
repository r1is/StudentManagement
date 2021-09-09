#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Struct.h"
#include "CFile.h"
using namespace std;

void InitNewData();
int main()
{
  
    srand((unsigned)time(NULL));
    clock_t start, end;
    //随机生成10W学生和100W选课记录
    //InitNewData();

    start = clock();
    //初始化学生ID树
    stuFileAct.InitStuClsIDTree(StuIDTree, STUDENT_FILE_PATH);
    //初始化课程ID树
    clsFileAct.InitStuClsIDTree(ClsIDTree, COURSE_FILE_PATH);
    //初始化选课记录挂到学生ID和课程ID树
    selRecord.InitSelLogTree(StuIDTree, ClsIDTree, Course_Selection_Record_FILE_PATH);

    end = clock();

    cout << "初始化成功,耗时:" << end - start << " 毫秒" << endl;

    while (true) {
    WHILE_START:
        system("cls");
        cout << ">>>请选择功能\n" << endl;
        cout << "1、增加操作\n" << endl;
        cout << "2、删除操作\n" << endl;
        cout << "3、修改操作\n" << endl;
        cout << "4、查询操作\n" << endl;
        cout << ">>>请输入序号：\n" << endl;
        char ch;
        cin >> ch;
        switch (ch) {
        case '1':
        {
            //增加操作
            system("cls");
            cout << "***请选择增加功能\n" << endl;
            cout << "1、增加学生\n" << endl;
            cout << "2、增加课程\n" << endl;
            cout << "3、增加课程记录\n" << endl;
            cout << "4、退出\n" << endl;
            cout << "***请输入序号：\n" << endl;
            while (true) {
                cin >> ch;
                switch (ch) {
                case '1':
                {
                    //增加学生
                    cout << "请输入学生ID和姓名:" << endl;
                    int nID;
                    std::string szName(1000, '\0');
                    cin >> nID >> szName;
                    CLEAR_BUFF;
                    StuIDTree.Insert({ nID, {nID,NULL,szName } });
                    stuFileAct.InsertStuClsToFile({ nID,NULL,szName }, STUDENT_FILE_PATH);
                    cout << nID << " " << szName << " " << StuIDTree.Size() << endl;
                    break;
                }
                case '2':
                {
                    //增加课程
                    cout << "请输入课程ID和课程名:" << endl;
                    int nID;
                    std::string szName(1000, '\0');
                    cin >> nID >> szName;
                    CLEAR_BUFF;
                    ClsIDTree.Insert({ nID, {nID,NULL,szName } });
                    cout << nID << " " << szName << " " << ClsIDTree.Size() << endl;
                    clsFileAct.InsertStuClsToFile({ nID,NULL,szName }, COURSE_FILE_PATH);
                    break;
                }
                case '3':
                {
                    //增加选课记录
                    cout << "请输入学生ID、课程ID和成绩:" << endl;
                    int nStuID, nClsID, nScore;
                    cin >> nStuID >> nClsID >> nScore;
                    CLEAR_BUFF;
                    selRecord.AddSelLog(StuIDTree, ClsIDTree, nStuID, nClsID, nScore);
                    cout << nStuID << " " << nClsID << " " << nScore << StuIDTree.Size() << " " << ClsIDTree.Size() << endl;
                    
                    break;
                }
                case '4':
                {
                    goto WHILE_START;
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case '2':
        {
            system("cls");
            cout << "***请选择删除功能\n" << endl;
            cout << "1、删除学生\n" << endl;
            cout << "2、删除课程\n" << endl;
            cout << "3、删除课程记录\n" << endl;
            cout << "4、退出\n" << endl;
            cout << "***请输入序号：\n" << endl;
            while (true) {
                cin >> ch;
                switch (ch) {
                case '1':
                {
                    //删除学生
                    CoutCText("请输入要删除的学生ID:");
                    int nStuID;
                    cin >> nStuID;
                    CLEAR_BUFF;
                    stuManage.DeleteStuClsByID(StuIDTree, ClsIDTree, nStuID);
                    stuFileAct.UpdateStuClsToFile(StuIDTree, STUDENT_FILE_PATH);
                    break;
                }
                case '2':
                {
                    //删除课程
                    CoutCText("请输入要删除的课程ID:");
                    int nClsID;
                    cin >> nClsID;
                    CLEAR_BUFF;
                    clsManage.DeleteStuClsByID(ClsIDTree, StuIDTree, nClsID);
                    clsFileAct.UpdateStuClsToFile(ClsIDTree, COURSE_FILE_PATH);
                    break;
                }
                case '3':
                {
                    //删除选课记录
                    CoutCText("请输入要删除选课记录的学生ID和课程ID:");
                    int nStuID, nClsID;
                    cin >> nStuID >> nClsID;
                    CLEAR_BUFF;
                    selRecord.DeleteSelLogByID(StuIDTree, ClsIDTree, nStuID, nClsID);
                    selRecord.UpdateSelLogToFile(ClsIDTree, Course_Selection_Record_FILE_PATH);
                    break;
                }
                case '4':
                {
                    goto WHILE_START;
                    break;
                }
                default:
                    break;
                }
            }
            break;
        }
        case '3':
        {
            system("cls");
            cout << "***请选择修改功能\n" << endl;
            cout << "1、修改学生\n" << endl;
            cout << "2、修改课程\n" << endl;
            cout << "3、修改课程记录\n" << endl;
            cout << "4、退出\n" << endl;
            cout << "***请输入序号：\n" << endl;
            while (true) {
                cin >> ch;
                switch (ch) {
                case '1':
                {
                    //修改学生
                    CoutCText("请输入要修改的学生ID:");
                    int nStuID;
                    cin >> nStuID;
                    CLEAR_BUFF;
                    CoutCText("请输入修改后的学生姓名:");
                    std::string szName(1000, '\0');
                    cin >> szName;
                    CLEAR_BUFF;
                    stuManage.ModifyStuClsByID(StuIDTree, nStuID, szName.c_str());
                    stuFileAct.UpdateStuClsToFile(StuIDTree, STUDENT_FILE_PATH);
                    break;
                }
                case '2':
                {
                    //修改课程
                    CoutCText("请输入要修改的课程ID:");
                    int nClsID;
                    cin >> nClsID;
                    CLEAR_BUFF;
                    CoutCText("请输入修改后的课程名:");
                    std::string szName(1000, '\0');
                    cin >> szName;
                    CLEAR_BUFF;
                    clsManage.ModifyStuClsByID(ClsIDTree, nClsID, szName.c_str());
                    clsFileAct.UpdateStuClsToFile(ClsIDTree, COURSE_FILE_PATH);
                    break;
                }
                case '3':
                {
                    //修改选课记录
                    CoutCText("请输入要修改选课记录的学生ID:");
                    int nStuID;
                    cin >> nStuID;
                    CLEAR_BUFF;
                    CoutCText("请输入修改后的课程ID:");
                    int nClsID;
                    cin >> nClsID;
                    CLEAR_BUFF;
                    CoutCText("请输入修改后的成绩:");
                    int nScore;
                    cin >> nScore;
                    CLEAR_BUFF;
                    selRecord.ModifySelLogByID(StuIDTree, ClsIDTree, nStuID, nClsID, nScore);
                    start = clock();
                    selRecord.UpdateSelLogToFile(ClsIDTree, Course_Selection_Record_FILE_PATH);
                    end = clock();
                    cout << end - start << endl;
                    break;
                }
                case '4':
                {
                    goto WHILE_START;
                    break;
                }
                default:break;
                }
            }
            break;
        }
        case '4':
        {
            system("cls");
            cout << "***请选择查询功能\n" << endl;
            cout << "1、查询学生\n" << endl;
            cout << "2、查询课程\n" << endl;
            cout << "3、查询课程记录\n" << endl;
            cout << "4、退出\n" << endl;
            cout << "***请输入序号：\n" << endl;
            while (true) {
                cin >> ch;
                switch (ch) {
                case '1':
                {
                    //查找学生
                    char nStu[100] = { 0 };
                    CoutCText("请输入查找的学生ID或者姓名:");
                    cin >> nStu;
                    CLEAR_BUFF;
                    if (nStu[0] >= '0' && nStu[0] <= '9')
                        stuManage.FindStuClsByID(StuIDTree, atoi(nStu));
                    else
                        stuManage.FindStuClsByName(StuIDTree, nStu);
                    break;
                }
                case '2':
                {
                    //查找课程
                    char nCls[100] = { 0 };
                    CoutCText("请输入查找的课程ID或课程名：");
                    cin >> nCls;
                    CLEAR_BUFF;
                    if (nCls[0] >= '0' && nCls[0] <= '9')
                        clsManage.FindStuClsByID(ClsIDTree, atoi(nCls));
                    else
                        clsManage.FindStuClsByName(ClsIDTree, nCls);
                    break;
                }
                case '3':
                {
                    //查找选课记录
                    int nSelClsLog = 0;
                    CoutCText("请输入查找的选课记录的学生ID或课程ID：");
                    cin >> nSelClsLog;
                    CLEAR_BUFF;
                    stuManage.FindSelLogByID(StuIDTree, nSelClsLog);
                    clsManage.FindSelLogByID(ClsIDTree, nSelClsLog);
                    break;
                }
                case '4':
                {
                    goto WHILE_START;
                    break;
                }
                default:break;
                }
            }
            break;
        }
        case '5':
            //退出
            exit(0);
            break;
        default:
            break;
                
        }
    }
    return 0;
}

void InitNewData() {
    clock_t start, end;
    //随机生成1000课程
    CAVLTree<CLSIDPair> IDTree1;
    start = clock();

    CFile cFile1;
    try {
        cFile1 = CFile("Data\\class", "wb+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }

    for (int i = 0; i < 1000; i++) {
        STCLASSSAVEINFO cls;
        cls._cls.m_nID = 1000000 + i;
        cls._cls.m_szName = course[rand() % 741];
   
        cls.len = sizeof(cls._cls.m_nID) + cls._cls.m_szName.length() + 1;
        try {
            cFile1.Write(&cls.len, 1, sizeof(int));
            cFile1.Flush();
            cFile1.Write(&cls._cls.m_nID, 1, sizeof(cls._cls.m_nID));
            cFile1.Flush();
            cFile1.Write((char*)cls._cls.m_szName.c_str(), 1, cls._cls.m_szName.length() + 1);
            cFile1.Flush();
        }
        catch (CFileError& e) {
            std::cout << e.GetErrorMsg() << endl;
        }
    }
    cFile1.Close();

    end = clock();
    std::cout << "插入用时:" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << endl;
    //IDTree1.PrintTree(IDTree1.GetRoot());
    ////////////////////////////////////////////////////////////////////
    //随机生成10w学生和100w选课记录
    CAVLTree<STUIDPair> IDTree;
    start = clock();

    CFile cFile;
    CFile cFile2;
    try {
        cFile = CFile("Data\\student", "wb+");
        cFile2 = CFile("Data\\record", "wb+");
    }
    catch (CFileError& e) {
        std::cout << e.GetErrorMsg() << endl;
    }
    for (int i = 0; i < 100000; i++) {
        STSTUDENTSAVEINFO stu;
        struct CRecord rec;
        stu._stu.m_nID = 1000000 + i;
        stu._stu.m_szName = LASTNAME[rand() % 444] + std::string(NAME[rand() % 305]) + (rand() % 2 == 1 ? std::string(NAME[rand() % 305]) : std::string(""));
        //IDTree.Insert({ stu._stu.m_nID, {stu._stu.m_nID,NULL,stu._stu.m_szName } });
        stu.len = sizeof(stu._stu.m_nID) + stu._stu.m_szName.length() + 1;
        try {
            cFile.Write(&stu.len, 1, sizeof(int));
            cFile.Flush();
            cFile.Write(&stu._stu.m_nID, 1, sizeof(stu._stu.m_nID));
            cFile.Flush();
            cFile.Write((char*)stu._stu.m_szName.c_str(), 1, stu._stu.m_szName.length() + 1);
            cFile.Flush();
        }
        catch (CFileError& e) {
            std::cout << e.GetErrorMsg() << endl;
        }
        for (int j = 0; j < 10; j++) {
            rec.m_nStuID = stu._stu.m_nID;
            rec.m_nClsID = 1000000 + rand() % 1000;
            rec.m_nScore = (rand() % 45) + 50;
            try {
                cFile2.Write(&rec.m_nStuID, 1, sizeof(rec.m_nStuID));
                cFile2.Flush();
                cFile2.Write(&rec.m_nClsID, 1, sizeof(rec.m_nClsID));
                cFile2.Flush();
                cFile2.Write(&rec.m_nScore, 1, sizeof(rec.m_nScore));
                cFile2.Flush();
            }
            catch (CFileError& e) {
                std::cout << e.GetErrorMsg() << endl;
            }
        }
    }
    cFile.Close();
    cFile2.Close();

    end = clock();
    std::cout << "插入用时:" << (double)(end - start) / CLOCKS_PER_SEC << "秒" << endl;
}