#pragma once
#define DarkBlue RGB(54, 46, 61)
#define NormalBlue RGB(80,100,120)
#define LightBlue RGB(197,213,237)
void StartPage();                                                   //初始界面
char* wideCharToMultiByte(wchar_t* pWCStrKey);//宽字符转换成字符串
string LoadFilePage();                                     //输入需要导入的文件界面
int menu();                                                     //菜单界面
int ToContinue();                                            //“继续”界面
void EncodePage();                                        //编码后展示编码内容的界面
void End();                                                      //“结束”界面
void ReturnButtum(int x1, int y1, int x2, int y2);//“返回”按钮设计
string MakeFilePage();                                      //输出编码后的文件界面
void SuccessPage();                                          //文件输出成功界面
int DecodeChoice();                                          //选择译码时输入编码方式的界面
string InputBox(int choice, int y);                      //文本框部件设计
void ShowContent(string content, int y);          //展示译码后的内容