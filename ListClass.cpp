#include "ConsoleProcess.h"
#include "CourseFunction.h"
#include "StaffFunction.h"
#include <Windows.h>
using namespace std;

const string CsvTail = ".csv";

struct DataBase {
	string No;
	string ID;
	string name;
	string Birth;
	string sex;
	string IDsocial;
};

void DrawASCIIMenuView();

DataBase Input()
{
	DataBase data;
	GotoXY(53, 17);
	cout << "IMPUT INFORMATION STUDENT" << endl;
	cin.ignore();
	GotoXY(58, 18);
	cout << "Mssv:";
	getline(cin, data.ID);
	GotoXY(58, 19);
	cout << "Name:";
	getline(cin, data.name);
	GotoXY(58, 20);
	cout << "Birth:";
	getline(cin, data.Birth);
	GotoXY(58, 21);
	cout << "Sex:";
	getline(cin, data.sex);
	GotoXY(58, 22);
	cout << "IDsocial:";
	getline(cin, data.IDsocial);
	return data;
}

int CheckRowInFile(string FileName)
{
	fstream f;
	f.open(FileName, ios::in);
	int count = -1;
	string name;
	while (!f.eof())
	{
		getline(f, name);
		count++;
	}
	return count;
}


string CheckSem()
{
	fstream Fclass;
	Fclass.open("Data//year_semester.csv");
	string YearTem, SemTem;
	string CheckSem;
	while (!Fclass.eof())
	{
		getline(Fclass, YearTem, ',');
		Fclass >> SemTem;
		CheckSem = SemTem;
	}
	Fclass.close();
	return CheckSem;
}

void CreateClassInSemester(string& Year, string& Name)
{
	string CheckSe = CheckSem();
	if (CheckSe == "0")
	{
		return;
	}
	else
	{
		string CreateClass = "Data//SchoolYear//" + Year + "//Semester" + CheckSe + "//Class//" + Name + CsvTail;
		fstream fCreate;
		fCreate.open(CreateClass, ios::out);
		/*fstream fRead;
		string S = "file_save//SchoolYear//" + Year + "//" + name + csv_tail;
		fRead.open(S, ios::in);
		int count = CheckRowInFile(S);*/

		fCreate.close();
	}
}

void CreateNewClass()
{
	string name;
	system("cls");
	DrawASCIIMenuView();
	string Year;
	TextBgColor(0, 11);
	DrawRectangle(35, 12, 60, 12, 11);
	fstream fs;
	fs.open("Data//year_semester.csv", ios::in);
	string tempYear;
	string tempSemester;
	while (!fs.eof())
	{
		getline(fs, tempYear, ',');
		getline(fs, tempSemester);
		Year = tempYear;
	}
	{
		//cin.ignore();

		TextBgColor(0, 11);
		GotoXY(43, 14);
		cout << "Enter Name Of Class(CTT,HOH,TTH,SHH):";

		DrawRectangle(43, 15, 45, 1, 15);
		GotoXY(43, 15);
		_getch();
		getline(cin, name);
		string str =  name;
		string CheckNameClass = { str[2] , str[3] , str[4] };
		string CheckSTTClass = { str[5] };
		if (CheckNameClass == "CTT" || CheckNameClass == "HOH"
			|| CheckNameClass == "TTH" || CheckNameClass == "SHH")
		{
			if (CheckSTTClass == "1" || CheckSTTClass == "2"
				|| CheckSTTClass == "3" || CheckSTTClass == "4")
			{
				fstream file1;
				bool check = true;
				file1.open("Data//SchoolYear//" + Year + "//class_info.csv", ios::in);
				string stt, NameClass, major, number, year;
				while (!file1.eof())
				{
					getline(file1, stt, ',');
					getline(file1, NameClass, ',');
					getline(file1, major, ',');
					getline(file1, number, ',');
					file1 >> year;
					if (name == NameClass)
					{
						check = false;
					}
				}
				if (check == false)
				{
					GotoXY(43, 17);
					cout << "CLASS EXIST! PLEASE TRY AGAIN" << endl;
					Sleep(1000);
				}
				if (check == true)
				{

					string NameMajor;
					TextBgColor(0, 11);
					GotoXY(43, 16);
					cout << "Enter Name Of Major: ";
					DrawRectangle(43, 17, 45, 1, 15);
					GotoXY(43, 17);
					getline(cin, NameMajor);
					if (NameMajor == "")
					{
						GotoXY(43, 19);
						cout << "Name Major is malformed!! Try again" << endl;
						Sleep(1000);
					}
					else
					{
						int numberStudent;
						TextBgColor(0, 11);
						GotoXY(43, 18);
						cout << "Enter Number Of Student(Max=100): ";
						DrawRectangle(43, 19, 45, 1, 15);
						GotoXY(43, 19);
						cin >> numberStudent;

						if (numberStudent <= 100)
						{
							string str = { Year };
							string yearStudent = { Year[0],Year[1],Year[2],Year[3] };

							fstream file;
							string filename = "Data//SchoolYear//" + Year + "//class_info.csv";
							int count = CheckRowInFile(filename);
							file.open("Data//SchoolYear//" + Year + "//class_info.csv", ios::app);
							file << endl << count + 1 << "," << name << "," << NameMajor << "," << numberStudent << "," << yearStudent;
							file.close();

							string FileName = "Data//SchoolYear//" + Year + "//" + name + CsvTail;
							fstream f1;
							f1.open(FileName, ios::out);
							f1 << "No" << "," << "ID" << "," << "Name" << "," << "Birth" << "," << "Sex" << "," << "IDSocial";
							f1.close();

							GotoXY(43, 23);
							cout << "CREATE CLASS SUCCESSFUL!!!" << endl;
							CreateClassInSemester(Year, name);
							Sleep(1000);
						}
						else
						{
							GotoXY(43, 21);
							cout << "Max Number Of Student is 100! Try again" << endl;
							Sleep(1000);
						}


					}

				}

			}
			else
			{
				GotoXY(43, 17);
				cout << "Name class is malformed!! Try again" << endl;
				Sleep(1000);
			}

		}
		else
		{
			GotoXY(43, 17);
			cout << "Name class is malformed!! Try again" << endl;
			Sleep(1000);
		}
	}
}

void DrawASCIIMenuView()
{
	TextBgColor(4, 7);
	PrintText("  ____  _         _     ____   ____  ", 40, 4);
	PrintText(" / ___|| |       / \\   / ___| / ___| ", 40, 5);
	PrintText("| |    | |      / _ \\  \\___ \\ \\___ \\ ", 40, 6);
	PrintText("| |___ | |___  / ___ \\  ___) | ___) |", 40, 7);
	PrintText(" \\____||_____|/_/   \\_\\|____/ |____/ ", 40, 8);
	PrintText("                                     ", 40, 9);
}

void ImportRandom(string& YearCourse, string& Class)
{
	fstream ofs, ifs;
	string NameClass = "Data//SchoolYear//" + YearCourse + "//" + Class + CsvTail;
	ofs.open(NameClass, ios::app);
	ifs.open("Data//InformationOfNewStudent.csv", ios::in);
	string  NameSt, BirthSt, SexSt, IdSocialSt;
	int count = CheckRowInFile(NameClass);
	int IDSt;
	string CheckYear = { YearCourse };
	string CheckNameYear = { CheckYear[2] , CheckYear[3] };
	int MasoNam;
	//MasoNam = atoi(CheckNameYear.c_str()) * 1000000;
	MasoNam = 23* 1000000;
	string str = { Class };
	string CheckNameClass = { str[2] , str[3] , str[4] };
	string CheckSTTClass = { str[5] };
	if (CheckNameClass == "CTT")
	{
		if (CheckSTTClass == "1")
		{
			IDSt = MasoNam + 120000;
		}
		if (CheckSTTClass == "2")
		{
			IDSt = MasoNam + 120100;
		}
		if (CheckSTTClass == "3")
		{
			IDSt = MasoNam + 120200;
		}
		if (CheckSTTClass == "4")
		{
			IDSt = MasoNam + 120300;
		}

	}
	if (CheckNameClass == "SHH")
	{
		if (CheckSTTClass == "1")
		{
			IDSt = MasoNam + 150000;
		}
		if (CheckSTTClass == "2")
		{
			IDSt = MasoNam + 150100;
		}
		if (CheckSTTClass == "3")
		{
			IDSt = MasoNam + 150200;
		}
		if (CheckSTTClass == "4")
		{
			IDSt = MasoNam + 150300;
		}
	}
	if (CheckNameClass == "HOH")
	{
		if (CheckSTTClass == "1")
		{
			IDSt = MasoNam + 170000;
		}
		if (CheckSTTClass == "2")
		{
			IDSt = MasoNam + 170100;
		}
		if (CheckSTTClass == "3")
		{
			IDSt = MasoNam + 170200;
		}
		if (CheckSTTClass == "4")
		{
			IDSt = MasoNam + 170300;
		}
	}
	if (CheckNameClass == "TTH")
	{
		if (CheckSTTClass == "1")
		{
			IDSt = MasoNam + 110000;
		}
		if (CheckSTTClass == "2")
		{
			IDSt = MasoNam + 110100;
		}
		if (CheckSTTClass == "3")
		{
			IDSt = MasoNam + 110200;
		}
		if (CheckSTTClass == "4")
		{
			IDSt = MasoNam + 110300;
		}
	}
	string NumberOfStudent;
	fstream file2;
	file2.open("Data//SchoolYear//" + YearCourse + "//class_info.csv", ios::in);
	string stt2, NameClass2, major2, number2, year2;
	while (!file2.eof())
	{
		getline(file2, stt2, ',');
		getline(file2, NameClass2, ',');
		getline(file2, major2, ',');
		getline(file2, number2, ',');
		file2 >> year2;
		if (Class == NameClass2)
		{
			NumberOfStudent = number2;
		}
	}
	int CheckNumberOfStudent = atoi(NumberOfStudent.c_str());
	int countFile = CheckRowInFile("Data//InformationOfNewStudent.csv");
	if (countFile < CheckNumberOfStudent)
	{
		GotoXY(43, 21);
		cout << "FILE INPUT IS FAIL, DON'T IMPORT INFO TO CLASS" << endl;
		Sleep(1000);
	}
	else
	{

		while (count != (CheckNumberOfStudent))
		{
			fstream finput;
			finput.open("Data//InformationOfLogin.csv", ios::app);
			int MSSV = IDSt + count;
			ofs << endl;
			ofs << count + 1 << ",";
			ofs << MSSV << ",";
			finput << endl << MSSV << "," << MSSV << "," << "1" << "," << Class;
			getline(ifs, NameSt, ',');
			ofs << NameSt << ",";
			getline(ifs, BirthSt, ',');
			ofs << BirthSt << ",";
			getline(ifs, SexSt, ',');
			ofs << SexSt << ',';
			getline(ifs, IdSocialSt);
			ofs << IdSocialSt;
			count++;
			finput.close();
		}
		ifs.close();
		ofs.close();
		string arr[10000];
		fstream f1;
		f1.open("Data//InformationOfNewStudent.csv", ios::in);

		while (!f1.eof())
		{
			for (int i = 0; i <= countFile; i++)
			{
				getline(f1, arr[i]);
			}
		}
		f1.close();
		fstream f2;
		f2.open("Data//InformationOfNewStudent.csv", ios::out);
		for (int i = CheckNumberOfStudent; i < countFile; i++)
		{
			f2 << arr[i] << endl;
		}
		f2.close();
	}
	string CheckSe = CheckSem();
	fstream F, FILE;
	string S = "Data//SchoolYear//" + YearCourse + "//Semester" + CheckSe + "//Class//" + Class + CsvTail;
	F.open(S, ios::app);
	int countF = CheckRowInFile(S);
	string SS = "Data//SchoolYear//" + YearCourse + "//" + Class + CsvTail;
	FILE.open(SS, ios::in);
	string CheckNo, CheckID, CheckName, CheckBirth, CheckSex, CheckIDso;
	while (!FILE.eof())
	{
		getline(FILE, CheckNo, ',');
		getline(FILE, CheckID, ',');
		getline(FILE, CheckName, ',');
		getline(FILE, CheckBirth, ',');
		getline(FILE, CheckSex, ',');
		FILE >> CheckIDso;
		int AtoiID = atoi(CheckID.c_str());
		if (AtoiID != 0)
		{
			if (countF == 0)
			{
				F << CheckID;
				countF++;
			}
			else
			{
				F << endl << CheckID;
			}
		}
	}


}

void CreateAutoClassAndImportRandomInfo()
{
	string name;
	system("cls");
	DrawASCIIMenuView();
	string Year;
	TextBgColor(0, 11);
	DrawRectangle(35, 12, 60, 12, 11);
	fstream fs;
	fs.open("Data//year_semester.csv", ios::in);
	string tempYear;
	string tempSemester;
	while (!fs.eof())
	{
		getline(fs, tempYear, ',');
		getline(fs, tempSemester);
		Year = tempYear;
	}
	{
		TextBgColor(0, 11);
		GotoXY(43, 13);
		cout << "Enter Name Abbreviations Of Class(CTT,HOH,TTH,SHH): ";
		DrawRectangle(43, 14, 45, 1, 15);
		GotoXY(43, 14);
		getline(cin, name);

		if (name == "CTT" || name == "HOH"
			|| name == "TTH" || name == "SHH")
		{
			fstream file1;
			bool check = true;
			file1.open("Data//SchoolYear//" + Year + "//class_info.csv", ios::in);
			string stt, NameClass, major, number, year;
			while (!file1.eof())
			{
				getline(file1, stt, ',');
				getline(file1, NameClass, ',');
				getline(file1, major, ',');
				getline(file1, number, ',');
				file1 >> year;
				if (name == NameClass)
				{
					check = false;
				}
			}
			if (check == false)
			{
				GotoXY(43, 16);
				cout << "CLASS EXIST! PLEASE TRY AGAIN" << endl;
			}
			if (check == true)
			{
				string NameMajor;
				TextBgColor(0, 11);
				GotoXY(43, 15);
				cout << "Enter Name Of Major: ";
				DrawRectangle(43, 16, 45, 1, 15);
				GotoXY(43, 16);
				getline(cin, NameMajor);
				int numberStudent;
				TextBgColor(0, 11);
				GotoXY(43, 17);
				cout << "Enter Number Of Student(Max=100): ";
				DrawRectangle(43, 18, 45, 1, 15);
				GotoXY(43, 18);
				cin >> numberStudent;
				if (numberStudent <= 100)
				{
					int NumberOfClass;
					TextBgColor(0, 11);
					GotoXY(43, 19);
					cout << "Enter Number Of Class(Max = 4): ";
					DrawRectangle(43, 20, 45, 1, 15);
					GotoXY(43, 20);
					cin >> NumberOfClass;
					if (NumberOfClass <= 4)
					{
						string str = { Year };
						string YearStudent = { Year[0],Year[1],Year[2],Year[3] };

						fstream file;
						string filename = "Data//SchoolYear//" + Year + "//class_info.csv";
						string CheckYear = { Year[2], Year[3] };
						for (int i = 1; i <= NumberOfClass; i++)
						{
							string s = to_string(i);
							string NameClasses = CheckYear + name + s;
							string FileName = "Data//SchoolYear//" + Year + "//" + NameClasses + CsvTail;
							fstream f1;
							f1.open(FileName, ios::out);
							f1 << "No" << "," << "ID" << "," << "Name" << "," << "Birth" << "," << "Sex" << "," << "IDSocial";;
							f1.close();
							int count = CheckRowInFile(filename);
							file.open("Data//SchoolYear//" + Year + "//class_info.csv", ios::app);
							file << endl << count << "," << CheckYear << name << i << "," << NameMajor << "," << numberStudent << "," << YearStudent;
							file.close();
							ImportRandom(Year, NameClasses);
						}

						GotoXY(43, 23);
						cout << "CREATE CLASS SUCCESSFUL" << endl;
						Sleep(1000);
					}
					else
					{
						GotoXY(43, 21);
						cout << "Max Number Of Class is 4! Try Again!!!" << endl;
						Sleep(1000);
					}
				}
				else
				{
					GotoXY(43, 20);
					cout << "Max Number Of Student is 100! Try Again!!!" << endl;
					Sleep(1000);
				}


			}
		}
		else
		{
			GotoXY(43, 17);
			cout << "Name abbreviations class is malformed!! Try again" << endl;
			Sleep(1000);
		}

	}
}

int RunMenuCreateClass()
{
	char ch;
	int command;

	while (true)
	{
		ShowPointer();
		system("cls");

		GotoXY(40, 12);
		string MenuView[] = { "1. Create 1 Class",
			"2. Create Auto Classes And Import Info",
			"3. Exit" };
		DrawMenu(MenuView, 3, 47, 12, 1, &DrawASCIIMenuView);
		command = MoveAndChoose(3, MenuView, 47, 12, 1);
		switch (command)
		{
		case 0:
		{
			system("cls");
			CreateNewClass();
			system("cls");
			break;
		}
		case 1:
		{
			system("cls");
			CreateAutoClassAndImportRandomInfo();
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
