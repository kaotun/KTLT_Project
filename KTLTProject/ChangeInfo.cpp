#include "Struct.h"
#include "ConsoleProcess.h"
#include "Login.h"

void RewriteInfoFile(User Usertmp) {
    fstream FilePrv, FileAft;
    string OldName = "Data/InformationOfLogin.csv";
    string NewName = "Data/InformationOfLogin_new.csv";
    FilePrv.open(OldName, ios::in);
    FileAft.open(NewName, ios::out);
    string temp;
    while (FilePrv.eof() == false) {
        getline(FilePrv, temp, ',');
        FileAft << temp << ',';
        if (Usertmp.IDUser.compare(temp) != 0) {
            getline(FilePrv, temp);
            FileAft << temp << '\n';
        }
        else {
            getline(FilePrv, temp);
            string temp1 = Usertmp.Password + ',' + to_string(Usertmp.role);
            if (Usertmp.role == 1) {
                temp1 = temp1 + ',' + Usertmp.info.Class;
            }
            FileAft << temp1 << '\n';
        }
    }
    FilePrv.close();
    FileAft.close();
    // removing the existing file
    remove(OldName.c_str());
    // renaming the updated file with the existing file name
    rename(NewName.c_str(), OldName.c_str());
};

void ChangePassword(User& Usertmp) {
    system("cls");
    PrintText(" _____  _____  _____  _____  _____  _____    _____  _____  _____  _____  _ _ _  _____  _____  ____  ", 10, 4);
    PrintText("|     ||  |  ||  _  ||   | ||   __||   __|  |  _  ||  _  ||   __||   __|| | | ||     || __  ||    \\ ", 10, 5);
    PrintText("|   --||     ||     || | | ||  |  ||   __|  |   __||     ||__   ||__   || | | ||  |  ||    -||  |  |", 10, 6);
    PrintText("|_____||__|__||__|__||_|___||_____||_____|  |__|   |__|__||_____||_____||_____||_____||__|__||____/ ", 10, 7);
    DrawRectangle(47, 15, 27, 12, 11);
    PrintText("YOUR PASSWORD :", 48, 16);
    PrintText("ENTER NEW PASSWORD :", 48, 19);
    PrintText("ENTER NEW PASSWORD AGAIN :", 48, 22);

    DrawRectangle(48, 17, 25, 1, 15);
    DrawRectangle(48, 20, 25, 1, 15);
    DrawRectangle(48, 23, 25, 1, 15);
    GotoXY(48, 17);
    string temp;
    InsertPassword(temp);
    if (temp.compare(Usertmp.Password) == 0) {
        GotoXY(48, 20);
        string temp1;
        InsertPassword(temp);
        GotoXY(48, 23);
        InsertPassword(temp1);
        if (temp.compare(temp1) == 0) {
            Usertmp.Password = temp;
            GotoXY(46, 25);
            cout << "Change password successfully \n";
            RewriteInfoFile(Usertmp);
        }
        else {
            GotoXY(48, 25);
            cout << "Password does not match.\n";
        }
    }
    else {
        GotoXY(48, 18);
        cout << "Incorrect password. \n";
    }
    system("pause");
}
