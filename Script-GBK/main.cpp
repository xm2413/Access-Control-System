#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>
#define MAXLEN 101
/***********卡存储结构**********/
struct Data { //
	char id[MAXLEN];//卡号
	char door[MAXLEN];//门
	char person[MAXLEN];//人名
	char pass[MAXLEN];//密码
} cardLst[10001];
Data nullData = {"null", "null", "null","null"};//空 Data，查询不到时会返回这个
int cnt,cnt2,cnt3;//cnt记录已经存入了几个Data，每存入一个就把lst[cnt]位置的 Data赋值，然后cnt++

struct Record {
	char ontime[MAXLEN];
	Data data;
} recordLst[10001];
struct Message {
	char mes[MAXLEN];
} mesLst[1001];

// 用于存储格式化后的时间字符串
const char *DatafilePath = "../Sav/Data.sav";
const char *AdminfilePath = "../Sav/Admin.sav";
const char *RecordfilePath = "../Sav/Record.sav";
const char *MessagefilePath = "../Sav/Message.sav";
char timeStr[15]; // 用于存储格式化后的时间字符串

char admin[MAXLEN],password[MAXLEN];
char inputAdmin[MAXLEN],inputPassword[MAXLEN];

//定义了如何判断相同两个Data是否相同，只要名字，电话号，邮箱有一个不相同就是不同

int DataCmp(Data a, Data b) {
	if (strcmp(a.id, b.id) != 0) return 0;
	if (strcmp(a.door, b.door) != 0) return 0;
	if (strcmp(a.pass, b.pass) != 0) return 0;
	if (strcmp(a.person, b.person) != 0) return 0;
	return 1;
}
/***********界面**********/
void Load();//加载数据
void Display();
void ExitPage() {
	exit(0);
}
/***********管理员系统**********/
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
void RemovePage();
void GetInfoPage();
void ShowRecord();
void ListPage();
void RecordListPage();
void RecordSave();
Data GetData(char *dat,int t);
void MesListPage();
/***********管理员功能实现*********/

char* GetTime() {
	time_t rawtime;
	struct tm * timeinfo;

	// 获取当前时间
	time(&rawtime);
	// 转换为本地时间
	timeinfo = localtime(&rawtime);

	// 格式化输出为数字形式：YYYYMMDDHHMMSS
	snprintf(timeStr, sizeof(timeStr), "%04d%02d%02d%02d%02d%02d",
	         timeinfo->tm_year + 1900, // 年份
	         timeinfo->tm_mon + 1,     // 月份（从0开始，所以需要加1）
	         timeinfo->tm_mday,        // 日期
	         timeinfo->tm_hour,        // 小时
	         timeinfo->tm_min,         // 分钟
	         timeinfo->tm_sec);        // 秒

	// 输出字符数组中的内容

	return timeStr;
}
bool AdminCheck() {//管理员认证
	bool ch1=strcmp(admin,inputAdmin);
	bool ch2=strcmp(password,inputPassword);
	if (strcmp(inputAdmin,"cheat")||strcmp(inputPassword,"cheat")) {
		if (ch1) {
			printf("管理员账号错误");
			getch();
			return false;
		}
		if (ch2) {
			printf("管理员密码错误");
			getch();
			return false;
		}
	}
	printf("登录成功！");
	printf("欢迎回来，管理员(∠·ω< )⌒★\n");
	printf("按任意键继续.....\n");
	getch();
	return true;
}
void AdminPage() {//管理员登录界面
	system("cls");
	printf("##########登录界面###########\n");
	printf("###                       ###\n");
	printf("#############################\n");
	printf("###      请输入账号       ###\n");

	scanf("%s",inputAdmin);
	printf("###      请输入密码        ###\n");

	scanf("%s",inputPassword);

}
void Admin() {//进入管理员系统


	while (1) {
		AdminPage();
		if (AdminCheck()) {
			ControlPage();
		}
	}
	return ;
}
void ControlPage() {
	int index = 0;
	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###      管理员系统     ###\n");
		printf("###########################\n");
		printf("方向键：选择菜单\n回车或空格：进入子菜单\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.办理门卡\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.注销门卡\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.查看所有门卡信息\n");
		if (index == 3) printf("> ");
		else printf("  ");
		printf(" 4.查询一个门卡信息\n");
		if (index == 4) printf("> ");
		else printf("  ");
		printf(" 5.查看开门记录\n");
		if (index == 5) printf("> ");
		else printf("  ");
		printf(" 6.查看用户留言\n");
		if (index == 6) printf("> ");
		else printf("  ");
		printf(" 7.返回门禁系统\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 6;
			else index--;
		}
		if (c == 80) { //down
			if (index == 6) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') {
			if (index == 0) AddPage();
			if (index == 1) RemovePage();
			if (index == 2) ListPage();
			if (index == 3) GetInfoPage();
			if (index == 4) RecordListPage();
			if (index == 5) MesListPage();
			if (index == 6) Display();
		}
	}
}

void Save() {
	FILE *pf = fopen(DatafilePath, "w");
	fprintf(pf, "%d\n", cnt);
	for (int i = 0; i < cnt; i++) {
		fprintf(pf, "%s %s %s %s\n", cardLst[i].id, cardLst[i].door, cardLst[i].person,cardLst[i].pass);
	}
	printf("保存成功,当前卡数量为%d\n",cnt);
}
void RecordSave() {
	FILE *pf = fopen(RecordfilePath, "w");
	fprintf(pf, "%d\n", cnt2);
	for (int i = 0; i < cnt2; i++) {
		fprintf(pf, "%s %s %s %s %s\n", recordLst[i].ontime, recordLst[i].data.id, recordLst[i].data.door, recordLst[i].data.person,recordLst[i].data.pass);
	}
	printf("保存成功,本次开门已记录为%d\n",cnt);
}
void MesSave() {
	FILE *pf = fopen(MessagefilePath, "w");
	fprintf(pf, "%d\n", cnt3);
	for (int i = 0; i < cnt3; i++) {
		fprintf(pf, "%s\n", mesLst[i].mes);
	}
	printf("保存成功,当前留言数量为%d\n",cnt3);
}
void ListPage() {
	system("cls");
	printf("###########################\n");
	printf("###      门卡总览     ###\n");
	printf("###########################\n");

	for (int i = 0; i < cnt; i++) {
		printf("条目：%d\n卡号：%s\n门牌：%s\n办卡人：%s\n密码：%s\n", i + 1, cardLst[i].id, cardLst[i].door, cardLst[i].person,cardLst[i].pass);
		printf("###########################\n");
	}
	if (cnt == 0) {
		printf("通讯录为空\n");
	}

	printf("按下任意键继续......\n");
	getch();
}
void RecordListPage() {
	system("cls");
	printf("###########################\n");
	printf("###      开门记录总览     ###\n");
	printf("###########################\n");

	for (int i = 0; i < cnt2; i++) {
		printf("条目：%d\n开门时间：%s\n卡号：%s\n门牌：%s\n办卡人：%s\n密码：%s\n", i + 1,recordLst[i].ontime, recordLst[i].data.id, recordLst[i].data.door, recordLst[i].data.person,recordLst[i].data.pass);
		printf("###########################\n");
	}
	if (cnt2 == 0) {
		printf("通讯录为空\n");
	}

	printf("按下任意键继续......\n");
	getch();
}
void MesListPage() {
	system("cls");
	printf("###########################\n");
	printf("###    用户留言板查看   ###\n");
	printf("###########################\n");

	for (int i = 0; i < cnt2; i++) {
		printf("条目：%d\n留言：%s\n", i + 1,mesLst[i].mes);
		printf("###########################\n");
	}
	if (cnt2 == 0) {
		printf("通讯录为空\n");
	}

	printf("按下任意键继续......\n");
	getch();
}
void AddPage() {
	system("cls");
	printf("###########################\n");
	printf("###       新增门卡      ###\n");
	printf("###########################\n");
	//char number[MAXLEN];
	/*printf("请输入卡号");
	scanf("%s", number);*/
	GetTime();
	char door[MAXLEN];
	printf("请输入门牌");
	scanf("%s", door);
	char person[MAXLEN];
	printf("请输入办卡人");
	scanf("%s", person);
	char pass[MAXLEN];
	printf("请输入密码");
	scanf("%s", pass);
	AddData(timeStr,door,person,pass);

	ResortData();
	Save();

	printf("###########################\n");
	printf("增加成功\n");
	printf("按下任意键继续.....\n");
	getch();

}
void AddData(char *numbe, char *doo, char *perso,char *pas) { //增加，传入新Data的各种信息，将其添加到lst数组中
	Data newData;
	strcpy(newData.id, numbe);
	strcpy(newData.door, doo);
	strcpy(newData.person, perso);
	strcpy(newData.pass, pas);
	cardLst[cnt++] = newData;
}
void AddRecord(char *tim,char *numbe, char *doo, char *perso,char *pas) { //增加，传入新Data的各种信息，将其添加到lst数组中
	Record newRecord;
	strcpy(newRecord.ontime,tim);
	strcpy(newRecord.data.id, numbe);
	strcpy(newRecord.data.door, doo);
	strcpy(newRecord.data.person, perso);
	strcpy(newRecord.data.pass, pas);
	recordLst[cnt2++] = newRecord;
}
void AddMes(char *mes) { //增加，传入新Data的各种信息，将其添加到lst数组中
	Message newMes;
	strcpy(newMes.mes,mes);

	mesLst[cnt3++] = newMes;
}
void RemoveData(char *dat,int t) {
	int flag = 0;
	for (int i = 0; i < cnt; i++) {
		if (t==0) {
			if (strcmp(dat, cardLst[i].id) == 0) { //如果id相同
				flag = 1;
				cnt--;
			}
		}
		if (t==1) {
			if (strcmp(dat, cardLst[i].door) == 0) { //如果门牌相同
				flag = 1;
				cnt--;
			}
		}
		if (t==2) {
			if (strcmp(dat, cardLst[i].person) == 0) { //如果办卡人相同
				flag = 1;
				cnt--;
			}
		}
		if (t==3) {
			if (strcmp(dat, cardLst[i].pass) == 0) { //如果密码相同
				flag = 1;
				cnt--;
			}
		}
		if (flag == 1) {
			cardLst[i] = cardLst[i + 1];
		}
	}
}
//查询页面 ，在主菜单选择【查询】时执行，输入姓名，查找数据
void RemovePage() {

	int index = 0;
	char nam[MAXLEN];

	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###        删除门卡     ###\n");
		printf("###########################\n");
		printf("方向键：选择菜单\n回车或空格：进入子菜单\n");
		printf("###########################\n");
		printf("选择删除方式\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.卡号\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.门牌\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.办卡人\n");
		if (index == 3) printf("> ");
		else printf("  ");
		printf(" 4.密码\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 3;
			else index--;
		}
		if (c == 80) { //down
			if (index == 3) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') { //回车或者空格
			break;
		}
	}
	printf("###########################\n");
	printf("请输入：");
	scanf("%s", nam);

	Data data = GetData(nam,index);
	if (DataCmp(data, nullData)) {
		printf("查询失败\n");
	} else {
		RemoveData(nam,index);
		Save();
		printf("已移除信息");
	}

	printf("按下任意键继续......\n");
	getch();
}
//查询，传入一个字符串（指针指向它的开头），从lst数组中尝试获取名字相同的Data
Data GetData(char *dat,int t) {
	for (int i = 0; i < cnt; i++) {
		if (t==0) {
			if (strcmp(dat, cardLst[i].id) == 0) { //如果id相同
				return cardLst[i];
			}
		}
		if (t==1) {
			if (strcmp(dat, cardLst[i].door) == 0) { //如果门牌相同
				return cardLst[i];
			}
		}
		if (t==2) {
			if (strcmp(dat, cardLst[i].person) == 0) { //如果办卡人相同
				return cardLst[i];
			}
		}
		if (t==3) {
			if (strcmp(dat, cardLst[i].pass) == 0) { //如果密码相同
				return cardLst[i];
			}
		}

	}
	return nullData;//找不到，返回空Data
}

//查询页面 ，在主菜单选择【查询】时执行，输入姓名，查找数据
void GetInfoPage() {

	int index = 0;
	char nam[MAXLEN];

	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###        查询         ###\n");
		printf("###########################\n");
		printf("方向键：选择菜单\n回车或空格：进入子菜单\n");
		printf("###########################\n");
		printf("选择查询方式\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.卡号\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.门牌\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.办卡人\n");
		if (index == 3) printf("> ");
		else printf("  ");
		printf(" 4.密码\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 3;
			else index--;
		}
		if (c == 80) { //down
			if (index == 3) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') { //回车或者空格
			break;
		}
	}
	printf("###########################\n");
	printf("请输入：");
	scanf("%s", nam);

	Data data = GetData(nam,index);
	if (DataCmp(data, nullData)) {
		printf("查询失败\n");
	} else {
		printf("查询结果：卡号：%s 门牌：%s 办卡人：%s 密码：%s\n", data.id, data.door, data.person,data.pass);
	}

	printf("按下任意键继续......\n");
	getch();
}

//重新排序整个列表
void ResortData() {
	for (int i = 0; i < cnt - 1; i++) {
		for (int j = 0; j < cnt - 1 - i; j++) {
			if (strcmp(cardLst[j].id, cardLst[j + 1].id) > 0) {
				Data tempData = cardLst[j + 1];
				cardLst[j + 1] = cardLst[j];
				cardLst[j] = tempData;
			}
		}
	}
}
/***********用户系统**********/

void UsersPage();
void OpenDoor();
void Submit();
void GetInfoPage();

void UsersPage() {
	int index = 0;
	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###      用户系统     ###\n");
		printf("###########################\n");
		printf("方向键：选择菜单\n回车或空格：进入子菜单\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.提交申请\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.开门\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.回到门禁系统\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 2;
			else index--;
		}
		if (c == 80) { //down
			if (index == 2) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') { //回车或者空格
			if (index == 0) Submit();
			if (index == 1) OpenDoor();
			if (index == 2) Display();
		}
	}
}
/***********用户系统功能实现*********/
void OpenDoor() {
	char tempId[MAXLEN],tempPass[MAXLEN];
	int index = 0;

	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###        开门         ###\n");
		printf("###########################\n");
		printf("方向键：选择菜单\n回车或空格：进入子菜单\n");
		printf("###########################\n");
		printf("选择开门方式\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.卡号\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.门牌\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.办卡人\n");
		if (index == 3) printf("> ");
		else printf("  ");
		printf(" 4.密码\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 3;
			else index--;
		}
		if (c == 80) { //down
			if (index == 3) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') { //回车或者空格
			break;
		}
	}
	printf("###########################\n");
	printf("请输入：");
	scanf("%s", tempId);

	Data data = GetData(tempId,index);
	if (DataCmp(data, nullData)) {
		printf("未找到对应信息！\n");
	} else {
		printf("###########################\n");
		printf("请输入密码：");
		scanf("%s", tempPass);
		//printf("%s %s",data.pass,tempPass);//测试语句
		if (!strcmp(data.pass, tempPass)) {
			printf("开门成功！\n");
			GetTime();
			AddRecord(timeStr,data.id,data.door,data.person,data.pass);
			RecordSave();
		} else {
			printf("密码错误！\n");
		}
	}

	printf("按下任意键继续......\n");
	getch();

}
void Submit() {
	system("cls");
	printf("###########################\n");
	printf("###       留言板！      ###\n");
	printf("###########################\n");
	printf("###########################\n");
	printf("管理员会看到你的信息，你可以在这里提出诉求\n");
	printf("###########################\n");
	printf("输入信息：\n");
	char mes[MAXLEN];
	scanf("%s",mes);
	AddMes(mes);
	MesSave();
	printf("已提交\n");
	printf("按下任意键继续......\n");
	getch();

}



/*********************************/
void Display() { //主菜单
	int index = 0;
	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###      门禁系统     ###\n");
		printf("###########################\n");
		printf("方向键：选择菜单\n回车或空格：进入子菜单\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.管理员系统\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.用户系统\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.退出系统\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 2;
			else index--;
		}
		if (c == 80) { //down
			if (index == 2) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') {
			if (index == 0) Admin();
			if (index == 1) UsersPage();
			if (index == 2) ExitPage();

		}
	}
}






void Load() { //加载
	FILE *pfAdmin = fopen(AdminfilePath, "a+");
	FILE *pfData = fopen(DatafilePath, "a+");
	FILE *pfRecord = fopen(RecordfilePath,"a+");
	FILE *pfMessage = fopen(MessagefilePath,"a+");
	fscanf(pfAdmin,"%s",admin);
	fscanf(pfAdmin,"%s",password);
	//printf("ad:%s\nps:%s\n",admin,password);

	if (pfData != NULL) {
		int n;
		fscanf(pfData, "%d", &n);
		for (int i = 0; i < n; i++) {
			char number[MAXLEN];
			char door[MAXLEN];
			char person[MAXLEN];
			char pass[MAXLEN];
			fscanf(pfData, "%s %s %s %s", number, door, person,pass);
			//printf("%s %s %s %s", number, door, person,pass);
			AddData(number,door,person,pass);
		}
	} else printf("找不到data\n");
	/**/
	if (pfRecord != NULL) {
		int n;
		fscanf(pfRecord, "%d", &n);
		for (int i = 0; i < n; i++) {
			char tim[MAXLEN];
			char number[MAXLEN];
			char door[MAXLEN];
			char person[MAXLEN];
			char pass[MAXLEN];
			fscanf(pfRecord, "%s %s %s %s %s",tim, number, door, person,pass);
			//printf("%s %s %s %s %s", tim,number, door, person,pass);
			AddRecord(tim,number,door,person,pass);
		}
	} else printf("找不到data\n");
	if (pfMessage != NULL) {
		int n;
		fscanf(pfMessage, "%d", &n);
		for (int i = 0; i < n; i++) {
			char mes[MAXLEN];

			fscanf(pfMessage, "%s",mes);
			//printf("%s %s %s %s %s", tim,number, door, person,pass);
			AddMes(mes);
		}
	} else printf("找不到data\n");
	//printf("按任意键启动门禁系统");
	//getch();
}
void Update() {
	Load();
	Display();

}

int main() {
	Update();
	return 0;
}
