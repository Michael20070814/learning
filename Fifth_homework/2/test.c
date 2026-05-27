#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 256
#include <string.h>

char HCode[128][MAXSIZE]={{0}};
FILE *Obj, *Src;
int bits_left = 0;

void CalcCount(); // 读入码表的前半部分确定相应Huffman编码
void HZIPtoa(); // 根据Huffman编码把指定Huffman码文件转换成ASCII码文本文件
char *GetHuffman(int length); // 读入指定长度的huffman编码
int get_next_bit(int *type); // 读入一个字节，但是按位处理

int main(void)
{
    char file[ ] = "myfile.hzip";
    Src=fopen(file,"rb");
    char *p = strrchr(file, '.');
    strcpy(p, ".txt");
    Obj=fopen(file,"wb");

    CalcCount(); // 词表注册成功
    HZIPtoa();
}

void CalcCount()
{
	int count = fgetc(Src); // 读取首字节

	for (int i = 0; i < count; i++)
	{
		int c = fgetc(Src); // 读取ASCII码
		int length = fgetc(Src); // 读取Huffman长度
		char *p = GetHuffman(length);
		strcpy(HCode[c], p);
		free(p); 
	}
}

char *GetHuffman(int length)
{
	char *result = (char *)malloc(sizeof(char) * MAXSIZE);
	int i; int byte;

	for (i = 0; i < length; i++)
	{
		if (i % 8 == 0) // 逢8位读一次
			fread(&byte, 1, 1, Src);
		
		int real = i % 8;
		int bit = (byte >> (7 - real)) & 1;
		result[i] = '0' + bit;
	}
	result[i] = '\0';
	
	return result;
}

void HZIPtoa()
{
	int type = 0;
	unsigned char bit = 0;
	char judge[MAXSIZE];
	int index = 0;

	while ((bit = get_next_bit(&type)) != -1)
	{
		if (index >= MAXSIZE - 1)
			return ;

		judge[index++] = '0' + bit;
		judge[index] = '\0';

		for (int i = 0; i < 128; i++)
		{
			if (strcmp(HCode[i], judge) == 0)
			{
				if (i == 0)
					return;
					
				fputc(i, Obj);
				index = 0;
				break;
			}
		}

	}

}

int get_next_bit(int *type)
{
	if (bits_left == 0)
	{
		if (fread(type, 1, 1, Src) != 1)
			return -1;
		bits_left = 8;
	}
	bits_left--;

	return (*type >> bits_left) & 1;
}