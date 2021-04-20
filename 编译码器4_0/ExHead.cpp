#include "head.h"

void TransCodes::inputEncodeRoad()
{
	cout << "����������ļ���ַ��";
	cin >> road;
	cout << "��ȷ�ϱ��������:" << road << endl;
}
void TransCodes::inputDecodeRoad()
{
	cout << "����������ѹ���ļ���ַ(�ϸ��ֶ�����)��";
	cin >> road;
	road[strlen(road) - 4] = '\0';
	cout << "��ȷ�����������:" << road << endl;
}
void TransCodes::HuffmanTree(int weight[], int n, HuffNode haffTree[])
//����Ҷ������ΪnȨֵ����Ϊweight�Ĺ�������haffTree
{
	int j, m1, m2, x1, x2;
	//��������haffTree�ۣݳ�ʼ����n��Ҷ��㹲��2n-1�����
	
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
	
	
	
	//�����������haffTree[]��n-1����Ҷ���
	for (int i = 0; i<n - 1; i++)
	{
		m1 = m2 = MaxValue;
		x1 = x2 = 0;
		for (j = 0; j<n + i; j++)
		{
			if (haffTree[j].weight<m1 && haffTree[j].parent == 0)//������СȨֵm1�ͱ��Ϊx1��m2��x2Ϊ����С
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
		//���ҳ�������Ȩֵ��С�������ϲ�Ϊһ������
		haffTree[x1].parent = n + i;
		haffTree[x2].parent = n + i;
		haffTree[n + i].weight = haffTree[x1].weight + haffTree[x2].weight;
		haffTree[n + i].leftChild = x1;
		haffTree[n + i].rightChild = x2;
	}
	btN=2*n-2;
}
void TransCodes::HaffmanCode(HuffNode huffTree[], int n, Code haffCode[])
//��n�����Ĺ�������huffTree[]�������������haffCode[]
{
	Code cd;
	int child, parent;
	//��n��Ҷ���Ĺ���������
	for (int i = 0; i<n; i++)
	{
		cd.start = n - 1;//���ȳ���������һλΪn-1
		cd.weight = huffTree[i].weight;
		cd.content = huffTree[i].content;
		//ȡ�ñ����ӦȨֵ���ַ�
		child = i;
		parent = huffTree[child].parent;
		//��Ҷ�������ֱ�������
		while (parent != 0)
		{
			if (huffTree[parent].leftChild == child)
				cd.bit[cd.start] = '0';//���ӽ�����0
			else
				cd.bit[cd.start] = '1';//�Һ��ӽ�����1
			cd.start--;
			child = parent;
			parent = huffTree[child].parent;
		}
		//����ÿ��Ҷ���ı���Ͳ��ȳ��������ʼλ
		for (int j = cd.start + 1; j<n; j++)
			haffCode[i].bit[j] = cd.bit[j];
		haffCode[i].start = cd.start + 1;
		haffCode[i].weight = cd.weight;
		haffCode[i].content = cd.content;
		//��ס�����ӦȨֵ���ַ�
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
	cout << "�����С���" << endl;
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
	cout << "������ϣ� ѹ���ļ��ѱ�����"<<tempWrite<< endl;
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
	cout << "�����С���" << endl;
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
	cout<<"������ɣ���ѹ�ļ��Ѵ洢��"<<tempWrite<<endl;
	cout << "�����и����ļ���׺��" << endl;
}
void TransCodes::readFile()
{
	FILE *fp;
	unsigned char c;
	if (fopen(road, "rb") == NULL)
	{
		cout << "δ�ҵ����ļ���";
		return;
	}
	fp = fopen(road, "rb");
	cout << "����ɨ��ԭ�ļ�����" << endl;
	while (fread(&c, sizeof(c), 1, fp))
	{
		//printf("%x ", c);
		Hash[c]++;
	}
	cout << "ɨ����ϣ�" << endl;
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
	cout<<"����ɽ����������ɹ���������"<<endl;
	//���ÿ��Ҷ���Ĺ���������
	//cout << "������������ǣ�" << endl;
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
	cout << "����������ѹ���洢��"<<temp_fp << endl;
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
	cout << "���������Ѷ����ڴ�" << endl;
}