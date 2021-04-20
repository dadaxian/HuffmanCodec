#ifndef BASE_H
#define BASE_H
static void getHex(unsigned char &buff, char*g, int m, int n)//二进制转十六进制
{
	unsigned char T;
	T = g[m]*128 + g[m + 1]*64  + g[m + 2]*32  + g[m + 3]*16  + g[m + 4]*8  + g[m + 5]*4  + g[m + 6]*2  + g[m + 7]-11984;
	buff = T;
}
static void getBin(char *buffs, unsigned char buff)//十六进制转二进制
{
	buffs[0] = buff / 128+48;
	buffs[1] = buff % 128 / 64+48;
	buffs[2] = buff % 64 / 32+48;
	buffs[3] = buff % 32 / 16+48;
	buffs[4] = buff % 16 / 8+48;
	buffs[5] = buff % 8 / 4+48;
	buffs[6] = buff % 4 / 2+48;
	buffs[7] = buff % 2 +48;
	buffs[8] = '\0';
}
#endif