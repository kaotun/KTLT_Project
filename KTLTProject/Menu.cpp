#include "Menu.h"
#include "Login.h"
#include "ConsoleProcess.h"
#include "ReadData.h"
#include "ChangeInfo.h"
#include "StaffFunction.h"
#include "CourseFunction.h"
#include "ListClass.h"
#include "AddStudent.h"













void DrawASCIIListCourse() {
	TextBgColor(4, 6);
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
	TextBgColor(6, 0);
	PrintText("                                                        ____            __", 20, 15);
	PrintText("   _____  __  __  _____  _____  ___    _____   _____   / __/  __  __   / /", 20, 16);
	PrintText("  / ___/ / / / / / ___/ / ___/ / _ \\  / ___/  / ___/  / /_   / / / /  / / ", 20, 17);
	PrintText(" (__  ) / /_/ / / /__  / /__  /  __/ (__  )  (__  )  / __/  / /_/ /  / /  ", 20, 18);
	PrintText("/____/  \\__,_/  \\___/  \\___/  \\___/ /____/  /____/  /_/     \\__,_/  /_/   ", 20, 19);
	PrintText("                                                                          ", 20, 20);
	TextBgColor(0, 15);
}

void DrawASCIIFailEnrol() {
	TextBgColor(6, 0);
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
	TextBgColor(4, 6);
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
	TextBgColor(6, 0);
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
	TextBgColor(0, 15);
}

void DrawASCIIChangeYear() {
	TextColor(46);
	PrintText("   ______    __                                        __  __                      ", 15, 4);
	PrintText("  / ____/   / /_   ____ _   ____    ____ _  ___        \\ \\/ /  ___   ____ _   _____", 15, 5);
	PrintText(" / /       / __ \\ / __ `/  / __ \\  / __ `/ / _ \\        \\  /  / _ \\ / __ `/  / ___/", 15, 6);
	PrintText("/ /___    / / / // /_/ /  / / / / / /_/ / /  __/        / /  /  __// /_/ /  / /    ", 15, 7);
	PrintText("\\____/   /_/ /_/ \\__,_/  /_/ /_/  \\__, /  \\___/        /_/   \\___/ \\__,_/  /_/     ", 15, 8);
	PrintText("                                 /____/                                            ", 15, 9);
	TextColor(496);
}

void DrawASCIIChangeSemester() {
	TextColor(46);
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
	TextColor(496);
}

void DrawASCIIEditScore() {
	TextBgColor(6, 0);
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
	TextBgColor(6, 0);
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
	TextBgColor(6, 0);
	PrintText(" ___ __  __ ____   ___  ____ _____    ____   ____ ___  ____  _____ ____   ___    _    ____  ____  ", 10, 1);
	PrintText("|_ _|  \\/  |  _ \\ / _ \\|  _ \\_   _|  / ___| / ___/ _ \\|  _ \\| ____| __ ) / _ \\  / \\  |  _ \\|  _ \\ ", 10, 2);
	PrintText(" | || |\\/| | |_) | | | | |_) || |    \\___ \\| |  | | | | |_) |  _| |  _ \\| | | |/ _ \\ | |_) | | | |", 10, 3);
	PrintText(" | || |  | |  __/| |_| |  _ < | |     ___) | |__| |_| |  _ <| |___| |_) | |_| / ___ \\|  _ <| |_| |", 10, 4);
	PrintText("|___|_|  |_|_|    \\___/|_| \\_\\|_|    |____/ \\____\\___/|_| \\_\\_____|____/ \\___/_/   \\_\\_| \\_\\____/ ", 10, 5);
	TextBgColor(0, 15);
}