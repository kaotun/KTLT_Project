#include"staffFunction.h"
#include"Header.h"
#include"ConsoleProcess.h"
#include"Course_function.h"
#include"read_data.h"
#include "Menu.h"

void CreateFolder(string NameFolder) {
    const char* namefolder = NameFolder.c_str();
    int check = _mkdir(namefolder);
    if (check) {
        cout << "Could not create folder" << endl;
        exit(1);
    }
    return;
}

bool IsPathExist(const std::string& s)
{
    struct stat buffer;
    return (stat(s.c_str(), &buffer) == 0);
}

void CopyContentFileToFile(string ScrcPath, string DesPath)
{
    fstream fileSource, fileDestination;
    fileSource.open(ScrcPath, ios::in);
    fileDestination.open(DesPath, ios::out);
    if (!fileSource.is_open()) return;
    string data;
    getline(fileSource, data);
    fileDestination << data;
    while (!fileSource.eof()) {
        getline(fileSource, data);
        fileDestination << endl << data;
    }
    fileSource.close();
    fileDestination.close();
}

void AddSchoolYear(SchoolYear& Yeartmp) {
    SchoolYear schoolyear;
    char ch;
    system("cls");
    textBgColor(13, 15);

    printtext(" ____   ____ _   _  ___   ___  _      __   _______    _    ____", 35, 2);
    printtext("/ ___| / ___| | | |/ _ \\ / _ \\| |     \\ \\ / / ____|  / \\  |  _ \\", 35, 3);
    printtext("\\___ \\| |   | |_| | | | | | | | |      \\ V /|  _|   / _ \\ | |_) |", 35, 4);
    printtext(" ___) | |___|  _| |_| | |_| | | |___    | | | |___ / ___ \\|  _ <", 35, 5);
    printtext("|____/ \\____|_| |_|\\___/ \\___/|_____|   |_| |_____/ _ / \\_\\_| \\_\\", 35, 6);
    while (true) {
        textBgColor(0, 11);
        drawRectangle(35, 8, 70, 7, 11);
        schoolyear.year = "";
        printtext("Enter school year (Ex:2020-2021,..) : ", 40, 10);
        drawRectangle(40, 11, 50, 1, 15);
        
        while (true) {
            showPointer();
            textBgColor(0, 15);
            gotoxy(40, 11);
            schoolyear.year = "";
            if (insertSchoolYear(schoolyear.year) == 0) return;
            string a, b;
            for (int i = 0; i < 4; i++) a.push_back(schoolyear.year[i]);
            for (int i = 5; i < 9; i++) b.push_back(schoolyear.year[i]);
            //Không thõa mãn định dạng nhập yyyy-yyyy
            if (!(stoi(a, 0, 10) >= stoi(b, 0, 10) || schoolyear.year[4] != 45 || (stoi(a, 0, 10) < 1000 || stoi(a, 0, 10) > 9999) || (stoi(b, 0, 10) < 1000 || stoi(b, 0, 10) > 9999)))
                break;
            else {
                textBgColor(4, 11);
                printtext("ERROR:SCHOOL YEAR MUST HAVE FORMAT LIKE YYYY-YYYY", 40, 13);
                printtext("PRESS ENTER TO TRY AGAIN", 40, 14);
                hidePointer();
                ch = getch();
                drawRectangle(40, 11, 50, 1, 15);
                drawRectangle(40, 13, 60, 1, 11);
                drawRectangle(40, 14, 60, 1, 11);
                showPointer();
            }
        }

        fstream file1, file2;
        bool check = true;
        file1.open("Data//year_semester.csv", ios::in);
        file2.open("Data//year_semester.csv", ios::in);

        string row, column;
        getline(file1, row);
        getline(file2, column);
        while (!file1.eof()) {
            getline(file2, column, ',');
            if (column.compare(schoolyear.year) == 0) {
                textBgColor(4, 11);
                printtext("SCHOOL YEAR EXIST ! PRESS ENTER TO TRY AGAIN", 40, 14);
                hidePointer();
                ch = getch();
                drawRectangle(40, 11, 50, 1, 15);
                drawRectangle(40, 14, 60, 1, 11);
                showPointer();
                check = false;
                break;
            }
            getline(file1, row);
            getline(file2, column);
        }
        if (check == true) break;
    }

    string nameFolder = "Data//SchoolYear//" + schoolyear.year;
    createFolder(nameFolder);

    fstream file;
    string data;
    file.open("Data//year_semester.csv", ios::app);
    file << endl << schoolyear.year << ",0";
    file.close();


    file.open("Data/SchoolYear/" + Yeartmp.year + "/class_info.csv", ios::in);
    getline(file, data);
    while (!file.eof()) {
        getline(file, data, ',');
        getline(file, data, ',');
        string source = "Data/SchoolYear/" + Yeartmp.year + "/" + data + ".csv", destination = "Data/SchoolYear/" + schoolyear.year + "/" + data + ".csv";
        CopyContentFileToFile(source, destination);
        getline(file, data);
    }
    CopyContentFileToFile("Data/SchoolYear/" + Yeartmp.year + "/staff.csv", "Data/SchoolYear/" + schoolyear.year + "/staff.csv");
    CopyContentFileToFile("Data/SchoolYear/" + Yeartmp.year + "/class_info.csv", "Data/SchoolYear/" + schoolyear.year + "/class_info.csv");
    Yeartmp.year = schoolyear.year;
    Yeartmp.semester.Name = "Semester0";
    hidePointer();
    textBgColor(4, 11);
    printtext("CREATE SCHOOL YEAR SUCCESSFUL,PRESS ENTER TO BACK TO MENU !!!", 40, 14);
    ch = getch();
    textBgColor(0, 15);
}

int InsertNameSemester(string& Name) {
    char word;
    do {
        showPointer();
        word = getch();
        if (word == 8) {
            if (Name.size() > 0) {
                Name.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        if (word == 27) {
            return 0;
        }
        else if (word >= 49 && word <= 51 && Name.size() < 1) {
            cout << word;
            Name.push_back(word);
        }
        if (word == 13){
            if (Name.size() == 1) break;
        }
    } while (true);
    return 1;
}

int InsertDate(string& Date) {
    int x = ReturnX(), y = ReturnY();
    char word;
    showPointer();
    do {
        word = getch();
        if (word == 8) {
            if (Date.size() > 0) {
                Date.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        else if (word >= 47 && word <= 57 && Date.size() < 10) {
            cout << word;
            Date.push_back(word);
        }
        if (word == 27) {
            return 0;
        }
    } while (word != 13 || Date.size() < 10);
    return 1;
}

int InsertSchoolYear(string& SchoolYear) {
    int x = ReturnX(), y = ReturnY();
    char word;
    showPointer();
    do {    
        word = getch();
        if (word == 8) {
            if (SchoolYear.size() > 0) {
                SchoolYear.pop_back();
                gotoxy(ReturnX() - 1, ReturnY());
                cout << " ";
                gotoxy(ReturnX() - 1, ReturnY());
            }
        }
        if (word == 27) {
            return 0;
        }
        else if (((word >= 48 && word <= 57) || word == 45) && SchoolYear.size() < 9) {
            cout << word;
            SchoolYear.push_back(word);
        }

    } while (word != 13 || SchoolYear.size() < 9);
    return 1;
}

int CheckSchoolYear(Semester Semestertmp)
{
    string a, b;
    for (int i = 0; i < 4; i++) a.push_back(Semestertmp.schoolyear[i]);
    for (int i = 5; i < 9; i++) b.push_back(Semestertmp.schoolyear[i]);
    //Không thõa mãn định dạng nhập yyyy-yyyy
    if (stoi(a, 0, 10) >= stoi(b, 0, 10) || Semestertmp.schoolyear[4] != 45 || (stoi(a, 0, 10) < 1000 || stoi(a, 0, 10) > 9999) || (stoi(b, 0, 10) < 1000 || stoi(b, 0, 10) > 9999))
        return 0;

    //Không tồn tại School Year
    if (IsPathExist("Data//SchoolYear//" + Semestertmp.schoolyear) == false) return -1;

    //Kiểm tra thử trong School Year đã nhập đã có tồn tại semester vừa nhập chưa
    fstream file2;
    file2.open("Data//year_semester.csv", ios::in);
    int check = 1;
    string column;
    getline(file2, column);
    while (!file2.eof()) {
        getline(file2, column, ',');
        if (column.compare(Semestertmp.schoolyear) == 0) {
            getline(file2, column, '\n');
            if (stoi(column, 0, 10) >= stoi(Semestertmp.Name, 0, 10)) check = -2;
            else if (stoi(Semestertmp.Name, 0, 10) - stoi(column, 0, 10) > 1) check = -3;
            break;
        }
        getline(file2, column);
    }
    file2.close();
    return check;
}

int CheckDate(string Date) {
    string dd, mm, yyyy;
    dd.push_back(Date[0]);
    dd.push_back(Date[1]);
    mm.push_back(Date[3]);
    mm.push_back(Date[4]);
    yyyy.push_back(Date[6]);
    yyyy.push_back(Date[7]);
    yyyy.push_back(Date[8]);
    yyyy.push_back(Date[9]);
    if (Date.size() < 10 || Date.find('/') != 2 || Date.find('/', 3) != 5 || (Date[2] != 47 || Date[5] != 47) || (stoi(dd, 0, 10) < 1 || stoi(dd, 0, 10) > 31) || (stoi(mm, 0, 10) < 1 || stoi(mm, 0, 10) > 12) || (stoi(yyyy, 0, 10) < 1000 || stoi(yyyy, 0, 10) > 9999))
        return 0;
    return 1;
}

void UpDatefileCSV(Semester Semestertmp) {
    fstream file_old1, file_old2, file_new;
    string data1, data2;
    file_old1.open("Data//year_semester.csv", ios::in);
    file_old2.open("Data/year_semester.csv", ios::in);
    file_new.open("Data//year_semester_new.csv", ios::app);
    file_new << "Năm,số kì đã học ";
    getline(file_old2, data2);
    getline(file_old1, data1);
    data1 = data2 = "";
    while (!file_old2.eof()) {
        getline(file_old2, data2);
        while (!file_old1.eof()) {
            getline(file_old1, data1, ',');
            if (data1.compare(Semestertmp.schoolyear) == 0) {
                file_new << endl << data1;
                getline(file_old1, data1);
                int a = stoi(data1, 0, 10);
                a++;
                file_new << ","  << to_string(a);
            }
            else file_new << endl << data2;
            getline(file_old1, data1);
            break;
        }
    }
    file_old1.close();
    file_old2.close();
    file_new.close();
    remove("Data//year_semester.csv");
    rename("Data//year_semester_new.csv", "Data//year_semester.csv");
}

void UpDateFileInfo(Semester Semestertmp){
    fstream file;
    file.open("Data//SchoolYear//" + Semestertmp.SchoolYear + "//Semester" + Semestertmp.NameSemester + "//SemesterInfo.txt", ios::app);
    file << "Semester: " << Semestertmp.NameSemester;
    file << endl << "Start Date: " << Semestertmp.DateBegin;
    file << endl << "End Date: " << Semestertmp.DateEnd;
    file.close();
}

void AddSemester(string& YearNow, string& SemesterNow) {
    char ch;
    Semester semester;
    system("cls");
    TextBgColor(4, 7);
    PrintText("  ____                           _            ", 40, 2);
    PrintText(" / ___|  ___ _ __ ___   ___  ___| |_ ___ _ __ ", 40, 3);
    PrintText(" \\___ \\ / _ \\ '_ ` _ \\ / _ \\/ __| __/ _ \\ '__|", 40, 4);
    PrintText("   ___)|  __/ | | | | |  __/\\__ \\ ||  __/ |   ", 40, 5);
    PrintText(" |____/ \\___|_| |_| |_|\\___||___/\\__\\___|_|   ", 40, 6);

    TextBgColor(0, 3);
    DrawRectangle(25, 8, 80, 12, 3);
    PrintText("Enter semester (1,2 or 3):", 35, 10);
    PrintText("Enter school year of the semester (Ex:2023-2024,...):", 35, 12);
    PrintText("Enter start date (dd/mm/yyyy):", 35, 14);
    PrintText("Enter end date (dd/mm/yyyy):", 35, 16);
    DrawRectangle(35, 11, 35, 1, 15);
    DrawRectangle(35, 13, 35, 1, 15);
    DrawRectangle(35, 15, 35, 1, 15);
    DrawRectangle(35, 17, 35, 1, 15);

    GotoXY(35, 11);
    if (InsertNameSemester(semester.NameSemester) == 0) return;

    do {
        GotoXY(35, 13);
        if (InsertSchoolYear(semester.SchoolYear) == 0) return;
        int check = CheckSchoolYear(semester);
        if (check != 1) {
            HidePointer();
            TextBgColor(4, 3);
            GotoXY(35, 19);
            if (check == 0)
                PrintText("ERROR:SCHOOL YEAR MUST HAVE FORMAT LIKE YYYY-YYYY,PRESS ENTER TO TRY AGAIN", 30, 19);
            else if (check == -1)
                PrintText("ERROR:SCHOOL YEAR WASN'T EXISTED, PRESS ENTER TO TRY AGAIN", 30, 19);
            else if (check == -2)
                PrintText("ERROR:SEMESTER WAS EXISTED IN SCHOOL YEAR, PRESS ENTER TO TRY AGAIN", 30, 19);
            else if (check == -3)
                PrintText("ERROR:SEMESTER ISN'T COME UP,PRESS ENTER TO TRY AGAIN", 30, 19);
            ch = getch();
            DrawRectangle(30, 19, 75, 1, 3);
            DrawRectangle(35, 13, 10, 1, 15);
            TextBgColor(0, 15);
            semester.SchoolYear = "";
            ShowPointer();
        }
        else break;
    } while (true);

    do {
        GotoXY(35, 15);
        if (InsertDate(semester.DateBegin) == 0) return;
        int check = CheckDate(semester.DateBegin);
        if (check == 0) {
            TextBgColor(4, 3);
            GotoXY(35, 18);
            HidePointer();
            cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020)";
            PrintText("PRESS ENTER TO TRY AGAIN", 35, 19);
            ch = getch();
            DrawRectangle(30, 18, 70, 1, 3);
            DrawRectangle(30, 19, 70, 1, 3);
            DrawRectangle(35, 15, 10, 1, 15);
            TextBgColor(0, 15);
            semester.DateBegin.clear();
            ShowPointer();
        }
        else break;
    } while (true);

    do {
        GotoXY(35, 17);
        if (InsertDate(semester.DateEnd) == 0) return;
        int check = CheckDate(semester.DateEnd);
        if (check == 0) {
            TextBgColor(4, 3);
            GotoXY(35, 18);
            HidePointer();
            cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020)";
            PrintText("PRESS ENTER TO TRY AGAIN", 35, 19);
            ch = getch();
            DrawRectangle(30, 18, 70, 1, 3);
            DrawRectangle(30, 19, 70, 1, 3);
            DrawRectangle(35, 17, 10, 1, 15);
            TextBgColor(0, 15);
            semester.DateEnd.clear();
            ShowPointer();
        }
        else break;
    } while (true);

    SemesterNow = semester.NameSemester;
    CreateFolder("Data//SchoolYear//" + semester.SchoolYear + "//Semester" + semester.NameSemester);
    CreateFolder("Data//SchoolYear//" + semester.SchoolYear + "//Semester" + semester.NameSemester + "//Class");
    CreateFolder("Data//SchoolYear//" + semester.SchoolYear + "//Semester" + semester.NameSemester + "//Course");
    CreateFolder("Data//SchoolYear//" + semester.SchoolYear + "//Semester" + semester.NameSemester + "//Course//score");
    UpDateFileCSV(semester);
    UpDateFileInfo(semester);

    fstream file;
    file.open("Data//SchoolYear//" + semester.SchoolYear + "//Semester" + semester.NameSemester + "//course_info.csv", ios::out);
    file << "ID,COURSE NAME,TEACHER NAME,NUMBER OF CREDITS,MAX STUDENT,DAY,SESSION1,SESSION2";
    file.close();

    fstream fileCourse;
    fileCourse.open("Data//SchoolYear//" + semester.SchoolYear + "//Semester" + semester.NameSemester + "//RegistrationCourseSession.txt", ios::out);
    fileCourse << 0;
    fileCourse.close();

    fstream class_info;
    class_info.open("Data//SchoolYear//" + semester.SchoolYear + "/class_info.csv", ios::in);
    if (!class_info.is_open()) return;
    string line;
    getline(class_info, line);
    while (!class_info.eof()) {
        getline(class_info, line);
        string className = line.substr(line.find(",") + 1, line.find(",", line.find(",") + 1) - line.find(",") - 1);
        fstream fileClass, fileStudent;
        fileClass.open("Data/SchoolYear/" + semester.SchoolYear + "/Semester" + semester.NameSemester + "/Class/" + className + ".csv", ios::out);
        fileStudent.open("Data/SchoolYear/" + semester.SchoolYear + "/" + className + ".csv", ios::in);
        string studentID;
        getline(fileStudent, studentID);
        int t = 1;
        while (!fileStudent.eof()) {
            getline(fileStudent, studentID);
            studentID = studentID.substr(studentID.find(",") + 1, studentID.find(",", studentID.find(",") + 1) - studentID.find(",") - 1);
            if (t == 1) {
                fileClass << studentID; t++;
            }
            else fileClass << endl << studentID;
        }
    }

    HidePointer();
    TextBgColor(2, 3);
    PrintText("CREATE SEMESTER SUCCESSFUL,PRESS ENTER BACK TO MENU !!!", 35, 19);
    ch = getch();
    TextBgColor(0, 15);
}

void CreateRegistrationCourse() {
    system("cls");
    string DateStart, DateEnd;
    char ch;
    TextBgColor(4, 7);
    PrintText("  ____ ____  _____    _  _____ _____    ____ ___  _   _ ____  ____  _____ ", 25, 2);
    PrintText(" / ___|  _ \\| ____|  / \\|_   _| ____|  / ___/ _ \\| | | |  _ \\/ ___|| ____|", 25, 3);
    PrintText("| |   | |_) |  _|   / _ \\ | | |  _|   | |  | | | | | | | |_) \\___ \\|  _|  ", 25, 4);
    PrintText("| |___|  _< | |___ / ___ \\| | | |___  | |__| |_| | |_| |  _ < ___) | |___ ", 25, 5);
    PrintText(" \\____|_| \\_\\_____/_/   \\_\\_| |_____|  \\____\\___/ \\___/|_| \\_\\____/|_____|", 25, 6);

    PrintText(" ____  _____ ____ ___ ____ _____ ____      _  _____ ___ ___  _   _ ", 28, 8);
    PrintText("|  _ \\| ____/ ___|_ _/ ___|_   _|  _ \\    / \\|_   _|_ _/ _ \\| \\ | |", 28, 9);
    PrintText("| |_) |  _|| |  _ | |\\___ \\ | | | |_) |  / _ \\ | |  | | | | |  \\| |", 28, 10);
    PrintText("|  _ <| |__| |_| || | ___) || | |  _ <  / ___ \\| |  | | |_| | |\\  |", 28, 11);
    PrintText("|_| \\_\\_____\\____|___|____/ |_| |_| \\_\\/_/   \\_\\_| |___\\___/|_| \\_|", 28, 12);

    PrintText(" ____  _____ ____ ____ ___ ___  _   _ ", 35, 14);
    PrintText("/ ___|| ____/ ___/ ___|_ _/ _ \\| \\ | |", 35, 15);
    PrintText("\\___ \\|  _| \\___ \\___ \\| | | | |  \\| |", 35, 16);
    PrintText(" ___) | |___ ___) |__) | | |_| | |\\  |", 35, 17);
    PrintText("|____/|_____|____/____/___\\___/|_| \\_|", 35, 18);

    string year, semester;
    DetermineYearSemesterNow(year, semester);
    if (stoi(semester.substr(8, 1), 0, 10) == 0) {
        TextBgColor(4, 15);
        PrintText("YOU HAVEN'T CREATED SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 40, 10);
        ch = getch();
    }
    else {
        DrawRectangle(30, 20, 50, 7, 3);
        TextBgColor(0, 3);
        PrintText("START DATE (DD/MM/YYYY):", 35, 21);
        PrintText("END DATE (DD/MM/YYYY):", 35, 24);
        DrawRectangle(35, 22, 40, 1, 15);
        DrawRectangle(35, 25, 40, 1, 15);

        string FileName = "Data//SchoolYear//" + year + "//" + semester + "//RegistrationCourseSession.txt";
        do {
            GotoXY(35, 22);
            if (InsertDate(DateStart) == 0) return;
            int check = CheckDate(DateStart);
            if (check == 0) {
                TextBgColor(4, 15);
                GotoXY(20, 28);
                HidePointer();
                cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020,..), PRESS ENTER TO TRY AGAIN";
                ch = getch();
                DrawRectangle(20, 28, 90, 1, 15);
                DrawRectangle(35, 22, 40, 1, 15);
                TextBgColor(0, 15);
                DateStart.clear();
                ShowPointer();
            }
            else break;
        } while (true);

        do {
            GotoXY(35, 25);
            if (InsertDate(DateEnd) == 0) return;
            int check = CheckDate(DateEnd);
            if (check == 0) {
                TextBgColor(4, 15);
                GotoXY(20, 28);
                HidePointer();
                cout << "ERROR: DATE MUST HAVE FORMAT LIKE DD/MM/YYYY (01/02/2020,..), PRESS ENTER TO TRY AGAIN";
                ch = getch();
                DrawRectangle(20, 28, 90, 1, 15);
                DrawRectangle(35, 25, 40, 1, 15);
                TextBgColor(0, 15);
                DateEnd.clear();
                ShowPointer();
            }
            else break;
        } while (true);
        HidePointer();
        fstream file;
        file.open(FileName, ios::out);
        file << 1;
        file << endl << "Date start: " << DateStart;
        file << endl << "Date end:" << DateEnd;
        file.close();
        TextBgColor(9, 15);
        PrintText("CREATE COURSE REGISTRATION SESSION SUCCESSFUL !!! ,PRESS ENTER TO BACK TO MENU", 20, 28);
        ch = getch();
    }
    TextBgColor(0, 15);
}

int InsertNum(int& n) {
    char c;
    string num = "";
    do {
        ShowPointer();
        c = getch();
        if (c == 8) {
            if (num.size() > 0) {
                num.pop_back();
                GotoXY(ReturnX() - 1, ReturnY());
                cout << " ";
                GotoXY(ReturnX() - 1, ReturnY());
            }
        }
        else if (c >= 48 && c <= 57) {
            cout << c;
            num.push_back(c);
        }
        if (c == 27) {
            return 0;
        }
        if (c == 13) {
            if (num.size() >= 1) {
                break;
            }
        }
    } while (true);
    n = stoi(num, 0, 10);
    return 1;
}

int CountLine(string FileName) {
    fstream file;
    string line;
    file.open(FileName, ios::in);
    int count = 0;
    while (getline(file, line, '\n'))
        count++;
    file.close();
    return count;
}

void DetermineYearSemesterNow(string& Year, string& Semester) {
    fstream file1;
    string data1;
    file1.open("Data/year_semester.csv", ios::in);
    getline(file1, data1);
    while (!file1.eof()) {
        getline(file1, data1);
    }
    Year = data1.substr(0, 9);
    Semester = "Semester" + data1.substr(10, 1);
}

void AddCourse() {
    char ch;
    Course course;
    string Day[7] = { "MON","TUE","WED","THU","FRI","SAT" }, session[4] = { "S1","S2","S3","S4" };
    system("cls");
    TextBgColor(4, 7);
    PrintText("  ____ ___  _   _ ____  ____  _____ ", 40, 2);
    PrintText(" / ___/ _ \\| | | |  _ \\/ ___|| ____|", 40, 3);
    PrintText("| |  | | | | | | | |_) \\___ \\| _|   ", 40, 4);
    PrintText("| |__| |_| | |_| |  _ < ___) | |___ ", 40, 5);
    PrintText(" \\____\\___/ \\___/|_| \\_\\____/|_____|", 40, 6);

    string year = "", semester = "";
    DetermineYearSemesterNow(year, semester);
    if (stoi(semester.substr(8, 1), 0, 10) == 0) {
        TextBgColor(4, 15);
        PrintText("YOU HAVEN'T CREATED SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 40, 10);
        ch = getch();
    }

    else {
        DrawRectangle(25, 9, 70, 18, 3);
        PrintText("COURSE ID: ", 30, 10);
        PrintText("COURSE NAME: ", 30, 12);
        PrintText("TEACHER NAME: ", 30, 14);
        PrintText("NUMBER OF CREDITS: ", 30, 16);
        PrintText("MAXIMUN OF STUDENT: ", 30, 18);
        PrintText("DAY OF THE WEEK (MON / TUE / WED / THU / FRI / SAT): ", 30, 20);
        PrintText("SESSION: S1 (7:30), S2 (9:30), S3 (13:30), S4 (15:30) :", 30, 22);

        DrawRectangle(30, 11, 55, 1, 15);
        DrawRectangle(30, 13, 55, 1, 15);
        DrawRectangle(30, 15, 55, 1, 15);
        DrawRectangle(30, 17, 55, 1, 15);
        DrawRectangle(30, 19, 55, 1, 15);
        DrawRectangle(30, 21, 55, 1, 15);
        DrawRectangle(30, 23, 55, 1, 15);
        DrawRectangle(30, 24, 55, 1, 15);


        ///////////////////////////////////////////
        do
        {
            GotoXY(30, 11);
            if (InsertString(course.IDCourse, 15) == 0) return;
            if (CountLine("Data/SchoolYear/" + year + "/" + semester + "/course_info.csv") == 1) break;
            fstream file;
            string line;
            file.open("Data/SchoolYear/" + year + "/" + semester + "/course_info.csv", ios::in);
            getline(file, line);
            bool check = false;
            while (!file.eof()) {
                getline(file, line, ',');
                if (line.compare(course.IDCourse) != 0) {
                    check = true; break;
                }
            }
            if (check == true) break;
            else {
                TextBgColor(4, 15);
                HidePointer();
                PrintText("ERROR: COURSE ALREADY EXISTS,PRESS ENTER TO TRY AGAIN.", 25, 27);
                ch = getch();
                TextBgColor(0, 15);
                DrawRectangle(25, 27, 80, 1, 15);
                DrawRectangle(30, 11, 50, 1, 15);
            }
        } while (true);

        ShowPointer();
        GotoXY(30, 13);
        if (InsertString(course.NameCourse, 20) == 0) return;
        GotoXY(30, 15);
        if (InsertString(course.Teacher, 20) == 0) return;
        GotoXY(30, 17);
        if (InsertNum(course.NumOfCreadit) == 0) return;
        GotoXY(30, 19);
        if (InsertNum(course.MaxStudent) == 0) return;
        do {
            GotoXY(30, 21);
            ShowPointer();
            if (InsertString(course.DayOfWeek, 15) == 0) return;
            bool check = false;
            for (int i = 0; i < 7; i++) {
                if (course.DayOfWeek.compare(Day[i]) == 0) {
                    check = true;
                    break;
                }
            }
            if (check == true) break;
            else {
                course.DayOfWeek = "";
                TextBgColor(4, 15);
                HidePointer();
                PrintText("ERROR: YOUR DAY MUST HAVE FORMAT LIKE (MON,TUE,..),PRESS ENTER TO TRY AGAIN.", 25, 27);
                ch = getch();
                TextBgColor(0, 15);
                DrawRectangle(25, 27, 80, 1, 15);
                DrawRectangle(30, 21, 50, 1, 15);
            }
        } while (true);

        do
        {
            GotoXY(30, 23);
            ShowPointer();
            if (InsertString(course.Session[0], 15) == 0) return;
            bool check = false;
            for (int i = 0; i < 4; i++) {
                if (course.Session[0].compare(session[i]) == 0) {
                    check = true;
                    break;
                }
            }
            if (check == true) break;
            else {
                course.Session[0] = "";
                TextBgColor(4, 15);
                HidePointer();
                PrintText("ERROR: YOUR SESSION MUST HAVE FORMAT LIKE (S1,S2,..),PRESS ENTER TO TRY AGAIN.", 25, 27);
                TextBgColor(0, 15);
                ch = getch();
                DrawRectangle(25, 27, 80, 1, 15);
                DrawRectangle(30, 23, 50, 1, 15);
            }
        } while (true);

        do
        {
            GotoXY(30, 24);
            ShowPointer();
            if (InsertString(course.Session[1], 15) == 0) return;
            int check = 0;
            for (int i = 0; i < 4; i++) {
                if (course.Session[1].compare(session[i]) == 0) {
                    if (course.Session[1].compare(course.Session[0]) == 0)
                        check = -1;
                    else check = 1;
                    break;
                }
            }
            if (check == 1) break;
            else {
                course.Session[1] = "";
                TextBgColor(4, 15);
                HidePointer();
                if (check == 0)
                    PrintText("ERROR: YOUR SESSION MUST HAVE FORMAT LIKE (S1,S2,..),PRESS ENTER TO TRY AGAIN.", 25, 27);
                else
                    PrintText("ERROR: YOUR SESSION IS THE SAME AS LAST SESSION ,PRESS ENTER TO TRY AGAIN.", 25, 27);
                TextBgColor(0, 15);
                ch = getch();
                DrawRectangle(25, 27, 80, 1, 15);
                DrawRectangle(30, 24, 50, 1, 15);
            }
        } while (true);
        fstream file;
        file.open("Data/SchoolYear/" + year + "/" + semester + "/course_info.csv", ios::app);
        file << endl << course.IDCourse << "," << course.NameCourse << "," << course.Teacher << "," << course.NumOfCreadit << "," << course.MaxStudent << "," << course.DayOfWeek << "," << course.Session[0] << "," << course.Session[1];
        file.close();

        file.open("Data/SchoolYear/" + year + "/" + semester + "/Course/" + course.IDCourse + ".csv", ios::out);
        file << "ID STUDENT,NAME,BIRTHDAY,SEX,ID SOCIAL";
        file.close();
        PrintText("CREATE COURSE SUCCESSFUL !!!, PRESS ENTER TO BACK TO MENU.", 25, 27);
        ch = getch();
    }
    TextBgColor(0, 15);
}

void GetLineInfo(string FileName, int Line, string Column[], int ColumnNum) {
    if (Line > CountLine(FileName)) cout << "Not exist line";
    int numLine = CountLine(FileName);
    fstream file;
    string data;
    file.open(FileName, ios::in);
    for (int i = 1; i <= numLine; i++) {
        if (i == Line) {
            for (int j = 0; j < ColumnNum; j++) {
                if (j != ColumnNum - 1) {
                    getline(file, data, ',');
                    Column[j] = data;
                }
                else {
                    getline(file, data);
                    Column[j] = data;
                }
            }
            break;
        }
        else {
            getline(file, data);
        }
    }
}

/*
ID[5]: 1
Name[21]: 9
Teachar[15]: 34
Credits[3] 60
student[5] 76
Day[5] 88
Session[5] 98 108
*/

int InsertString(string& Data, int Limit) {
    char ch;
    do
    {
        ShowPointer();
        ch = getch();
        if (ch == 8) {
            if (Data.size() > 0) {
                Data.pop_back();
                GotoXY(ReturnX() - 1, ReturnY());
                cout << " ";
                GotoXY(ReturnX() - 1, ReturnY());
            }
        }
        else if (ch == 32 && Data.size() < Limit) {
            Data.push_back(ch);
            cout << " ";
        }
        else if (((ch >= 33 && ch <= 57) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || ch == 95) && Data.size() < Limit) {
            cout << ch;
            Data.push_back(ch);
        }
        if (ch == 27) {
            return 0;
        }
        if (ch == 13) {
            if (Data.size() > 1) {
                break;
            }
        }
    } while (true);
    return 1;
}

int InsertNum2(string& Data, int Limit) {
    char ch;
    do
    {
        ch = getch();
        if (ch == 8) {
            if (Data.size() > 0) {
                Data.pop_back();
                GotoXY(ReturnX() - 1, ReturnY());
                cout << " ";
                GotoXY(ReturnX() - 1, ReturnY());
            }
        }
        if (ch == 27) {
            return 0;
        }
        else if ((ch >= 48 && ch <= 57) && Data.size() < Limit) {
            cout << ch;
            Data.push_back(ch);
        }
    } while (ch != 13);
    return 1;
}

int InsertDay(string& Data, int Limit) {
    string Day[7] = { "MON","TUE","WED","THU","FRI","SAT" };
    char ch;
    bool check = false;
    do
    {
        ch = getch();
        if (ch == 8) {
            if (Data.size() > 0) {
                Data.pop_back();
                GotoXY(ReturnX() - 1, ReturnY());
                cout << " ";
                GotoXY(ReturnX() - 1, ReturnY());
            }
        }
        else if ((ch >= 65 && ch <= 90) && Data.size() < Limit) {
            cout << ch;
            Data.push_back(ch);
        }
        if (ch == 27) {
            return 0;
        }
        for (int i = 0; i < 7; i++) {
            if (Data.compare(Day[i]) == 0) { check = true; break; }
        }
    } while (ch != 13 || check == false);
    return 1;
}

int InsertSession(string& Data, int Limit) {
    string session[4] = { "S1","S2","S3","S4" };
    char ch;
    bool check = false;
    do
    {
        ch = getch();
        if (ch == 8) {
            if (Data.size() > 0) {
                Data.pop_back();
                GotoXY(ReturnX() - 1, ReturnY());
                cout << " ";
                GotoXY(ReturnX() - 1, ReturnY());
            }
        }
        else if (((ch >= 65 && ch <= 90) || (ch >= 48 && ch <= 57)) && Data.size() < Limit) {
            cout << ch;
            Data.push_back(ch);
        }
        if (ch == 27) {
            return 0;
        }
        for (int i = 0; i < 4; i++) {
            if (Data.compare(session[i]) == 0) { check = true; break; }
        }
    } while (ch != 13 || check == false);
    return 1;
}

void UpdateFileCourse(int CurrentColumn, int CurrentLine, string Column[], string Year, string Semester) {
    fstream file_be, file_af;
    string newdata, line;
    string filename = "Data//SchoolYear//" + Year + "//" + Semester + "//course_info.csv";
    for (int i = 0; i < 8; i++) {
        if (i != 7) {
            newdata = newdata + Column[i] + ",";
        }
        else newdata = newdata + Column[i];
    }
    file_be.open(filename, ios::in);
    file_af.open("Data//SchoolYear//" + Year + "//" + Semester + "//course_info_new.csv", ios::app);
    getline(file_be, line);
    file_af << line;
    int i = 2;
    while (!file_be.eof()) {
        if (i == CurrentLine) {
            file_af << endl << newdata;
            getline(file_be, line);
        }
        else {
            getline(file_be, line);
            file_af << endl << line;
        }
        i++;
    }

    char* a = new char[filename.size() + 1];
    strcpy(a, filename.c_str());
    a[filename.size()] = '\0';
    string filename_new = "Data/SchoolYear/" + Year + "/" + Semester + "/course_info_new.csv";
    char* b = new char[filename_new.size() + 1];
    strcpy(b, filename_new.c_str());
    b[filename_new.size()] = '\0';
    file_be.close();
    file_af.close();
    remove(a);
    rename(b, a);

}

void EditInforCourse(int y, int CurrentLine, string Column[], string Year, string Semester) {
    char ch;
    int CurrentColumn = 2, pos[8] = { 1,9,32,63,79,91,101,111 }, limit[8] = { 5,20,20,3,5,5,2,2 };
    DrawRectangle(pos[CurrentColumn], y, 5, 1, 15);
    TextBgColor(0, 15);
    PrintText(Column[2], pos[CurrentColumn], y);
    do
    {
        ch = getch();
        //ESC
        if (ch == 27)
            break;
        //Left 
        if (ch == 75 && CurrentColumn > 2) {
            DrawRectangle(pos[CurrentColumn], y, limit[CurrentColumn], 1, 14);
            TextBgColor(0, 14);
            PrintText(Column[CurrentColumn], pos[CurrentColumn], y);

            CurrentColumn--;
            DrawRectangle(pos[CurrentColumn], y, limit[CurrentColumn], 1, 15);
            TextBgColor(0, 15);
            PrintText(Column[CurrentColumn], pos[CurrentColumn], y);
        }
        //Right
        if (ch == 77 && CurrentColumn < 7) {
            DrawRectangle(pos[CurrentColumn], y, limit[CurrentColumn], 1, 14);
            TextBgColor(0, 14);
            PrintText(Column[CurrentColumn], pos[CurrentColumn], y);

            CurrentColumn++;
            DrawRectangle(pos[CurrentColumn], y, limit[CurrentColumn], 1, 15);
            TextBgColor(0, 15);
            PrintText(Column[CurrentColumn], pos[CurrentColumn], y);
        }

        //[ENTER]
        if (ch == 13) {
            ShowPointer();
            TextBgColor(0, 15);

            if (CurrentColumn == 2) {
                GotoXY(pos[CurrentColumn] + Column[CurrentColumn].size(), y);
                InsertString(Column[2], limit[CurrentColumn]);
            }
            else if (CurrentColumn == 3) {
                GotoXY(pos[CurrentColumn] + Column[CurrentColumn].size(), y);
                InsertNum2(Column[CurrentColumn], limit[CurrentColumn]);
            }
            else if (CurrentColumn == 4) {
                GotoXY(pos[CurrentColumn] + Column[CurrentColumn].size(), y);
                InsertNum2(Column[CurrentColumn], limit[CurrentColumn]);
            }
            else if (CurrentColumn == 5) {
                GotoXY(pos[CurrentColumn] + Column[CurrentColumn].size(), y);
                InsertDay(Column[CurrentColumn], limit[CurrentColumn]);
            }
            else {
                GotoXY(pos[CurrentColumn] + Column[CurrentColumn].size(), y);
                InsertSession(Column[CurrentColumn], limit[CurrentColumn]);
            }
            HidePointer();
            UpdateFileCourse(CurrentColumn, CurrentLine, Column, Year, Semester);
        }
    } while (true);
}

void DeleteFile(string FileName) {
    char* a = new char[FileName.size() + 1];
    strcpy(a, FileName.c_str());
    a[FileName.size()] = '\0';
    remove(a);
}

void RenameFile(string OldName, string NewName) {
    char* a = new char[OldName.size() + 1];
    strcpy(a, OldName.c_str());
    a[OldName.size()] = '\0';

    char* b = new char[NewName.size() + 1];
    strcpy(b, NewName.c_str());
    b[NewName.size()] = '\0';

    rename(a, b);
}

void DeleteCourse(string FileName, string CourseName, int CurrentLine, string Year, string Semester) {
    fstream file_be, file_af;
    string newdata, line;
    file_be.open(FileName, ios::in);
    file_af.open("Data//SchoolYear//" + Year + "//" + Semester + "//course_info_new.csv", ios::app);
    getline(file_be, line);
    file_af << line;
    int i = 2;
    while (!file_be.eof()) {
        if (i == CurrentLine) {
            getline(file_be, line);
        }
        else {
            getline(file_be, line);
            file_af << endl << line;
        }
        i++;
    }

    char* a = new char[FileName.size() + 1];
    strcpy(a, FileName.c_str());
    a[FileName.size()] = '\0';
    string filename_new = "Data/SchoolYear/" + Year + "/" + Semester + "/course_info_new.csv";
    char* b = new char[filename_new.size() + 1];
    strcpy(b, filename_new.c_str());
    b[filename_new.size()] = '\0';
    file_be.close();
    file_af.close();
    remove(a);
    rename(b, a);

    //xoa trong folder course
    DeleteFile("Data/SchoolYear/" + Year + "/" + Semester + "/Course/" + CourseName + ".csv");

    //xoa trong folder score
    DeleteFile("Data/SchoolYear/" + Year + "/" + Semester + "/Course/score/" + CourseName + ".csv");

    //Xoa trong folder class
    fstream file;
    file.open("Data/SchoolYear/" + Year + "/class_info.csv", ios::in);
    if (!file.is_open()) {
        return;
    }
    string info;
    getline(file, info);
    while (!file.eof()) {
        getline(file, info);
        info = info.substr(info.find(",") + 1, info.find(",", info.find(",") + 1) - info.find(",") - 1);
        fstream fileClass, file_new;
        fileClass.open("Data/SchoolYear/" + Year + "/" + Semester + "/Class/" + info + ".csv", ios::in);
        file_new.open("Data/SchoolYear/" + Year + "/" + Semester + "/Class/" + info + "_new.csv", ios::out);
        if (!fileClass.is_open() || !file_new.is_open()) continue;
        string line;
        int i = 1;
        while (!fileClass.eof()) {
            getline(fileClass, line);
            if (line.find("," + CourseName) != -1) {
                line.erase(line.find("," + CourseName), CourseName.size() + 1);
            }
            if (i == 1) {
                file_new << line;
                i++;
            }
            else file_new << endl << line;
        }
        fileClass.close();
        file_new.close();
        DeleteFile("Data/SchoolYear/" + Year + "/" + Semester + "/Class/" + info + ".csv");
        RenameFile("Data/SchoolYear/" + Year + "/" + Semester + "/Class/" + info + "_new.csv", "Data/SchoolYear/" + Year + "/" + Semester + "/Class/" + info + ".csv");
    }
    file.close();
}

void MoveUp(string FileName, int& CurrentLine, int ColumnNum, int IndexB[], int y, string Column[], int LineInConsole, int Width, int x) {
    GetLineInfo(FileName, CurrentLine + 1, Column, ColumnNum);
    DrawRectangle(x, y + LineInConsole + 1, Width, 1, 3);
    TextBgColor(0, 3);
    for (int i = 0; i < ColumnNum; i++) {
        PrintText(Column[i], IndexB[i], y + LineInConsole + 1);
    }

    GetLineInfo(FileName, CurrentLine, Column, ColumnNum);
    DrawRectangle(x, y + LineInConsole, Width, 1, 14);
    TextBgColor(0, 14);
    for (int i = 0; i < ColumnNum; i++) {
        PrintText(Column[i], IndexB[i], y + LineInConsole);
    }
}

void MoveDown(string FileName, int& CurrentLine, int ColumnNum, int IndexB[], int y, string Column[], int LineInConsole, int Width, int x) {

    GetLineInfo(FileName, CurrentLine - 1, Column, ColumnNum);
    DrawRectangle(x, y - 1 + LineInConsole, Width, 1, 3);
    TextBgColor(0, 3);
    for (int i = 0; i < ColumnNum; i++) {
        PrintText(Column[i], IndexB[i], y + LineInConsole - 1);
    }
    GetLineInfo(FileName, CurrentLine, Column, ColumnNum);
    DrawRectangle(x, y + LineInConsole, Width, 1, 14);
    TextBgColor(0, 14);
    for (int i = 0; i < ColumnNum; i++) {
        PrintText(Column[i], IndexB[i], y + LineInConsole);
    }
}

int EditCourse(User A, string& Year, string& Semester) {
    int checkOut = -1;
    do {
        char ch;
        int line = CountLine("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv");
        int CurrentLine = 2;
        int y = 11;
        string column[8];
        int lineInConsole = 1;
        int a[8] = { 2,13,32,55,76,91,98,108 };
        int b[8] = { 1,9,32,63,79,91,101,111 };
        GetLineInfo("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", CurrentLine, column, 8);
        DrawRectangle(1, y + lineInConsole, 110, 1, 14);
        TextBgColor(0, 14);
        for (int i = 0; i < 8; i++)
            PrintText(column[i], b[i], y + lineInConsole);
        do {
            HidePointer();
            ch = getch();
            //[ESC]
            if (ch == 27) {
                TextBgColor(0, 15);
                checkOut = 1;
                break;
            }
            else {
                if (ch == 72 && CurrentLine > 2) //up
                {
                    CurrentLine--;
                    lineInConsole--;
                    if (lineInConsole + y <= 11) {
                        lineInConsole = 12;
                        DrawRectangle(0, 10, 120, 15, 15);
                        DrawRectangle(0, 10, 120, 15, 11);
                        DrawList(8, "Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", y, a, b, line, CurrentLine - 11);
                        GetLineInfo("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", CurrentLine, column, 8);
                        DrawRectangle(1, y + lineInConsole, 110, 1, 14);
                        TextBgColor(0, 14);
                        for (int i = 0; i < 8; i++) {
                            PrintText(column[i], b[i], y + lineInConsole);
                        }
                    }
                    else
                        MoveUp("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", CurrentLine, 8, b, y, column, lineInConsole, 110, 1);

                }
                if (ch == 80 && CurrentLine < line) //down
                {
                    CurrentLine++;
                    lineInConsole++;
                    if (lineInConsole + y > 23) {
                        lineInConsole = 1;
                        DrawRectangle(0, 10, 120, 15, 15);
                        DrawRectangle(0, 10, 120, 15, 11);
                        DrawList(8, "Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", y, a, b, line, CurrentLine);
                        GetLineInfo("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", CurrentLine, column, 8);
                        DrawRectangle(1, y + lineInConsole, 110, 1, 14);
                        TextBgColor(0, 14);
                        for (int i = 0; i < 8; i++) {
                            PrintText(column[i], b[i], y + lineInConsole);
                        }
                    }
                    else
                        MoveDown("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", CurrentLine, 8, b, y, column, lineInConsole, 110, 1);
                }
                if (ch == 13) {
                    //printtext();
                    EditInforCourse(y + lineInConsole, CurrentLine, column, Year, Semester);
                    DrawRectangle(1, y + lineInConsole, 110, 1, 14);
                    TextBgColor(0, 14);
                    for (int i = 0; i < 8; i++)
                        PrintText(column[i], b[i], y + lineInConsole);
                }

                if (ch == 'c') {
                    SchoolYear s;
                    ChangeYearSemester(s);
                    Year = s.Year;
                    Semester = s.SemesterSchool.NameSemester;
                    checkOut = 0;
                    break;
                    //editCourse(A, s.year, s.semester.Name);
                }

                if (ch == 'x') {
                    DeleteCourse("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", column[0], CurrentLine, Year, Semester);
                    string FileName = "Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv";
                    //drawList(8, FileName , y, a, b, line,CurrentLine-lineInConsole+1);
                    if (CurrentLine == line) {
                        CurrentLine = line - 1;
                        if (lineInConsole == 1) lineInConsole = 12;
                        else lineInConsole--;
                    }
                    line--;

                    DrawRectangle(0, 10, 120, 15, 11);
                    if (line == 1) {
                        TextBgColor(4, 15);
                        PrintText("THERE ISN'T ANY COURSE EXIST, PRESS ENTER TO BACK TO MENU.", 30, 14);
                        ch = getch();
                        TextBgColor(0, 15);
                        checkOut = 1;
                        break;
                    }
                    DrawList(8, FileName, y, a, b, line, CurrentLine - lineInConsole + 1);
                    DrawRectangle(1, y + lineInConsole, 110, 1, 14);
                    TextBgColor(0, 14);
                    GetLineInfo(FileName, CurrentLine, column, 8);
                    for (int i = 0; i < 8; i++)
                        PrintText(column[i], b[i], y + lineInConsole);
                }
            }
        } while (true);
    } while (checkOut == -1);
    return checkOut;
}

void DrawList(int ColumnNum, string FileName, int y, int IndexA[], int IndexB[], int Line, int FlagLine) {
    if (Line == 0 || ColumnNum == 0) return;
    string* datanew = new string[Line];
    string* column = new string[ColumnNum];
    TextBgColor(4, 3);

    GetLineInfo(FileName, 1, column, ColumnNum);
    for (int i = 0; i < ColumnNum; i++) {
        PrintText(column[i], IndexA[i], y);
    }
    TextBgColor(0, 3);
    y++;
    int j = FlagLine, h = 1;
    while (j <= Line && h <= 12) {
        GetLineInfo(FileName, j, column, ColumnNum);
        for (int i = 0; i < ColumnNum; i++) {
            PrintText(column[i], IndexB[i], y);
        }
        y++; j++;
        h++;
    }
}

void ListCourse(User A, string Year, string Semester) {

    char ch;
    if (stoi(Semester.substr(8, 1), 0, 10) == 0) {
        TextBgColor(4, 15);
        PrintText("YOU HAVEN'T CREATED SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 30, 14);
        ch = getch();
        TextBgColor(0, 15);
        return;
    }
    int checkOut = -1;
    do {
        HidePointer();
        system("cls");
        TextBgColor(4, 7);
        PrintText(" _     ___ ____ _____    ____ ___  _   _ ____  ____  _____ ", 30, 2);
        PrintText("| |   |_ _/ ___|_   _|  / ___/ _ \\| | | |  _ \\/ ___|| ____|", 30, 3);
        PrintText("| |    | |\\___ \\ | |   | |  | | | | | | | |_) \\___ \\|  _|  ", 30, 4);
        PrintText("| |___ | | ___) || |   | |__| |_| | |_| |  _ < ___) | |___ ", 30, 5);
        PrintText("|_____|___|____/ |_|    \\____\\___/ \\___/|_| \\_\\____/|_____|", 30, 6);

        DrawRectangle(97, 0, 22, 5, 3);
        TextBgColor(4, 3);
        PrintText("-[ESC]: BACK TO MENU", 97, 2);
        PrintText("OR RETURN", 97, 3);

        DrawRectangle(0, 0, 26, 5, 3);
        TextBgColor(4, 3);
        PrintText("-[x]: DELETE COURSE", 0, 0.5);
        PrintText("-[ENTER]: EDIT COURSE", 0, 1.5);
        PrintText("-USE UP,DOWN,LEFT,RIGHT", 0, 2.5);
        PrintText("KEY TO MOVE IN EDIT STATUS", 0, 3.5);
        PrintText("-[c]: CHANGE TIME", 0, 4.5);

        string FileName = "Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv";
        int lineNum = CountLine(FileName);
        if (lineNum == 1) {
            TextBgColor(4, 15);
            PrintText("THERE ISN'T ANY COURSE EXIST, PRESS ENTER TO BACK TO MENU.", 30, 14);
            ch = getch();
            TextBgColor(0, 15);
            break;
        }
        DrawRectangle(0, 10, 120, 15, 3);
        int a[8] = { 2,13,32,55,76,91,98,108 };
        int b[8] = { 1,9,32,63,79,91,101,111 };
        DrawList(8, FileName, 11, a, b, lineNum, 2);
        HidePointer();
        checkOut = EditCourse(A, Year, Semester);
        TextBgColor(0, 15);
    } while (checkOut == -1 || checkOut == 0);
}

void ViewCourse(string year, string semester) {
    char ch;
    HidePointer();
    system("cls");
    TextBgColor(13, 15);
    PrintText(" _     ___ ____ _____    ____ ___  _   _ ____  ____  _____", 30, 2);
    PrintText("| |   |_ _/ ___|_   _|  / ___/ _ \\| | | |  _ \\/ ___|| ____|", 30, 3);
    PrintText("| |    | |\\___ \\ | |   | |  | | | | | | | |_) \\___ \\|  _|", 30, 4);
    PrintText("| |___ | | ___) || |   | |__| |_| | |_| |  _ < ___) | |___", 30, 5);
    PrintText("|_____|___|____/ |_|    \\____\\___/ \\___/|_| \\_\\____/|_____|", 30, 6);

    DrawRectangle(97, 0, 22, 5, 11);
    TextBgColor(4, 11);
    PrintText("-[ESC]: BACK TO MENU", 97, 2);
    PrintText("OR RETURN", 97, 3);

    if (stoi(semester.substr(8, 1), 0, 10) == 0) {
        TextBgColor(4, 15);
        PrintText("YOU HAVEN'T CREATED SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 30, 14);
        ch = getch();
        TextBgColor(0, 15);
    }
    else {
        int CurrentLine = 2, y = 11;
        string FileName = "Data/SchoolYear/" + year + "/" + semester + "/course_info.csv";
        int line = CountLine(FileName);
        DrawRectangle(0, 10, 120, 15, 11);
        int a[8] = { 2,13,32,55,76,91,98,108 };
        int b[8] = { 1,9,32,63,79,91,101,111 };
        DrawList(8, FileName, 11, a, b, line, 2);
        HidePointer();
        do
        {
            ch = getch();
            if (ch == 72 && CurrentLine > 2) //up
            {
                CurrentLine -= 12;
                DrawRectangle(0, 10, 120, 15, 15);
                DrawRectangle(0, 10, 120, 15, 11);
                DrawList(8, "Data/SchoolYear/" + year + "/" + semester + "/course_info.csv", y, a, b, line, CurrentLine);
                TextBgColor(0, 14);
            }
            if (ch == 80 && CurrentLine < (line / 12) * 12) //down
            {
                CurrentLine += 12;
                DrawRectangle(0, 10, 120, 15, 15);
                DrawRectangle(0, 10, 120, 15, 11);
                DrawList(8, "Data/SchoolYear/" + year + "/" + semester + "/course_info.csv", y, a, b, line, CurrentLine);
                TextBgColor(0, 14);
            }
            if (ch == 'c') {
                SchoolYear s;
                ChangeYearSemester(s);
                ViewCourse(s.Year, s.SemesterSchool.NameSemester);
            }
            if (ch == 27) {
                break;
            }
        } while (true);
        TextBgColor(0, 15);
    }
}

bool CheckTimeEnd(string Date, string Month, string Year) {
    int Monthtmp = stoi(Month, 0, 10);
    int Yeartmp = stoi(Year, 0, 10);
    int Datetmp = stoi(Date, 0, 10);
    time_t now = time(0);
    tm* ltm = localtime(&now);
    //Năm hiện tại nhỏ hơn
    if (ltm->tm_year + 1900 < Yeartmp)
        return true;
    else {
        //Năm hiện tại lớn hơn
        if (ltm->tm_year + 1900 > Yeartmp)
            return false;
        //Năm hiện tại bằng
        else {
            //Tháng hiện tại nhỏ hơn
            if (ltm->tm_mon + 1 < Monthtmp)
                return true;
            else {
                //Tháng hiện tại lớn hơn
                if (ltm->tm_mon + 1 > Monthtmp)
                    return false;
                //Tháng hiện tại bằng
                else {
                    if (ltm->tm_mday <= Datetmp)
                        return true;
                    else
                        return false;
                }
            }
        }
    }
}

bool CheckTimeStart(string Date, string Month, string Year) {
    int Monthtmp = stoi(Month, 0, 10);
    int Yeartmp = stoi(Year, 0, 10);
    int Datetmp = stoi(Date, 0, 10);
    time_t now = time(0);
    tm* ltm = localtime(&now);
    //Năm hiện tại lớn hơn
    if (ltm->tm_year + 1900 > Yeartmp)
        return true;
    else {
        //Năm hiện tại nhỏ hơn
        if (ltm->tm_year + 1900 < Yeartmp)
            return false;
        //Năm hiện tại bằng
        else {
            //Tháng hiện tại lớn hơn
            if (ltm->tm_mon + 1 > Monthtmp)
                return true;
            else {
                //Tháng hiện tại nhỏ hơn
                if (ltm->tm_mon + 1 < Monthtmp)
                    return false;
                //Tháng hiện tại bằng
                else {
                    if (ltm->tm_mday >= Datetmp)
                        return true;
                    else
                        return false;
                }
            }
        }
    }
}

int CheckCourseSession() {
    string year, semester;
    DetermineYearSemesterNow(year, semester);
    if (stoi(semester.substr(8, 1), 0, 10) == 0) {
        TextBgColor(4, 15);
        PrintText("HAVEN'T CREATE SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 40, 10);
        char ch = getch();
    }
    else {
        fstream file;
        file.open("Data/SchoolYear/" + year + "/" + semester + "/RegistrationCourseSession.txt", ios::in);
        string data;
        getline(file, data);
        if (stoi(data, 0, 10) == 0) return 0;//not open session yet
        else {
            getline(file, data);
            string dateStart = data.substr(12, 10);
            getline(file, data);
            string dateEnd = data.substr(9, 10);
            if (CheckTimeStart(dateStart.substr(0, 2), dateStart.substr(3, 2), dateStart.substr(6, 4)) == false) return -1;//It's not time to start yet
            else {
                if (CheckTimeEnd(dateEnd.substr(0, 2), dateEnd.substr(3, 2), dateEnd.substr(6, 4)) == false) return -2;//It was late to register the course
                else return 1;//can register the course 
            }
        }
    }
    TextBgColor(0, 15);
}

void ExportScoreBoardInterface(User A, string Year, string Semester, int CurrentLine, int LineInConsole) {
    bool checkOut = false;
    do {
        char ch;
        system("cls");
        TextBgColor(4, 7);
        PrintText(" _______  ______   ___  ____ _____ ", 30, 0);
        PrintText("| ____\\ \\/ /  _ \\ / _ \\|  _ \\_   _|", 30, 1);
        PrintText("|  _|  \\  /| |_) | | | | |_) || |  ", 30, 2);
        PrintText("| |___ /  \\|  __/| |_| |  _ < | |  ", 30, 3);
        PrintText("|_____/_/\\_\\_|    \\___/|_| \\_\\|_|  ", 30, 4);
        PrintText(" ____   ____ ___  ____  _____ ____   ___    _    ____  ____  ", 30, 5);
        PrintText("/ ___| / ___/ _ \\|  _ \\| ____| __ ) / _ \\  / \\  |  _ \\|  _ \\ ", 30, 6);
        PrintText("\\___ \\| |  | | | | |_) |  _| |  _ \\| | | |/ _ \\ | |_) | | | |", 30, 7);
        PrintText(" ___) | |__| |_| |  _ <| |___| |_) | |_| / ___ \\|  _ <| |_| |", 30, 8);
        PrintText("|____/ \\____\\___/|_| \\_\\_____|____/ \\___/_/   \\_\\_| \\_\\____/ ", 30, 9);

        DrawRectangle(97, 0, 23, 4, 3);
        TextBgColor(4, 3);
        PrintText("-[c]: CHANGE SCHOOL", 97, 0);
        PrintText(" YEAR", 97, 1);
        PrintText("-[a]: EXPORT ALL COURSE", 97, 2);
        PrintText("-[ESC]: BACK TO MENU", 97, 3);

        if (stoi(Semester.substr(8, 1), 0, 10) == 0) {
            TextBgColor(4, 15);
            PrintText("HAVEN'T CREATE SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 40, 10);
            char ch = getch();
            checkOut = true;
        }
        else {
            int y = 11;
            string column[8];
            string FileName = "Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv";
            int lineNum = CountLine(FileName);
            if (lineNum == 1) {
                TextBgColor(4, 15);
                PrintText("THERE ISN'T ANY COURSE EXIST, PRESS ENTER TO BACK TO MENU.", 30, 14);
                ch = getch();
                TextBgColor(0, 15);
                checkOut = true;
                break;
            }
            DrawRectangle(0, 10, 120, 15, 3);
            int a[8] = { 2,13,35,52,73,88,95,105 };
            int b[8] = { 1,9,34,60,76,88,98,108 };
            if (lineNum == 1) {
                string column[8];
                GetLineInfo(FileName, 1, column, 8);
                for (int i = 0; i < 8; i++) {
                    PrintText(column[i], a[i], 11);

                }
                ch = getch();
            }
            else {
                DrawList(8, FileName, 11, a, b, lineNum, CurrentLine - LineInConsole + 1);
                HidePointer();

                GetLineInfo("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", CurrentLine, column, 8);
                DrawRectangle(1, y + LineInConsole, 110, 1, 14);
                TextBgColor(0, 14);
                for (int i = 0; i < 8; i++)
                    PrintText(column[i], b[i], y + LineInConsole);

                do {
                    HidePointer();
                    ch = getch();
                    //[ESC]
                    if (ch == 27) {
                        TextBgColor(0, 15);
                        checkOut = true;
                        break;
                    }
                    if (ch == 72 && CurrentLine > 2) //up
                    {
                        CurrentLine--;
                        LineInConsole--;
                        if (LineInConsole + y <= 11) {
                            LineInConsole = 12;
                            DrawRectangle(0, 10, 120, 15, 15);
                            DrawRectangle(0, 10, 120, 15, 3);
                            DrawList(8, "Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", y, a, b, lineNum, CurrentLine - 11);
                            GetLineInfo("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", CurrentLine, column, 8);
                            DrawRectangle(1, y + LineInConsole, 110, 1, 14);
                            TextBgColor(0, 14);
                            for (int i = 0; i < 8; i++) {
                                PrintText(column[i], b[i], y + LineInConsole);
                            }
                        }
                        else
                            MoveUp("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", CurrentLine, 8, b, y, column, LineInConsole, 110, 1);

                    }
                    if (ch == 80 && CurrentLine < lineNum) //down
                    {
                        CurrentLine++;
                        LineInConsole++;
                        if (LineInConsole + y > 23) {
                            LineInConsole = 1;
                            DrawRectangle(0, 10, 120, 15, 15);
                            DrawRectangle(0, 10, 120, 15, 3);
                            DrawList(8, "Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", y, a, b, lineNum, CurrentLine);
                            GetLineInfo("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", CurrentLine, column, 8);
                            DrawRectangle(1, y + LineInConsole, 110, 1, 14);
                            TextBgColor(0, 14);
                            for (int i = 0; i < 8; i++) {
                                PrintText(column[i], b[i], y + LineInConsole);
                            }
                        }
                        else
                            MoveDown("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", CurrentLine, 8, b, y, column, LineInConsole, 110, 1);
                    }

                    if (ch == 13) {
                        ExportSB(Year, Semester, column[0]);
                        DrawRectangle(40, 15, 25, 5, 4);
                        TextBgColor(14, 4);
                        PrintText("EXPORT SUCCESSFULLY !!!", 41, 17);
                        ch = getch();
                        TextBgColor(0, 15);
                        break;
                        //exportScoreboardInterface(A, year, semester, CurrentLine, lineInConsole);
                    }

                    if (ch == 'a') {
                        fstream file;
                        file.open("Data/SchoolYear/" + Year + "/" + Semester + "/course_info.csv", ios::in);
                        if (!file.is_open()) {
                            cout << "Can't open file" << endl;
                            Sleep(900);
                            checkOut = true;
                            break;
                        }
                        string courseID;
                        getline(file, courseID);
                        while (!file.eof()) {
                            if (courseID.size() == 1) break;
                            getline(file, courseID, ',');
                            ExportSB(Year, Semester, courseID);
                            getline(file, courseID);
                        }
                        DrawRectangle(40, 15, 35, 5, 4);
                        TextBgColor(15, 4);
                        PrintText("EXPORT ALL COURSE SUCCESSFULLY !!!", 41, 17);
                        ch = getch();
                        TextBgColor(0, 15);
                        break;
                        //exportScoreboardInterface(A, year, semester, CurrentLine, lineInConsole);
                    }

                    if (ch == 'c') {
                        SchoolYear s;
                        ChangeYearSemester(s);
                        Year = s.Year;
                        Semester = s.SemesterSchool.NameSemester;
                        break;
                        //exportScoreboardInterface(A, s.year, s.semester.Name, CurrentLine, lineInConsole);
                    }
                    TextBgColor(0, 15);
                } while (true);
            }
        }
        TextBgColor(0, 15);
    } while (checkOut == false);
}

void ExportSB(string SchoolYear, string Semester, string CourseID) {
    fstream fileScore, fileList;
    fileScore.open("Score/Export/" + SchoolYear + "_" + Semester + "_" + CourseID + ".csv", ios::out);
    fileScore << "NO,STUDENT ID,NAME,TOTAL MARK,FINAL MARK,MIDTERM MARK,OTHER MARK";
    fileList.open("Data/SchoolYear/" + SchoolYear + "/" + Semester + "/Course/" + CourseID + ".csv", ios::in);
    string data;
    getline(fileList, data);
    int i = 1;
    while (!fileList.eof()) {
        fileScore << endl << i;
        getline(fileList, data, ',');
        fileScore << "," << data;
        getline(fileList, data, ',');
        fileScore << "," << data;
        getline(fileList, data);
        i++;
        if (i >= 300) break;
    }
}

void ImportScoreBoard(string Year, string Semester, string CourseID, string FileName) {
    fstream file, fileScore;
    file.open(FileName + ".csv", ios::in);
    fileScore.open("Data//SchoolYear//" + Year + "//" + Semester + "//Course//score//" + CourseID + ".csv", ios::out);
    string data;
    getline(file, data);
    fileScore << data;
    while (!file.eof()) {
        getline(file, data);
        fileScore << endl << data;
    }
    file.close();
    fileScore.close();
}

string InputFileName() {
    ShowPointer();
    DrawRectangle(20, 13, 90, 4, 3);
    TextBgColor(0, 3);
    PrintText("ENTER PATH TO FILE NAME (EX: C:/Users/2023-2024_Semester3_TLDC ) :", 20, 13);
    string FileName = "";
    DrawRectangle(21, 14.5, 50, 1, 15);
    TextBgColor(0, 15);
    GotoXY(21, 14.5);
    //getline(cin,FileName);

    char ch;
    do
    {
        ch = getch();
        if (ch == 8) {
            if (FileName.size() > 0) {
                FileName.pop_back();
                GotoXY(ReturnX() - 1, ReturnY());
                cout << " ";
                GotoXY(ReturnX() - 1, ReturnY());
            }
        }
        if (((ch >= 47 && ch <= 58) || (ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122) || ch == 95 || ch == 45 || ch == 32) && FileName.size() < 50) {
            cout << ch;
            FileName.push_back(ch);
        }
        if (ch == 27) {
            return "";
        }
    } while (ch != 13 || FileName.size() == 0);
    return FileName;
}

void ImportScoreBoardUI() {
    char ch;
    system("cls");
    DrawASCIIImport();
    User user;
    SchoolYear SY;
    string FileName;
    DetermineYearSemesterNow(SY.Year, SY.SemesterSchool.NameSemester);
    string year, semester;
    DetermineYearSemesterNow(year, semester);
    if (stoi(semester.substr(8, 1), 0, 10) == 0) {
        TextBgColor(4, 15);
        PrintText("HAVEN'T CREATE SEMESTER YET, PRESS ENTER TO BACK TO MENU.", 40, 10);
        char ch = getch();
    }
    else {
        string ImportMenu[] = { "1. Import from file library.", "2. Import file by path.", "3.Back to Menu" };
        int option;
        do {

            bool flagout = false;
            system("cls");
            DrawMenu(ImportMenu, 3, 45, 10, 2, &DrawASCIIImport);
            option = MoveAndChoose(3, ImportMenu, 45, 10, 2);
            switch (option)
            {
            case 0: {
                system("cls");
                while (true) {
                    try {
                        Course* SLC = SelectCourse(user, SY, &ReadFileListCourse, &DrawASCIIImport);
                        if (SLC == NULL) {
                            flagout = true;
                            break;
                        }
                        FileName = "Score/Import/" + SY.Year + "_" + SY.SemesterSchool.NameSemester + "_" + SLC->IDCourse;
                        ifstream f;
                        f.open(FileName + ".csv");
                        if (!f.is_open()) {
                            DrawRectangle(3, 14, 115, 4, 4);
                            PrintText("The score file for this course is not in the file library. ", 35, 15);
                            PrintText("Please pass it in file library or import by path. ", 40, 16);
                            Sleep(4500);
                            f.close();
                            continue;
                        }
                        else {
                            f.close();
                            break;
                        }
                    }
                    catch (const char* err) {
                        string s = string(err);
                        s.pop_back();
                        s += " to import.";
                        DrawRectangle(3, 14, 115, 3, 4);
                        PrintText(err, 45, 15);
                        TextBgColor(0, 15);
                        Sleep(1800);
                        break;
                    }
                }
                break;
            }
            case 1: {
                system("cls");
                DrawASCIIImport();
                FileName = InputFileName();
                if (FileName == "") {
                    continue;
                }
                break;
            }
            default:
                return;
            }
            if (flagout == true) {
                continue;
            }
            fstream file;
            file.open(FileName + ".csv", ios::in);
            if (!file.is_open()) {
                DrawRectangle(40, 15, 25, 5, 4);
                TextBgColor(15, 4);
                PrintText("FILE DOESN'T EXIST !!!", 41, 17);
                ch = getch();
                TextBgColor(0, 15);
            }
            else {
                HidePointer();
                string info = FileName.substr(FileName.find_last_of("/") + 1, FileName.size() - FileName.find_last_of("/"));
                ImportScoreBoard(info.substr(0, 9), info.substr(10, 9), info.substr(20, info.size() - 1), FileName);
                DrawRectangle(40, 15, 25, 5, 4);
                TextBgColor(15, 4);
                PrintText("IMPORT SUCCESSFUL !!!", 41, 17);
                ch = getch();
                TextBgColor(0, 15);
            }
            file.close();
        } while (true);
        TextBgColor(0, 15);
    }
}

void ListClass(User A, SchoolYear Yeartmp, FunShowClass Fun) {
    bool checkOut = false;
    do {
        string year = Yeartmp.Year, semester = Yeartmp.SemesterSchool.NameSemester;
        char ch;
        HidePointer();
        system("cls");
        TextBgColor(4, 7);
        PrintText(" _     ___ ____ _____    ____ _        _    ____ ____  ", 30, 2);
        PrintText("| |   |_ _/ ___|_   _|  / ___| |      / \\  / ___/ ___| ", 30, 3);
        PrintText("| |    | |\\___ \\ | |   | |   | |     / _ \\ \\___ \\___ \\ ", 30, 4);
        PrintText("| |___ | | ___) || |   | |___| |___ / ___ \\ ___) |__) |", 30, 5);
        PrintText("|_____|___|____/ |_|    \\____|_____/_/   \\_\\____/____/ ", 30, 6);

        DrawRectangle(97, 0, 22, 6, 3);
        TextBgColor(4, 3);
        PrintText("-[c]: CHANGE SCHOOL", 97, 0);
        PrintText(" YEAR", 97, 1);
        PrintText("-[ESC]: BACK TO MENU", 97, 3);
        PrintText("-[ENTER]: CHOSE", 97, 5);

        string FileName = "Data/SchoolYear/" + year + "/class_info.csv";
        int lineNum = CountLine(FileName);
        int y = 11;
        DrawRectangle(8, 10, 95, 15, 3);
        int a[5] = { 11,17,33,65,90 };
        int b[5] = { 11,18,33,72,90 };
        DrawList(5, FileName, y, a, b, lineNum, 2);
        HidePointer();

        int CurrentLine = 2, lineInConsole = 1;
        string column[5];
        GetLineInfo(FileName, CurrentLine, column, 5);
        DrawRectangle(8, y + lineInConsole, 95, 1, 3);
        TextBgColor(0, 3);
        for (int i = 0; i < 5; i++)
            PrintText(column[i], b[i], y + lineInConsole);

        do {
            HidePointer();
            ch = getch();
            //[ESC]
            if (ch == 27) {
                TextBgColor(0, 15);
                checkOut = true;
                break;
                //menuStaff(A);
            }
            if (ch == 72 && CurrentLine > 2) //up
            {
                CurrentLine--;
                lineInConsole--;
                if (lineInConsole + y <= 11) {
                    lineInConsole = 12;
                    DrawRectangle(8, 10, 95, 15, 15);
                    DrawRectangle(8, 10, 95, 15, 3);
                    DrawList(5, FileName, y, a, b, lineNum, CurrentLine - 11);
                    GetLineInfo(FileName, CurrentLine, column, 5);
                    DrawRectangle(8, y + lineInConsole, 95, 1, 3);
                    TextBgColor(0, 3);
                    for (int i = 0; i < 5; i++) {
                        PrintText(column[i], b[i], y + lineInConsole);
                    }
                }
                else
                    MoveUp(FileName, CurrentLine, 5, b, y, column, lineInConsole, 95, 8);
            }
            if (ch == 80 && CurrentLine < lineNum) //down
            {
                CurrentLine++;
                lineInConsole++;
                if (lineInConsole + y > 23) {
                    lineInConsole = 1;
                    DrawRectangle(8, 10, 95, 15, 15);
                    DrawRectangle(8, 10, 95, 15, 3);
                    DrawList(5, FileName, y, a, b, lineNum, CurrentLine);
                    GetLineInfo(FileName, CurrentLine, column, 5);
                    DrawRectangle(8, y + lineInConsole, 95, 1, 3);
                    TextBgColor(0,3);
                    for (int i = 0; i < 5; i++) {
                        PrintText(column[i], b[i], y + lineInConsole);
                    }
                }
                else
                    MoveDown(FileName, CurrentLine, 5, b, y, column, lineInConsole, 95, 8);
            }
            if (ch == 13) {
                TextBgColor(0, 15);
                Fun(A, Yeartmp, column[1]);
                break;
                //listClass(A, Y, Fun);
            }
            if (ch == 'c') {
                TextBgColor(0, 15);
                ChangeYearSemester(Yeartmp);
                break;
                //listClass(A, Y, Fun);
            }
        } while (true);
        TextBgColor(0, 15);
    } while (checkOut == false);
}

void ShowStudentInclass(User Usertmp, SchoolYear Yeartmp, string ClassName) {
    bool checkOut = false;
    do {
        string year = Yeartmp.Year, semester = Yeartmp.SemesterSchool.NameSemester;
        char ch;
        HidePointer();
        system("cls");
        TextBgColor(4, 7);
        PrintText(" _     ___ ____ _____   ____ _____ _   _ ____  _____ _   _ _____ ", 30, 2);
        PrintText("| |   |_ _/ ___|_   _| / ___|_   _| | | |  _ \\| ____| \\ | |_   _|", 30, 3);
        PrintText("| |    | |\\___ \\ | |   \\___ \\ | | | | | | | | |  _| |  \\| | | | ", 30, 4);
        PrintText("| |___ | | ___) || |    ___) || | | |_| | |_| | |___| |\\  | | | ", 30, 5);
        PrintText("|_____|___|____/ |_|   |____/ |_|  \\___/|____/|_____|_| \\_| |_| ", 30, 6);

        DrawRectangle(97, 0, 22, 6, 3);
        TextBgColor(4, 3);
        //PrintText("-[c]: CHANGE SCHOOL", 97, 0);
        //PrintText(" YEAR", 97, 1);
        PrintText("-[ESC]: BACK TO MENU", 97, 3);
        //printtext("-[ENTER]: CHOSE", 97, 5);

        string FileName = "Data/SchoolYear/" + year + "/" + ClassName + ".csv";
        int lineNum = CountLine(FileName);
        int y = 11;
        DrawRectangle(8, 10, 100, 15, 3);
        int a[6] = { 8,18,36,64,85,95 };
        int b[6] = { 8,18,36,64,85,95 };
        DrawList(6, FileName, y, a, b, lineNum, 2);
        HidePointer();

        int CurrentLine = 2, lineInConsole = 1;
        string column[6];
        GetLineInfo(FileName, CurrentLine, column, 6);
        DrawRectangle(8, y + lineInConsole, 100, 1, 14);
        TextBgColor(0, 14);
        for (int i = 0; i < 6; i++)
            PrintText(column[i], b[i], y + lineInConsole);

        do {
            HidePointer();
            ch = getch();
            //[ESC]
            if (ch == 27) {
                TextBgColor(0, 15);
                checkOut = true;
                break;
                //listClass(user, Y, &showStudentInclass);
            }
            if (ch == 72 && CurrentLine > 2) //up
            {
                CurrentLine--;
                lineInConsole--;
                if (lineInConsole + y <= 11) {
                    lineInConsole = 12;
                    DrawRectangle(8, 10, 100, 15, 15);
                    DrawRectangle(8, 10, 100, 15, 3);
                    DrawList(6, FileName, y, a, b, lineNum, CurrentLine - 11);
                    GetLineInfo(FileName, CurrentLine, column, 6);
                    DrawRectangle(8, y + lineInConsole, 100, 1, 14);
                    TextBgColor(0, 14);
                    for (int i = 0; i < 6; i++) {
                        PrintText(column[i], b[i], y + lineInConsole);
                    }
                }
                else
                    MoveUp(FileName, CurrentLine, 6, b, y, column, lineInConsole, 100, 8);
            }
            if (ch == 80 && CurrentLine < lineNum) //down
            {
                CurrentLine++;
                lineInConsole++;
                if (lineInConsole + y > 23) {
                    lineInConsole = 1;
                    DrawRectangle(8, 10, 100, 15, 15);
                    DrawRectangle(8, 10, 100, 15, 3);
                    DrawList(6, FileName, y, a, b, lineNum, CurrentLine);
                    GetLineInfo(FileName, CurrentLine, column, 6);
                    DrawRectangle(8, y + lineInConsole, 100, 1, 14);
                    TextBgColor(0, 14);
                    for (int i = 0; i < 6; i++) {
                        PrintText(column[i], b[i], y + lineInConsole);
                    }
                }
                else
                    MoveDown(FileName, CurrentLine, 6, b, y, column, lineInConsole, 100, 8);
            }
            /*if (ch == 13) {
                User A;
                A.ID = column[1];
                A.info.IDstd = column[1];
                A.info.Class = classname;
                A.info.IDsocial = column[5];
                A.info.Bir = column[3];
                A.info.name = column[2];
                A.info.sex = column[4];
                get_course(A, Y);
                TextBgColor(0, 15);
                edit_score(A, Y, view_all_score_of_1_student(A, Y));
                //showStudentInclass(user,Y, classname);
                break;
            }*/
        } while (true);
        TextBgColor(0, 15);
    } while (checkOut == false);

}

void DrawListStudent(int ColumnNum, SchoolYear Yeartmp, string FileName, int y, int IndexA[], int IndexB[], int Line, int FlagLine) {
    if (Line == 0 || ColumnNum == 0) return;
    string* datanew = new string[Line];
    string* column = new string[ColumnNum];
    TextBgColor(4, 11);
    GetLineInfoForStudent(FileName, Yeartmp, 1, column, ColumnNum);
    for (int i = 0; i < ColumnNum; i++) {
        PrintText(column[i], IndexA[i], y);
    }
    TextBgColor(0, 11);
    y++;
    int j = FlagLine, h = 1;
    while (j <= Line && h <= 12) {
        GetLineInfoForStudent(FileName, Yeartmp, j, column, ColumnNum);
        for (int i = 0; i < ColumnNum; i++) {
            PrintText(column[i], IndexB[i], y);
        }
        y++; j++;
        h++;
    }
}

void GetAllCourseStudent(User& B, SchoolYear SY, float& OverallGPA) {
    DetermineYearSemesterNow(SY.Year, SY.SemesterSchool.NameSemester);
    InitListMark(B.info.head);
    int i = 0;
    int count = 0;
    float NumCredit = 0;
    do {
        i = GetCourse(B, SY, 1);
        if (i == -1) {
            break;
        }
        GetScore(B, SY, count);
        //Tinh diem trung binh 1 ki hoc ma sinh vien da hoc
        MarkNode* temp = B.info.head;
        while (temp != NULL) {
            if (temp->info.AvgMark != 0) {
                NumCredit += stoi(temp->info.C, 0, 10);
                OverallGPA += stoi(temp->info.C, 0, 10) * temp->info.AvgMark;
            }
            temp = temp->next;
        }
        BackASemester(SY);
    } while (i != -1);
    OverallGPA = ((OverallGPA / NumCredit) / 10) * 4;
}

void GetLineInfoForStudent(string FileName, SchoolYear Yeartmp, int Line, string Column[], int ColumnNum) {
    if (Line > CountLine(FileName)) cout << "Not exist line";
    int numLine = CountLine(FileName);
    fstream file;
    string data;
    file.open(FileName, ios::in);
    if (Line == 1) {
        for (int j = 0; j < ColumnNum - 3; j++) {
            getline(file, data, ',');
            Column[j] = data;
        }
        Column[3] = "TOTAL MARK";
        Column[4] = "GPA SEMESTER";
        Column[5] = "GPA OVERALL";
        return;
    }
    for (int i = 1; i <= numLine; i++) {
        if (i == Line) {
            for (int j = 0; j < ColumnNum; j++) {
                if (j != ColumnNum - 1) {
                    getline(file, data, ',');
                    Column[j] = data;
                }
                else {
                    getline(file, data);
                    Column[j] = data;
                }
            }
            //Get Mark
            User A, B;
            A.IDUser = Column[1];
            A.info.IDSt = Column[1];
            A.info.Class = FileName.substr(31, FileName.find_last_of(".") - FileName.find_last_of("/") - 1);
            A.info.NameSt = Column[2];
            B = A;
            GetCourse(A, Yeartmp, 0);
            int count = 0;
            GetScore(A, Yeartmp, count);
            float TotalMark = 0;
            int NumCredit = 0;
            MarkNode* temp = A.info.head;
            while (temp != NULL) {
                if (temp->info.AvgMark != 0) {
                    NumCredit += stoi(temp->info.C, 0, 10);
                    TotalMark += stoi(temp->info.C, 0, 10) * temp->info.AvgMark;
                }
                temp = temp->next;
            }
            if (NumCredit == 0) NumCredit = 1;
            TotalMark = TotalMark / float(NumCredit);
            float semesterGPA = (TotalMark / 10) * 4;
            float overallGPA = 0;
            GetAllCourseStudent(B, Yeartmp, overallGPA);
            //////////////////////////////////////
            Column[3] = to_string(TotalMark);
            Column[4] = to_string(semesterGPA);
            Column[5] = to_string(overallGPA);
            break;
        }
        else {
            getline(file, data);
        }
    }
}

void ShowScoreOfClass(User Usertmp, SchoolYear Yeartmp, string ClassName) {
    bool checkOut = false;
    do {
        string year = Yeartmp.Year, semester = Yeartmp.SemesterSchool.NameSemester;
        char ch;
        HidePointer();
        system("cls");
        TextBgColor(13, 15);
        PrintText(" _     ___ ____ _____   ____ _____ _   _ ____  _____ _   _ _____ ", 30, 2);
        PrintText("| |   |_ _/ ___|_   _| / ___|_   _| | | |  _ \\| ____| \\ | |_   _|", 30, 3);
        PrintText("| |    | |\\___ \\ | |   \\___ \\ | | | | | | | | |  _| |  \\| | | | ", 30, 4);
        PrintText("| |___ | | ___) || |    ___) || | | |_| | |_| | |___| |\\  | | | ", 30, 5);
        PrintText("|_____|___|____/ |_|   |____/ |_|  \\___/|____/|_____|_| \\_| |_| ", 30, 6);

        DrawRectangle(97, 0, 22, 6, 11);
        TextBgColor(4, 11);
        PrintText("-[c]: CHANGE SCHOOL", 97, 0);
        PrintText(" YEAR", 97, 1);
        PrintText("-[ESC]: BACK TO MENU", 97, 3);
        PrintText("-[ENTER]: CHOSE", 97, 5);

        string FileName = "Data/SchoolYear/" + year + "/" + ClassName + ".csv";
        int lineNum = CountLine(FileName);
        int y = 11;
        DrawRectangle(8, 10, 100, 15, 11);
        int a[6] = { 8,18,36,63,80,95 };
        int b[6] = { 8,18,36,64,80,95 };
        DrawListStudent(6, Yeartmp, FileName, y, a, b, lineNum, 2);
        HidePointer();

        int CurrentLine = 2, lineInConsole = 1;
        string column[6];
        GetLineInfoForStudent(FileName, Yeartmp, CurrentLine, column, 6);
        DrawRectangle(8, y + lineInConsole, 100, 1, 14);
        TextBgColor(0, 14);
        for (int i = 0; i < 6; i++)
            PrintText(column[i], b[i], y + lineInConsole);
        do {
            HidePointer();
            ch = getch();
            //[ESC]
            if (ch == 27) {
                TextBgColor(0, 15);
                checkOut = true;
                break;
            }
            if (ch == 72 && CurrentLine > 2) //up
            {
                CurrentLine--;
                lineInConsole--;
                if (lineInConsole + y <= 11) {
                    lineInConsole = 12;
                    DrawRectangle(8, 10, 100, 15, 15);
                    DrawRectangle(8, 10, 100, 15, 11);
                    DrawListStudent(6, Yeartmp, FileName, y, a, b, lineNum, CurrentLine - 11);
                    GetLineInfoForStudent(FileName, Yeartmp, CurrentLine, column, 6);
                    DrawRectangle(8, y + lineInConsole, 100, 1, 14);
                    TextBgColor(0, 14);
                    for (int i = 0; i < 6; i++) {
                        PrintText(column[i], b[i], y + lineInConsole);
                    }
                }
                else {
                    GetLineInfoForStudent(FileName, Yeartmp, CurrentLine + 1, column, 6);
                    DrawRectangle(8, y + lineInConsole + 1, 100, 1, 11);
                    TextBgColor(0, 11);
                    for (int i = 0; i < 6; i++) {
                        PrintText(column[i], b[i], y + lineInConsole + 1);
                    }
                    GetLineInfoForStudent(FileName, Yeartmp, CurrentLine, column, 6);
                    DrawRectangle(8, y + lineInConsole, 100, 1, 14);
                    TextBgColor(0, 14);
                    for (int i = 0; i < 6; i++) {
                        PrintText(column[i], b[i], y + lineInConsole);
                    }
                }
            }
            if (ch == 80 && CurrentLine < lineNum) //down
            {
                CurrentLine++;
                lineInConsole++;
                if (lineInConsole + y > 23) {
                    lineInConsole = 1;
                    DrawRectangle(8, 10, 100, 15, 15);
                    DrawRectangle(8, 10, 100, 15, 11);
                    DrawListStudent(6, Yeartmp, FileName, y, a, b, lineNum, CurrentLine);
                    GetLineInfoForStudent(FileName, Yeartmp, CurrentLine, column, 6);
                    DrawRectangle(8, y + lineInConsole, 100, 1, 14);
                    TextBgColor(0, 14);
                    for (int i = 0; i < 6; i++) {
                        PrintText(column[i], b[i], y + lineInConsole);
                    }
                }
                else
                {
                    GetLineInfoForStudent(FileName, Yeartmp, CurrentLine - 1, column, 6);
                    DrawRectangle(8, y - 1 + lineInConsole, 100, 1, 11);
                    TextBgColor(0, 11);
                    for (int i = 0; i < 6; i++) {
                        PrintText(column[i], b[i], y + lineInConsole - 1);
                    }
                    GetLineInfoForStudent(FileName, Yeartmp, CurrentLine, column, 6);
                    DrawRectangle(8, y + lineInConsole, 100, 1, 14);
                    TextBgColor(0, 14);
                    for (int i = 0; i < 6; i++) {
                        PrintText(column[i], b[i], y + lineInConsole);
                    }
                }
            }
            if (ch == 13) {
                User A;
                A.IDUser = column[1];
                A.info.IDSt = column[1];
                A.info.Class = ClassName;
                A.info.IDSocial = column[5];
                A.info.Birthday = column[3];
                A.info.NameSt = column[2];
                A.info.sex = column[4];
                GetCourse(A, Yeartmp);
                TextBgColor(0, 15);
                EditScore(A, Yeartmp, ViewAllScoreOfOneStudent(A, Yeartmp));
                break;
                //showScoreOfClass(user, Y, classname);
            }
        } while (true);
        TextBgColor(0, 15);
    } while (checkOut == false);
}

void ListClassUseFor14(SchoolYear Y) {
    string year = Y.Year, semester = Y.SemesterSchool.NameSemester;
    char ch;
    HidePointer();
    system("cls");
    TextBgColor(4, 7);
    PrintText(" _     ___ ____ _____    ____ _        _    ____ ____ ", 30, 2);
    PrintText("| |   |_ _/ ___|_   _|  / ___| |      / \\  / ___/ ___|", 30, 3);
    PrintText("| |    | |\\___ \\ | |   | |   | |     / _ \\ \\___ \\___ \\ ", 30, 4);
    PrintText("| |___ | | ___) || |   | |___| |___ / ___ \\ ___) |__) |", 30, 5);
    PrintText("|_____|___|____/ |_|    \\____|_____/_/   \\_\\____/____/ ", 30, 6);

    DrawRectangle(97, 0, 22, 6, 11);
    TextBgColor(4, 11);
    PrintText("-[c]: CHANGE SCHOOL", 97, 0);
    PrintText(" YEAR", 97, 1);
    PrintText("-[ESC]: BACK TO MENU", 97, 3);
    PrintText("-[ENTER]: CHOSE", 97, 5);

    string FileName = "Data/SchoolYear/" + year + "/class_info.csv";
    int lineNum = CountLine(FileName);
    int y = 11;
    DrawRectangle(8, 10, 95, 15, 11);
    int a[5] = { 11,17,33,65,90 };
    int b[5] = { 11,18,33,72,90 };
    DrawList(5, FileName, y, a, b, lineNum, 2);
    HidePointer();

    int CurrentLine = 2, lineInConsole = 1;
    string column[5];
    GetLineInfo(FileName, CurrentLine, column, 5);
    DrawRectangle(8, y + lineInConsole, 95, 1, 14);
    TextBgColor(0, 14);
    for (int i = 0; i < 5; i++)
        PrintText(column[i], b[i], y + lineInConsole);

    do {
        HidePointer();
        ch = getch();
        //[ESC]
        if (ch == 27) {
            break;
        }
        if (ch == 72 && CurrentLine > 2) //up
        {
            CurrentLine--;
            lineInConsole--;
            if (lineInConsole + y <= 11) {
                lineInConsole = 12;
                DrawRectangle(8, 10, 95, 15, 15);
                DrawRectangle(8, 10, 95, 15, 11);
                DrawList(5, FileName, y, a, b, lineNum, CurrentLine - 11);
                GetLineInfo(FileName, CurrentLine, column, 5);
                DrawRectangle(8, y + lineInConsole, 95, 1, 14);
                TextBgColor(0, 14);
                for (int i = 0; i < 5; i++) {
                    PrintText(column[i], b[i], y + lineInConsole);
                }
            }
            else
                MoveUp(FileName, CurrentLine, 5, b, y, column, lineInConsole, 95, 8);
        }
        if (ch == 80 && CurrentLine < lineNum) //down
        {
            CurrentLine++;
            lineInConsole++;
            if (lineInConsole + y > 23) {
                lineInConsole = 1;
                DrawRectangle(8, 10, 95, 15, 15);
                DrawRectangle(8, 10, 95, 15, 11);
                DrawList(5, FileName, y, a, b, lineNum, CurrentLine);
                GetLineInfo(FileName, CurrentLine, column, 5);
                DrawRectangle(8, y + lineInConsole, 95, 1, 14);
                TextBgColor(0, 14);
                for (int i = 0; i < 5; i++) {
                    PrintText(column[i], b[i], y + lineInConsole);
                }
            }
            else
                MoveDown(FileName, CurrentLine, 5, b, y, column, lineInConsole, 95, 8);
        }
        if (ch == 13) {
            TextBgColor(0, 15);
            ShowScoreOfClassPreventive(Y, column[1]);
            ListClassUseFor14(Y);
        }
        if (ch == 'c') {
            TextBgColor(0, 15);
            ChangeYearSemester(Y);
            ListClassUseFor14(Y);
        }
    } while (true);
    TextBgColor(0, 15);
}

void ShowScoreOfClassPreventive(SchoolYear Y, string ClassName) {
    string year = Y.Year, semester = Y.SemesterSchool.NameSemester;
    char ch;
    HidePointer();
    system("cls");
    TextBgColor(4, 7);
    PrintText(" _     ___ ____ _____   ____ _____ _   _ ____  _____ _   _ _____ ", 30, 2);
    PrintText("| |   |_ _/ ___|_   _| / ___|_   _| | | |  _ \\| ____| \\ | |_   _|", 30, 3);
    PrintText("| |    | |\\___ \\ | |   \\___ \\ | | | | | | | | |  _| |  \\| | | | ", 30, 4);
    PrintText("| |___ | | ___) || |    ___) || | | |_| | |_| | |___| |\\  | | | ", 30, 5);
    PrintText("|_____|___|____/ |_|   |____/ |_|  \\___/|____/|_____|_| \\_| |_| ", 30, 6);

    DrawRectangle(97, 0, 22, 6, 3);
    TextBgColor(4, 3);
    PrintText("-[c]: CHANGE SCHOOL", 97, 0);
    PrintText(" YEAR", 97, 1);
    PrintText("-[ESC]: BACK TO MENU", 97, 3);
    PrintText("-[ENTER]: CHOSE", 97, 5);

    string FileName = "Data/SchoolYear/" + year + "/" + ClassName + ".csv";
    int lineNum = CountLine(FileName);
    int y = 11;
    DrawRectangle(8, 10, 100, 15, 3);
    int a[6] = { 8,18,44,63,80,95 };
    int b[6] = { 8,18,36,64,80,95 };
    DrawListStudent(6, Y, FileName, y, a, b, lineNum, 2);
    HidePointer();

    int CurrentLine = 2, lineInConsole = 1;
    string column[6];
    GetLineInfoForStudent(FileName, Y, CurrentLine, column, 6);
    DrawRectangle(8, y + lineInConsole, 100, 1, 14);
    TextBgColor(0, 14);
    for (int i = 0; i < 6; i++)
        PrintText(column[i], b[i], y + lineInConsole);

    do {
        HidePointer();
        ch = getch();
        //[ESC]
        if (ch == 27) {
            break;
        }
        if (ch == 72 && CurrentLine > 2) //up
        {
            CurrentLine--;
            lineInConsole--;
            if (lineInConsole + y <= 11) {
                lineInConsole = 12;
                DrawRectangle(8, 10, 100, 15, 15);
                DrawRectangle(8, 10, 100, 15, 3);
                DrawListStudent(6, Y, FileName, y, a, b, lineNum, CurrentLine - 11);
                GetLineInfoForStudent(FileName, Y, CurrentLine, column, 6);
                DrawRectangle(8, y + lineInConsole, 100, 1, 14);
                TextBgColor(0, 14);
                for (int i = 0; i < 6; i++) {
                    PrintText(column[i], b[i], y + lineInConsole);
                }
            }
            else {
                GetLineInfoForStudent(FileName, Y, CurrentLine + 1, column, 6);
                DrawRectangle(8, y + lineInConsole + 1, 100, 1, 3);
                TextBgColor(0, 3);
                for (int i = 0; i < 6; i++) {
                    PrintText(column[i], b[i], y + lineInConsole + 1);
                }

                GetLineInfoForStudent(FileName, Y, CurrentLine, column, 6);
                DrawRectangle(8, y + lineInConsole, 100, 1, 14);
                TextBgColor(0, 14);
                for (int i = 0; i < 6; i++) {
                    PrintText(column[i], b[i], y + lineInConsole);
                }
            }
        }
        if (ch == 80 && CurrentLine < lineNum) //down
        {
            CurrentLine++;
            lineInConsole++;
            if (lineInConsole + y > 23) {
                lineInConsole = 1;
                DrawRectangle(8, 10, 100, 15, 15);
                DrawRectangle(8, 10, 100, 15, 3);
                DrawListStudent(6, Y, FileName, y, a, b, lineNum, CurrentLine);
                GetLineInfoForStudent(FileName, Y, CurrentLine, column, 6);
                DrawRectangle(8, y + lineInConsole, 100, 1, 14);
                TextBgColor(0, 14);
                for (int i = 0; i < 6; i++) {
                    PrintText(column[i], b[i], y + lineInConsole);
                }
            }
            else
            {
                GetLineInfoForStudent(FileName, Y, CurrentLine - 1, column, 6);
                DrawRectangle(8, y - 1 + lineInConsole, 100, 1, 3);
                TextBgColor(0, 3);
                for (int i = 0; i < 6; i++) {
                    PrintText(column[i], b[i], y + lineInConsole - 1);
                }
                GetLineInfoForStudent(FileName, Y, CurrentLine, column, 6);
                DrawRectangle(8, y + lineInConsole, 100, 1, 14);
                TextBgColor(0, 14);
                for (int i = 0; i < 6; i++) {
                    PrintText(column[i], b[i], y + lineInConsole);
                }
            }
        }
    } while (true);
    TextBgColor(0, 15);
}
