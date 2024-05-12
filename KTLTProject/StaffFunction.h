#pragma once

#pragma warning (disable : 4996)
#include "Struct.h"
#include <direct.h>
#include <sys/stat.h>
#include <ctime>

typedef void (*FunShowClass)(User, SchoolYear, string);

void CreateFolder(string NameFolder);

bool IsPathExist(const std::string& s);

void CopyContentFileToFile(string ScrcPath, string DesPath);

void AddSchoolYear(SchoolYear& Yeartmp);

int InsertSchoolYear(string& SchoolYear);

int InsertDate(string& Date);

int InsertNameSemester(string& Name);

void AddSemester(string& YearNow, string& SemesterNow);

int CheckSchoolYear(Semester Semestertmp);

void UpDateFileInfo(Semester Semestertmp);

void UpDateFileCSV(Semester Semestertmp);

void CreateRegistrationCourse();

int CheckDate(string Date);

void DetermineYearSemesterNow(string& Year, string& Semester);

void AddCourse();

int InsertNum(int& n);

int CountLine(string FileName);

void MoveUp(string FileName, int& CurrentLine, int ColumnNum, int IndexB[], int y, string Column[], int LineInConsole, int Width, int x);

void MoveDown(string FileName, int& CurrentLine, int ColumnNum, int IndexB[], int y, string Column[], int LineInConsole, int Width, int x);

void DrawList(int ColumnNum, string FileName, int y, int IndexA[], int IndexB[], int Line, int FlagLine);

void ListCourse(User A, string Year, string Semester);

void GetLineInfo(string FileName, int Line, string Column[], int ColumnNum);

void UpdateFileCourse(int CurrentColumn, int CurrentLine, string Column[], string Year, string Semester);

void EditInforCourse(int y, int CurrentLine, string Column[], string Year, string Semester);

int InsertSession(string& Data, int Limit);

int InsertDay(string& Data, int Limit);

int InsertNum2(string& Data, int Limit);

int InsertString(string& Data, int Limit);

int EditCourse(User A, string& Year, string& Semester);

void DeleteCourse(string FileName, string CourseName, int CurrentLine, string Year, string Semester);

void ViewCourse(string Year, string Semester);

bool CheckTimeEnd(string Date, string Month, string Year);

bool CheckTimeStart(string Date, string Month, string Year);

int CheckCourseSession();

void ExportScoreBoardInterface(User A, string Year, string Semester, int CurrentLine, int LineInConsole);

void ExportSB(string SchoolYear, string Semester, string CourseID);

void ImportScoreBoard(string Year, string Semester, string CourseID, string FileName);

void ImportScoreBoardUI();

string InputFileName();

void ListClass(User A, SchoolYear Yeartmp, FunShowClass Fun);

void ShowStudentInclass(User Usertmp, SchoolYear Yeartmp, string ClassName);

void DrawListStudent(int ColumnNum, SchoolYear Yeartmp, string FileName, int y, int IndexA[], int IndexB[], int Line, int FlagLine);

void GetLineInfoForStudent(string FileName, SchoolYear Yeartmp, int Line, string Column[], int ColumnNum);

void GetAllCourseStudent(User& B, SchoolYear SY, float& OverallGPA);

void ShowScoreOfClass(User Usertmp, SchoolYear Yeartmp, string ClassName);

void ListClassUseFor14(SchoolYear Y);

void ShowScoreOfClassPreventive(SchoolYear Y, string ClassName);

void DeleteFile(string FileName);

void RenameFile(string OldName, string NewName);