#include "ReadData.h"
#include <string>
#include <fstream>
using namespace std;

void ReadOneInfo(User& A, ifstream& fIn) {
	string NO_temp;
	std::getline(fIn, NO_temp, ',');
	A.info.NoInClass = stoi(NO_temp);
	std::getline(fIn, A.info.IDSt, ',');// giáo viên thì sẽ là id đăng nhập
	getline(fIn, A.info.NameSt, ',');
	getline(fIn, A.info.Birthday, ',');
	getline(fIn, A.info.sex, ',');
	getline(fIn, A.info.IDSocial);
	A.info.head = NULL;
}

void ReadInfo(User& A, SchoolYear SY) {
	string year_path = "Data/SchoolYear/" + SY.Year + '/';
	string fileName;
	if (A.role == 1) {
		fileName = year_path + A.info.Class + CsvTail;
	}
	else {
		fileName = year_path + "staff.csv";
	}
	ifstream info_file;
	info_file.open(fileName, ios::in);
	string temp;
	getline(info_file, temp);
	while (info_file.eof() == false) {
		ReadOneInfo(A, info_file);
		if (A.IDUser.compare(A.info.IDSt) == 0) {
			break;
		}
		else {
			continue;
		}
	}
	info_file.close();
}

void ReadCourse(User A, SchoolYear Y)
{
	system("cls");
	TextBgColor(4, 7);
	PrintText(".-.  .-. .----. .-. .-..----.     .---.  .----. .-. .-..----.  .----..----.", 20, 4);
	PrintText(" \\ \\/ / /  {}  \\| { } || {}  }   /  ___\}/  {}  \\| { } || {}  \}{ {__  | {__  ", 20, 5);
	PrintText("  }  {  \\      /| {_} || .-. \\   \\     }\\      /| {_} || .-. \\.-._} }| {__ ", 20, 6);
	PrintText("  `--'   `----' `-----'`-' `-'    `---'  `----' `-----'`-' `-'`----' `----'", 20, 7);
	DrawRectangle(1, 14, 115, 2, 3);
	GotoXY(1, 15); std::cout << "N.o";
	GotoXY(8, 15); std::cout << "Id course";
	GotoXY(19, 15); std::cout << "Course name";
	GotoXY(45, 15); std::cout << "Lecturer";
	GotoXY(70, 15); std::cout << "Number of credits";
	GotoXY(90, 15); std::cout << "Max student";
	GotoXY(102, 15); std::cout << "Schedule";
	ifstream fi;
	string fileName = "Data/SchoolYear/" + Y.Year + "/" + Y.SemesterSchool.NameSemester + "/course_info.csv";
	MarkNode* tempo = new MarkNode;
	tempo = A.info.head;
	int i = 1;
	if (tempo == NULL) {
		DrawRectangle(1, 17, 115, 3, 4);
		PrintText("You has not registered for any courses this semester ", 30, 18);
		TextBgColor(0, 15);
		return;
	}
	while (tempo != NULL)
	{
		string fl;
		Course co;
		fi.open(fileName, ios::in);
		getline(fi, fl);
		while (!fi.eof())
		{
			ReadOneCourseInfo(co, fi);
			if (_strcmpi(co.IDCourse.c_str(), tempo->info.ID.c_str()) == 0)
			{
				DrawRectangle(1, 15 + i, 115, 2, 3);
				GotoXY(1, 15 + i); std::cout << i;
				GotoXY(8, 15 + i); std::cout << co.IDCourse;
				GotoXY(19, 15 + i); std::cout << co.NameCourse;
				GotoXY(45, 15 + i); std::cout << co.Teacher;
				GotoXY(78, 15 + i); std::cout << co.NumOfCreadit;
				GotoXY(94, 15 + i); std::cout << co.MaxStudent;
				GotoXY(102, 15 + i); std::cout << co.Schedule;
				i++;
				tempo = tempo->next;
				break;
			}
		}
		fi.close();
		TextBgColor(0, 15);
	}
}

void ReadOneCourseInfo(Course& A, ifstream& fOut)
{
	string flag;
	getline(fOut, A.IDCourse, ',');
	getline(fOut, A.NameCourse, ',');
	getline(fOut, A.Teacher, ',');
	getline(fOut, flag, ',');
	A.NumOfCreadit = stoi(flag, 0, 10);
	getline(fOut, flag, ',');
	A.MaxStudent = stoi(flag, 0, 10);
	getline(fOut, A.DayOfWeek, ',');
	getline(fOut, A.Session[0], ',');
	getline(fOut, A.Session[1]);
	A.Schedule = A.Session[0] + ';' + A.Session[1] + '-' + A.DayOfWeek;
}

void InitListMark(MarkNode*& head) {
	head = NULL;
}

void AddTailListMark(MarkNode*& head, string ID, string Name, string NumOfCreadit) {
	//khởi tạo 1 node
	MarkNode* n1 = new MarkNode;
	n1->info.ID = ID;
	n1->info.Name = Name;
	n1->info.C = NumOfCreadit;
	n1->info.MidtermMark = 0;
	n1->info.FinalMark = 0;
	n1->info.OtherMark = 0;
	n1->info.AvgMark = 0;
	n1->next = NULL;
	MarkNode* temp = head;
	if (head == NULL) {
		head = n1;
		return;
	}
	else {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = n1;
	}
}
//bool checkCourseInSemester(User A, SchoolYear SY){
//	ifstream f;
//	string semester_path = "file_save/SchoolYear/" + SY.year + '/' + SY.SemesterSchool.NameSemester + '/';
//	string class_path = semester_path + "Class/";
//	string fileName = class_path + A.info.Class + CsvTail;
//	f.o
// pen(fileName, ios::in);
//	if (!f.is_open()) {
//		return true;
//	}
//	while (!f.eof()) {
//		getline(f, temp);
//	}
//
//}

int GetCourse(User& A, SchoolYear SY, int Flag) {
	ifstream f;
	string semester_path = "Data/SchoolYear/" + SY.Year + '/' + SY.SemesterSchool.NameSemester + '/';
	string class_path = semester_path + "Class/";
	string course_path = semester_path + "Course/";
	string fileName = class_path + A.info.Class + CsvTail;
	bool IDflag = false;
	f.open(fileName, ios::in);
	if (!f.is_open()) {
		return -1;
	}
	if (Flag == 0) {
		InitListMark(A.info.head);
	}
	while (f.eof() == false) {

		string temp1;
		getline(f, temp1);
		size_t found = temp1.find(",");
		if (found == std::string::npos) {
			if (_strcmpi(temp1.c_str(), A.info.IDSt.c_str()) != 0) {
				continue;
			}
			else {
				return -2;
			}
		}
		int length = f.tellg();
		if (length == -1) {
			f.close();
			f.open(fileName, ios::in);
			f.seekg(0, ios::end);
			int a = f.tellg();
			f.seekg(a - temp1.length(), ios::beg);
		}
		else {
			f.seekg(length - temp1.length() - 2, ios::beg);
		}
		string temp;
		getline(f, temp, ',');
		if (temp.compare(A.info.IDSt) != 0) {
			getline(f, temp);
		}
		else {
			string temp1;
			getline(f, temp1);
			string IDtemp = "";
			for (int i = 0; i < temp1.length(); i++) {
				if (temp1[i] == ',' || i == temp1.length() - 1)
				{
					if (i == temp1.length() - 1) {
						IDtemp += temp1[i];
					}
					ifstream fi;
					string fileName = "Data/SchoolYear/" + SY.Year + "/" + SY.SemesterSchool.NameSemester + "/course_info.csv";
					fi.open(fileName, ios::in);
					string temp;
					string NumOfCreadit;
					while (!fi.eof()) {
						getline(fi, temp, ',');
						if (_strcmpi(temp.c_str(), IDtemp.c_str()) == 0) {
							getline(fi, temp, ',');
							getline(fi, NumOfCreadit, ',');
							getline(fi, NumOfCreadit, ',');
							break;
						}
						else {
							getline(fi, temp);
						}
					}
					AddTailListMark(A.info.head, IDtemp, temp, NumOfCreadit);
					IDtemp = "";
					fi.close();
				}
				else if (temp1[i] != ',') {
					IDtemp += temp1[i];
				}
			}
			f.close();
			return 0;
		}
	}

}

void BackASemester(SchoolYear& SY) {
	if (SY.SemesterSchool.NameSemester.back() == '1' || SY.SemesterSchool.NameSemester.back() == '0') {
		string year = "";
		for (int i = 0; i < 4; i++) {
			year += SY.Year[i];
		}
		int Y = atoi(year.c_str());
		Y--;
		SY.Year = to_string(Y) + "-" + year;
		SY.SemesterSchool.NameSemester = "Semester3";
	}
	else {
		if (SY.SemesterSchool.NameSemester.back() == '2') {
			SY.SemesterSchool.NameSemester.pop_back();
			SY.SemesterSchool.NameSemester.push_back('1');
		}
		else if (SY.SemesterSchool.NameSemester.back() == '3') {
			SY.SemesterSchool.NameSemester.pop_back();
			SY.SemesterSchool.NameSemester.push_back('2');
		}
	}
}

void GetAllCourse(User& A, SchoolYear SY) {
	InitListMark(A.info.head);
	int i = 0;
	int count = 0;
	do {
		i = GetCourse(A, SY, 1);
		if (i == -1) {
			break;
		}
		GetScore(A, SY, count);
		BackASemester(SY);
	} while (i != -1);
}

void DeleteMarkNode(MarkNode*& head, string ID) {
	MarkNode** Dp = &head;
	while (*Dp != NULL) {
		MarkNode* temp = *Dp;
		if (_strcmpi(temp->info.ID.c_str(), ID.c_str()) == 0) {
			*Dp = temp->next;
			delete (temp);
		}
		else
			Dp = &(temp->next);
	}
}

void GetOneScore(MarkNode*& A, string ID, ifstream& fIn) {
	string temp;
	getline(fIn, temp);
	while (!fIn.eof()) {
		getline(fIn, temp, ',');// doc stt
		getline(fIn, temp, ',');//doc mssv
		if (_strcmpi(temp.c_str(), ID.c_str()) == 0) {
			getline(fIn, temp, ',');//doc ten
			getline(fIn, temp, ',');//doc lop
			getline(fIn, temp, ',');
			A->info.MidtermMark = atof(temp.c_str());
			getline(fIn, temp, ',');
			A->info.FinalMark = atof(temp.c_str());
			getline(fIn, temp, ',');
			A->info.OtherMark = atof(temp.c_str());
			getline(fIn, temp);
			A->info.AvgMark = atof(temp.c_str());
			return;
		}
		else {
			getline(fIn, temp);
		}
	}
}

void GetScore(User& A, SchoolYear SY, int& i) {
	ifstream f;
	string SemesterPath = "Data/SchoolYear/" + SY.Year + '/' + SY.SemesterSchool.NameSemester + '/';
	string CoursePath = SemesterPath + "Course/score/";
	i = 0;
	MarkNode* temp = A.info.head;
	while (temp != NULL) {
		string fileName = CoursePath + temp->info.ID + CsvTail;
		f.open(fileName, ios::in);
		if (f.good()) {
			GetOneScore(temp, A.IDUser, f);
		}
		else {
			temp->info.FinalMark = 0;
			temp->info.MidtermMark = 0;
			temp->info.OtherMark = 0;
			temp->info.AvgMark = 0;
		}
		f.close();
		i++;
		temp = temp->next;
	}
}

void SaveMark(User& A, Mark* B, int i, SchoolYear SY) {
	string Str = ',' + A.info.IDSt + ',' + A.info.NameSt + ',' + A.info.Class + ',' + to_string(B[i].MidtermMark) + ',' + to_string(B[i].FinalMark) + ',' + to_string(B[i].OtherMark) + ',' + to_string(B[i].AvgMark);
	fstream file_prv, file_aft;
	string fileName = "Data/SchoolYear/" + SY.Year + '/' + SY.SemesterSchool.NameSemester + "/Course/score/" + B[i].ID;
	bool flag_first_line = true;
	string oldName = fileName + CsvTail;
	string newName = fileName + "new" + CsvTail;
	file_prv.open(oldName, ios::in);
	file_aft.open(newName, ios::out);
	MarkNode* temp = A.info.head;
	for (int j = 0; j < i; j++) {
		temp = temp->next;
	}
	temp->info = B[i];
	string temp_str;
	while (file_prv.eof() == false) {
		getline(file_prv, temp_str, ',');
		if (flag_first_line == true) {
			flag_first_line = false;
			file_aft << temp_str;
		}
		else {
			file_aft << endl << temp_str;
		}
		getline(file_prv, temp_str, ',');
		if (_strcmpi(temp_str.c_str(), A.info.IDSt.c_str()) == 0) {
			getline(file_prv, temp_str);
			file_aft << Str;
		}
		else {
			file_aft << ',' << temp_str;
			getline(file_prv, temp_str);
			file_aft << ',' << temp_str;
		}
	}

	file_prv.close();
	file_aft.close();
	// removing the existing file
	remove(oldName.c_str());
	// renaming the updated file with the existing file name
	rename(newName.c_str(), oldName.c_str());
}

void InsertMark(string& Data, int Limit, int& Flag) {
	char ch;
	do
	{
		ch = _getch();
		if (ch == 8) {
			if (Data.size() > 0) {
				Data.pop_back();
				GotoXY(ReturnX() - 1, ReturnY());
				cout << " ";
				GotoXY(ReturnX() - 1, ReturnY());
			}
		}
		else if (((ch >= 48 && ch <= 57) || ch == '.') && Data.size() < Limit) {
			cout << ch;
			Data.push_back(ch);
		}
		else if (ch == 27) {
			Flag = -1;
			return;
		}
	} while (ch != 13);
}

Mark* ReadFileScoreOfCourse(SchoolYear SY, string IDCourse, int& n) {
	string fileName = "Data/SchoolYear/" + SY.Year + '/' + SY.SemesterSchool.NameSemester + "/Course/score/" + IDCourse + CsvTail;
	ifstream f;
	f.open(fileName, ios::in);
	if (!f.good()) {
		return NULL;
	}
	n = CountLine(fileName) - 1;
	Mark* M = new Mark[n];
	string temp;
	getline(f, temp);
	for (int i = 0; i < n; i++) {
		getline(f, temp, ',');
		getline(f, M[i].ID, ',');
		getline(f, M[i].Name, ',');
		getline(f, M[i].C, ',');
		getline(f, temp, ',');
		M[i].MidtermMark = atof(temp.c_str());
		getline(f, temp, ',');
		M[i].FinalMark = atof(temp.c_str());
		getline(f, temp, ',');
		M[i].OtherMark = atof(temp.c_str());
		getline(f, temp);
		M[i].AvgMark = atof(temp.c_str());
	}
	f.close();
	return M;
}

void SaveMarkWithListCousre(string IDCourse, Mark B, SchoolYear SY) {
	string Str = ',' + B.ID + ',' + B.Name + ',' + B.C + ',' + to_string(B.MidtermMark) + ',' + to_string(B.FinalMark) + ',' + to_string(B.OtherMark) + ',' + to_string(B.AvgMark);
	fstream file_prv, file_aft;
	string fileName = "Data/SchoolYear/" + SY.Year + '/' + SY.SemesterSchool.NameSemester + "/Course/score/" + IDCourse;
	bool flag_first_line = true;
	string oldName = fileName + CsvTail;
	string newName = fileName + "new" + CsvTail;
	file_prv.open(oldName, ios::in);
	file_aft.open(newName, ios::out);
	string temp_str;
	while (file_prv.eof() == false) {
		getline(file_prv, temp_str, ',');
		if (flag_first_line == true) {
			flag_first_line = false;
			file_aft << temp_str;
		}
		else {
			file_aft << endl << temp_str;
		}
		getline(file_prv, temp_str, ',');
		if (_strcmpi(temp_str.c_str(), B.ID.c_str()) == 0) {
			getline(file_prv, temp_str);
			file_aft << Str;
		}
		else {
			file_aft << ',' << temp_str;
			getline(file_prv, temp_str);
			file_aft << ',' << temp_str;
		}
	}

	file_prv.close();
	file_aft.close();
	// removing the existing file
	remove(oldName.c_str());
	// renaming the updated file with the existing file name
	rename(newName.c_str(), oldName.c_str());
}

Course* ReadFileListCourse(User A, SchoolYear SY, int& n) {
	string fileName = "Data/SchoolYear/" + SY.Year + '/' + SY.SemesterSchool.NameSemester + "/course_info" + CsvTail;
	ifstream f;
	f.open(fileName, ios::in);
	if (!f.good()) {
		DrawRectangle(3, 14, 115, 3, 4);
		PrintText("Can't open information file.", 47, 15);
		TextBgColor(0, 15);
		Sleep(1800);
		return NULL;
	}
	n = CountLine(fileName) - 1;
	if (n == 0) {
		return NULL;
	}
	Course* M = new Course[n];
	string temp;
	getline(f, temp);
	for (int i = 0; i < n; i++) {
		getline(f, M[i].IDCourse, ',');
		getline(f, M[i].NameCourse, ',');
		getline(f, M[i].Teacher, ',');
		getline(f, temp, ',');
		M[i].NumOfCreadit = atoi(temp.c_str());
		getline(f, temp, ',');
		M[i].MaxStudent = atoi(temp.c_str());
		getline(f, M[i].DayOfWeek, ',');
		getline(f, M[i].Session[0], ',');
		getline(f, M[i].Session[1]);
	}
	f.close();
	return M;
}

Course* GetCourseOfStudent(User A, SchoolYear SY, int& n) {
	string fileName = "Data/SchoolYear/" + SY.Year + '/' + SY.SemesterSchool.NameSemester + "/course_info" + CsvTail;
	ifstream f;
	f.open(fileName, ios::in);
	if (!f.good()) {
		return NULL;
	}
	string temp;
	GetCourse(A, SY);
	if (A.info.head == NULL) {
		return NULL;
	}
	n = 0;
	MarkNode* count = A.info.head;
	while (count != NULL) {
		n++;
		count = count->next;
	}
	count = A.info.head;
	Course* M = new Course[n];
	int i = 0;
	while (i < n && !f.eof()) {
		getline(f, M[i].IDCourse, ',');
		if (_strcmpi(M[i].IDCourse.c_str(), count->info.ID.c_str()) == 0) {
			getline(f, M[i].NameCourse, ',');
			getline(f, M[i].Teacher, ',');
			getline(f, temp, ',');
			M[i].NumOfCreadit = atoi(temp.c_str());
			getline(f, temp, ',');
			M[i].MaxStudent = atoi(temp.c_str());
			getline(f, M[i].DayOfWeek, ',');
			getline(f, M[i].Session[0], ',');
			getline(f, M[i].Session[1]);
			i++;
			count = count->next;
			f.close();
			f.open(fileName, ios::in);
		}
		else {
			getline(f, temp);
		}
	}
	return M;
}

Data* ReadFileStudentInfoOfCourse(SchoolYear SY, string IDCourse, int& n) {
	string fileName = "Data/SchoolYear/" + SY.Year + '/' + SY.SemesterSchool.NameSemester + "/Course/" + IDCourse + CsvTail;
	ifstream f;
	f.open(fileName, ios::in);
	if (!f.good()) {
		return NULL;
	}
	n = CountLine(fileName) - 1;
	Data* M = new Data[n];
	string temp;
	getline(f, temp);
	for (int i = 0; i < n; i++) {
		getline(f, M[i].IDSt, ',');
		getline(f, M[i].NameSt, ',');
		getline(f, M[i].Birthday, ',');
		getline(f, M[i].sex, ',');
		getline(f, M[i].IDSocial);
		M[i].NoInClass = i + 1;
	}
	f.close();
	return M;
}
