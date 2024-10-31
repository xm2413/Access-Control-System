#include"admin.h"
#include"user.h"
#include"load.h"
//定义了如何判断相同两个Data是否相同，只要名字，电话号，邮箱有一个不相同就是不同

int DataCmp(Data a, Data b) {
	if (strcmp(a.id, b.id) != 0) return 0;
	if (strcmp(a.door, b.door) != 0) return 0;
	if (strcmp(a.pass, b.pass) != 0) return 0;
	if (strcmp(a.person, b.person) != 0) return 0;
	return 1;
}
/***********界面**********/

void Display();
void ExitPage() {
	exit(0);
}
/***********管理员系统**********/


/***********管理员功能实现*********/

void Save() {
	FILE *pf = fopen(DatafilePath, "w");
	fprintf(pf, "%d\n", cnt);
	for (int i = 0; i < cnt; i++) {
		fprintf(pf, "%s %s %s %s\n", cardLst[i].id, cardLst[i].door, cardLst[i].person,cardLst[i].pass);
	}
	printf("保存成功,当前卡数量为%d\n",cnt);
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
void Deletedata() {

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
void ShowRecord() {

}
void DeletePage() {

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
		if (c == 13 || c == ' ') { //回车或者空格
			if (index == 0) Submit();
			if (index == 1) GetInfoPage();
			if (index == 2) OpenDoor();
			if (index == 3) Display();
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
		} else {
			printf("密码错误！\n");
		}
	}

	printf("按下任意键继续......\n");
	getch();

}
void Submit() {}



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
	FILE *pfData = fopen(DatafilePath, "a+");
	FILE *pfRecord = fopen(RecordfilePath,"a+");
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
			//printf("%s %s %s %s", number, door, person,pass);
			AddData(number,door,person,pass);
		}
	} else printf("找不到data\n");
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
