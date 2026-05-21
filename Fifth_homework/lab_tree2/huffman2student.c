#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 32

struct tnode 
{            //Huffman树结构
    char c;        
    int weight;        //树节点权重，叶节点为字符和它的出现次数
    struct tnode *left,*right;
} ; 
int Ccount[128]={0};        //存放每个字符的出现次数，如Ccount[i]表示ASCII值为i的字符出现次数 
struct tnode *Root=NULL;     //Huffman树的根节点
char HCode[128][MAXSIZE]={{0}}; //字符的Huffman编码，如HCode['a']为字符a的Huffman编码（字符串形式） 
int Step=0;            //实验步骤 
FILE *Src, *Obj;
    
void statCount();        //步骤1：统计文件中字符频率
void createHTree();        //步骤2：创建一个Huffman树，根节点为Root 
void makeHCode();        //步骤3：根据Huffman树生成Huffman编码
void atoHZIP();         //步骤4：根据Huffman编码将指定ASCII码文本文件转换成Huffman码文件
void makeTree(struct tnode *list[128], struct tnode *list2[128], int *index); // 把两个进行合并
int getNum(struct tnode *list[128]); // 获取元素数量
void visitHTree(struct tnode *p, char *buffer, int index); // 前序遍历根节点为Root的树

void print1();            //输出步骤1的结果
void print2(struct tnode *p);    //输出步骤2的结果 
void print3();            //输出步骤3的结果
void print4();            //输出步骤4的结果

int main()
{
	if((Src = fopen("input.txt","r"))==NULL) 
	{
		fprintf(stderr, "%s open failed!\n", "input.txt");
	return 1; 
    }

    if((Obj = fopen("output.txt","w"))==NULL) 
	{
        fprintf(stderr, "%s open failed!\n", "output.txt");
        return 1;
    }
    scanf("%d",&Step);        //输入当前实验步骤 
    
    statCount();            //实验步骤1：统计文件中字符出现次数（频率）
    (Step==1) ? print1() : 1;       //输出实验步骤1结果    
    createHTree();            //实验步骤2：依据字符频率生成相应的Huffman树
    (Step==2) ? print2(Root) : 2;     //输出实验步骤2结果    
    makeHCode();        //实验步骤3：依据Root为树的根的Huffman树生成相应Huffman编码
    (Step==3) ? print3() : 3;       //输出实验步骤3结果
    (Step>=4) ? atoHZIP(),print4() : 4;//实验步骤4：据Huffman编码生成压缩文件，并输出实验步骤4结果    

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

// 获取当前时刻树林的数目
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

// 合并两个树叶
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
}

//【实验步骤2】结束

//【实验步骤3】开始
void makeHCode()
{
	struct tnode *p;
	int index = 0;

	p = Root;

	char buffer[MAXSIZE] = {0};
	
	visitHTree(p, buffer, index);
} 

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
		strcpy(HCode[p -> c], buffer);
		return;
	}

	buffer[index] = '0';
	buffer[index + 1] = '\0';
	visitHTree(p -> left, buffer, index + 1);
	buffer[index] = '1';
	buffer[index + 1] = '\0';
	visitHTree(p -> right, buffer, index + 1);
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

		if (c == '\n')
			continue;

		for(int i = 0; p[i] != '\0'; i++) 
		{
			hc = (hc << 1) | (p[i]-'0');
			if((index + 1) % 8 == 0)
			{
				fputc(hc, Obj);     //输出到目标（压缩）文件中
				printf("%x",hc);
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
			printf("%x",hc);//输出到目标（压缩）文件中
			fputc(hc, Obj);     
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
		fputc(hc, Obj);
		printf("%x", hc);
	}
}

//【实验步骤4】结束

void print1()
{
    int i;
    printf("NUL:1\n");
    for(i=1; i<128; i++)
        if(Ccount[i] > 0)
            printf("%c:%d\n", i, Ccount[i]);
}

void print2(struct tnode *p)
{
    if(p != NULL){
        if((p->left==NULL)&&(p->right==NULL)) 
            switch(p->c){
                case 0: printf("NUL ");break;
                case ' ':  printf("SP ");break;
                case '\t': printf("TAB ");break;
                case '\n':  printf("CR ");break;
                default: printf("%c ",p->c); break;
            }
        print2(p->left);
        print2(p->right);
    }
}

void print3()
{
    int i;
    
    for(i=0; i<128; i++)
	{
        if(HCode[i][0] != 0)
		{
            switch(i)
			{
                case 0: printf("NUL:");break;
                case ' ':  printf("SP:");break;
                case '\t': printf("TAB:");break;
                case '\n':  printf("CR:");break;
                default: printf("%c:",i); break;
            }
            printf("%s\n",HCode[i]);
        }
    }
} 

void print4()
{
    long int in_size, out_size;
    
    fseek(Src,0,SEEK_END);
    fseek(Obj,0,SEEK_END);
    in_size = ftell(Src);
    out_size = ftell(Obj);
    
    printf("\n原文件大小：%ldB\n", in_size);
    printf("压缩后文件大小：%ldB\n", out_size);
    printf("压缩率：%.2f%%\n",(float)(in_size-out_size)*100/in_size);
}
