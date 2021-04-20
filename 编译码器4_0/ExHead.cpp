#include "head.h"

void TransCodes::inputEncodeRoad()
{
	cout << "请输入编码文件地址：";
	cin >> road;
	cout << "已确认编码码对象:" << road << endl;
}
void TransCodes::inputDecodeRoad()
{
	cout << "请输入译码压缩文件地址(严格手动输入)：";
	cin >> road;
	road[strlen(road) - 4] = '\0';
	cout << "已确认译码码对象:" << road << endl;
}
void TransCodes::HuffmanTree(int weight[], int n, HuffNode haffTree[])
//建立叶结点个数为n权值数组为weight的哈夫曼树haffTree
{
	int j, m1, m2, x1, x2;
	//哈夫曼树haffTree［］初始化。n个叶结点共有2n-1个结点
	
	int count = 0;
	for (int i = 0; i < 256; i++)
	{
		if (weight[i] != 0)
		{
			haffTree[count].weight = weight[i];
			haffTree[count].content = i;
			haffTree[count].parent = 0;
			haffTree[count].leftChild = -1;
			haffTree[count].rightChild = -1;
			count++;
		}
	}
	for (int i = count; i < 2 * n - 1; i++)
	{
		haffTree[i].weight = 0;
		haffTree[i].parent = 0;
		haffTree[i].leftChild = -1;
		haffTree[i].rightChild = -1;
	}
	//for (int i = 0; i<2 * n - 1; i++)
	//{
	//	if (i < n)
	//	{
	//		haffTree[i].weight = weight[i];
	//		haffTree[i].content = i;
	//	}
	//	else
	//		haffTree[i].weight = 0;
	//	haffTree[i].parent = 0;
	//	haffTree[i].leftChild = -1;
	//	haffTree[i].rightChild = -1;
	//}
	
	
	
	//构造哈夫曼树haffTree[]的n-1个非叶结点
	for (int i = 0; i<n - 1; i++)
	{
		m1 = m2 = MaxValue;
		x1 = x2 = 0;
		for (j = 0; j<n + i; j++)
		{
			if (haffTree[j].weight<m1 && haffTree[j].parent == 0)//查找最小权值m1和标号为x1；m2和x2为次最小
			{
				m2 = m1;
				x2 = x1;
				m1 = haffTree[j].weight;
				x1 = j;
			}
			else if (haffTree[j].weight<m2 && haffTree[j].parent == 0)
			{
				m2 = haffTree[j].weight;
				x2 = j;
			}
		}
		//将找出的两棵权值最小的子树合并为一棵子树
		haffTree[x1].parent = n + i;
		haffTree[x2].parent = n + i;
		haffTree[n + i].weight = haffTree[x1].weight + haffTree[x2].weight;
		haffTree[n + i].leftChild = x1;
		haffTree[n + i].rightChild = x2;
	}
	btN=2*n-2;
}
void TransCodes::HaffmanCode(HuffNode huffTree[], int n, Code haffCode[])
//由n个结点的哈夫曼树huffTree[]构造哈夫曼编码haffCode[]
{
	Code cd;
	int child, parent;
	//求n个叶结点的哈夫曼编码
	for (int i = 0; i<n; i++)
	{
		cd.start = n - 1;//不等长编码的最后一位为n-1
		cd.weight = huffTree[i].weight;
		cd.content = huffTree[i].content;
		//取得编码对应权值的字符
		child = i;
		parent = huffTree[child].parent;
		//由叶结点向上直到根结点
		while (parent != 0)
		{
			if (huffTree[parent].leftChild == child)
				cd.bit[cd.start] = '0';//左孩子结点编码0
			else
				cd.bit[cd.start] = '1';//右孩子结点编码1
			cd.start--;
			child = parent;
			parent = huffTree[child].parent;
		}
		//保存每个叶结点的编码和不等长编码的起始位
		for (int j = cd.start + 1; j<n; j++)
			haffCode[i].bit[j] = cd.bit[j];
		haffCode[i].start = cd.start + 1;
		haffCode[i].weight = cd.weight;
		haffCode[i].content = cd.content;
		//记住编码对应权值的字符
	}
}
void TransCodes::Encode()
{
	FILE *fp_read;
	FILE *fp_write;
	char tempWrite[100];
	strcpy(tempWrite, road);
	strcat(tempWrite, Suffix_zip);

	fp_read = fopen(road, "rb");
	fp_write = fopen(tempWrite, "wb");
	cout << "编码中……" << endl;
	char buffs[9];
	unsigned char buff_Read,buff_Write;
	int BuffsIndex = 0,CodeIndex;
	while (fread(&buff_Read, 1, 1, fp_read))
	{
		CodeIndex = 0;
		while (CodeIndex < strlen(TransCode[buff_Read]))
		{
			buffs[BuffsIndex++] = TransCode[buff_Read][CodeIndex++];
			if (BuffsIndex == 8)
			{
				getHex(buff_Write,buffs, 0, 7);
				fwrite(&buff_Write, 1, 1, fp_write);
				BuffsIndex = 0;
			}
		}
	}
	cout << "编码完毕！ 压缩文件已保存至"<<tempWrite<< endl;
	fclose(fp_read);
	fclose(fp_write);
}
void TransCodes::Decode()
{
	FILE *fp_read;
	FILE *fp_write;

	char tempRead[100],tempWrite[100];
	strcpy(tempWrite, road);
	strcpy(tempRead, road);
	strcat(tempRead, Suffix_zip);
	strcat(tempWrite, Yuan);

	fp_write = fopen(tempWrite, "wb");
	fp_read = fopen(tempRead, "rb");
	cout << "解码中……" << endl;
	int boot = getBoot();
	int bt = boot;
	char bitBuff;
	int BuffsIndex = 0;
	char buffs[9];
	unsigned char buff;
	while (fread(&buff, 1, 1, fp_read))
	{
		getBin(buffs, buff);
		while (BuffsIndex < 8)
		{
			bitBuff = buffs[BuffsIndex++];
			if (bitBuff == '1')
				bt = myHaffTree[bt].rightChild;
			else
				bt = myHaffTree[bt].leftChild;
			if (myHaffTree[bt].leftChild == -1 && myHaffTree[bt].rightChild == -1)
			{
				fwrite(&myHaffTree[bt].content,1,1,fp_write);
				bt=boot;
			}
		}
		BuffsIndex = 0;
	}

	fclose(fp_read);
	fclose(fp_write);
	cout<<"解码完成，解压文件已存储至"<<tempWrite<<endl;
	cout << "请自行更改文件后缀！" << endl;
}
void TransCodes::readFile()
{
	FILE *fp;
	unsigned char c;
	if (fopen(road, "rb") == NULL)
	{
		cout << "未找到该文件！";
		return;
	}
	fp = fopen(road, "rb");
	cout << "正在扫描原文件……" << endl;
	while (fread(&c, sizeof(c), 1, fp))
	{
		//printf("%x ", c);
		Hash[c]++;
	}
	cout << "扫描完毕！" << endl;
}
int TransCodes::getCount()
{
	int count = 0;
	for (int i = 0; i < 256; i++)
		if (Hash[i] != 0)
			count++;
	return count;
}
int TransCodes::getBoot()
{
	int k=0;
	for (int i = 0; i < 512; i++)
	{
		if (myHaffTree[i].parent == 0)
		{
			k = i;
			break;
		}	
	}
	return k;
}
void TransCodes::setCount()
{
	int count = 0;
	for (int i = 0; i < 256; i++)
		if (Hash[i] != 0)
			count++;
	N = count;
	
}
void TransCodes::Huffman()
{
	HuffmanTree(Hash, getCount(),myHaffTree);
	HaffmanCode(myHaffTree, N, myHaffCode);
	int temp;
	for (int i = 0; i<N; i++)
	{
		temp = myHaffCode[i].start;
		for (int j = myHaffCode[i].start; j<N; j++)
			TransCode[myHaffCode[i].content][j - temp] = myHaffCode[i].bit[j];
	}
	cout<<"已完成建树，并生成哈夫曼编码"<<endl;
	//输出每个叶结点的哈夫曼编码
	//cout << "哈夫曼编码表是：" << endl;
	//for (int i = 0; i<N; i++)
	//{
	//	printf("%x", myHaffCode[i].content);
	//	cout<< "--";
	//	//cout << "Content="; printf("%d",myHaffTree[i].content); cout << " " << "Weight=" << myHaffCode[i].weight << "  " << "Code=";
	//	for (int j = myHaffCode[i].start; j<N; j++)
	//		cout << myHaffCode[i].bit[j];
	//	cout << "*" << TransCode[myHaffCode[i].content]<< "*";
	//	cout << endl;
	//}

}
void TransCodes::SaveHuffTree()
{
	FILE *fp;
	char temp_fp[100];
	strcpy(temp_fp,road);
	strcat(temp_fp, codeSuffix_zip);
	fp = fopen(temp_fp, "wb");
	fwrite(myHaffTree, sizeof(HuffNode), 511, fp);
	fclose(fp);
	cout << "哈夫曼树已压缩存储到"<<temp_fp << endl;
}
void TransCodes::ReadHuffTree()
{
	FILE *fp;
	char temp_fp[100];
	strcpy(temp_fp, road);
	strcat(temp_fp, codeSuffix_zip);
	fp = fopen(temp_fp, "rb");
	fread(myHaffTree, sizeof(HuffNode), 511, fp);
	fclose(fp);
	cout << "哈夫曼树已读入内存" << endl;
}