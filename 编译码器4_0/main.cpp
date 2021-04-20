#include "head.h"

void Menu()
{
	cout << "----------------------<<--------±àÒëÂëÆ÷------->>-------------------------" << endl;
	cout << "          1           <<----------±àÂë--------->>                         " << endl;
	cout << "          2           <<----------ÒëÂë--------->>                         " << endl;
	cout << "          3           <<----------ÍË³ö--------->>                         " << endl;
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
		cout << "ÇëÑ¡Ôñ£º";
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