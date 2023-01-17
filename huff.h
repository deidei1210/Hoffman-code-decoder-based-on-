#pragma once
#include<iostream>
#define DefaultSize  20  //默认大小
using namespace std;

class Node{
public:
	friend class HuffmanTree;
	friend class MinHeap;
	Node() :Data(0),Name('&'),left_child(NULL), right_child(NULL) {};
	Node(int data,char ch, Node* l = NULL, Node* r = NULL){
		Data = data;
		Name = ch;
		left_child = l;
		right_child = r;
	}
	Node& operator=(Node& R)
	{
		this->Data = R.Data;
		this->Name = R.Name;
		this->left_child = R.left_child;
		this->right_child = R.right_child;
		return *this;
	}
	bool operator>(Node& R)
	{
		return this->Data > R.Data;
	}
	bool operator<(Node& R)
	{
		return this->Data < R.Data;
	}
	int Data;            //编码权重
	char Name;           //字符名字
	string Code;          //记录编码
	Node* left_child;
	Node* right_child;
};

class HuffmanTree{
public:
	HuffmanTree();
	HuffmanTree(int data, char ch);
	HuffmanTree(HuffmanTree& R);
	~HuffmanTree();
	HuffmanTree* Creat_Tree(HuffmanTree& H1, HuffmanTree& H2);  //创建Huffman树
	Node* Get_root();
	void Reset_root();
	bool Is_Empty();
	void PreOrder(Node* p, const int choice = 0);
	void PreDelete(Node* p);                       //遍历删除
	void Outputcode(Node* p,int stop=1);
	void DrawTree(Node* p,int x,int y);
	void SearchCode(Node*p,char c,string& a,int flag=0);
	void clear();     //用于将哈夫曼树中的节点全部释放

	HuffmanTree& operator=(const HuffmanTree& R);
	bool operator>(const HuffmanTree& R);
	bool operator<(const HuffmanTree& R);
private:
	Node* root;
};


//最小堆算法实现
class MinHeap{
public:
	MinHeap(int sz = DefaultSize);
	~MinHeap(){
		delete[]heap;
	}
	void creat_mheap(int Number);
	bool Insert(HuffmanTree& x);
	bool Delete(HuffmanTree& N);   //默认删除第一个元素
	void DownSift(int start);   //向下调整
	void UpSift(int start);     //向上调整
	bool Isempty() {
		return CurrentSize == 0;
	}
	bool Isfull(){
		return CurrentSize == MaxSize;
	}
	void Print();
	int Get_Current(){
		return this->CurrentSize;
	}
	HuffmanTree* Get_Top(){
		return this->heap;
	}
private:
	HuffmanTree* heap;  //一个存储数据的数据
	int CurrentSize;
	int MaxSize;
};
