#include "head.h"

void Menu()
{
	cout << "----------------------<<--------��������------->>-------------------------" << endl;
	cout << "          1           <<----------����--------->>                         " << endl;
	cout << "          2           <<----------����--------->>                         " << endl;
	cout << "          3           <<----------�˳�--------->>                         " << endl;
}
void ENCODE()
{
	TransCodes Tc;
	Tc.inputEncodeRoad();
	Tc.readFile();
	Tc.setCount();
	Tc.Huffman();
	Tc.Encode();
	Tc.SaveHuffTree();
}
void DECODE()
{
	TransCodes Tc;
	Tc.inputDecodeRoad();
	Tc.ReadHuffTree();
	Tc.Decode();
}

void HUFFCODE()
{
	int switch1;
	bool IsEnd=0;
	while(!IsEnd)
	{
		cout << "��ѡ��";
		cin >> switch1;
		switch (switch1)
		{
		case 1:
			ENCODE();
			break;
		case 2:
			DECODE();
			break;
		//case 3:
		case 3:
			IsEnd=1;
			break;
		}
	}
}
void main()
{
	
	Menu();
	HUFFCODE();
}