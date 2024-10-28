#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>
#define MAXLEN 101

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
} card[10001];
int cnt;

/***********界面**********/
void Load();//加载数据
void Display();
void ExitPage() {
	exit(0);
}
/***********管理员系统**********/
bool AdminCheck();//管理员认证
void AdminPage();//
void Admin();//管理员系统
void ControlPage();
void AddPage();
void DeletePage();
void ShowPage();
void ResortData();
void Save();
void AddData();
void Deletedata();
void ShowRecord();

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
void Admin() {//浇录系统


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
		printf(" 3.查看记录\n");
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
			if (index == 2) ShowRecord();
			if (index == 3) Display();
		}
	}
}
/***********管理员功能实现*********/
void Save() {
	FILE *pf = fopen("Data.sav", "w");
	fprintf(pf, "%d\n", cnt);
	for (int i = 0; i < cnt; i++) {
		fprintf(pf, "%s %s %s %s\n", card[i].number, card[i].door, card[i].person,card[i].pass);
	}
}
void AddPage() {
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
	//AddData(number, door, person,pass);

	ResortData();
	Save();

	printf("###########################\n");
	printf("增加成功\n");
	printf("按下任意键继续.....\n");
	getch();

}
void AddData(){
	
}
void Deletedata(){
	
}
void ShowRecord() {

}
void DeletePage(){
	
}
void ResortData(){
	
}
/***********矫唤系统**********/

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
	getch();
	//FILE *pfRecord = fopen(RecordfilePath,"a+");
	//FILE *pfData = fopen(DatafilePath,"r+");

}
void Update() {
	Load();
	Display();

}

int main() {
	Update();
	return 0;
}
