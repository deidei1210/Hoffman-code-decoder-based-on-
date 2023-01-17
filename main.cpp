#include<iostream>
#include<easyx.h>
#include <conio.h>	 
#include"class.h"
#include"FrontPage.h"
using namespace std;
int ct = 0;
int main()
{
	System sys;
	//初始界面
	StartPage();
	string filename = "";
	while (1) {
		//选择要打开的文件
	    filename = LoadFilePage();
		if (sys.File_read(filename))   //读取指定文件
			break;
	}
	sys.Initial();  //哈夫曼树生成成功
	sys.Encode();//对每一个字符开始编码
    
	int d = 1;
	while (d == 1) {
		//选择要进行的操作
		int choice = menu();

		if (choice == 1) {
			//一旦使用这个功能，先初始化界面
			EncodePage();			//输出哈弗曼编码界面
			sys.OutPut_Code();   //输出内容
			ReturnButtum(700, 750, 780, 790);//返回按钮
		}
		else if (choice == 2) {   //将指定文件用刚刚得到的字符编码输出
			string file=MakeFilePage();
			cout << file << endl;
			sys.Make_HuffFile(filename, file);
			SuccessPage();
			//ReturnButtum(300, 350, 380, 390);
		}
		else if (choice == 3) {
			sys.OutPut_Tree();
			//draw_main(root);					//调用图形化主函数
			ReturnButtum(5, 55, 85, 95);
		}
		else if (choice == 4) {  //选择该选项表示需要译码
			int c=DecodeChoice();  //做选择的界面
			//手动输入译码文件
			if (c == 1) {
				//先打印每个单词对应的译码
				EncodePage();			//输出哈弗曼编码界面
				sys.OutPut_Code(0);   //输出每个字符对应的编码内容
				//给出输入编码的输入框
				string content=InputBox(1, 55 + (ct / 3 + 2) * 25);
				string name2 = InputBox(3, 55 + (ct / 3 + 7) * 25);//要输出的文件名
				//显示译码后的内容
				string result = sys.Decode(content, name2, 2);
				ShowContent(result, 55 + (ct / 3 + 11) * 25);
				ReturnButtum(700, 750, 780, 790);//返回按钮
			}
			//读入文件译码
			else if (c == 2) {
				EncodePage();			//输出哈弗曼编码界面
				sys.OutPut_Code(0);   //输出每个字符对应的编码内容
				string address1=InputBox(2, 55 + (ct / 3 + 2) * 25);//要读入的文件地址
				string name2= InputBox(3, 55 + (ct / 3 + 7) * 25);//要输出的文件名
				//显示译码后的内容
				string result=sys.Decode(address1, name2,1);
				ShowContent(result, 55 + (ct / 3 + 11) * 25);
				ReturnButtum(700, 750, 780, 790);//返回按钮
			}

		}
		else if (choice == 5) {//重新读入文件
			sys.Clear();//对之前的哈夫曼树进行清空
			while (1) {
				//选择要打开的文件
				filename = LoadFilePage();
				if (sys.File_read(filename))   //读取指定文件
					break;
			}
			sys.Initial();  //哈夫曼树生成成功
			sys.Encode();//对每一个字符开始编码
		}
		else if (choice == 0) {
			break;
		}
		else {
			outtextxy(35, 330, _T("没有你要执行的选项，请重新输入！"));
			Sleep(2000);
			continue;
		}
		d = ToContinue();
     }
	End();
	closegraph();
	return 0;
}

