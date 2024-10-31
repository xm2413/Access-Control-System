#ifndef ADMIN_H
#define ADMIN_H

#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>
#define MAXLEN 101

// 用于存储格式化后的时间字符串
const char *DatafilePath = "../Sav/Data.sav";
const char *AdminfilePath = "../Sav/Admin.sav";
const char *RecordfilePath = "../Sav/Record.sav";
char timeStr[15]; // 用于存储格式化后的时间字符串

char admin[MAXLEN],password[MAXLEN];
char inputAdmin[MAXLEN],inputPassword[MAXLEN];


char* GetTime();
bool AdminCheck();//管理员认证
void AdminPage();//
void Admin();//管理员系统
void ControlPage();
void AddPage();
void DeletePage();
void ShowPage();
void ResortData();
void Save();
void AddData(char *numbe, char *doo, char *perso,char *pas);
void Deletedata();
void GetInfoPage();
void ShowRecord();
void ListPage();



#endif
