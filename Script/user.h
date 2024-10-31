#ifndef USER_H
#define USER_H
#include"admin.h"

/***********卡存储结构**********/
struct Data { //
	char id[MAXLEN];//卡号
	char door[MAXLEN];//门
	char person[MAXLEN];//人名
	char pass[MAXLEN];//密码
} cardLst[10001];
Data nullData = {"null", "null", "null","null"};//空 Data，查询不到时会返回这个
int cnt,cnt2;//cnt记录已经存入了几个Data，每存入一个就把lst[cnt]位置的 Data赋值，然后cnt++

struct Record {
	char ontime[MAXLEN];
	Data data;
} recordLst[10001];
#endif
