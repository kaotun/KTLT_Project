#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <iostream>
#include <Windows.h>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <string>
#include <stdio.h>
#include <conio.h>
using namespace std;

struct Mark {
	string ID;
	string Name;
	string C;
	double AvgMark, FinalMark, MidtermMark, OtherMark;
};

struct MarkNode {
	Mark info;
	MarkNode* next;
};

struct Data {
	int NoInClass;
	string IDSt;
	string NameSt;
	string sex;
	string Birthday;
	string IDSocial;
	string Class;
	MarkNode* head;
};

struct Course {
	string IDCourse;
	string NameCourse;
	string Teacher;
	int NumOfCreadit;
	int MaxStudent;
	string Schedule;
	string Session[2];
	string DayOfWeek;
	MarkNode* head;
};

struct Class {
	string NameClass;
	string MajorClass;
	int NumOfStudentNow;
	int YearOfEntering;
};

struct Semester {
	string NameSemester;
	int NumOfStudentNow;
	string SchoolYear;
	string DateBegin;
	string DateEnd;
	Course CourseInSemester;
	Class ClassInSemester;
};

struct SchoolYear {
	Semester SemesterSchool;
	string Year;   //VD: 2023 - 2024
	int NumOfStudentNow;
	string DateBegin;
	string DateEnd;
};

struct User {
	string IDUser;
	string Password;
	int role;  //0 - giao vien, 1 - sinh vien
	Data info;
};


#endif // !_STRUCT_H_



