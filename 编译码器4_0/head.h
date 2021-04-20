#define _CRT_SECURE_NO_WARNINGS

#ifndef HEAD_H
#define	HEAD_H
#include <iostream>
#include <fstream>
#include <string>
#include "Base.h"

using namespace std;
const int MaxValue = 100000000;//作权值最大值
const int MaxN = 10000;
const int Maxsize = 10;
const char Yuan[6]=".yuan";
const char Suffix_file[6] = ".file";
const char Suffix_zip[5] = ".zip";
const char codeSuffix_zip[13] = ".codezip";
struct HuffNode
{
	unsigned char content;			//内容
	int weight;           //权值
	int parent;           //双亲结点下标
	int leftChild;        //左孩子下
	int rightChild;//右孩子下标
};
struct  Code    //存放哈夫曼编码的数组元素结构
{
	unsigned char content;			//内容
	char bit[MaxN];    //数组
	int start;        //编码的起始下标
	int weight;       //字符的权值
};

class TransCodes
{
private:
	char TransCode[256][20];//预设编码最大长度：20
	char everyNodeLength[256];//读取huffman编码时得到每一组哈夫曼编码的长度
	char road[100];//读取路径
	int Hash[256];//存放原始数据
	int N;//哈弗曼树叶节点数
	int btN;//根序号
	HuffNode* myHaffTree;
	Code* myHaffCode;
public:
	TransCodes()
	{
		for(int i=0;i<256;i++)
			Hash[i]=0;
		for(int i=0;i<256;i++)
			for(int j=0;j<20;j++)
				TransCode[i][j]='\0';
		myHaffTree = new HuffNode[511];
		myHaffCode = new Code[511];
	}
	~TransCodes()
	{
		delete[] myHaffTree;
		delete[] myHaffCode;
	}
	void inputEncodeRoad();
	void inputDecodeRoad();
	int getCount();
	int getBoot();
	void setCount();
	void HaffmanCode(HuffNode huffTree[], int n, Code haffCode[]);
	void HuffmanTree(int weight[], int n, HuffNode haffTree[]);
	void readFile();
	void Huffman();
	void SaveHuffTree();
	void ReadHuffTree();
	void Encode();
	void Decode();
};
#endif