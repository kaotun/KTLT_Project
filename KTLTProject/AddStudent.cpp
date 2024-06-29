#include "ConsoleProcess.h"
#include "Struct.h"
#include "AddStudent.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <stdlib.h>
#include <string>
#include <fstream>
#include "ListClass.h"

using namespace std;
const string CsvTail = ".csv";

void AddStudentToClass()
{
	DrawASCIIMenuView();
	TextBgColor(0, 15);
	string YearCourse;
	string Class;
	DrawRectangle(35, 11, 60, 5, 3);
	GotoXY(43, 11);
	cout << "Enter School Year:";
	DrawRectangle(43, 12, 45, 1, 15);
	GotoXY(43, 12);
	getline(cin, YearCourse);
	fstream file;
	file.open("Data\\year_semester.csv", ios::in);
	string Year;
	string tempSemester;
	bool check = false;
	while (!file.eof())
	{
		getline(file, Year, ',');
		getline(file, tempSemester);
		if (YearCourse == Year)
		{
			check = true;
		}
	}
	if (check == false)
	{
		GotoXY(43, 13);
		cout << "Don't Find School Year " << endl;
		Sleep(1000);
	}
	if (check == true)
	{
		TextBgColor(0, 3);
		GotoXY(43, 13);
		cout << "Enter Name Of Class:";
		DrawRectangle(43, 14, 45, 1, 15);
		GotoXY(43, 14);
		getline(cin, Class);
		fstream file1;
		bool check1 = false;
		file1.open("Data\\SchoolYear\\" + YearCourse + "\\class_info.csv", ios::in);
		string stt, NameClass, major, number, year;
		while (!file1.eof())
		{
			getline(file1, stt, ',');
			getline(file1, NameClass, ',');
			getline(file1, major, ',');
			getline(file1, number, ',');
			file1 >> year;
			if (Class == NameClass)
			{
				check1 = true;
			}
		}
		if (check1 == false)
		{
			GotoXY(43, 15);
			cout << "Don't Find Class" << endl;
			Sleep(1000);
		}
		else
		{
			DataBase data;
			data = Input();
			string ClassSem = "Data\\SchoolYear\\" + YearCourse + "\\" + Class + CsvTail;
			fstream file2;
			int count = CheckRowInFile(ClassSem);
			file2.open(ClassSem, ios::app);
			file2 << endl << count + 1 << "," << data.ID << "," << data.Name << "," << data.Birth << "," << data.Sex << "," << data.IDSocial;
			file2.close();
			fstream file3;
			file3.open("Data\\login_info.csv", ios::app);
			file3 << endl << data.ID << "," << data.ID << "," << "1" << "," << Class;
			file3.close();

			string CheckSe = CheckSem();
			fstream F, FILE;
			string S = "Data\\SchoolYear\\" + YearCourse + "\\Semester" + CheckSe + "\\Class\\" + Class + CsvTail;
			F.open(S, ios::app);
			F << data.ID << endl;
			int countFile = CheckRowInFile("Data\\InformationOfNewStudent.csv");
			string checkName[1000], checkBirth[1000], checkSex[1000], checkIDso[1000];
			fstream File;
			File.open("Data\\InformationOfNewStudent.csv", ios::in);
			int countRow = 1;
			int Dem = 0;
			while (!File.eof())
			{
				for (int i = 1; i <= countFile; i++)
				{
					getline(File, checkName[i], ',');
					getline(File, checkBirth[i], ',');
					getline(File, checkSex[i], ',');
					File >> checkIDso[i];
					countRow++;
					if (data.IDSocial == checkIDso[i])
					{
						Dem = countRow;
					}
				}

			}
			string arr[1000];
			fstream FIle;
			FIle.open("Data\\InformationOfNewStudent.csv", ios::in);
			while (!FIle.eof())
			{
				for (int i = 0; i <= countFile; i++)
				{
					getline(FIle, arr[i]);
				}
			}
			FIle.close();;
			if (Dem != countFile)
			{
				fstream FIle;
				FIle.open("Data\\InformationOfNewStudent.csv", ios::out);
				for (int i = 0; i < Dem - 2; i++)
				{
					FIle << arr[i] << endl;
				}
				for (int i = Dem - 1; i <= countFile; i++)
				{
					FIle << arr[i] << endl;
				}
				FIle.close();
			}
			GotoXY(43, 24);
			cout << "IMPORT INFO STUDENT SUCCESSFUL!!!" << endl;
			Sleep(1000);

		}
	}
}


void AddRandomInfoStudentToClass()
{
	DrawASCIIMenuView();
	TextBgColor(5, 15);
	string YearCourse;
	string Class;
	DrawRectangle(35, 11, 60, 7, 3);
	GotoXY(43, 11);
	cout << "Enter School Year:";
	DrawRectangle(43, 12, 45, 1, 15);
	GotoXY(43, 12);
	getline(cin, YearCourse);
	fstream file;
	file.open("Data\\year_semester.csv", ios::in);
	string Year;
	string tempSemester;
	bool check = false;
	while (!file.eof())
	{
		getline(file, Year, ',');
		getline(file, tempSemester);
		if (YearCourse == Year)
		{
			check = true;
		}
	}
	if (check == false)
	{
		GotoXY(43, 13);
		cout << "Don't Find School Year" << endl;
		Sleep(1000);
	}
	if (check == true)
	{
		TextBgColor(0, 3);
		GotoXY(43, 13);
		cout << "Enter Name Of Class:";
		DrawRectangle(43, 14, 45, 1, 15);
		GotoXY(43, 14);
		getline(cin, Class);
		fstream file1;
		bool check1 = false;
		file1.open("Data\\SchoolYear\\" + YearCourse + "\\class_info.csv", ios::in);
		string stt, NameClass, major, number, year;
		while (!file1.eof())
		{
			getline(file1, stt, ',');
			getline(file1, NameClass, ',');
			getline(file1, major, ',');
			getline(file1, number, ',');
			file1 >> year;
			if (Class == NameClass)
			{
				check1 = true;
			}
		}
		if (check1 == false)
		{
			GotoXY(43, 15);
			cout << "Don't Find Class" << endl;
			Sleep(1000);
		}
		else
		{
			ImportRandom(YearCourse, Class);
		}
	}
}


int RunMenuAddInfoStudentToClass()
{
	char ch;
	int command;
	while (true)
	{
		ShowPointer();
		system("cls");
		GotoXY(40, 12);

		string MenuAdd[] = { "1. Add One Student To Class",
		"2. Import Info Student From File To Class",
		"3. Exit" };
		DrawMenu(MenuAdd, 3, 45, 12, 1, &DrawASCIIMenuView);
		command = MoveAndChoose(3, MenuAdd, 45, 12, 1);

		switch (command)
		{
		case 0:
		{
			system("cls");
			AddStudentToClass();
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			AddRandomInfoStudentToClass();
			system("cls");
			break;
		}
		case 2:
		{
			TextBgColor(10, 11);
			PrintText("YOU WANT TO EXIT, PRESS ENTER TO BACK TO MENU !!!", 40, 20);
			ch = _getch();
			TextBgColor(0, 15);
			return 0;
		}
		}
	}
}
