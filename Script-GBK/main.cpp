#include<stdio.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
#include<stdbool.h>
#include <time.h>
#define MAXLEN 101
/***********���洢�ṹ**********/
struct Data { //
	char id[MAXLEN];//����
	char door[MAXLEN];//��
	char person[MAXLEN];//����
	char pass[MAXLEN];//����
} cardLst[10001];
Data nullData = {"null", "null", "null","null"};//�� Data����ѯ����ʱ�᷵�����
int cnt,cnt2,cnt3;//cnt��¼�Ѿ������˼���Data��ÿ����һ���Ͱ�lst[cnt]λ�õ� Data��ֵ��Ȼ��cnt++

struct Record {
	char ontime[MAXLEN];
	Data data;
} recordLst[10001];
struct Message {
	char mes[MAXLEN];
} mesLst[1001];

// ���ڴ洢��ʽ�����ʱ���ַ���
const char *DatafilePath = "../Sav/Data.sav";
const char *AdminfilePath = "../Sav/Admin.sav";
const char *RecordfilePath = "../Sav/Record.sav";
const char *MessagefilePath = "../Sav/Message.sav";
char timeStr[15]; // ���ڴ洢��ʽ�����ʱ���ַ���

char admin[MAXLEN],password[MAXLEN];
char inputAdmin[MAXLEN],inputPassword[MAXLEN];

//����������ж���ͬ����Data�Ƿ���ͬ��ֻҪ���֣��绰�ţ�������һ������ͬ���ǲ�ͬ

int DataCmp(Data a, Data b) {
	if (strcmp(a.id, b.id) != 0) return 0;
	if (strcmp(a.door, b.door) != 0) return 0;
	if (strcmp(a.pass, b.pass) != 0) return 0;
	if (strcmp(a.person, b.person) != 0) return 0;
	return 1;
}
/***********����**********/
void Load();//��������
void Display();
void ExitPage() {
	exit(0);
}
/***********����Աϵͳ**********/
char* GetTime();
bool AdminCheck();//����Ա��֤
void AdminPage();//
void Admin();//����Աϵͳ
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
/***********����Ա����ʵ��*********/

char* GetTime() {
	time_t rawtime;
	struct tm * timeinfo;

	// ��ȡ��ǰʱ��
	time(&rawtime);
	// ת��Ϊ����ʱ��
	timeinfo = localtime(&rawtime);

	// ��ʽ�����Ϊ������ʽ��YYYYMMDDHHMMSS
	snprintf(timeStr, sizeof(timeStr), "%04d%02d%02d%02d%02d%02d",
	         timeinfo->tm_year + 1900, // ���
	         timeinfo->tm_mon + 1,     // �·ݣ���0��ʼ��������Ҫ��1��
	         timeinfo->tm_mday,        // ����
	         timeinfo->tm_hour,        // Сʱ
	         timeinfo->tm_min,         // ����
	         timeinfo->tm_sec);        // ��

	// ����ַ������е�����

	return timeStr;
}
bool AdminCheck() {//����Ա��֤
	bool ch1=strcmp(admin,inputAdmin);
	bool ch2=strcmp(password,inputPassword);
	if (strcmp(inputAdmin,"cheat")||strcmp(inputPassword,"cheat")) {
		if (ch1) {
			printf("����Ա�˺Ŵ���");
			getch();
			return false;
		}
		if (ch2) {
			printf("����Ա�������");
			getch();
			return false;
		}
	}
	printf("��¼�ɹ���");
	printf("��ӭ����������Ա(�ϡ���< )�С�\n");
	printf("�����������.....\n");
	getch();
	return true;
}
void AdminPage() {//����Ա��¼����
	system("cls");
	printf("##########��¼����###########\n");
	printf("###                       ###\n");
	printf("#############################\n");
	printf("###      �������˺�       ###\n");

	scanf("%s",inputAdmin);
	printf("###      ����������        ###\n");

	scanf("%s",inputPassword);

}
void Admin() {//�������Աϵͳ


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
		printf("###      ����Աϵͳ     ###\n");
		printf("###########################\n");
		printf("�������ѡ��˵�\n�س���ո񣺽����Ӳ˵�\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.�����ſ�\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.ע���ſ�\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.�鿴�����ſ���Ϣ\n");
		if (index == 3) printf("> ");
		else printf("  ");
		printf(" 4.��ѯһ���ſ���Ϣ\n");
		if (index == 4) printf("> ");
		else printf("  ");
		printf(" 5.�鿴���ż�¼\n");
		if (index == 5) printf("> ");
		else printf("  ");
		printf(" 6.�鿴�û�����\n");
		if (index == 6) printf("> ");
		else printf("  ");
		printf(" 7.�����Ž�ϵͳ\n");
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
	printf("����ɹ�,��ǰ������Ϊ%d\n",cnt);
}
void RecordSave() {
	FILE *pf = fopen(RecordfilePath, "w");
	fprintf(pf, "%d\n", cnt2);
	for (int i = 0; i < cnt2; i++) {
		fprintf(pf, "%s %s %s %s %s\n", recordLst[i].ontime, recordLst[i].data.id, recordLst[i].data.door, recordLst[i].data.person,recordLst[i].data.pass);
	}
	printf("����ɹ�,���ο����Ѽ�¼Ϊ%d\n",cnt);
}
void MesSave() {
	FILE *pf = fopen(MessagefilePath, "w");
	fprintf(pf, "%d\n", cnt3);
	for (int i = 0; i < cnt3; i++) {
		fprintf(pf, "%s\n", mesLst[i].mes);
	}
	printf("����ɹ�,��ǰ��������Ϊ%d\n",cnt3);
}
void ListPage() {
	system("cls");
	printf("###########################\n");
	printf("###      �ſ�����     ###\n");
	printf("###########################\n");

	for (int i = 0; i < cnt; i++) {
		printf("��Ŀ��%d\n���ţ�%s\n���ƣ�%s\n�쿨�ˣ�%s\n���룺%s\n", i + 1, cardLst[i].id, cardLst[i].door, cardLst[i].person,cardLst[i].pass);
		printf("###########################\n");
	}
	if (cnt == 0) {
		printf("ͨѶ¼Ϊ��\n");
	}

	printf("�������������......\n");
	getch();
}
void RecordListPage() {
	system("cls");
	printf("###########################\n");
	printf("###      ���ż�¼����     ###\n");
	printf("###########################\n");

	for (int i = 0; i < cnt2; i++) {
		printf("��Ŀ��%d\n����ʱ�䣺%s\n���ţ�%s\n���ƣ�%s\n�쿨�ˣ�%s\n���룺%s\n", i + 1,recordLst[i].ontime, recordLst[i].data.id, recordLst[i].data.door, recordLst[i].data.person,recordLst[i].data.pass);
		printf("###########################\n");
	}
	if (cnt2 == 0) {
		printf("ͨѶ¼Ϊ��\n");
	}

	printf("�������������......\n");
	getch();
}
void MesListPage() {
	system("cls");
	printf("###########################\n");
	printf("###    �û����԰�鿴   ###\n");
	printf("###########################\n");

	for (int i = 0; i < cnt2; i++) {
		printf("��Ŀ��%d\n���ԣ�%s\n", i + 1,mesLst[i].mes);
		printf("###########################\n");
	}
	if (cnt2 == 0) {
		printf("ͨѶ¼Ϊ��\n");
	}

	printf("�������������......\n");
	getch();
}
void AddPage() {
	system("cls");
	printf("###########################\n");
	printf("###       �����ſ�      ###\n");
	printf("###########################\n");
	//char number[MAXLEN];
	/*printf("�����뿨��");
	scanf("%s", number);*/
	GetTime();
	char door[MAXLEN];
	printf("����������");
	scanf("%s", door);
	char person[MAXLEN];
	printf("������쿨��");
	scanf("%s", person);
	char pass[MAXLEN];
	printf("����������");
	scanf("%s", pass);
	AddData(timeStr,door,person,pass);

	ResortData();
	Save();

	printf("###########################\n");
	printf("���ӳɹ�\n");
	printf("�������������.....\n");
	getch();

}
void AddData(char *numbe, char *doo, char *perso,char *pas) { //���ӣ�������Data�ĸ�����Ϣ��������ӵ�lst������
	Data newData;
	strcpy(newData.id, numbe);
	strcpy(newData.door, doo);
	strcpy(newData.person, perso);
	strcpy(newData.pass, pas);
	cardLst[cnt++] = newData;
}
void AddRecord(char *tim,char *numbe, char *doo, char *perso,char *pas) { //���ӣ�������Data�ĸ�����Ϣ��������ӵ�lst������
	Record newRecord;
	strcpy(newRecord.ontime,tim);
	strcpy(newRecord.data.id, numbe);
	strcpy(newRecord.data.door, doo);
	strcpy(newRecord.data.person, perso);
	strcpy(newRecord.data.pass, pas);
	recordLst[cnt2++] = newRecord;
}
void AddMes(char *mes) { //���ӣ�������Data�ĸ�����Ϣ��������ӵ�lst������
	Message newMes;
	strcpy(newMes.mes,mes);

	mesLst[cnt3++] = newMes;
}
void RemoveData(char *dat,int t) {
	int flag = 0;
	for (int i = 0; i < cnt; i++) {
		if (t==0) {
			if (strcmp(dat, cardLst[i].id) == 0) { //���id��ͬ
				flag = 1;
				cnt--;
			}
		}
		if (t==1) {
			if (strcmp(dat, cardLst[i].door) == 0) { //���������ͬ
				flag = 1;
				cnt--;
			}
		}
		if (t==2) {
			if (strcmp(dat, cardLst[i].person) == 0) { //����쿨����ͬ
				flag = 1;
				cnt--;
			}
		}
		if (t==3) {
			if (strcmp(dat, cardLst[i].pass) == 0) { //���������ͬ
				flag = 1;
				cnt--;
			}
		}
		if (flag == 1) {
			cardLst[i] = cardLst[i + 1];
		}
	}
}
//��ѯҳ�� �������˵�ѡ�񡾲�ѯ��ʱִ�У�������������������
void RemovePage() {

	int index = 0;
	char nam[MAXLEN];

	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###        ɾ���ſ�     ###\n");
		printf("###########################\n");
		printf("�������ѡ��˵�\n�س���ո񣺽����Ӳ˵�\n");
		printf("###########################\n");
		printf("ѡ��ɾ����ʽ\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.����\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.����\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.�쿨��\n");
		if (index == 3) printf("> ");
		else printf("  ");
		printf(" 4.����\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 3;
			else index--;
		}
		if (c == 80) { //down
			if (index == 3) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') { //�س����߿ո�
			break;
		}
	}
	printf("###########################\n");
	printf("�����룺");
	scanf("%s", nam);

	Data data = GetData(nam,index);
	if (DataCmp(data, nullData)) {
		printf("��ѯʧ��\n");
	} else {
		RemoveData(nam,index);
		Save();
		printf("���Ƴ���Ϣ");
	}

	printf("�������������......\n");
	getch();
}
//��ѯ������һ���ַ�����ָ��ָ�����Ŀ�ͷ������lst�����г��Ի�ȡ������ͬ��Data
Data GetData(char *dat,int t) {
	for (int i = 0; i < cnt; i++) {
		if (t==0) {
			if (strcmp(dat, cardLst[i].id) == 0) { //���id��ͬ
				return cardLst[i];
			}
		}
		if (t==1) {
			if (strcmp(dat, cardLst[i].door) == 0) { //���������ͬ
				return cardLst[i];
			}
		}
		if (t==2) {
			if (strcmp(dat, cardLst[i].person) == 0) { //����쿨����ͬ
				return cardLst[i];
			}
		}
		if (t==3) {
			if (strcmp(dat, cardLst[i].pass) == 0) { //���������ͬ
				return cardLst[i];
			}
		}

	}
	return nullData;//�Ҳ��������ؿ�Data
}

//��ѯҳ�� �������˵�ѡ�񡾲�ѯ��ʱִ�У�������������������
void GetInfoPage() {

	int index = 0;
	char nam[MAXLEN];

	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###        ��ѯ         ###\n");
		printf("###########################\n");
		printf("�������ѡ��˵�\n�س���ո񣺽����Ӳ˵�\n");
		printf("###########################\n");
		printf("ѡ���ѯ��ʽ\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.����\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.����\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.�쿨��\n");
		if (index == 3) printf("> ");
		else printf("  ");
		printf(" 4.����\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 3;
			else index--;
		}
		if (c == 80) { //down
			if (index == 3) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') { //�س����߿ո�
			break;
		}
	}
	printf("###########################\n");
	printf("�����룺");
	scanf("%s", nam);

	Data data = GetData(nam,index);
	if (DataCmp(data, nullData)) {
		printf("��ѯʧ��\n");
	} else {
		printf("��ѯ��������ţ�%s ���ƣ�%s �쿨�ˣ�%s ���룺%s\n", data.id, data.door, data.person,data.pass);
	}

	printf("�������������......\n");
	getch();
}

//�������������б�
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
/***********�û�ϵͳ**********/

void UsersPage();
void OpenDoor();
void Submit();
void GetInfoPage();

void UsersPage() {
	int index = 0;
	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###      �û�ϵͳ     ###\n");
		printf("###########################\n");
		printf("�������ѡ��˵�\n�س���ո񣺽����Ӳ˵�\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.�ύ����\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.����\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.�ص��Ž�ϵͳ\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 2;
			else index--;
		}
		if (c == 80) { //down
			if (index == 2) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') { //�س����߿ո�
			if (index == 0) Submit();
			if (index == 1) OpenDoor();
			if (index == 2) Display();
		}
	}
}
/***********�û�ϵͳ����ʵ��*********/
void OpenDoor() {
	char tempId[MAXLEN],tempPass[MAXLEN];
	int index = 0;

	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###        ����         ###\n");
		printf("###########################\n");
		printf("�������ѡ��˵�\n�س���ո񣺽����Ӳ˵�\n");
		printf("###########################\n");
		printf("ѡ���ŷ�ʽ\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.����\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.����\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.�쿨��\n");
		if (index == 3) printf("> ");
		else printf("  ");
		printf(" 4.����\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 3;
			else index--;
		}
		if (c == 80) { //down
			if (index == 3) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') { //�س����߿ո�
			break;
		}
	}
	printf("###########################\n");
	printf("�����룺");
	scanf("%s", tempId);

	Data data = GetData(tempId,index);
	if (DataCmp(data, nullData)) {
		printf("δ�ҵ���Ӧ��Ϣ��\n");
	} else {
		printf("###########################\n");
		printf("���������룺");
		scanf("%s", tempPass);
		//printf("%s %s",data.pass,tempPass);//�������
		if (!strcmp(data.pass, tempPass)) {
			printf("���ųɹ���\n");
			GetTime();
			AddRecord(timeStr,data.id,data.door,data.person,data.pass);
			RecordSave();
		} else {
			printf("�������\n");
		}
	}

	printf("�������������......\n");
	getch();

}
void Submit() {
	system("cls");
	printf("###########################\n");
	printf("###       ���԰壡      ###\n");
	printf("###########################\n");
	printf("###########################\n");
	printf("����Ա�ῴ�������Ϣ��������������������\n");
	printf("###########################\n");
	printf("������Ϣ��\n");
	char mes[MAXLEN];
	scanf("%s",mes);
	AddMes(mes);
	MesSave();
	printf("���ύ\n");
	printf("�������������......\n");
	getch();

}



/*********************************/
void Display() { //���˵�
	int index = 0;
	while (1) {
		system("cls");
		printf("###########################\n");
		printf("###      �Ž�ϵͳ     ###\n");
		printf("###########################\n");
		printf("�������ѡ��˵�\n�س���ո񣺽����Ӳ˵�\n");
		printf("###########################\n");
		if (index == 0) printf("> ");
		else printf("  ");
		printf(" 1.����Աϵͳ\n");
		if (index == 1) printf("> ");
		else printf("  ");
		printf(" 2.�û�ϵͳ\n");
		if (index == 2) printf("> ");
		else printf("  ");
		printf(" 3.�˳�ϵͳ\n");
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






void Load() { //����
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
	} else printf("�Ҳ���data\n");
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
	} else printf("�Ҳ���data\n");
	if (pfMessage != NULL) {
		int n;
		fscanf(pfMessage, "%d", &n);
		for (int i = 0; i < n; i++) {
			char mes[MAXLEN];

			fscanf(pfMessage, "%s",mes);
			//printf("%s %s %s %s %s", tim,number, door, person,pass);
			AddMes(mes);
		}
	} else printf("�Ҳ���data\n");
	//printf("������������Ž�ϵͳ");
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
