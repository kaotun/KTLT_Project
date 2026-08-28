#pragma once
#include <stdlib.h>
#include "StaffFunction.h"

struct DataBase {
	string No;
	string ID;
	string Name;
	string Birth;
	string Sex;
	string IDSocial;
};

DataBase Input();

void CreateNewClass();

int RunMenuCreateClass();

int CheckRowInFile(string FileName);

void DrawASCIIMenuView();

void CreateAutoClassAndImportRandomInfo();

void ImportRandom(string& YearCourse, string& Class);

void CreateClassInSemester(string& Year, string& Name);

string CheckSem();


