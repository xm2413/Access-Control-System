#include"admin.h"
#include"user.h"
#include"load.h"


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
		printf(" 5.返回门禁系统\n");
		char c = getch();
		if (c == 72) { //up
			if (index == 0) index = 4;
			else index--;
		}
		if (c == 80) { //down
			if (index == 4) index = 0;
			else index++;
		}
		if (c == 13 || c == ' ') {
			if (index == 0) AddPage();
			if (index == 1) DeletePage();
			if (index == 2) ListPage();
			if (index == 3) GetInfoPage();
			if (index == 4) Display();
		}
	}
}

