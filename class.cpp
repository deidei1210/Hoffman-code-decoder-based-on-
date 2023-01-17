#include<iostream>
#include<fstream>
#include<string>
#include"class.h"
#include"huff.h"
#include"FrontPage.h"
#define ROOT_TAG '^'
const char SNAME[] = "data.txt";
using namespace std;

extern int ct;
int dis = 0;
int ch_n = 0;  //记录出现了多少个不同的字符
//System的内部函数
int System::File_read(string filename)     //是不是可以直接利用堆进行构建
{
	//cerr << "请输入文件名 : ";
	int count[ENG_LEN] = { 0 };         //用于统计每一个字符在文章中出现的次数
	//char filename[NAME_LEN];         //文件名
	ifstream ifs(filename, ios::in);
	ch_n = 0;
	if (!ifs.is_open()) {
		cleardevice();
		settextcolor(DarkBlue);
		settextstyle(20, 0, _T("黑体"));
		outtextxy(50, 100, L"文件不存在！请重新输入文件名称！:(");
		Sleep(2000);

		cerr << "输入文件" << filename << "打开失败" << endl;
		return 0;
	}
	else {                      //如果文件打开成功
		char ch;
		while ((ch = ifs.get()) != EOF) {             //统计每一种字符一共有多少个
			if (ch >= 'a' && ch <= 'z')
				count[(ch - 'a')]++;
			else if (ch >= 'A' && ch <= 'Z')
				count[(ch - 'A') + 26]++;
			else if (ch == ' ')
				count[54]++;        //空格放置末尾特殊处理
			else if (ch == ',')
				count[52]++;
			else if (ch == '.')
				count[53]++;
			else if (ch == '?')
				count[55]++;
			else if (ch == '-')
				count[56]++;
		}
	}
	ifs.close();

	//新建一个data文件，将之前数的每个符号出现的频次都输出来
	ofstream ost(SNAME, ios::out);
	if (!ost.is_open()) {
		cerr << "输出文件" << SNAME << "打开失败" << endl;
		return 0;
	}
	else {
		for (int i = 0; i < 26; ++i) {
			if (count[i] != 0) {//出现了就写进data中
				ost << char('a' + i) << " " << count[i] << endl;
				ch_n++;
			}
		}
		for (int i = 0; i < 26; ++i) {
			if (count[i + 26] != 0) {
				ost << char('A' + i) << " " << count[i + 26] << endl;
				ch_n++;
			}
		}
		if (count[52] != 0) {
			ost << ',' << " " << count[52] << endl;
			ch_n++;
		}
		if (count[53] != 0) {
			ost << '.' << " " << count[53] << endl;
			ch_n++;
		}
		if (count[55] != 0) {
			ost << '?' << " " << count[55] << endl;
			ch_n++;
		}
		if (count[56] != 0) {
			ost << "-" << " " << count[56] << endl;
			ch_n++;
		}
		if (count[54] != 0) {
			ost << ' ' << " " << count[54] << endl;
			ch_n++;
		}
	}
	ost.close();
	return 1;
}
void System::Initial(){
	MinHeap M_Heap;
	M_Heap.creat_mheap(ch_n);
	HuffmanTree H1, H2, Put;      //分别取最小的元素,合并后的元素重新放到堆中
	while (!M_Heap.Isempty()){
		M_Heap.Delete(H1);
		M_Heap.Delete(H2);
		Put = *(Sys_Tree.Creat_Tree(H1, H2));
		if (Put.Get_root() != NULL && !M_Heap.Isempty())
			M_Heap.Insert(Put);
	}
	//程序结束时，H_Tree和M_Heap有一个重复释放的问题
	H1.Reset_root();
	H2.Reset_root();
	Put.Reset_root();
	//这里输出没有问题，说明是堆的释放出了问题
	//堆空间释放导致了哈夫曼树出现了问题
}
void System::OutPut_Tree(){  //用来画树
	//Sys_Tree.PreOrder(Sys_Tree.Get_root()); 
	//进行绘图窗口初始化
	closegraph();                      //关掉前面的绘图窗口
	initgraph(1920, 1080);			// 创建绘图窗口
	setbkcolor(WHITE);			// 设置背景填充颜色
	cleardevice();						//进行填充
	setcolor(BLACK);

	dis = 0;
	//调用画树函数
	Sys_Tree.DrawTree(Sys_Tree.Get_root(), 600, 5);

}
void System::Encode()
{
	Sys_Tree.PreOrder(Sys_Tree.Get_root());
}
void System::OutPut_Code(int stop){
	ct = 0;
	Sys_Tree.Outputcode(Sys_Tree.Get_root(),stop);
	outtextxy(5 + (ct % 3) * 267, 55 + (ct / 3 + 1) * 25, L"显示完毕！");
}
int System::Make_HuffFile(string filename,string HuffFile) {

	ifstream ifs(filename, ios::in);
	ofstream ofs(HuffFile, ios::out);
	if (!ifs.is_open()) {
		cerr << "输入文件" << filename << "打开失败" << endl;
		return -1;
	}
	else {                      //如果文件打开成功
		char ch;
		while ((ch = ifs.get()) != EOF) {             
			string code="";
			Sys_Tree.SearchCode(Sys_Tree.Get_root(), ch, code);
			ofs << code;    //将编码输出到ofs中
			//cout << code;
		 }
	}
	ifs.close();
	ofs.close();
	return 1;
}
string System::Decode(string ifile,string ofile,int choice)        //进行解码
{
	string Result;
	if (choice == 1) {
		ifstream ifs(ifile, ios::in);
		if (!ifs.is_open()) {
			cerr << "输入文件" << ifile << "打开失败" << endl;
			return " ";
		}
		else {
			Node* root = Sys_Tree.Get_root();
			Node* p = root;
			char ch;
			while ((ch = ifs.get()) != EOF) {
				if (ch == '0')
					p = p->left_child;
				else
					p = p->right_child;
				if (p->left_child == NULL && p->right_child == NULL) {
					Result += p->Name;
					p = root;
				}
			}
		}
		ifs.close();
	}
	else if (choice == 2) {//这时候应该根据ifile字符串的内容进行解码，并输出
		Node* root = Sys_Tree.Get_root();
		Node* p = root;
		char ch;
		for(int i=0;ifile[i]!='\0';i++){
			ch = ifile[i];
			if (ch == '0')
				p = p->left_child;
			else
				p = p->right_child;
			if (p!=NULL&&p->left_child == NULL && p->right_child == NULL) {
				Result += p->Name;
				p = root;
			}
		}
	}
	ofstream ofs(ofile, ios::out);
	if (ofs.is_open())
		ofs << Result;
	else{
		cerr << "输入文件" << ofile << "打开失败" << endl;
		return " ";
	}
	ofs.close();
	return Result;
}
void System::Clear(){
	Sys_Tree.clear();
}

//哈夫曼树内部函数
HuffmanTree::HuffmanTree(){
	root = new Node;
};       //默认构造函数
HuffmanTree::HuffmanTree(int data, char ch){
	root = new Node(data, ch);
}    //带参构造函数
HuffmanTree::HuffmanTree(HuffmanTree& R){
	*this = R;
}
HuffmanTree::~HuffmanTree(){
	delete root;              //有问题，重复释放？
	root = NULL;
}
Node* HuffmanTree::Get_root(){
	return this->root;
}	            //返回节点值
void HuffmanTree::Reset_root(){
	this->root = NULL;
}
bool HuffmanTree::Is_Empty(){
	return root == NULL;
}
void HuffmanTree::PreOrder(Node* p, const int choice){
	static string s;
	if (p != NULL){
		s += '0';
		//if (choice != 0)
			cout << p->Name << "  " << p->Data << endl;
		PreOrder(p->left_child);
		s.pop_back();
		s += '1';
		PreOrder(p->right_child);
		s.pop_back();
		p->Code = s;
	}
}           //前序递归记录编码
HuffmanTree& HuffmanTree::operator=(const HuffmanTree& R)
{
	this->root = R.root;
	return *this;
}
bool HuffmanTree::operator>(const HuffmanTree& R)
{
	return this->root->Data > R.root->Data;
}
bool HuffmanTree::operator<(const HuffmanTree& R)
{
	return this->root->Data < R.root->Data;
}
void HuffmanTree::Outputcode(Node* p,int stop){
	settextstyle(18, 0, _T("宋体"));
	if (p == NULL)
		return;
	else{
		//是叶子节点
		if (p->left_child == NULL && p->right_child == NULL){
			//想办法将他输出到绘图界面上
			outtextxy(5 + (ct % 3) * 267, 55 + (ct / 3 + 1) * 25, p->Name);
			//cout << p->Name;
			if(stop)
			    Sleep(100);
			//printf("%c ", p->info);
			for (int j = 0; p->Code[j] != '\0'; j++) {
				outtextxy(100 + j * 10 + (ct % 3) * 267, 55 + (ct / 3 + 1) * 25, p->Code[j]);
				if(stop)
				    Sleep(10);
			}
			ct++;
		}
		else{
			Outputcode(p->left_child,stop);
			Outputcode(p->right_child,stop);
		}
	}
}
HuffmanTree* HuffmanTree::Creat_Tree(HuffmanTree& H1, HuffmanTree& H2)  //创建Huffman树
{
	if (H1.Get_root() != NULL && H2.Get_root() != NULL){
		HuffmanTree* p = new HuffmanTree(H1.Get_root()->Data + H2.Get_root()->Data, ROOT_TAG);
		this->root = p->Get_root();       //
		root->left_child = H1.Get_root();
		root->right_child = H2.Get_root();
		return p;
	}
	else    //说明只有一根木头
		return NULL;
}
void HuffmanTree::DrawTree(Node* p, int x, int y) {

	//先遍历左子树，画左边的
	if (p->left_child != NULL) {
		//先画线，把线两个端点的左边都先求出来
		int x1 = x,y1=y,x2,y2;                 //线的起点
		if (dis != 2) {
			x2 = x - 200 + dis * 30;
			y2 = y + 50;//线的终点
		}
		else {
			x2 = x - 140;
			y2 = y + 50;//线的终点
		}
		setlinecolor(BLACK);
		line(x1, y1, x2 , y2);              //画线  
		outtextxy((x1+x2)/2, (y1+y2)/2, '0');  //标注这一条线是'0'
		//outtextxy(x2, y2, p->Name);//标注这个节点的名字
		cout << p->Name;
		Sleep(200);
		dis++;
		DrawTree(p->left_child, x2, y2);
		dis--;
	}

	//然后遍历右子树，画右边的
	if (p->right_child != NULL) {
		//先画线，把线两个端点的左边都先求出来
		int x1 = x, y1 = y, x2, y2;                 //线的起点
		if (dis != 2) {
			x2 = x + 200 - dis * 30;
			y2 = y + 50;//线的终点
		}
		else {
			x2 = x + 140;
			y2 = y + 50;//线的终点
		}	
		setlinecolor(RED);
		line(x1, y1, x2, y2);              //画线  
		outtextxy((x1 + x2) / 2, (y1 + y2) / 2, '1');  //标注这一条线是'1'
		//outtextxy(x2, y2, p->Name);//标注这个节点的名字
		cout << p->Name;
		Sleep(200);
		dis++;
		DrawTree(p->right_child, x2, y2);
		dis--;
	}

	if (p->left_child == NULL && p->right_child == NULL) {
		settextstyle(18, 0, _T("宋体"));
		outtextxy(x, y, p->Name);//标注这个节点的名字
		cout << dis << p->Name << endl;
	}
}
void HuffmanTree::SearchCode(Node* p, char c, string& a,int flag) {  //返回指定字符的哈夫曼编码
	Node* s[1000], * m;
	int top = 0;
	s[top] = p;

	while (top >= 0){
		// 首元素的栈筛比较简单，就是直接输出就完事儿
		m = s[top--];
		//cout << m->Name << "     " << c << endl;
		if (m->Name == c) {
			a = m->Code;
			break;
		}
		// 后续要递归的栈筛入栈
		if (m->right_child)
			s[++top] = m->right_child;
		if (m->left_child)
			s[++top] = m->left_child;
	}
}
void HuffmanTree::PreDelete(Node* p)  //递归调用清除
{
	if (p == NULL)
		return;
	else{
		PreDelete(p->left_child);
		PreDelete(p->right_child);
		delete p;
		p = NULL;
	}
}
void HuffmanTree::clear()         //清除函数
{
	PreDelete(root);
	root = new Node;
}

//最小堆算法内部函数
MinHeap::MinHeap(int sz)
{
	CurrentSize = sz;
	MaxSize = sz * 2 - 1;
	heap = new HuffmanTree[MaxSize];
}
void MinHeap::creat_mheap(int Number){
	ifstream ifs(SNAME, ios::in);
	CurrentSize = Number;
	MaxSize = Number * 2 - 1;
	heap = new HuffmanTree[MaxSize];
	if (!ifs.is_open()){
		cout << "文件" << SNAME << "打开失败！" << endl;
		return;
	}
	else{
		int i = 0;
		//空格读取有问题,会越过
		for (; i < Number - 1; ++i)
			ifs >> heap[i].Get_root()->Name >> heap[i].Get_root()->Data;   //读取权重构建树
		ifs.get();
		heap[Number - 1].Get_root()->Name = char(ifs.get());
		ifs.get();
		heap[Number - 1].Get_root()->Data = ifs.get();
		int Pa = (CurrentSize - 2) / 2;
		while (Pa >= 0){
			DownSift(Pa);
			Pa--;
		}
	}
	ifs.close();
}
bool MinHeap::Insert(HuffmanTree& x)
{
	if (Isfull())
		return false;
	else{
		heap[CurrentSize++] = x;
		UpSift(CurrentSize - 1);
	}
	return true;
}
bool MinHeap::Delete(HuffmanTree& N)   //默认删除第一个元素
{
	if (!Isempty())
	{
		N = heap[0];
		heap[0] = heap[--CurrentSize];
		DownSift(0);
		heap[CurrentSize].Reset_root();     //使原来的指向NULL,避免重复释放
		return true;
	}
	return false;
}
void MinHeap::DownSift(int start)   //向下调整
{
	int i = start, child = 2 * i + 1;
	HuffmanTree temp = heap[i];
	while (child <= CurrentSize - 1)
	{
		if (child<CurrentSize - 1 && heap[child] > heap[child + 1])
			++child;
		if (temp > heap[child])
		{
			heap[i] = heap[child];
			i = child;
			child = 2 * i + 1;
		}
		else
			break;
	}
	heap[i] = temp;
	temp.Reset_root();        //解决局部变量的释放问题，否则temp析构时清空了heap[i]的内存
}
void MinHeap::UpSift(int start)     //向上调整
{
	int i = start, Parent = (i - 1) / 2;  //Insert时候i就是Currentsize了
	HuffmanTree tmp = heap[i];             //这个方法更加巧妙
	while (i > 0)        //parent>=0会死循环
	{
		if (tmp < heap[Parent])
		{
			heap[i] = heap[Parent];
			i = Parent;
			Parent = (i - 1) / 2;
		}
		else
			break;
	}
	heap[i] = tmp;
	tmp.Reset_root();        //局部变量作用结束后清除
}
void MinHeap::Print()
{
	for (int i = 0; i < this->CurrentSize; ++i)
		cout << heap[i].Get_root()->Name << "*" << heap[i].Get_root()->Data << endl;
	cout << endl;
}
