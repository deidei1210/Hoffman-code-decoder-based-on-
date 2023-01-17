#include"class.h"
#include"FrontPage.h"
#include<iostream>
using namespace std;

EasyTextBox txtName;
EasyTextBox Choice;
extern int ct;
//不要忘记使用完char*后delete[]释放内存
char* wideCharToMultiByte(wchar_t* pWCStrKey){
	//第一次调用确认转换后单字节字符串的长度，用于开辟空间
	int pSize = WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), NULL, 0, NULL, NULL);
	char* pCStrKey = new char[pSize + 1];
	//第二次调用将双字节字符串转换成单字节字符串
	WideCharToMultiByte(CP_OEMCP, 0, pWCStrKey, wcslen(pWCStrKey), pCStrKey, pSize, NULL, NULL);
	pCStrKey[pSize] = '\0';
	return pCStrKey;

	//如果想要转换成string，直接赋值即可
	//string pKey = pCStrKey;
}

//最开始的界面
void StartPage() {
	initgraph(400, 400);
	//设置背景颜色为白色
	setbkcolor(WHITE);
	cleardevice();

	// 获得窗口句柄
	HWND hWnd = GetHWnd();
	// 使用 Windows API 修改窗口名称
	SetWindowText(hWnd, _T("霍夫曼编码译码器"));

	//将名称打印在中央
	settextcolor(DarkBlue);
	settextstyle(35, 0, _T("黑体"));
	outtextxy(60, 130, _T("霍夫曼编码译码器"));

	//画三个长方形
	setfillcolor(DarkBlue);
	solidrectangle(0, 0, 400, 45);
	setfillcolor(NormalBlue);
	solidrectangle(0, 45, 400, 75);
	setfillcolor(LightBlue);
	solidrectangle(0, 75, 400, 90);

	//开始按钮
	setlinecolor(DarkBlue);
	rectangle(150, 200, 250, 250);
	setlinecolor(DarkBlue);
	rectangle(155, 205, 245, 245);
	settextcolor(DarkBlue);
	settextstyle(20, 0, _T("黑体"));
	outtextxy(176, 215, _T("Start"));

	IMAGE img;
	putimage(255, 255, &img);

	MOUSEMSG mouse;//获得一条关于鼠标的信息

	while (1) {
		mouse = GetMouseMsg();//获得关于鼠标的信息
		if (mouse.x >= 155 && mouse.x <= 245 && mouse.y >= 205 && mouse.y <= 245) {
			setfillcolor(NormalBlue);
			solidrectangle(155, 205, 245, 245);
			settextcolor(LightBlue);
			settextstyle(20, 0, _T("黑体"));
			setbkmode(TRANSPARENT);
			outtextxy(176, 215, _T("Start"));
			//鼠标单击在这片区域
			if (mouse.uMsg == WM_LBUTTONDOWN) {
				break;
			}
		}
		else {
			setfillcolor(WHITE);
			solidrectangle(155, 205, 245, 245);
			setlinecolor(DarkBlue);
			rectangle(155, 205, 245, 245);
			settextcolor(DarkBlue);
			settextstyle(20, 0, _T("黑体"));
			outtextxy(176, 215, _T("Start"));
		}
	}
}
//请选择你要读取的文件
string LoadFilePage() {
	//这是导入文件页
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(40, 7, _T("欢迎来到霍夫曼编码译码器！"));
	settextstyle(19, 0, _T("宋体"));
	outtextxy(50, 150, _T("请输入需要编码的文件的地址："));
	setlinecolor(DarkBlue);

	settextcolor(BLACK);
	outtextxy(10, 190, L"地址：");
	txtName.Create(50, 190, 380, 220, 1000);						// 创建用户名文本框控件
	EasyButton btnOK;
	btnOK.Create(350, 225, 390, 245, L"OK");	// 创建按钮控件

	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN) {
			// 判断控件
			if (txtName.Check(msg.x, msg.y))
				txtName.OnMessage();
			if (btnOK.Check(msg.x, msg.y))
				break;
		}
	}

	outtextxy(300, 155, txtName.Text());
	string filename = wideCharToMultiByte(txtName.Text());
	return filename;
}
//显示菜单
int menu() {
	//显示菜单
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(180, 7, _T("菜单"));

	settextstyle(18, 0, _T("宋体"));
	outtextxy(35, 45, _T("显示每个字符的霍夫曼编码---请按1"));
	outtextxy(35, 70, _T("获得编码文件---请按2"));
	outtextxy(35, 95, _T("显示霍夫曼树---请按3"));
	outtextxy(35, 120, _T("霍夫曼译码---请按4"));
	outtextxy(35, 145, _T("重新读入需要编码的文件---请按5"));
	outtextxy(35, 170, _T("退出---请按0"));
	outtextxy(35, 195, _T("请输入想要进行的操作："));
	//outtextxy(300, 155, txtName.Text());
	Choice.Create(230, 195, 260, 215, 10);
	EasyButton btnOK;
	btnOK.Create(350, 300, 390, 325, L"OK");	// 创建按钮控件

	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN) {
			// 判断控件
			if (Choice.Check(msg.x, msg.y))
				Choice.OnMessage();
			if (btnOK.Check(msg.x, msg.y))
				break;
		}
	}
	string c = wideCharToMultiByte(Choice.Text());
	if (c.length() > 1)
		return 9;
	int num = c[0] - '0';
	return num;
}
//是否继续
int ToContinue() {
	closegraph();
	initgraph(400, 400);
	setbkcolor(WHITE);
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(30, 0, L"黑体");
	outtextxy(50, 100, L"是否继续下一步操作？");
	EasyButton Yes, No;
	Yes.Create(120, 210, 180, 245, L"Yes");
	No.Create(200, 210, 260, 245, L"No");
	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN) {
			// 判断控件
			if (No.Check(msg.x, msg.y)) {
				return -1;
			}
			if (Yes.Check(msg.x, msg.y)) {
				return 1;
			}
		}
	}
	return 0;
}
//霍夫曼编码界面
void EncodePage() {
	closegraph();
	initgraph(800, 800);
	setbkcolor(WHITE);
	cleardevice();
	//标题
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(330, 7, _T("霍夫曼编码表"));
	//分割线
	setlinecolor(DarkBlue);
	line(267, 40, 267, 800);
	line(534, 40, 534, 800);
	//表头
	settextcolor(DarkBlue);
	settextstyle(20, 0, _T("黑体"));
	for (int i = 0; i < 3; i++) {
		outtextxy(5 + i * 267, 40, _T("字符"));
		outtextxy(100 + i * 267, 40, L"编码");
	}

}
//结束界面
void End() {
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(100, 100, _T("感谢您的使用！:)"));
	Sleep(1000);
	outtextxy(160, 130, _T("再见！"));
	Sleep(3000);
}
//返回
void ReturnButtum(int x1,int y1,int x2,int y2) {
	EasyButton Ret;
	Ret.Create(x1,y1,x2,y2, L"返回");
	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN) {
			// 判断控件
			if (Ret.Check(msg.x, msg.y))
				break;
		}
	}

}
//输出霍夫曼编码文件的函数
string MakeFilePage() {
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(30, 100, L"请输入编码后的文件名：");
	EasyTextBox name;
	EasyButton btnOK;
	name.Create(150, 150, 250, 180,100);
	btnOK.Create(270, 230, 320, 260,L"OK");
	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN) {
			// 判断控件
			if (name.Check(msg.x, msg.y))
				name.OnMessage();
			if (btnOK.Check(msg.x, msg.y))
				break;
		}
	}
	string c = wideCharToMultiByte(name.Text());
	return c;
}
//输出编码文件成功后的界面
void SuccessPage() {
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(100, 100, L"文件已输出！:)");
	Sleep(2000);
}
//译码方式选择界面
int DecodeChoice() {
	cleardevice();
	settextcolor(DarkBlue);
	settextstyle(25, 0, _T("黑体"));
	outtextxy(10, 100, L"请选择需要译码的文件的输入方式！:)");
	EasyButton Hand, Read;
	Hand.Create(60, 200, 180, 230, L"手动输入");
	Read.Create(210, 200, 330, 230, L"读取文件");
	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN) {
			// 判断控件
			if (Hand.Check(msg.x, msg.y))
				return 1;
			if (Read.Check(msg.x, msg.y))
				return 2;
		}
	}
	return 0;
}
//输入编码的输入框
string InputBox(int choice,int y ) {
	//画一个很大的白色矩形
	setfillcolor(WHITE);
	solidrectangle(0, y, 800, 800);
	if(choice==1)
	    outtextxy(5, y, L"请输入要译码的内容：");
	else if(choice==2)
		outtextxy(5, y, L"请输入要译码的文件地址：");
	else if(choice==3)
		outtextxy(5, y, L"请输入要译码后输出的文件名称：");

	//给出输入框
	EasyTextBox Put;
	EasyButton Ok;
	Put.Create(5, y+25, 795, y + 50, 1000);
	Ok.Create(650, y+75, 700, y + 100, L"OK");
	ExMessage msg;
	while (true) {
		msg = getmessage(EM_MOUSE);			// 获取消息输入

		if (msg.message == WM_LBUTTONDOWN) {
			// 判断控件
			if (Put.Check(msg.x, msg.y))
				Put.OnMessage();
			else if (Ok.Check(msg.x, msg.y))
				break;
		}
	}
	string c = wideCharToMultiByte(Put.Text());
	//遮住输入框，使得输入内容直接显示出来
	setfillcolor(WHITE);
	solidrectangle(5, y+25, 795, y+50);
	for (int j = 0; c[j] != '\0'; j++) {
		outtextxy(5 + j * 10 ,  y+25, c[j]);
	}

	return c;
}
//展示译码后的内容
void ShowContent(string content,int y) {
	outtextxy(5, y, L"解码后的内容为：");
	//int i = 0;
	for (int j = 0; content[j] != '\0'; j++) {
		outtextxy(20 + 10 * (j % 70), y + 25 + 25 *(j / 70), content[j]);
	}
}
