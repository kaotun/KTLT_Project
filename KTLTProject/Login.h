#ifndef _LOGIN_H_
#define _LOGIN_H_
#include "Struct.h"

#pragma warning(disable: 4996)

void LoginInterFace(User& Usertmp);

void RepeatLogin(User& Usertmp);

int CheckLogin(User& Usertmp);

void InsertUserName(string& UserName);

void InsertPassword(string& Password);

#endif
