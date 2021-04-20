#define _CRT_SECURE_NO_WARNINGS

#ifndef HEAD_H
#define	HEAD_H
#include <iostream>
#include <fstream>
#include <string>
#include "Base.h"

using namespace std;
const int MaxValue = 100000000;//��Ȩֵ���ֵ
const int MaxN = 10000;
const int Maxsize = 10;
const char Yuan[6]=".yuan";
const char Suffix_file[6] = ".file";
const char Suffix_zip[5] = ".zip";
const char codeSuffix_zip[13] = ".codezip";
struct HuffNode
{
	unsigned char content;			//����
	int weight;           //Ȩֵ
	int parent;           //˫�׽���±�
	int leftChild;        //������
	int rightChild;//�Һ����±�
};
struct  Code    //��Ź��������������Ԫ�ؽṹ
{
	unsigned char content;			//����
	char bit[MaxN];    //����
	int start;        //�������ʼ�±�
	int weight;       //�ַ���Ȩֵ
};

class TransCodes
{
private:
	char TransCode[256][20];//Ԥ�������󳤶ȣ�20
	char everyNodeLength[256];//��ȡhuffman����ʱ�õ�ÿһ�����������ĳ���
	char road[100];//��ȡ·��
	int Hash[256];//���ԭʼ����
	int N;//��������Ҷ�ڵ���
	int btN;//�����
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