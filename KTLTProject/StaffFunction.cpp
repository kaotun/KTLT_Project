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
