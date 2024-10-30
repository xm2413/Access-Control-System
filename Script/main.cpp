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
char admin[MAXLEN],password[MAXLEN];
char inputAdmin[MAXLEN],inputPassword[MAXLEN];
/***********卡存储结构**********/
struct Data { //
	char number[MAXLEN];//卡号
	char door[MAXLEN];//门
	char person[MAXLEN];//人名
	char pass[MAXLEN];//密码
} cardLst[10001];
Data nullData = {"null", "null", "null","null"};//空 Data，查询不到时会返回这个
int cnt;//cnt记录已经存入了几个Data，每存入一个就把lst[cnt]位置的 Data赋值，然后cnt++

//定义了如何判断相同两个Data是否相同，只要名字，电话号，邮箱有一个不相同就是不同
int DataCmp(Data a, Data b) {
	if (strcmp(a.number, b.number) != 0) return 0;
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
void Deletedata();
void ShowRecord();
void MainPage();

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
		printf(" 4.返回门禁系统\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 3;
			else index--;
		}
		if (c == 80) { //down
			if (index == 3) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') {
			if (index == 0) AddPage();
			if (index == 1) DeletePage();
			if (index == 2) MainPage();
			if (index == 3) Display();
		}
	}
}



/***********管理员功能实现*********/

void Save() {
	FILE *pf = fopen("Data.sav", "w");
	fprintf(pf, "%d\n", cnt);
	for (int i = 0; i < cnt; i++) {
		fprintf(pf, "%s %s %s %s\n", cardLst[i].number, cardLst[i].door, cardLst[i].person,cardLst[i].pass);
	}
}
void MainPage(){
	system("cls"); 
	printf("###########################\n");
	printf("###      门卡总览     ###\n");
	printf("###########################\n");
	
	for(int i = 0; i < cnt; i++){
		printf("条目：%d\n卡号：%s\n门牌：%s\n办卡人：%s\n", i + 1, cardLst[i].number, cardLst[i].door, cardLst[i].person);
		printf("###########################\n");
	}
	if(cnt == 0){
		printf("通讯录为空\n");
	}
	
	printf("按下任意键继续......\n");
	getch();
}
void AddPage() {
	char timeStr[15];

	//获取系统时间

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

	system("cls");
	printf("###########################\n");
	printf("###       新增门卡      ###\n");
	printf("###########################\n");
	char number[MAXLEN];
	printf("请输入卡号");
	scanf("%s", number);
	char door[MAXLEN];
	printf("请输入门牌");
	scanf("%s", door);
	char person[MAXLEN];
	printf("请输入办卡人");
	scanf("%s", person);
	char pass[MAXLEN];
	printf("请输入密码");
	scanf("%s", pass);
	AddData(number,door,person,pass);

	ResortData();
	Save();

	printf("###########################\n");
	printf("增加成功\n");
	printf("按下任意键继续.....\n");
	getch();

}
void AddData(char *numbe, char *doo, char *perso,char *pas) { //增加，传入新Data的各种信息，将其添加到lst数组中
	Data newData;
	strcpy(newData.number, numbe);
	strcpy(newData.door, doo);
	strcpy(newData.person, perso);
	strcpy(newData.pass, pas);
	cardLst[cnt++] = newData;
}
void Deletedata() {

}
void ShowRecord() {

}
void DeletePage() {

}
//重新排序整个列表
void ResortData() {
	for (int i = 0; i < cnt - 1; i++) {
		for (int j = 0; j < cnt - 1 - i; j++) {
			if (strcmp(cardLst[j].number, cardLst[j + 1].number) > 0) {
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
		printf(" 2.获取信息\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.开门\n");
		if (index == 3) printf("> ");
		else printf("  ");
		printf(" 4.回到门禁系统\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 3;
			else index--;
		}
		if (c == 80) { //down
			if (index == 3) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') { //截晨锝呖缚?
			if (index == 0) Submit();
			if (index == 1) GetInfoPage();
			if (index == 2) OpenDoor();
			if (index == 3) Display();
		}
	}
}
/***********用户系统功能实现*********/
void OpenDoor() {}
void Submit() {}
void GetInfoPage() {}




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
		printf(" 2.门禁系统\n");
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
	fscanf(pfAdmin,"%s",admin);
	fscanf(pfAdmin,"%s",password);
	printf("ad:%s\nps:%s\n",admin,password);

	//FILE *pfRecord = fopen(RecordfilePath,"a+");
	//FILE *pfData = fopen(DatafilePath,"r+");
	time_t rawtime;
	struct tm * timeinfo;

	time(&rawtime); // 获取当前时间
	timeinfo = localtime(&rawtime); // 转换为本地时间

	printf("Current local time and date: %s", asctime(timeinfo));
	getch();

}
void Update() {
	Load();
	Display();

}

int main() {
	Update();
	return 0;
}
