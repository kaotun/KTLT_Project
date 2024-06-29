#include "Struct.h"
#include "CourseFunction.h"
#include "ConsoleProcess.h"
#include "ReadData.h"
#include "Login.h"
#include "StaffFunction.h"

// hàm tổng quát, command_flag >=0, thì thêm data vào file, <0 xóa data khỏi file
void RewriteCourseOfStudentFile(User user, string FileName, string Data, int CommandFlag) {
	fstream FilePrv, FileAft;
	string OldName = FileName + CsvTail;
	string NewName = FileName + "new" + CsvTail;
	FilePrv.open(OldName, ios::in);
	FileAft.open(NewName, ios::out);
	string temp;
	bool FlagChange = true;
	while (FilePrv.eof() == false) {
		//đọc, ghi lại số thứ tự
		/*getline(file_prv, temp, ',');
		file_aft << temp << ',';*/
		//đọc ghi lại mssv
		getline(FilePrv, temp);
		string temp1 = "";
		int i = 0;
		for (i = 0; i < temp.length(); i++) {
			if (temp[i] == ',' || i == temp.length() - 1)
			{
				if (i == temp.length() - 1) {
					temp1 += temp[i];
				}
				break;
			}
			else if (temp[i] != ',') {
				temp1 += temp[i];
			}
		}
		if (user.IDUser.compare(temp1) != 0) {
			if (FlagChange == true) {
				FileAft << temp;
				FlagChange = false;
			}
			else {
				FileAft << '\n' << temp;
			}
		}
		else {
			if (CommandFlag >= 0) {
				temp1 = temp + ',' + Data;
			}
			else {
				string temp2 = "";
				for (i = i + 1; i < temp.length(); i++) {
					if (temp[i] == ',' || i == temp.length() - 1)
					{
						if (i == temp.length() - 1) {
							temp2 += temp[i];
						}
						if (_strcmpi(temp2.c_str(), Data.c_str()) != 0) {
							temp1 = temp1 + ',' + temp2;
						}
						temp2 = "";
					}
					else if (temp[i] != ',') {
						temp2 += temp[i];
					}
				}
			}
			if (FlagChange == true) {
				FileAft << temp1;
				FlagChange = false;
			}
			else {
				FileAft << '\n' << temp1;
			}
		}
	}
	FilePrv.close();
	FileAft.close();
	// removing the existing file
	remove(OldName.c_str());
	// renaming the updated file with the existing file name
	rename(NewName.c_str(), OldName.c_str());
}

void RewriteCourseFile(User Usertmp, string FileName, int CommandFlag) {
	fstream FilePrv, FileAft;
	string OldName = FileName + CsvTail;
	string NewName = FileName + "new" + CsvTail;
	FilePrv.open(OldName, ios::in);
	FileAft.open(NewName, ios::out);
	string temp;
	bool FlagChange = true;
	while (FilePrv.eof() == false) {
		//đọc, ghi lại số thứ tự
		/*getline(file_prv, temp, ',');
		file_aft << temp << ',';*/
		//đọc ghi lại mssv
		getline(FilePrv, temp, ',');
		if (_strcmpi(temp.c_str(), Usertmp.info.IDSt.c_str()) == 0) {
			getline(FilePrv, temp);
			continue;
		}
		else {
			if (FlagChange == true) {
				FileAft << temp << ',';
				FlagChange = false;
			}
			else {
				FileAft << '\n' << temp << ',';
			}
			getline(FilePrv, temp);
			FileAft << temp;
		}
	}
	if (CommandFlag >= 0) {
		temp = Usertmp.info.IDSt + ',' + Usertmp.info.NameSt + ',' + Usertmp.info.Birthday + ',' + Usertmp.info.sex + ',' + Usertmp.info.IDSocial;
		if (FlagChange == true) {
			FileAft << temp;
			FlagChange = false;
		}
		else {
			FileAft << '\n' << temp;
		}
	}
	FilePrv.close();
	FileAft.close();
	// removing the existing file
	remove(OldName.c_str());
	// renaming the updated file with the existing file name
	rename(NewName.c_str(), OldName.c_str());
}

void MoveUpMenu(int X, int& Y, int dis) {
	Y = Y - (dis + 1);
	GotoXY(X, Y);
}

void MoveDownMenu(int X, int& Y, int dis) {
	Y = Y + (dis + 1);
	GotoXY(X, Y);
}

int MoveAndChoose(int a, string A[], int _X, int _Y, int dis) { //ham di chuyen len xuong va chon doi tuong trong cac dang menu
	char _COMMAND = _getch();
	int X = _X, Y = _Y;
	int i = 0;
	int maxlength = A[0].length();
	for (int j = 1; j < a; j++) {
		if (maxlength < A[j].length()) {
			maxlength = A[j].length();
		}
	}
	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27) {  //27 Esc
			return -1;
		}
		else {
			if (i >= 0 && i < a && Y <= 23 + a) {
				if (_COMMAND == 72 && Y > _Y) {       //72 di len
					DrawRectangle(X, Y, maxlength, 1, 12);
					GotoXY(X, Y);
					TextBgColor(0, 12);
					cout << A[i];
					MoveUpMenu(X, Y, dis);
					i--;
					DrawRectangle(X, Y, maxlength, 1, 12);
					TextBgColor(12, 0);
					GotoXY(X, Y);
					cout << A[i];
					TextBgColor(0, 15);
				}
				else if (_COMMAND == 80 && Y < _Y + (dis + 1) * (a - 1)) {     //80 di xuong
					DrawRectangle(X, Y, maxlength, 1, 12);
					GotoXY(X, Y);
					TextBgColor(0, 12);
					cout << A[i];
					MoveDownMenu(X, Y, dis);
					i++;
					DrawRectangle(X, Y, maxlength, 1, 12);
					TextBgColor(12, 0);
					GotoXY(X, Y);
					cout << A[i];
					TextBgColor(0, 15);
				}
				else if (_COMMAND == 13) {    //13 Enter
					return i;
				}
			}

		}
	}
}

void DrawMenu(string* S, int n, int x, int y, int dis, DrawASCII Fun) {
	HidePointer();

	int maxlength = S[0].length();
	for (int j = 1; j < n; j++) {
		if (maxlength < S[j].length()) {
			maxlength = S[j].length();
		}
	}
	maxlength += 20;
	Fun();
	DrawRectangle(x - 10, y, maxlength, n + (n - 1) * dis, 12);
	for (int i = 0; i < n; i++) {
		if (i == 0) {
			DrawRectangle(x, y, maxlength - 20, 1, 12);
			TextBgColor(12, 0);
			PrintText(S[i], x, y + (dis + 1) * i);
		}
		else
			TextBgColor(0, 12);
		PrintText(S[i], x, y + (dis + 1) * i);
		TextBgColor(0, 15);
	}
}

int GetYearData(string* Data1, int* Data2, string FileName) {

	ifstream fIn;
	fIn.open(FileName, ios::in);
	string temp;
	int i = 0;
	getline(fIn, temp);
	while (!fIn.eof()) {
		getline(fIn, Data1[i], ',');
		getline(fIn, temp);
		Data2[i] = atoi(temp.c_str());
		i++;
	}
	return i;
}

void ChangeYearSemester(SchoolYear& SY) {
	string* year;
	int* semester;
	string filename = "Data\\year_semester.csv";
	int n = CountLine(filename) - 1;
	year = new string[n];
	semester = new int[n];
	GetYearData(year, semester, filename);
	system("cls");

	DrawMenu(year, n, 55, 15, 1, &DrawASCIIChangeYear);
	int A = MoveAndChoose(n, year, 55, 15, 1);
	if (A == -1) {
		return;
	}
	string* SemesterOfYear = new string[semester[A]];
	for (int i = 0; i < semester[A]; i++) {
		SemesterOfYear[i] = "Semester" + to_string(i + 1);
	}
	system("cls");

	DrawMenu(SemesterOfYear, semester[A], 55, 15, 1, &DrawASCIIChangeSemester);
	int i = MoveAndChoose(semester[A], SemesterOfYear, 55, 15, 1);
	if (i == -1) {
		return;
	}
	SY.Year = year[A];
	SY.SemesterSchool.NameSemester = SemesterOfYear[i];
}

void DisPlayCourseOfStudent(SchoolYear SY, User A) {
	char ch;
	HidePointer();
	GetCourse(A, SY);
	ReadCourse(A, SY);
	do {
		DrawRectangle(27, 29, 60, 1, 3);
		TextColor(496);
		string text = SY.SemesterSchool.NameSemester + "; Year: " + SY.Year + ".   Press[C] to change!";
		PrintText(text, 32, 29);
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			return;
		}
		else {
			//Control Up down 
			if (ch == 'c' || ch == 'C') //up
			{
				ChangeYearSemester(SY);
				int a = GetCourse(A, SY);
				if (a == -1) {
					DrawRectangle(3, 14, 115, 3, 4);
					PrintText("Invalid school year ", 50, 15);
					TextBgColor(0, 15);
					Sleep(1800);
					DetermineYearSemesterNow(SY.Year, SY.SemesterSchool.NameSemester);
				}
				ReadCourse(A, SY);
			}
		}
	} while (true);
}

void EditScore(User& A, SchoolYear SY, Mark* M) {
	char ch;
	int line_now = 1;
	int x = 15, y = 14;
	int line = 0;
	MarkNode* temp = A.info.head;
	while (temp != NULL) {
		line++;
		temp = temp->next;
	}
	if (M == NULL) {
		DrawRectangle(0, 17, 120, 3, 6);
		PrintText("He/she has not registered for any courses this semester ", 30, 18);
		Sleep(2700);
		TextBgColor(0, 15);
		return;
	}
	DrawRectangle(1, y + line_now, 115, 1, 14);
	TextBgColor(0, 14);
	ViewOneLine(M[line_now - 1], x, y + line_now);
	do {
		HidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			DrawRectangle(1, y + line_now, 115, 1, 11);
			TextBgColor(0, 11);
			ViewOneLine(M[line_now - 1], x, y + line_now);
			break;
		}
		else {
			//Control Up down 
			if (ch == 72 && line_now > 1) //up
			{
				DrawRectangle(1, y + line_now, 115, 1, 11);
				TextBgColor(0, 11);
				ViewOneLine(M[line_now - 1], x, y + line_now);

				line_now--;
				DrawRectangle(1, y + line_now, 115, 1, 14);
				TextBgColor(0, 14);
				ViewOneLine(M[line_now - 1], x, y + line_now);
			}
			if (ch == 80 && line_now < line) //down
			{
				DrawRectangle(1, y + line_now, 115, 1, 11);
				TextBgColor(0, 11);
				ViewOneLine(M[line_now - 1], x, y + line_now);

				line_now++;
				DrawRectangle(1, y + line_now, 115, 1, 14);
				TextBgColor(0, 14);
				ViewOneLine(M[line_now - 1], x, y + line_now);
			}
			if (ch == 13) {
				string fCheck = "Data\\SchoolYear\\" + SY.Year + '\\' + SY.SemesterSchool.NameSemester + "\\Course\\score\\" + M[line_now - 1].ID + CsvTail;
				fstream fcheck;
				fcheck.open(fCheck, ios::in);
				if (!fcheck.good())
				{
					GotoXY(x + 42, y + line_now);
					cout << "Fail!! This subject has not been graded by the teacher yet.";
					Sleep(900);
					DrawRectangle(1, y + line_now, 115, 1, 14);
					TextBgColor(0, 14);
					ViewOneLine(M[line_now - 1], x, y + line_now);
					fcheck.close();
					continue;
				}
				else {
					fcheck.close();
					int y_now = y + line_now;
					int x_now = x + 42, x_max = x + 70, x_min = x + 42;
					string S[] = { to_string(M[line_now - 1].MidtermMark),to_string(M[line_now - 1].FinalMark),to_string(M[line_now - 1].OtherMark) };
					DrawRectangle(x + 42, y_now, 14, 1, 15);
					TextBgColor(0, 15);
					PrintText(to_string(M[line_now - 1].MidtermMark), x + 42, y_now);
					char CH;
					do
					{
						CH = _getch();
						//ESC
						if (CH == 27) {
							DrawRectangle(x_now, y_now, 14, 1, 14);
							TextBgColor(0, 14);
							PrintText(S[(x_now - x_min) / 14], x_now, y_now);
							break;
						}
						else {
							//Left 
							if (CH == 75 && x_now > x_min) {
								DrawRectangle(x_now, y_now, 14, 1, 14);
								TextBgColor(0, 14);
								PrintText(S[(x_now - x_min) / 14], x_now, y_now);

								x_now = x_now - 14;
								DrawRectangle(x_now, y_now, 14, 1, 15);
								TextBgColor(0, 15);
								PrintText(S[(x_now - x_min) / 14], x_now, y_now);
							}
							//Right
							if (CH == 77 && x_now < x_max) {
								DrawRectangle(x_now, y_now, 14, 1, 14);
								TextBgColor(0, 14);
								PrintText(S[(x_now - x_min) / 14], x_now, y_now);

								x_now = x_now + 14;
								DrawRectangle(x_now, y_now, 14, 1, 15);
								TextBgColor(0, 15);
								PrintText(S[(x_now - x_min) / 14], x_now, y_now);
							}

							//[ENTER]
							if (CH == 13) {
								DrawRectangle(x_now, y_now, 14, 1, 15);
								TextBgColor(0, 15);
								float i;
								string mark;
								int flag = 0;
								do {
									mark = "";
									GotoXY(x_now, y_now);
									InsertMark(mark, 5, flag);
									if (flag == -1) {
										DrawRectangle(x_now, y_now, 14, 1, 15);
										TextBgColor(0, 15);
										PrintText(S[(x_now - x_min) / 14], x_now, y_now);
										break;
									}
									else {
										i = atof(mark.c_str());
										if (i > 10) {
											GotoXY(x_now, y_now);
											cout << "Erroll!!";
											Sleep(900);
											DrawRectangle(x_now, y_now, 14, 1, 15);
										}
									}
								} while (i > 10);
								if (flag == 0) {
									int a = (x_now - x_min) / 14;
									switch (a)
									{
									case 0:
										M[line_now - 1].MidtermMark = i;
										S[(x_now - x_min) / 14] = to_string(M[line_now - 1].MidtermMark);
										break;
									case 1:
										M[line_now - 1].FinalMark = i;
										S[(x_now - x_min) / 14] = to_string(M[line_now - 1].FinalMark);
										break;
									case 2:
										M[line_now - 1].OtherMark = i;
										S[(x_now - x_min) / 14] = to_string(M[line_now - 1].OtherMark);
										break;
									default:
										break;
									}
									M[line_now - 1].AvgMark = 0.3 * M[line_now - 1].MidtermMark + 0.6 * M[line_now - 1].FinalMark + 0.1 * M[line_now - 1].OtherMark;
									DrawRectangle(1, y + line_now, 115, 1, 14);
									TextBgColor(0, 14);
									ViewOneLine(M[line_now - 1], x, y + line_now);
									DrawRectangle(x_now, y_now, 14, 1, 15);
									TextBgColor(0, 15);
									PrintText(S[(x_now - x_min) / 14], x_now, y_now);
									SaveMark(A, M, line_now - 1, SY);
								}
							}

						}
					} while (true);
				}

			}
		}
	} while (true);
	TextBgColor(0, 15);
}

void DisPlayMarkOfStudent(SchoolYear SY, User A) {
	char ch;
	int a = GetCourse(A, SY);
	ViewAllScoreOfOneStudent(A, SY);
	do {
		HidePointer();
		DrawRectangle(27, 29, 60, 1, 3);
		TextColor(499);
		string text = SY.SemesterSchool.NameSemester + "; Year: " + SY.Year + ".   Press[C] to change!";
		PrintText(text, 32, 29);
		ch = getch();
		//[ESC]
		if (ch == 27) {
			return;
		}
		else {
			if (ch == 'c' || ch == 'C')
			{
				ChangeYearSemester(SY);
				int a = GetCourse(A, SY);
				if (a == -1) {
					DrawRectangle(3, 14, 115, 3, 4);
					PrintText("Invalid school year ", 50, 15);
					TextBgColor(0, 15);
					Sleep(1800);
					DetermineYearSemesterNow(SY.Year, SY.SemesterSchool.NameSemester);
				}
				ViewAllScoreOfOneStudent(A, SY);
			}
		}
	} while (true);
	TextBgColor(0, 15);
}

void EditScoreInListCourse(User& A, SchoolYear SY, string IDCourse) {
	int n = 0;
	Mark* M = ReadFileScoreOfCourse(SY, IDCourse, n);
	if (M == NULL) {
		//thong báo mở file thất bại
		TextBgColor(0, 15);
		system("cls");
		DrawRectangle(3, 14, 115, 3, 4);
		PrintText("Fail!! The teacher has not entered the score for this course!! ", 35, 15);
		TextBgColor(0, 15);
		Sleep(1800);
		return;
	}
	char ch;
	int line_now = 0;
	int x = 10, y = 14;
	int tab_now = ViewScoreOfCourseInYear(M, n);
	if (tab_now == -1) {
		TextBgColor(0, 15);
		return;
	}
	DrawRectangle(1, y + line_now, 115, 1, 14);
	TextBgColor(0, 14);
	ViewOneScoreOfCourse(M[tab_now * 10], x, y);
	int count = tab_now * 10;
	do {
		if (tab_now == -1) {
			TextBgColor(0, 15);
			return;
		}
		HidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			tab_now = ViewScoreOfCourseInYear(M, n);
			if (tab_now == -1) {
				TextBgColor(0, 15);
				return;
			}
			line_now = 0;
			count = tab_now * 10;
			DrawRectangle(1, y + line_now, 115, 1, 14);
			TextBgColor(0, 14);
			ViewOneScoreOfCourse(M[tab_now * 10], x, y);
		}
		else {
			//Control Up down 
			if (ch == 72 && line_now > 0) //up
			{
				DrawRectangle(1, y + line_now, 115, 1, 3);
				TextBgColor(0, 3);
				ViewOneScoreOfCourse(M[count], x, y + line_now);

				line_now--;
				count--;
				DrawRectangle(1, y + line_now, 115, 1, 14);
				TextBgColor(0, 14);
				ViewOneScoreOfCourse(M[count], x, y + line_now);
			}
			else if (ch == 72 && line_now == 0 && count > 0) {
				count--;
				DrawRectangle(0, y, 120, 11, 3);
				ViewTenScoreOfCourse(M, count, n, x, y);
				DrawRectangle(1, y + line_now, 115, 1, 14);
				TextBgColor(0, 14);
				ViewOneScoreOfCourse(M[count], x, y + line_now);
			}
			else if (ch == 80 && line_now < 9 && count < n - 1) //down
			{
				DrawRectangle(1, y + line_now, 115, 1, 3);
				TextBgColor(0, 3);
				ViewOneScoreOfCourse(M[count], x, y + line_now);

				line_now++;
				count++;
				DrawRectangle(1, y + line_now, 115, 1, 14);
				TextBgColor(0, 14);
				ViewOneScoreOfCourse(M[count], x, y + line_now);
			}
			else if (ch == 80 && line_now == 9 && count < n - 1) {
				count++;
				DrawRectangle(0, y, 120, 11, 3);
				ViewTenScoreOfCourse(M, count - 9, n, x, y);
				DrawRectangle(1, y + line_now, 115, 1, 14);
				TextBgColor(0, 14);
				ViewOneScoreOfCourse(M[count], x, y + line_now);
			}
			if (ch == 13) {
				int y_now = y + line_now;
				int x_now = x + 52, x_max = x + 80, x_min = x + 52;
				string S[] = { to_string(M[count].MidtermMark),to_string(M[count].FinalMark),to_string(M[count].OtherMark) };
				DrawRectangle(x_now, y_now, 14, 1, 15);
				TextBgColor(0, 15);
				PrintText(to_string(M[count].MidtermMark), x_now, y_now);
				char CH;
				do
				{
					CH = _getch();
					//ESC
					if (CH == 27) {
						DrawRectangle(x_now, y_now, 14, 1, 14);
						TextBgColor(0, 14);
						PrintText(S[(x_now - x_min) / 14], x_now, y_now);
						break;
					}
					else {
						//Left 
						if (CH == 75 && x_now > x_min) {
							DrawRectangle(x_now, y_now, 14, 1, 14);
							TextBgColor(0, 14);
							PrintText(S[(x_now - x_min) / 14], x_now, y_now);
							x_now = x_now - 14;
							DrawRectangle(x_now, y_now, 14, 1, 15);
							TextBgColor(0, 15);
							PrintText(S[(x_now - x_min) / 14], x_now, y_now);
						}
						//Right
						if (CH == 77 && x_now < x_max) {
							DrawRectangle(x_now, y_now, 14, 1, 14);
							TextBgColor(0, 14);
							PrintText(S[(x_now - x_min) / 14], x_now, y_now);
							x_now = x_now + 14;
							DrawRectangle(x_now, y_now, 14, 1, 15);
							TextBgColor(0, 15);
							PrintText(S[(x_now - x_min) / 14], x_now, y_now);
						}
						//[ENTER]
						if (CH == 13) {
							DrawRectangle(x_now, y_now, 14, 1, 15);
							TextBgColor(0, 15);
							float i;
							string mark;
							int flag = 0;
							do {
								mark = "";
								GotoXY(x_now, y_now);
								InsertMark(mark, 5, flag);
								if (flag == -1) {
									DrawRectangle(x_now, y_now, 14, 1, 15);
									TextBgColor(0, 15);
									PrintText(S[(x_now - x_min) / 14], x_now, y_now);
									break;
								}
								else {
									i = atof(mark.c_str());
									if (i > 10) {
										GotoXY(x_now, y_now);
										cout << "Erroll!!";
										Sleep(900);
										DrawRectangle(x_now, y_now, 14, 1, 15);
									}
								}
							} while (i > 10);
							if (flag == 0) {
								int a = (x_now - x_min) / 14;
								switch (a)
								{
								case 0:
									M[count].MidtermMark = i;
									S[(x_now - x_min) / 14] = to_string(M[count].MidtermMark);
									break;
								case 1:
									M[count].FinalMark = i;
									S[(x_now - x_min) / 14] = to_string(M[count].FinalMark);
									break;
								case 2:
									M[count].OtherMark = i;
									S[(x_now - x_min) / 14] = to_string(M[count].OtherMark);
									break;
								default:
									break;
								}
								M[count].AvgMark = 0.3 * M[count].MidtermMark + 0.6 * M[count].FinalMark + 0.1 * M[count].OtherMark;
								DrawRectangle(1, y + line_now, 115, 1, 14);
								TextBgColor(0, 14);
								ViewOneScoreOfCourse(M[count], x, y + line_now);
								DrawRectangle(x_now, y_now, 14, 1, 15);
								TextBgColor(0, 15);
								PrintText(S[(x_now - x_min) / 14], x_now, y_now);
								SaveMarkWithListCousre(IDCourse, M[count], SY);
							}
						}
					}

				} while (true);


			}
		}
	} while (true);
	TextBgColor(0, 15);
}

void EnrollCourse(User& A, SchoolYear SY) {
	string semesterPath = "Data\\SchoolYear\\" + SY.Year + '\\' + SY.SemesterSchool.NameSemester + '\\';
	string class_path = semesterPath + "Class\\";
	string course_path = semesterPath + "Course\\";
	//hàm trang trí
	//hàm hiện danh sách các môn học.

	Course* course_input = SelectCourse(A, SY, &ReadFileListCourse, &DrawASCIIEnrolCourse);
	if (course_input == NULL) {
		return;
	}
	//kiểm tra xem trong danh sách môn học của sinh viên đã có môn này hay chưa
	GetAllCourse(A, SY);
	MarkNode* Mtemp = A.info.head;
	while (Mtemp != NULL) {
		if (_strcmpi(course_input->IDCourse.c_str(), Mtemp->info.ID.c_str()) == 0) {
			//nếu có thì return.
			DrawASCIIFailEnrol();
			Sleep(1800);
			return;
		}
		Mtemp = Mtemp->next;
	}
	//chưa có thì thêm vào danh sách.
	AddTailListMark(A.info.head, course_input->IDCourse, course_input->NameCourse, to_string(course_input->NumOfCreadit));
	//ghi them vao file;
	string file_cousre_of_class = class_path + A.info.Class;
	RewriteCourseOfStudentFile(A, file_cousre_of_class, course_input->IDCourse, 1);
	string file_cousre = course_path + course_input->IDCourse;
	RewriteCourseFile(A, file_cousre, 1);
	DrawASCIISuccessful();
	Sleep(3000);
}

void DeleteCourse(User& A, SchoolYear SY) {
	string semesterPath = "Data\\SchoolYear\\" + SY.Year + '\\' + SY.SemesterSchool.NameSemester + '\\';
	string class_path = semesterPath + "Class\\";
	string course_path = semesterPath + "Course\\";
	//hàm trang trí
	//hàm hiện danh sách các môn học.
	Course* course_input = SelectCourse(A, SY, &GetCourseOfStudent, &DrawASCIIDeleteCourse);
	if (course_input == NULL) {
		return;
	}
	DeleteMarkNode(A.info.head, course_input->IDCourse);
	string file_cousre_of_class = class_path + A.info.Class;
	RewriteCourseOfStudentFile(A, file_cousre_of_class, course_input->IDCourse, -1);
	string file_cousre = course_path + course_input->IDCourse;
	RewriteCourseFile(A, file_cousre, -1);
	DrawASCIISuccessful();
	Sleep(3000);
	return;
}

void ViewStudentInCourse(User Usertmp, SchoolYear SY) {
	try {
		while (true) {
			User A;
			Course* SLC = SelectCourse(A, SY, &ReadFileListCourse, &DrawASCIIListCourse);
			if (SLC == NULL) {
				return;
			}
			int n = 0;
			Data* M = ReadFileStudentInfoOfCourse(SY, SLC->IDCourse, n);
			ViewStudentInfoOfCourse(M, n);
		}
	}
	catch (const char* err) {
		DrawRectangle(3, 14, 115, 3, 4);
		PrintText(err, 50, 15);
		TextBgColor(0, 15);
		Sleep(1800);
	}
}

void OutputInfo(User A) {
	TextBgColor(3, 0);
	system("cls");
	PrintText(" _            ___                                     _               ", 20, 2);
	PrintText("(_)          / __)                               _   (_)              ", 20, 3);
	PrintText(" _  ____   _| |__   ___    ____  ____   _____  _| |_  _   ___   ____  ", 20, 4);
	PrintText("| ||  _  \\(_   __) / _ \\  / ___)|    \\ (____ |(_   _)| | / _ \\ |  _ \\ ", 20, 5);
	PrintText("| || | | |  | |   | |_| || |    | | | |/ ___ |  | |_ | || |_| || | | |", 20, 6);
	PrintText("|_||_| |_|  |_|    \\___/ |_|    |_|_|_|\\_____|  \\___)|_| \\___/ |_| |_|", 20, 7);
	//TextBgColor(0, 15);

	int a = 0;
	if (A.role == 1) {
		DrawRectangle(30, 12, 50, 16, 14);
		PrintText("Ma so sinh vien: " + A.info.IDSt, 35, 15);
		PrintText("Lop: " + A.info.Class, 35, 17);
		a = 2;
		PrintText("Chuc vu: Hoc sinh", 35, 21 + a);
	}
	else {
		DrawRectangle(30, 12, 50, 13, 14);
		PrintText("Email : " + A.info.IDSt + "@hcmus.edu.vn", 35, 15);
		PrintText("Chuc vu: Admin", 35, 21 + a);
	}
	PrintText("Ho va ten: " + A.info.NameSt, 35, 13);
	PrintText("Ngay sinh: " + A.info.Birthday, 35, 17 + a);
	PrintText("Gioi tinh: " + A.info.sex, 35, 19 + a);

	PrintText("CMND/CCCD: " + A.info.IDSocial, 35, 23 + a);
	TextBgColor(0, 15);
	system("pause");
}

void ViewOneLine(Mark M, int x, int y) {
	PrintText(M.ID, x, y);
	PrintText(M.Name, x + 12, y);//12 ki tu cho id
	PrintText(to_string(M.MidtermMark), x + 42, y);//30 ki tu cho ten
	PrintText(to_string(M.FinalMark), x + 56, y);//14 ki tu cho 1 diem
	PrintText(to_string(M.OtherMark), x + 70, y);//14 ki tu cho 1 diem
	PrintText(to_string(M.AvgMark), x + 84, y);//14 ki tu cho 1 diem
}

Mark* ViewAllScoreOfOneStudent(User A, SchoolYear SY) {
	system("cls");
	int n;
	GetScore(A, SY, n);

	int x = 15;
	int y = 14;
	TextBgColor(4, 7);
	PrintText(" _      _  ____  _____     ____    ____   ___   ____   _____   ", 25, 3);
	PrintText("| |    | |/ ___||_   _|   / ___|  / ___| / _ \\ |  _ \\ |  ___|  ", 25, 4);
	PrintText("| |    | |\\___ \\  | |     \\___ \\ | |    | | | || |_) ||  _|    ", 25, 5);
	PrintText("| |___ | | ___) | | |      ___) || |___ | |_| ||  _ < | |___   ", 25, 6);
	PrintText("|_____||_||____/  |_|     |____/  \\____| \\___/ |_| \\_\\|_____|  ", 25, 7);
	PrintText("                                                               ", 25, 8);
	DrawRectangle(0, 13, 120, n + 3, 3);
	TextBgColor(0, 3);
	PrintText("ID", x, y);
	PrintText("Name of Course", x + 12, y);//12 ki tu cho id
	PrintText("Midterm Mark", x + 42, y);//30 ki tu cho ten
	PrintText("Final Mark", x + 56, y);//14 ki tu cho 1 diem
	PrintText("Other Mark", x + 70, y);//14 ki tu cho 1 diem
	PrintText("Total Mark", x + 84, y);//14 ki tu cho 1 diem
	y++;
	if (n == 0) {
		DrawRectangle(0, 17, 120, 3, 4);
		PrintText("You has not registered for any courses this semester ", 30, 18);
		TextBgColor(0, 7);
		return NULL;
	}
	Mark* M = new Mark[n];
	MarkNode* temp = A.info.head;
	for (int i = 0; i < n; i++) {
		M[i] = temp->info;
		ViewOneLine(M[i], x, y + i);
		temp = temp->next;
	}
	TextBgColor(0, 7);
	return M;
}

void ViewOneScoreOfCourse(Mark M, int x, int y) {
	PrintText(M.ID, x, y);
	PrintText(M.Name, x + 12, y);//12 ki tu cho id
	PrintText(M.C, x + 42, y);
	PrintText(to_string(M.MidtermMark), x + 52, y);//30 ki tu cho ten
	PrintText(to_string(M.FinalMark), x + 66, y);//14 ki tu cho 1 diem
	PrintText(to_string(M.OtherMark), x + 80, y);//14 ki tu cho 1 diem
	PrintText(to_string(M.AvgMark), x + 94, y);//14 ki tu cho 1 diem
}

void ViewTenScoreOfCourse(Mark* M, int i, int n, int x, int y) {
	if (n - i >= 10) {
		for (int j = 0; j < 10; j++) {
			ViewOneScoreOfCourse(M[i + j], x, y + j);
		}
	}
	else {
		for (int j = 0; j < n - i; j++) {
			ViewOneScoreOfCourse(M[i + j], x, y + j);
		}
	}

}

int ViewScoreOfCourseInYear(Mark* M, int n) {
	TextBgColor(0, 15);
	system("cls");
	int x = 10;
	int y = 14;
	TextBgColor(4, 6);
	PrintText(" _      _  ____  _____     ____    ____   ___   ____   _____   ", 25, 3);
	PrintText("| |    | |/ ___||_   _|   / ___|  / ___| / _ \\ |  _ \\ |  ___|  ", 25, 4);
	PrintText("| |    | |\\___ \\  | |     \\___ \\ | |    | | | || |_) ||  _|    ", 25, 5);
	PrintText("| |___ | | ___) | | |      ___) || |___ | |_| ||  _ < | |___   ", 25, 6);
	PrintText("|_____||_||____/  |_|     |____/  \\____| \\___/ |_| \\_\\|_____|  ", 25, 7);
	PrintText("                                                               ", 25, 8);
	DrawRectangle(0, y - 2, 120, 13, 11);
	TextBgColor(0, 11);
	PrintText("ID", x, y - 1);
	PrintText("Name", x + 12, y - 1);//12 ki tu cho id
	PrintText("Class", x + 42, y - 1);
	PrintText("Midterm Mark", x + 52, y - 1);//30 ki tu cho ten
	PrintText("Final Mark", x + 66, y - 1);//14 ki tu cho 1 diem
	PrintText("Other Mark", x + 80, y - 1);//14 ki tu cho 1 diem
	PrintText("Total Mark", x + 94, y - 1);//14 ki tu cho 1 diem
	char ch;
	int tab_now = 0;
	ViewTenScoreOfCourse(M, tab_now * 10, n, x, y);
	do {
		HidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			return-1;
		}
		else {
			//Control Up down 
			if (ch == 72 && tab_now > 0) //up
			{
				tab_now--;
				DrawRectangle(0, y, 120, 11, 11);
				ViewTenScoreOfCourse(M, tab_now * 10, n, x, y);
			}
			if (ch == 80 && tab_now < (n - 1) / 10) //down
			{
				tab_now++;
				DrawRectangle(0, y, 120, 11, 11);
				ViewTenScoreOfCourse(M, tab_now * 10, n, x, y);
			}
			if (ch == 13) {
				return tab_now;
			}
		}
	} while (true);
}

void ViewOneCourseOfListCourse(Course M, int x, int y) {
	PrintText(M.IDCourse, x, y);
	PrintText(M.NameCourse, x + 8, y);//12 ki tu cho id
	PrintText(M.Teacher, x + 33, y);
	PrintText(to_string(M.NumOfCreadit), x + 59, y);//30 ki tu cho ten
	PrintText(to_string(M.MaxStudent), x + 75, y);//14 ki tu cho 1 diem
	PrintText(M.DayOfWeek, x + 87, y);//14 ki tu cho 1 diem
	PrintText(M.Session[0], x + 97, y);//14 ki tu cho 1 diem
	PrintText(M.Session[1], x + 107, y);
}

void ViewTenCourseOfListCourse(Course* M, int i, int n, int x, int y) {
	if (n - i >= 10) {
		for (int j = 0; j < 10; j++) {
			ViewOneCourseOfListCourse(M[i + j], x, y + j);
		}
	}
	else {
		for (int j = 0; j < n - i; j++) {
			ViewOneCourseOfListCourse(M[i + j], x, y + j);
		}
	}

}

int ViewCourseInYear(Course* M, int n, DrawASCII Fun) {
	if (M == NULL) {
		return -1;
	}
	TextBgColor(0, 15);
	system("cls");
	int x = 1;
	int y = 14;
	Fun();
	DrawRectangle(0, y - 2, 120, 13, 3);
	TextBgColor(0, 3);
	PrintText("ID COURSE", x + 2, y - 1);
	PrintText("COURSE NAME", x + 12, y - 1);//12 ki tu cho id
	PrintText("TEACHER NAME", x + 35, y - 1);
	PrintText("NUMBER OF CREDITS", x + 50, y - 1);//30 ki tu cho ten
	PrintText("MAX STUDENT", x + 72, y - 1);
	PrintText("DAY", x + 87, y - 1);//14 ki tu cho 1 diem
	PrintText("SESSION 1", x + 94, y - 1);//14 ki tu cho 1 diem
	PrintText("SESSION 2", x + 104, y - 1);//14 ki tu cho 1 diem
	char ch;
	int tab_now = 0;
	ViewTenCourseOfListCourse(M, tab_now * 10, n, x, y);
	do {
		HidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			return-1;
		}
		else {
			//Control Up down 
			if (ch == 72 && tab_now > 0) //up
			{
				tab_now--;
				DrawRectangle(0, y, 120, 11, 3);
				ViewTenCourseOfListCourse(M, tab_now * 10, n, x, y);
			}
			if (ch == 80 && tab_now < (n - 1) / 10) //down
			{
				tab_now++;
				DrawRectangle(0, y, 120, 11, 3);
				ViewTenCourseOfListCourse(M, tab_now * 10, n, x, y);
			}
			if (ch == 13) {
				return tab_now;
			}
		}
	} while (true);
}

Course* SelectCourse(User A, SchoolYear SY, FuncGetCourse Fun, DrawASCII FunDraw) {
	int n = 0;
	Course* M = Fun(A, SY, n);
	if (M == NULL) {
		throw "There isn't course.";
	}
	char ch;
	int line_now = 0;
	int x = 1, y = 14;
	int tab_now = ViewCourseInYear(M, n, FunDraw);
	if (tab_now == -1) {
		TextBgColor(0, 15);
		return NULL;
	}
	DrawRectangle(1, y + line_now, 115, 1, 14);
	TextBgColor(0, 14);
	ViewOneCourseOfListCourse(M[tab_now * 10], x, y);
	int count = tab_now * 10;
	do {
		if (tab_now == -1) {
			TextBgColor(0, 15);
			return NULL;
		}
		HidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			tab_now = ViewCourseInYear(M, n, FunDraw);
			if (tab_now == -1) {
				TextBgColor(0, 15);
				return NULL;
			}
			line_now = 0;
			count = tab_now * 10;
			DrawRectangle(1, y + line_now, 115, 1, 14);
			TextBgColor(0, 14);
			ViewOneCourseOfListCourse(M[tab_now * 10], x, y);
		}
		else {
			//Control Up down 
			if (ch == 72 && line_now > 0) //up
			{
				DrawRectangle(1, y + line_now, 115, 1, 3);
				TextBgColor(0, 3);
				ViewOneCourseOfListCourse(M[count], x, y + line_now);

				line_now--;
				count--;
				DrawRectangle(1, y + line_now, 115, 1, 14);
				TextBgColor(0, 14);
				ViewOneCourseOfListCourse(M[count], x, y + line_now);
			}
			else if (ch == 72 && line_now == 0 && count > 0) {
				count--;
				DrawRectangle(0, y, 120, 11, 3);
				ViewTenCourseOfListCourse(M, count, n, x, y);
				DrawRectangle(1, y + line_now, 115, 1, 14);
				TextBgColor(0, 14);
				ViewOneCourseOfListCourse(M[count], x, y + line_now);
			}
			else if (ch == 80 && line_now < 9 && count < n - 1) //down
			{
				DrawRectangle(1, y + line_now, 115, 1, 3);
				TextBgColor(0, 3);
				ViewOneCourseOfListCourse(M[count], x, y + line_now);

				line_now++;
				count++;
				DrawRectangle(1, y + line_now, 115, 1, 14);
				TextBgColor(0, 14);
				ViewOneCourseOfListCourse(M[count], x, y + line_now);
			}
			else if (ch == 80 && line_now == 9 && count < n - 1) {
				count++;
				DrawRectangle(0, y, 120, 11,3);
				ViewTenCourseOfListCourse(M, count - 9, n, x, y);
				DrawRectangle(1, y + line_now, 115, 1, 14);
				TextBgColor(0, 14);
				ViewOneCourseOfListCourse(M[count], x, y + line_now);
			}
			if (ch == 13) {
				return &M[count];
			}
		}
	} while (true);
	TextBgColor(0, 15);
}

void ViewOneStudentInfoOfCourse(Data M, int x, int y) {
	PrintText(to_string(M.NoInClass), x, y);
	PrintText(M.IDSt, x + 7, y);
	PrintText(M.NameSt, x + 35, y);
	PrintText(M.Birthday, x + 57, y);
	PrintText(M.sex, x + 80, y);
	PrintText(M.IDSocial, x + 90, y);
}

void ViewTenStudentInfoOfCourse(Data* M, int i, int n, int x, int y) {
	if (n - i >= 10) {
		for (int j = 0; j < 10; j++) {
			ViewOneStudentInfoOfCourse(M[i + j], x, y + j);
		}
	}
	else {
		for (int j = 0; j < n - i; j++) {
			ViewOneStudentInfoOfCourse(M[i + j], x, y + j);
		}
	}

}

void ViewStudentInfoOfCourse(Data* M, int n) {
	TextBgColor(0, 15);
	system("cls");
	int x = 10;
	int y = 14;
	TextBgColor(4, 6);
	PrintText("   _____   __                __                 __            ____            ____       ", 10, 3);
	PrintText("  / ___/  / /_  __  __  ____/ /  ___    ____   / /_          /  _/   ____    / __/  ____ ", 10, 4);
	PrintText("  \\__ \\  / __/ / / / / / __  /  / _ \\  / __ \\ / __/          / /    / __ \\  / /_   / __ \\", 10, 5);
	PrintText(" ___/ / / /_  / /_/ / / /_/ /  /  __/ / / / // /_          _/ /    / / / / / __/  / /_/ /", 10, 6);
	PrintText("/____/  \\__/  \\__,_/  \\__,_/   \\___/ /_/ /_/ \\__/         /___/   /_/ /_/ /_/     \\____/ ", 10, 7);
	PrintText("                                                                                         ", 10, 8);
	DrawRectangle(0, y - 2, 120, 13, 11);
	TextBgColor(0, 11);
	PrintText("NO", x, y - 1);
	PrintText("ID", x + 7, y - 1);//12 ki tu cho id
	PrintText("Name", x + 35, y - 1);
	PrintText("Birthday", x + 57, y - 1);//30 ki tu cho ten
	PrintText("Sex", x + 80, y - 1);//14 ki tu cho 1 diem
	PrintText("ID Social", x + 90, y - 1);//14 ki tu cho 1 diem
	char ch;
	int tab_now = 0;
	ViewTenStudentInfoOfCourse(M, tab_now * 10, n, x, y);
	do {
		HidePointer();
		ch = _getch();
		//[ESC]
		if (ch == 27) {
			return;
		}
		else {
			//Control Up down 
			if (ch == 72 && tab_now > 0) //up
			{
				tab_now--;
				DrawRectangle(0, y, 120, 11, 11);
				ViewTenStudentInfoOfCourse(M, tab_now * 10, n, x, y);
			}
			if (ch == 80 && tab_now < (n - 1) / 10) //down
			{
				tab_now++;
				DrawRectangle(0, y, 120, 11, 11);
				ViewTenStudentInfoOfCourse(M, tab_now * 10, n, x, y);
			}
		}
	} while (true);
}
