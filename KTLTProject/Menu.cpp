#include "Menu.h"
#include "Login.h"
#include "ConsoleProcess.h"
#include "ReadData.h"
#include "ChangeInfo.h"
#include "StaffFunction.h"
#include "CourseFunction.h"
#include "ListClass.h"
#include "AddStudent.h"

void MenuStaff(User& Usertmp)
{
	ShowPointer();
	bool isExit = false;
	SchoolYear SY;
	DetermineYearSemesterNow(SY.Year, SY.SemesterSchool.NameSemester);
	ReadInfo(Usertmp, SY);
	int option;
	string MenuStaff[] = { "YOUR INFO","NEW","CLASS INFO","COURSE INFO","RESULT OF STUDENTS","LOG OUT" };
	string MenuStaff1[] = { "1. Profile info", "2. Change password","3. Back to Menu" };
	string MenuStaff2[] = {
	"1. Create school - year",
	"2. Create semester ", "3. Create course registration session", "4. Create course",
	"5. Create Class","6. Add Student to class","7. Back to Menu"
	};
	string MenuStaff4[] = {
	"1. View List Course And List Student in Course",
	 "2. Delete or Edit Course info","3.Back to Menu" };
	string MenuStaff5[] = { "1. View and edit student's marks", "2. Export student list mark", "3. Import student list mark", "4. Back to Menu" };
	do
	{
		ShowPointer();
		system("cls");
		GotoXY(0, 7);
		/*{

"4. CLASS",

"7. Add student to class",
,
 "9. Edit student's marks",
 "10. View list of course\, Delete a course\, update course information",
 "11. Export student list",
 "12. Import student list",
 "13. View score board of a course",
 "14. View score board of a class" };*/
		DrawMenu(MenuStaff, 6, 50, 10, 1, &DrawASCIIStaffMenu);
		option = MoveAndChoose(6, MenuStaff, 50, 10, 1);
		switch (option)
		{
		case 0: {
			system("cls");
			DrawMenu(MenuStaff1, 3, 50, 11, 2, &DrawASCIIStaffMenu);
			int option1 = MoveAndChoose(3, MenuStaff1, 50, 11, 2);
			switch (option1)
			{
			case 0: {
				// lenh show thong tin 
				OutputInfo(Usertmp);
				break;
			}
			case 1: {
				// lenh thay mat khau
				ChangePassword(Usertmp);
				break;
			}
			case 2: {
				break;
			}
			}
			break;
		}

		case 1: {
			system("cls");

			DrawMenu(MenuStaff2, 7, 40, 9, 1, &DrawASCIIStaffMenu);
			int option1 = MoveAndChoose(7, MenuStaff2, 40, 9, 1);
			switch (option1)
			{
			case 0: {
				// lenh tao nam
				AddSchoolYear(SY);
				break;
			}
			case 1: {
				//lenh them hoc ki
				AddSemester(SY.Year, SY.SemesterSchool.NameSemester);
				break;
			}
			case 2: {
				// tao phien dang ki khoa hoc
				CreateRegistrationCourse();
				break;
			}
			case 3: {
				// lenh them khoa hoc
				AddCourse();
				break;
			}
			case 4: {
				// lenh them lop hoc
				RunMenuCreateClass();
				break;
			}
			case 5:
			{

				system("cls");
				//AddStudentToClass();
				RunMenuAddInfoStudentToClass();
				break;
			}
			default:
				break;
			}
			break;
		}

		case 2:
		{
			system("cls");
			//xem danh sach lop hoc va danh sach sinh vien trong lop
			ListClass(Usertmp, SY, &ShowStudentInclass);
			break;
		}
		case 3: {
			system("cls");
			DrawMenu(MenuStaff4, 3, 40, 12, 2, &DrawASCIIStaffMenu);
			int option1 = MoveAndChoose(3, MenuStaff4, 40, 12, 2);
			switch (option1)
			{
			case 0: {
				system("cls");
				//xem danh sach khoa hoc va danh sach sinh vien trong khoa
				ViewStudentInCourse(Usertmp, SY);
				TextBgColor(0, 15);
				break;
			}
			case 1: {
				//view danh sach hoc phan
				ListCourse(Usertmp, SY.Year, SY.SemesterSchool.NameSemester);
				break;
			}
			case 2: {
				break;
			}
			}
			break;
		}
		case 4:
			/*system("cls");
			RunMenuViewListClass();
			break;*/
		{
			bool checkMenu = true;
			do {
				system("cls");
				DrawMenu(MenuStaff5, 4, 40, 10, 2, &DrawASCIIStaffMenu);
				int option1 = MoveAndChoose(4, MenuStaff5, 40, 10, 2);
				switch (option1)
				{
				case 0: //edit diem sinh vien
				{
					system("cls");
					string edit[] = { "1. From List Class.","2. From List Course.","3. Exit to Menu." };
					DrawMenu(edit, 3, 45, 20, 2, &DrawASCIIEditScore);
					int choose = MoveAndChoose(3, edit, 45, 20, 2);
					switch (choose)
					{
					case 0: {
						ListClass(Usertmp, SY, &ShowScoreOfClass);
						break;
					}
					case 1: {
						try {
							Course* SLC = SelectCourse(Usertmp, SY, &ReadFileListCourse, &DrawASCIIListCourse);
							if (SLC == NULL) {
								break;
							}
							EditScoreInListCourse(Usertmp, SY, SLC->IDCourse);
						}
						catch (const char* err) {
							DrawRectangle(3, 14, 115, 3, 4);
							PrintText(err, 50, 15);
							TextBgColor(0, 15);
							Sleep(1800);
						}
						break;
					}
					default:
						break;
					}
					break;
				}
				case 1: {
					//xuat diem hoc sinh vao file
					ExportScoreBoardInterface(Usertmp, SY.Year, SY.SemesterSchool.NameSemester, 2, 1);
					break;
				}
				case 2: {
					//xuat diem hoc sinh vao file
					ImportScoreBoardUI();
					break;
				}
				case 3: {
					checkMenu = false;
					break;
				}
				}
			} while (checkMenu == true);
			break;
		}
		case 5:
			isExit = true;
			break;
			//default: std::cout << "your choice is invalid!!!\n";
		}
	} while (!isExit);
	RepeatLogin(Usertmp);
}

void MenuStudent(User& Usertmp)
{
	ShowPointer();
	SchoolYear SY;
	DetermineYearSemesterNow(SY.Year, SY.SemesterSchool.NameSemester);
	if (SY.SemesterSchool.NameSemester == "Semester0") {
		DrawRectangle(3, 14, 115, 3, 4);
		PrintText("The school year hasn't started yet ", 40, 15);
		Sleep(1800);
		RepeatLogin(Usertmp);
		return;
	}
	ReadInfo(Usertmp, SY);
	InitListMark(Usertmp.info.head);
	bool isExit = false;
	int option;
	string menuStudent[] = { "YOUR INFO", "COURSE" , "YOUR RESULTS","LOG OUT" };
	string MenuStd1[] = { "1. Profile info","2. Change password","3.Back to Menu" };
	string MenuStd2[] = { "1. Enroll courses","2. Remove course","3. View your list of course","4. Back to Menu" };
	//, "3. Score board"
	//, "4. Enroll courses"
	//, "5. List of enrolled courses"
	//, "6. Remove courses"
	//, "7. View your list of course" };
	do
	{
		system("cls");
		DrawMenu(menuStudent, 4, 50, 10, 2, &DrawASCIIMenuStudent);
		option = MoveAndChoose(4, menuStudent, 50, 10, 2);
		switch (option)
		{
		case 0: {
			system("cls");
			DrawMenu(MenuStd1, 3, 50, 11, 2, &DrawASCIIStaffMenu);
			int option1 = MoveAndChoose(3, MenuStd1, 50, 11, 2);
			switch (option1)
			{
			case 0: {
				// lenh show thong tin 
				OutputInfo(Usertmp);
				break;
			}
			case 1: {
				// lenh thay mat khau
				ChangePassword(Usertmp);
				break;
			}
			case 2: {
				break;
			}
			}
			break;
		}
		case 1: {
			system("cls");
			DrawMenu(MenuStd2, 4, 45, 10, 2, &DrawASCIIMenuStudent);
			int option1 = MoveAndChoose(4, MenuStd2, 45, 10, 2);
			switch (option1)
			{
			case 0: {
				//enroll_course(user, SY);
				try {
					int check = CheckCourseSession();
					if (check == 1) {
						EnrollCourse(Usertmp, SY);
					}
					else {
						DrawRectangle(35, 15, 50, 5, 4);
						TextBgColor(15, 4);
						if (check == 0) PrintText("NOT OPEN REGISTER COURSE YET", 45, 17);
						else if (check == -1) PrintText("IT'S NOT THE TIME TO START YET", 45, 17);
						else PrintText("It was late to register the course", 45, 17);
						Sleep(1800);
						TextBgColor(0, 15);
					}
				}
				catch (const char* err) {
					string s = string(err);
					s.pop_back();
					s += " to enroll.";
					DrawRectangle(3, 14, 115, 3, 4);
					PrintText(s, 45, 15);
					TextBgColor(0, 15);
					Sleep(1800);
				}
				break;
			}
			case 1: {
				//lenh xoa bot khoa hoc da dang ki
				try {
					int check = CheckCourseSession();
					if (check == 1) {
						DeleteCourse(Usertmp, SY);
					}
					else {
						DrawRectangle(35, 15, 50, 5, 4);
						TextBgColor(15, 4);
						if (check == 0) PrintText("NOT OPEN REGISTER COURSE YET", 45, 17);
						else if (check == -1) PrintText("IT'S NOT THE TIME TO START YET", 45, 17);
						else PrintText("It was late to register the course", 45, 17);
						Sleep(1800);
						TextBgColor(0, 15);
					}
				}
				catch (const char* err) {
					string s = string(err);
					s.pop_back();
					s += " to delete.";
					DrawRectangle(3, 14, 115, 3, 4);
					PrintText(s, 45, 15);
					TextBgColor(0, 15);
					Sleep(1800);
				}
				break;
			}
			case 2: {
				DisPlayCourseOfStudent(SY, Usertmp);
				break;
			}
			default: {
				break;
			}
			}
			break;
		}
		case 2: {
			// lenh show bang diem
			DisPlayMarkOfStudent(SY, Usertmp);
			break;
		}
		case 3: {
			isExit = true;
			break;
		}
		}
	} while (!isExit);
	RepeatLogin(Usertmp);
}

void DrawASCIIListCourse() {
	TextBgColor(4, 7);
	PrintText(" _     ___ ____ _____    ____ ___  _   _ ____  ____  _____ ", 30, 2);
	PrintText("| |   |_ _/ ___|_   _|  / ___/ _ \\| | | |  _ \\/ ___|| ____|", 30, 3);
	PrintText("| |    | |\\___ \\ | |   | |  | | | | | | | |_) \\___ \\|  _|  ", 30, 4);
	PrintText("| |___ | | ___) || |   | |__| |_| | |_| |  _ < ___) | |___ ", 30, 5);
	PrintText("|_____|___|____/ |_|    \\____\\___/ \\___/|_| \\_\\____/|_____|", 30, 6);
	PrintText("                                                           ", 30, 7);
}

void DrawASCIIEnrolCourse() {
	TextBgColor(4, 6);
	PrintText("                                 __                                                   ", 20, 3);
	PrintText("  ___    ____    _____  ____    / /         _____  ____   __  __   _____   _____  ___ ", 20, 4);
	PrintText(" / _ \\  / __ \\  / ___/ / __ \\  / /         / ___/ / __ \\ / / / /  / ___/  / ___/ / _ \\", 20, 5);
	PrintText("/  __/ / / / / / /    / /_/ / / /         / /__  / /_/ // /_/ /  / /     (__  ) /  __/", 20, 6);
	PrintText("\\___/ /_/ /_/ /_/     \\____/ /_/          \\___/  \\____/ \\__,_/  /_/     /____/  \\___/ ", 20, 7);
	PrintText("                                                                                      ", 20, 8);
	PrintText("Choose the course you want to enrol. Enter to choose.", 35, 28);
}

void DrawASCIISuccessful() {
	TextBgColor(3, 0);
	PrintText("                                                        ____            __", 20, 15);
	PrintText("   _____  __  __  _____  _____  ___    _____   _____   / __/  __  __   / /", 20, 16);
	PrintText("  / ___/ / / / / / ___/ / ___/ / _ \\  / ___/  / ___/  / /_   / / / /  / / ", 20, 17);
	PrintText(" (__  ) / /_/ / / /__  / /__  /  __/ (__  )  (__  )  / __/  / /_/ /  / /  ", 20, 18);
	PrintText("/____/  \\__,_/  \\___/  \\___/  \\___/ /____/  /____/  /_/     \\__,_/  /_/   ", 20, 19);
	PrintText("                                                                          ", 20, 20);
	TextBgColor(0, 15);
}

void DrawASCIIFailEnrol() {
	TextBgColor(3, 0);
	PrintText("    ______            _     __             __    __    __", 35, 15);
	PrintText("   / ____/  ____ _   (_)   / /  ___   ____/ /   / /   / /", 35, 16);
	PrintText("  / /_     / __ `/  / /   / /  / _ \\ / __  /   / /   / / ", 35, 17);
	PrintText(" / __/    / /_/ /  / /   / /  /  __// /_/ /   /_/   /_/  ", 35, 18);
	PrintText("/_/       \\__,_/  /_/   /_/   \\___/ \\__,_/   (_)   (_)   ", 35, 19);
	PrintText("                                                         ", 35, 20);
	PrintText("        The course has been registered before.           ", 35, 21);
	PrintText("                                                         ", 35, 22);
	TextBgColor(0, 15);
}

void DrawASCIIDeleteCourse() {
	TextBgColor(4, 7);
	PrintText("    ____           __         __                 ______                                     ", 20, 5);
	PrintText("   / __ \\  ___    / /  ___   / /_  ___          / ____/  ____   __  __   _____   _____  ___ ", 20, 6);
	PrintText("  / / / / / _ \\  / /  / _ \\ / __/ / _ \\        / /      / __ \\ / / / /  / ___/  / ___/ / _ \\", 20, 7);
	PrintText(" / /_/ / /  __/ / /  /  __// /_  /  __/       / /___   / /_/ // /_/ /  / /     (__  ) /  __/", 20, 8);
	PrintText("/_____/  \\___/ /_/   \\___/ \\__/  \\___/        \\____/   \\____/ \\__,_/  /_/     /____/  \\___/ ", 20, 9);
	PrintText("                                                                                            ", 20, 10);
	PrintText("Choose the course you want to delete. Enter to choose.", 35, 28);
}

void DrawASCIIStaffMenu() {
	SchoolYear SY;
	DetermineYearSemesterNow(SY.Year, SY.SemesterSchool.NameSemester);
	DrawRectangle(3, 1, 115, 5, 0);
	DrawRectangle(3, 24, 115, 5, 0);
	DrawRectangle(3, 7, 115, 1, 0);
	TextBgColor(3,0);
	PrintText(" __    __     ______     __   __     __  __    ", 35, 1);
	PrintText("/\\ \"-./  \\   /\\  ___\\   /\\ \"-.\\ \\   /\\ \\/\\ \\   ", 35, 2);
	PrintText("\\ \\ \\-./\\ \\  \\ \\  __\\   \\ \\ \\-.  \\  \\ \\ \\_\\ \\  ", 35, 3);
	PrintText(" \\ \\_\\ \\ \\_\\  \\ \\_____\\  \\ \\_\\\\\"\\_\\  \\ \\_____\\ ", 35, 4);
	PrintText("  \\/_/  \\/_/   \\/_____/   \\/_/ \\/_/   \\/_____/ ", 35, 5);
	PrintText(" ______     ______   ______     ______   ______  ", 35, 24);
	PrintText("/\\  ___\\   /\\__  _\\ /\\  __ \\   /\\  ___\\ /\\  ___\\ ", 35, 25);
	PrintText("\\ \\___  \\  \\/_/\\ \\/ \\ \\  __ \\  \\ \\  __\\ \\ \\  __\\ ", 35, 26);
	PrintText(" \\/\\_____\\    \\ \\_\\  \\ \\_\\ \\_\\  \\ \\_\\    \\ \\_\\   ", 35, 27);
	PrintText("  \\/_____/     \\/_/   \\/_/\\/_/   \\/_/     \\/_/   ", 35, 28);
	PrintText("     " + SY.SemesterSchool.NameSemester + " - " + SY.Year + "     ", 43, 7);
	//PrintText("     Semester 3 - 2023 - 2024    ", 43, 7);
	TextBgColor(0, 15);
}

void DrawASCIIChangeYear() {
	TextBgColor(4, 7);
	PrintText("   ______    __                                        __  __                      ", 15, 4);
	PrintText("  / ____/   / /_   ____ _   ____    ____ _  ___        \\ \\/ /  ___   ____ _   _____", 15, 5);
	PrintText(" / /       / __ \\ / __ `/  / __ \\  / __ `/ / _ \\        \\  /  / _ \\ / __ `/  / ___/", 15, 6);
	PrintText("/ /___    / / / // /_/ /  / / / / / /_/ / /  __/        / /  /  __// /_/ /  / /    ", 15, 7);
	PrintText("\\____/   /_/ /_/ \\__,_/  /_/ /_/  \\__, /  \\___/        /_/   \\___/ \\__,_/  /_/     ", 15, 8);
	PrintText("                                 /____/                                            ", 15, 9);
	TextBgColor(0, 15);
}

void DrawASCIIChangeSemester() {
	TextBgColor(4, 7);
	PrintText("   ______    __                                 ", 35, 5);
	PrintText("  / ____/   / /_   ____ _   ____    ____ _  ___ ", 35, 6);
	PrintText(" / /       / __ \\ / __ `/  / __ \\  / __ `/ / _ \\", 35, 7);
	PrintText("/ /___    / / / // /_/ /  / / / / / /_/ / /  __/", 35, 8);
	PrintText("\\____/   /_/ /_/ \\__,_/  /_/ /_/  \\__, /  \\___/ ", 35, 9);
	PrintText("                                 /____/         ", 35, 10);
	PrintText("   _____                                   __               ", 30, 23);
	PrintText("  / ___/  ___    ____ ___   ___    _____  / /_  ___    _____", 30, 24);
	PrintText("  \\__ \\  / _ \\  / __ `__ \\ / _ \\  / ___/ / __/ / _ \\  / ___/", 30, 25);
	PrintText(" ___/ / /  __/ / / / / / //  __/ (__  ) / /_  /  __/ / /    ", 30, 26);
	PrintText("/____/  \\___/ /_/ /_/ /_/ \\___/ /____/  \\__/  \\___/ /_/     ", 30, 27);
	PrintText("                                                            ", 30, 28);
	TextBgColor(0, 15);
}

void DrawASCIIEditScore() {
	TextBgColor(4, 7);
	PrintText("    ______    ____     ____  ______          _____   ______   ____     ____     ______", 20, 4);
	PrintText("   / ____/   / __ \\   /  _/ /_  __/         / ___/  / ____/  / __ \\   / __ \\   / ____/", 20, 5);
	PrintText("  / __/     / / / /   / /    / /            \\__ \\  / /      / / / /  / /_/ /  / __/   ", 20, 6);
	PrintText(" / /___    / /_/ /  _/ /    / /            ___/ / / /___   / /_/ /  / _, _/  / /___   ", 20, 7);
	PrintText("/_____/   /_____/  /___/   /_/            /____/  \\____/   \\____/  /_/ |_|  /_____/   ", 20, 8);
	PrintText("                                                                                      ", 20, 9);
	TextBgColor(0, 15);
}

void DrawASCIIMenuStudent() {
	SchoolYear SY;
	DetermineYearSemesterNow(SY.Year, SY.SemesterSchool.NameSemester);
	DrawRectangle(3, 1, 115, 5, 0);
	DrawRectangle(3, 23, 115, 5, 0);
	DrawRectangle(3, 7, 115, 1, 0);
	TextBgColor(3, 0);
	PrintText(" ______     ______   __  __     _____     ______     __   __     ______  ", 23, 1);
	PrintText("/\\  ___\\   /\\__  _\\ /\\ \\/\\ \\   /\\  __-.  /\\  ___\\   /\\ \"-.\\ \\   /\\__  _\\ ", 23, 2);
	PrintText("\\ \\___  \\  \\/_/\\ \\/ \\ \\ \\_\\ \\  \\ \\ \\/\\ \\ \\ \\  __\\   \\ \\ \\-.  \\  \\/_/\\ \\/ ", 23, 3);
	PrintText(" \\/\\_____\\    \\ \\_\\  \\ \\_____\\  \\ \\____-  \\ \\_____\\  \\ \\_\\\\\"\\_\\    \\ \\_\\ ", 23, 4);
	PrintText("  \\/_____/     \\/_/   \\/_____/   \\/____/   \\/_____/   \\/_/ \\/_/     \\/_/", 23, 5);
	PrintText(" __    __     ______     __   __     __  __    ", 35, 23);
	PrintText("/\\ \"-./  \\   /\\  ___\\   /\\ \"-.\\ \\   /\\ \\/\\ \\", 35, 24);
	PrintText("\\ \\ \\-./\\ \\  \\ \\  __\\   \\ \\ \\-.  \\  \\ \\ \\_\\ \\ ", 35, 25);
	PrintText(" \\ \\_\\ \\ \\_\\  \\ \\_____\\  \\ \\_\\\\\"\\_\\  \\ \\_____\\ ", 35, 26);
	PrintText("  \\/_/  \\/_/   \\/_____/   \\/_/ \\/_/   \\/_____/ ", 35, 27);
	PrintText("     " + SY.SemesterSchool.NameSemester + " - " + SY.Year + "     ", 43, 7);
	TextBgColor(0, 15);
}

void DrawASCIIImport() {
	TextBgColor(4, 7);
	PrintText(" ___ __  __ ____   ___  ____ _____    ____   ____ ___  ____  _____ ____   ___    _    ____  ____  ", 10, 1);
	PrintText("|_ _|  \\/  |  _ \\ / _ \\|  _ \\_   _|  / ___| / ___/ _ \\|  _ \\| ____| __ ) / _ \\  / \\  |  _ \\|  _ \\ ", 10, 2);
	PrintText(" | || |\\/| | |_) | | | | |_) || |    \\___ \\| |  | | | | |_) |  _| |  _ \\| | | |/ _ \\ | |_) | | | |", 10, 3);
	PrintText(" | || |  | |  __/| |_| |  _ < | |     ___) | |__| |_| |  _ <| |___| |_) | |_| / ___ \\|  _ <| |_| |", 10, 4);
	PrintText("|___|_|  |_|_|    \\___/|_| \\_\\|_|    |____/ \\____\\___/|_| \\_\\_____|____/ \\___/_/   \\_\\_| \\_\\____/ ", 10, 5);
	TextBgColor(0, 15);
}
