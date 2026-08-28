#include "ConsoleProcess.h"
#include "Login.h"
#include "Menu.h"
#include "ListClass.h"
#include "Struct.h"
#include <stdio.h> 
#include <conio.h> 

void InsertUserName(string& UserName) {
    ShowPointer();
    char index = getch();
    while (index != 13) {  //Enter
        if (index == 8) {       //Backspace
            if (UserName.size() > 0) {
                UserName.pop_back();
                GotoXY(ReturnX() - 1, ReturnY());
                cout << " ";
                GotoXY(ReturnX() - 1, ReturnY());
            }
        }
        //Other index
        else if (index >= 33 && index <= 126 && UserName.size() <= 15) {
            cout << index;
            UserName.push_back(index);
        }
        index = getch();
    }
}

void InsertPassword(string& Password) {
    ShowPointer();
    Password = "";
    char index = getch();
    while (index != 13) {    //Enter
        if (index == 8) {      //Backspace
            if (Password.size() > 0) {
                Password.pop_back();
                GotoXY(ReturnX() - 1, ReturnY());
                cout << " ";
                GotoXY(ReturnX() - 1, ReturnY());
            }
        }
        //Other index
        else if (index >= 33 && index <= 126 && Password.size() <= 15) {
            cout << "*";
            Password.push_back(index);
        }
        index = getch();
    }
}

void LoginInterFace(User& Usertmp) {

    ShowPointer();
    TextBgColor(3, 0);
    system("cls");

    Usertmp.IDUser = Usertmp.Password = "";

    PrintText("  _   _   ____  __  __  _   _  ____", 2, 15);
    PrintText(" | | | | / ___||  \\/  || | | |/ ___|", 2, 16);
    PrintText(" | |_| || |    | |\\/| || | | |\\___ \\", 2, 17);
    PrintText(" |  _  || |___ | |  | || |_| | ___) |", 2, 18);
    PrintText(" |_| |_| \\____||_|  |_| \\___/ |____/", 2, 19);

    PrintText("  _____  ___  _____", 86, 15);
    PrintText(" |  ___||_ _||_   _|", 86, 16);
    PrintText(" | |_    | |   | |", 86, 17);
    PrintText(" |  _|   | |   | |", 86, 18);
    PrintText(" |_|    |___|  |_|", 86, 19);
    PrintText(" __  __    _    _   _    _    ____ _____ ____", 38, 0);
    PrintText("|  \\/  |  / \\  | \\ | |  / \\  / ___| ____|  _ \\ ", 38, 1);
    PrintText("| |\\/| | / _ \\ |  \\| | / _ \\| |  _|  _| | |_) |", 38, 2);
    PrintText("| |  | |/ ___ \\| |\\  |/ ___ \\ |_| | |___|  _ <", 38, 3);
    PrintText("|_|  |_/_/   \\_\\_| \\_/_/   \\_\\____|_____|_| \\_\\ ", 38, 4);

    PrintText(" ____ _____ _   _ ____  _____ _   _ _____", 40, 6);
    PrintText("/ ___|_   _| | | |  _ \\| ____| \\ | |_   _|", 40, 7);
    PrintText("\\___ \\ | | | | | | | | |  _| |  \\| | | |", 40, 8);
    PrintText(" ___) || | | |_| | |_| | |___| |\\  | | |", 40, 9);
    PrintText("|____/ |_|  \\___/|____/|_____|_| \\_| |_|", 40, 10);

    TextColor(0);
    DrawRectangle(47, 15, 27, 10, 19);
    PrintText("USERNAME : ", 48, 16);
    PrintText("PASSWORD : ", 48, 19);

    DrawRectangle(48, 17, 25, 1, 15);
    DrawRectangle(48, 20, 25, 1, 15);
    GotoXY(48, 22);
    cout << "ENTER TO LOGIN";

    GotoXY(48, 17);
    InsertUserName(Usertmp.IDUser);

    GotoXY(48, 20);
    InsertPassword(Usertmp.Password);
}

int CheckLogin(User& Usertmp) {
    fstream file1, file2;
    file1.open("Data\\InformationOfLogin.csv", ios::in);
    file2.open("Data\\InformationOfLogin.csv", ios::in);

    if (!file1.is_open() || !file2.is_open()) {
        cout << "Error File Open";
        return -1;
    }

    string row, column;
    int caseUser;
    bool check = false;
    while (!file1.eof())
    {
        getline(file1, row);
        while (!file2.eof())
        {
            getline(file2, column, ',');
            if (column.compare(Usertmp.IDUser) == 0) {
                getline(file2, column, ',');
                if (column.compare(Usertmp.Password) == 0) {
                    check = true;
                    getline(file2, column, ',');
                    caseUser = stoi(column, 0, 10);
                    break;
                }
            }
            getline(file2, column);
            break;
        }
        if (check == true) break;
    }

    if (check == false) return -1;

    Usertmp.role = caseUser;
    if (caseUser == 1) {
        getline(file2, column, '\n');
        Usertmp.info.Class = column;
    }

    file1.close();
    file2.close();

    return caseUser;
}

void RepeatLogin(User& Usertmp) {
    TextColor(0);
    do
    {
        system("cls");
        LoginInterFace(Usertmp);

        if (CheckLogin(Usertmp) == -1)
        {
            GotoXY(48, 24);
            cout << "LOGIN FAIL";
            HidePointer();
            Sleep(900);
        }
    } while (CheckLogin(Usertmp) == -1);
    GotoXY(48, 24);
    cout << "LOGIN SUCCESSFUL";
    HidePointer();
    Sleep(900);
    system("cls");
    if (Usertmp.role == 1) MenuStudent(Usertmp);
    else MenuStaff(Usertmp);
}



