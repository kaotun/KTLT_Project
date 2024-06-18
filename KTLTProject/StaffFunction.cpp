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
