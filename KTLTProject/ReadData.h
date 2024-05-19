#pragma once
#include "StaffFunction.h"
#include "ConsoleProcess.h"
#include "Struct.h"
#include "Menu.h"

typedef Course* (*FuncGetCourse)(User, SchoolYear, int&);

typedef void (*drawASCII)();

const string CsvTail = ".csv";

const string TxtTail = ".txt";

void ReadOneInfo(User& A, ifstream& fIn);

void ReadInfo(User& A, SchoolYear SY);

void ReadCourse(User A, SchoolYear y);

void ReadOneCourseInfo(Course& A, ifstream& fOut);

void InitListMark(MarkNode*& head);

void AddTailListMark(MarkNode*& head, string ID, string Name, string NumOfCreadit);

int GetCourse(User& A, SchoolYear SY, int Flag = 0);

void BackASemester(SchoolYear& SY);

void GetAllCourse(User& A, SchoolYear SY);

void DeleteMarkNode(MarkNode*& head, string ID);

void GetOneScore(MarkNode*& A, string ID, ifstream& fIn);

void GetScore(User& A, SchoolYear SY, int& i);

void InsertMark(string& Data, int Limit, int& Flag);

void SaveMark(User& A, Mark* B, int i, SchoolYear SY);

Mark* ReadFileScoreOfCourse(SchoolYear SY, string IDCourse, int& n);

void SaveMarkWithListCousre(string IDCourse, Mark B, SchoolYear SY);

Course* ReadFileListCourse(User A, SchoolYear SY, int& n);

Course* GetCourseOfStudent(User A, SchoolYear SY, int& n);

Data* ReadFileStudentInfoOfCourse(SchoolYear SY, string IDCourse, int& n);
