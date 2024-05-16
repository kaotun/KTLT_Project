#pragma once
#include "Menu.h"

typedef void (*DrawASCII)();
typedef Course* (*FuncGetCourse)(User, SchoolYear, int&);

void RewriteCourseOfStudentFile(User user, string FileName, string Data, int CommandFlag);
//hàm ghi danh vào file khóa học tổng của staff, user là học sinh.

void RewriteCourseFile(User Usertmp, string FileName, int CommandFlag);

void EnrollCourse(User& A, SchoolYear SY);

void MoveUpMenu(int X, int& Y, int dis);

void MoveDownMenu(int X, int& Y, int dis);

int MoveAndChoose(int a, string A[], int X, int Y, int dis);

void DrawMenu(string* S, int n, int x, int y, int dis, DrawASCII Fun);

int GetYearData(string* Data1, int* data2, string FileName);

void ChangeYearSemester(SchoolYear& SY);

void DisPlayCourseOfStudent(SchoolYear SY, User A);

void EditScore(User& A, SchoolYear SY, Mark* M);

void DisPlayMarkOfStudent(SchoolYear SY, User A);

void EditScoreInListCourse(User& A, SchoolYear SY, string IDCourse);

void DeleteCourse(User& A, SchoolYear SY);

void ViewStudentInCourse(User Usertmp, SchoolYear SY);

void OutputInfo(User A);

void ViewOneLine(Mark M, int x, int y);

Mark* ViewAllScoreOfOneStudent(User A, SchoolYear SY);

void ViewOneScoreOfCourse(Mark M, int x, int y);

void ViewTenScoreOfCourse(Mark* M, int i, int n, int x, int y);

int ViewScoreOfCourseInYear(Mark* M, int n);

void ViewOneCourseOfListCourse(Course M, int x, int y);

void ViewTenCourseOfListCourse(Course* M, int i, int n, int x, int y);

int ViewCourseInYear(Course* M, int n, DrawASCII Fun);

Course* SelectCourse(User A, SchoolYear SY, FuncGetCourse Fun, DrawASCII FunDraw);

void ViewOneStudentInfoOfCourse(Data M, int x, int y);

void ViewTenStudentInfoOfCourse(Data* M, int i, int n, int x, int y);

void ViewStudentInfoOfCourse(Data* M, int n);

