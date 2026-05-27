#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 256

struct tnode {            //Huffman树结构
    char c;        
    int weight;        //树节点权重，叶节点为字符和它的出现次数
    struct tnode *left,*right;
} ; 
int Ccount[128]={0};        //存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL;     //Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;            //实验步骤 
int bits_left = 0; // 记录还有多少个位可以读取
FILE *Src, *Obj;

int getNum(struct tnode *list[128]); // 获取当前时刻树林的数目
int checkExt(char *filename, char *ext); // 判断扩展名是否合乎规范
void makeTree(struct tnode *list[128], struct tnode *list2[128], int *index); // 合并两个树叶
void visitHTree(struct tnode *p, char *buffer, int index); // 遍历访问树 并创建对应的编码
void CalcCount(); // 读入码表的前半部分确定相应Huffman编码
void HZIPtoa(); // 根据Huffman编码把指定Huffman码文件转换成ASCII码文本文件
char *GetHuffman(int length); // 读入指定长度的huffman编码
int get_next_bit(int *type); // 读入一个字节，但是按位处理
void statCount();        //步骤1：统计文件中字符频率
void createHTree();        //步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();        //步骤3：根据Huffman树生成Huffman编码
void printHCode();       // 写入码表长度以及对应的东西
void atoHZIP();         //步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件

// void print1();            //输出步骤1的结果
// void print2(struct tnode *p);    //输出步骤2的结果 
// void print3();            //输出步骤3的结果
// void print4();            //输出步骤4的结果

int main(int argc, char **argv)
{
    // char file[MAXSIZE];
    // char obj[] = "-u";
    // int flag = 0;
    // // 输入错误加载
    // if (argc < 2 || argc > 3)
    // {    
    //     printf("Usage: hzip.exe [-u] <filename>");
    //     flag = 1;
    // }
    // else if (argc == 3 && strcmp(obj, argv[1]) != 0)
    // {    
    //     printf("Usage: hzip.exe [-u] <filename>");
    //     flag = 1;
    // }
    // else if (argc == 2 && !checkExt(argv[1], ".txt"))
    // {
    //     printf("File extension error!");
    //     flag = 1;
    // }
    // else if (argc == 3 && !checkExt(argv[2], ".hzip"))
    // {    
    //     printf("File extension error!");
    //     flag = 1;
    // }
    // if (flag == 1)
    //     return 0;
        
    // // 根据参数选择不同分流
    // if (argc == 2)
    //     strcpy(file, argv[1]);
    // else if (argc == 3)
    //     strcpy(file, argv[2]);

    // if (argc == 2)
    // {
    //     // 文件读取
    //     if((Src=fopen(file,"rb"))==NULL) 
    //     {
    //         fprintf(stderr, "%s open failed!\n", "input.txt");
    //         return 1; 
    //     }

    //     // 文件写入
    //     char *p = strrchr(file, '.');
    //     strcpy(p, ".hzip");

    //     if((Obj=fopen(file,"wb"))==NULL)
    //     {
    //         fprintf(stderr, "%s open failed!\n", "output.txt");
    //         return 1;
    //     }

    //     statCount();
    //     createHTree();
    //     makeHCode();
    //     printHCode();
    //     atoHZIP();
    // }
    // else if (argc == 3)
    // {
    //     // 文件读取
    //     if((Src=fopen(file,"r"))==NULL) 
    //     {
    //         fprintf(stderr, "%s open failed!\n", "input.txt");
    //         return 1; 
    //     }

	// 	char *p = strrchr(file, '.');
    //     strcpy(p, ".txt");

    //     // 文件写入
    //     if((Obj=fopen(p,"w"))==NULL)
    //     {
    //         fprintf(stderr, "%s open failed!\n", "output.txt");
    //         return 1;
    //     }

	// 	CalcCount(); // 读入码表的前半部分确定相应Huffman编码
	// 	// HZIPtoa();
    // }


    // scanf("%d",&Step);        //输入当前实验步骤 
    //实验步骤1：统计文件中字符出现次数（频率）
    // (Step==1)?print1():1;       //输出实验步骤1结果    
    //实验步骤2：依据字符频率生成相应的Huffman树
    // (Step==2)?print2(Root):2;     //输出实验步骤2结果    
    //实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
    // (Step==3)?print3():3;       //输出实验步骤3结果
    // (Step>=4)?atoHZIP(),print4():4;//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果 
	
	char file[ ] = "myfile.txt";
    Src=fopen(file,"rb");
    char *p = strrchr(file, '.');
    strcpy(p, ".hzip");
	
	    statCount();
        createHTree();
        makeHCode();
        printHCode();

    fclose(Src);
    fclose(Obj);
        return 0;
} 

//【实验步骤1】开始 
void statCount()
{
	int c;
	while ((c = fgetc(Src)) != EOF)
		Ccount[c]++;

	Ccount[0] = 1;
}

//【实验步骤1】结束

//【实验步骤2】开始

int getNum(struct tnode *list[128])
{
	int result = 0;
	for (int i = 0; i < 128; i++)
	{
		if (list[i] != NULL)
			result++;
	}

	return result;
}

void makeTree(struct tnode *list[128], struct tnode *list2[128], int *index)
{
	struct tnode* smallest = NULL; int temp; int flag; int c;
	int check = 1;
	struct tnode* smallestbitbigger = NULL;

	// 找到一个非空元素
	for (int i = 0; i < 128; i++)
		if (list[i] != NULL)
		{
			temp = list[i]->weight;
			smallest = list[i];
			flag = i;
			c = list[i] -> c;
			break;
		}

	if (smallest == NULL)
	{
		for (int i = 0; i < *index; i++)
			if (list2[i] != NULL)
			{
				check = 0;
				temp = list2[i] -> weight;
				smallest = list2[i];
				flag = i;
				break;
			}
	}

	// 找出最小指针
	for (int i = 0; i < 128; i++)
	{
		if ((list[i] != NULL && list[i] -> weight < temp) || (list[i] != NULL && list[i] -> weight == temp && list[i] -> c < c))
		{
			temp = list[i]->weight;
			smallest = list[i];
			flag = i;
			c = list[i] -> c;
		}
	}

	// 检查Q2队列是否有更小的，这里天然满足自动放在后面的条件
	for (int i = 0; i < *index; i++)
	{
		if (list2[i] != NULL && list2[i] -> weight < temp)
		{
			check = 0;
			smallest = list2[i];
			temp = list2[i] -> weight;
			flag = i;
		}
	}

	if (check)
		list[flag] = NULL;
	else
		list2[flag] = NULL;

	check = 1;

	// 找到一个非空元素
	for (int i = 0; i < 128; i++)
		if (list[i] != NULL)
		{
			temp = list[i]->weight;
			smallestbitbigger = list[i];
			flag = i;
			c = list[i] -> c;
			break;
		}

	if (smallestbitbigger == NULL)
	{
		for (int i = 0; i < *index; i++)
			if (list2[i] != NULL)
			{
				check = 0;
				temp = list2[i] -> weight;
				smallestbitbigger = list2[i];
				flag = i;
				break;
			}
	}

	// 找出第二小指针
	for (int i = 0; i < 128; i++)
	{
		if ((list[i] != NULL && list[i] -> weight < temp) || (list[i] != NULL && list[i] -> weight == temp && list[i] -> c < c))
		{
			temp = list[i]->weight;
			smallestbitbigger = list[i];
			c = list[i] -> c;
			flag = i;
		}
	}

	// 寻找Q2最小的数值
	for (int i = 0; i < *index; i++)
	{
		if (list2[i] != NULL && list2[i] -> weight < temp)
		{
			check = 0;
			smallestbitbigger = list2[i];
			temp = list2[i] -> weight;
			flag = i;
		}
	}

	if (check)
		list[flag] = NULL;
	else
		list2[flag] = NULL;

	// 两个节点进行合并
	struct tnode *new = (struct tnode *) malloc(sizeof(struct tnode));
	new -> weight = smallest -> weight + smallestbitbigger -> weight;
	new -> left = smallest; new -> right = smallestbitbigger;
	new -> c = 0;
	list2[(*index)++] = new;

}

//【实验步骤2】开始
void createHTree()
{
	struct tnode *p;
	Root = NULL;
	// 创建树林
	struct tnode* TnodeList[128] = {0};
	struct tnode* array[128] = {0}; int index = 0;
	
	for (int i = 0; i < 128; i++)
	{
		if (Ccount[i] > 0)
		{
			p = (struct tnode *) malloc(sizeof(struct tnode));
			p -> c = i;
			p -> weight = Ccount[i];
			p -> left = p -> right = NULL;
			TnodeList[i] = p;
		}
	}

	while (getNum(TnodeList) + getNum(array) > 1)
		makeTree(TnodeList, array, &index);

	// 找出唯一非零元素
	for (int i = 0; i < 128; i++)
		if (array[i] != NULL)
			Root = array[i];

	// for (int i = 0; Root == NULL && i < 128; i++)
	// 	if (TnodeList[i] != NULL)
	// 		Root = TnodeList[i];
}




//【实验步骤2】结束

//【实验步骤3】开始

void visitHTree(struct tnode *p, char *buffer, int index)
{
	if (p == NULL)
		return ;

	// 注意如果只有一个节点的话 要初始化一下
	if (index == 0)
	{
		buffer[index] = '0';
		buffer[index + 1] = '\0';
	}

	if (p -> right == NULL && p -> left == NULL)
	{
		strcpy(HCode[(unsigned char)p -> c], buffer); // 转换为正常的数字而不是使用假意转换
		return;
	}

	buffer[index] = '0';
	buffer[index + 1] = '\0';
	visitHTree(p -> left, buffer, index + 1);
	buffer[index] = '1';
	buffer[index + 1] = '\0';
	visitHTree(p -> right, buffer, index + 1);

}

void makeHCode()
{
	struct tnode *p;
	int index = 0;

	p = Root;

	char buffer[MAXSIZE] = {0};
	
	visitHTree(p, buffer, index);
} 





//【实验步骤3】结束

//【实验步骤4】开始
void atoHZIP()
{
	// 文件回到最开始
	rewind(Src);

	int c; int index = 0;

	unsigned char hc = 0;

	// 按字符来进行读取
	while ((c = fgetc(Src)) != EOF)
	{
		char *p;
		p = HCode[c];

		// if (c == '\n')
		// 	continue;

		for(int i = 0; p[i] != '\0'; i++) 
		{
			hc = (hc << 1) | (p[i]-'0');
			if((index + 1) % 8 == 0)
			{
				fputc(hc, Obj);     //输出到目标（压缩）文件中
				hc = 0; // 直接重置
				// printf("%x",hc); // 直接打印出来
			}
			index++;
		}
	}

	char *p = HCode[0];
	// 处理最后的结尾字符
	for(int i = 0; p[i] != '\0'; i++) 
	{
		hc = (hc << 1) | (p[i]-'0');
		if((index + 1) % 8 == 0)
		{
			// printf("%x",hc);//输出到目标（压缩）文件中
			fputc(hc, Obj); // 直接打印出来
			hc = 0;
		}
		index++;
	}

	// 处理最后不足八位的字符
	// 不是所有的都需要输入
	if (index % 8 != 0)
	{
		for ( ; index % 8 != 0; index++)
		{
			hc <<= 1;
		}
		fputc(hc, Obj); // 直接打印出来
		// printf("%x", hc);
	}
}

void printHCode()
{
    int count = 0;

    for (int i = 0; i < 128; i++)
        if (HCode[i][0] != '\0')
            count++;
    fputc(count, Obj);

    for (int i = 0; i < 128; i++)
    {
        char *p = HCode[i];

        if (p[0] != '\0')
        {
            int len = strlen(p);
            unsigned char hc = 0;
            int index = 0;

            fputc(i, Obj);
            fputc(len, Obj);

            for (int j = 0; j < len; j++)
            {
                hc = (hc << 1) | (p[j] - '0');
                index++;
                if (index % 8 == 0)
                {
                    fputc(hc, Obj);
                    hc = 0;
                }
            }

            if (index % 8 != 0)
            {
                hc <<= 8 - index % 8; // 左移补齐8位数字
                fputc(hc, Obj);
            }
        }
    }
}

int checkExt(char *filename, char *ext)
{
    char *p = strrchr(filename, '.');
    if (p == NULL)
        return 0;
    return strcmp(p, ext) == 0;
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
	int bit;
	char judge[MAXSIZE];
	int index = 0;

	while ((bit = get_next_bit(&type)) != -1)
	{
		judge[index++] = '0' + bit;
		judge[index] = '\0';

		for (int i = 0; i < 128; i++)
		{
			if (strcmp(HCode[i], judge) == 0)
			{
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
		if (fread(&type, 1, 1, Src) != 1)
			return -1;
		bits_left = 8;
	}
	bits_left--;

	return (*type >> bits_left) & 1;
}

//【实验步骤4】结束

// void print1()
// {
//     int i;
//     printf("NUL:1\n");
//     for(i=1; i<128; i++)
//         if(Ccount[i] > 0)
//             printf("%c:%d\n", i, Ccount[i]);
// }

// void print2(struct tnode *p)
// {
//     if(p != NULL){
//         if((p->left==NULL)&&(p->right==NULL)) 
//             switch(p->c){
//                 case 0: printf("NUL ");break;
//                 case ' ':  printf("SP ");break;
//                 case '\t': printf("TAB ");break;
//                 case '\n':  printf("CR ");break;
//                 default: printf("%c ",p->c); break;
//             }
//         print2(p->left);
//         print2(p->right);
//     }
// }

// void print3()
// {
//     int i;
    
//     for(i=0; i<128; i++){
//         if(HCode[i][0] != 0){
//             switch(i){
//                 case 0: printf("NUL:");break;
//                 case ' ':  printf("SP:");break;
//                 case '\t': printf("TAB:");break;
//                 case '\n':  printf("CR:");break;
//                 default: printf("%c:",i); break;
//             }
//             printf("%s\n",HCode[i]);
//         }
//     }
// } 

// void print4()
// {
//     long int in_size, out_size;
    
//     fseek(Src,0,SEEK_END);
//     fseek(Obj,0,SEEK_END);
//     in_size = ftell(Src);
//     out_size = ftell(Obj);
    
//     printf("\n原文件大小：%ldB\n",in_size);
//     printf("压缩后文件大小：%ldB\n",out_size);
//     printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
// }
