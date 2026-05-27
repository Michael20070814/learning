#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define MAXSIZE 2048
#define LENGTH 512
#define DIM 7

typedef struct vector
{
    double *data;
    int index;
} vector;

int ispunct_real(unsigned char c); // 判断某个字母是否是标点符号需要除去单引号
void process_document(); // 读取文档 进行文档预处理 划分为句子
int process_line(char *input, char vocab[LENGTH][LENGTH / 4]); // 进行句子预处理 划分为单词
void generate_dict(); // 进行字典全量生成
double calc_aver_len(char *input); // 计算语句所有有效单词的平均字符
double calc_variance(char *input); // 计算有效单词长度的总体样本方差
int calc_num(char *input); // 计算单词总数
double calc_vowel_ratio(char *input); // 计算元音比例
double calc_symbol_density(char *input); // 计算标点符号密度
double calc_upper_density(char *input); // 计算大写字母密度
double calc_num_ratio(char *input); // 计算数字密度
void load_stop_list(); // 载入停用词
int is_stop_list(char *input); // 判断是否是在停用词里面
vector *init_vector(int num); // 创建一个n维向量
void L2_vector(vector *input); // 对输入向量进行L2归一化
void min_max_vector(vector *input); // 对输入向量进行min-max归一化
double calc_cosin(vector input1, vector input2); // 计算余弦相似度
double calc_S_hybrid(vector semantic1, vector semantic2, vector structure1, vector structure2, double a); // 计算混合相似度
int *retreive_top_k(int k); // 检索取回前k个语句
void free_vector(vector *v); // 释放向量内存
int cmp_desc(const void *a, const void *b); // 给qsort用的比较函数，按similarity降序排列 值相同序号升序
vector *generate_semantice_vector(char *input); // 根据读入文本生成一个语义向量
vector *generate_structure_vector(char *input); // 根据读入文本生成一个结构性向量
void print(int num, int *result); // 打印输出

int line_num = 0; // 表示句子存储的位置、序号
char global[MAXSIZE][LENGTH]; // 存储全局句子
int dict_num = 0; // 表示字典中单词的数量
char dict[MAXSIZE][LENGTH / 4]; // 存储全局字典
char stop[MAXSIZE * 3][LENGTH / 4]; // 存储停用词
int similarity_num = 0;
double similarity[MAXSIZE]; // 存放语句之间的相似度

int main(void)
{
    process_document();
    load_stop_list();
    generate_dict();

    char input[MAXSIZE];
    double a;
    int k;

    fgets(input, MAXSIZE - 1, stdin); 
    scanf("%lf", &a); scanf("%d", &k); // 读取输入参数
    if (k < 0) k = 0;
    if (k > line_num) k = line_num;

    vector *semantic_input = generate_semantice_vector(input);
    vector *structure_input = generate_structure_vector(input);

    L2_vector(semantic_input);
    min_max_vector(structure_input);

    similarity_num = line_num;

    for (int i = 0; i < line_num; i++)
    {
        vector *semantic_retrieve = generate_semantice_vector(global[i]);
        vector *structure_retrieve = generate_structure_vector(global[i]);

        L2_vector(semantic_retrieve);
        min_max_vector(structure_retrieve);

        similarity[i] = calc_S_hybrid(*semantic_input, *semantic_retrieve, 
            *structure_input, *structure_retrieve, a);

        free_vector(semantic_retrieve);
        free_vector(structure_retrieve);
    }

    int *q = retreive_top_k(k);

    print(k, q);

    return 0;
}

int ispunct_real(unsigned char c)
{
    if (ispunct(c) && c != '\'')
        return 1;

    return 0;
}

void process_document(void)
{
    FILE *fp = fopen("document.txt", "r");

    if (fp == NULL) 
    {
        perror("Error opening document.txt");
        exit(EXIT_FAILURE);   /* 报错后退出，也可以按需求改为 return */
    }

    /* 获取文件大小 */
    fseek(fp, 0, SEEK_END);
    long fsize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    /* 分配缓冲区并读入整个文件内容 */
    char *buffer = (char *)malloc(fsize + 1);
    if (buffer == NULL) 
    {
        perror("Memory allocation failed");
        fclose(fp);
        exit(EXIT_FAILURE);
    }
    fread(buffer, 1, fsize, fp);
    buffer[fsize] = '\0';
    fclose(fp);

    const char *delimiters = ".?\n!";   /* 分隔符集合 */
    char *start = buffer;
    line_num = 0;

    while (*start && line_num < MAXSIZE) 
    {
        /* 寻找下一个分隔符的位置 */
        char *p = start;
        while (*p && strchr(delimiters, *p) == NULL) 
        {
            p++;
        }

        /* 如果找到分隔符，则将其包含在本段中 */
        if (*p && strchr(delimiters, *p) != NULL) 
        {
            size_t len = p - start + 1;          /* 包含分隔符的长度 */
            if (len >= LENGTH) len = LENGTH - 1; /* 防止溢出 */
            if (*start == ' ') start++;
            strncpy(global[line_num], start, len - 1);
            global[line_num][len] = '\0';
            start = p + 1;  /* 移到分隔符之后 */
        } 
        /* 没有遇到分隔符但还有剩余字符（文件末尾） */
        else if (*start) 
        {
            strncpy(global[line_num], start, LENGTH - 1); /* 会自动补\0 */
            global[line_num][LENGTH - 1] = '\0';
            start += strlen(start);  /* 结束循环 */
        } 
        else 
        {
            break;  /* 空字符串，退出 */
        }
        line_num++;
    }

    free(buffer);
}

int process_line(char *input, char vocab[LENGTH][LENGTH / 4]) 
{
    int vocab_count = 0;
    char word[LENGTH / 4];               // 暂存当前单词
    int wlen = 0;                        // 当前单词长度
    const int max_word_len = LENGTH / 4 - 1;

    for (char *p = input; ; ++p) 
    {
        unsigned char c = (unsigned char)*p;
        // 判断是否分隔符：空白 或 (非单引号的标点)
        int is_delim = (c == '\0') || isspace(c) || ispunct_real(c);

        if (is_delim) 
        {
            if (wlen > 0) // 单词结束
            {               
                word[wlen] = '\0';
                // 转为小写
                for (int i = 0; word[i] != '\0'; ++i) 
                {
                    word[i] = (char)tolower((unsigned char)word[i]);
                }
                // 非停用词则存入 vocab
                if (!is_stop_list(word)) 
                {
                    if (vocab_count < LENGTH) 
                    {
                        strncpy(vocab[vocab_count], word, max_word_len);
                        vocab[vocab_count][max_word_len] = '\0';
                        ++vocab_count;
                    }
                }
                wlen = 0;                 // 重置单词缓冲区
            }
            if (c == '\0') break;         // 字符串结束
        }
        else
        {
            // 非分隔符，累积字符（包括单引号）
            if (wlen < max_word_len)
            {
                word[wlen++] = (char)c;
            }
        }
    }

    return vocab_count;
}

void generate_dict() {
    int i, j;
    char vocab[LENGTH][LENGTH / 4];   // 暂存当前句子的单词

    for (i = 0; i < line_num; i++) {
        // 提取当前句子中的所有单词到 vocab
        int m = process_line(global[i], vocab);

        // 遍历 vocab 中的单词，直到遇到空字符串（假定 vocab 以空串结尾）
        for (j = 0; j < m; j++) {
            // 检查单词是否已在 dict 中
            int found = 0;
            for (int k = 0; k < dict_num; k++) {
                if (strcmp(dict[k], vocab[j]) == 0) {
                    found = 1;
                    break;
                }
            }

            // 若未重复且字典未满，则添加进字典
            if (!found && dict_num < LENGTH) {
                strcpy(dict[dict_num], vocab[j]);
                dict_num++;
            }
        }
    }
}

double calc_aver_len(char *input) 
{
    // 边界处理：空指针或空字符串
    if (input == NULL || *input == '\0') {
        return 0.0;
    }

    char vocab[LENGTH][LENGTH / 4];   // 存储有效单词
    int count = process_line(input, vocab);

    // 无有效单词
    if (count <= 0) {
        return 0.0;
    }

    // 统计所有单词的总字符数
    long total_len = 0;
    for (int i = 0; i < count; ++i) {
        total_len += strlen(vocab[i]);
    }

    return (double)total_len / count;
}

double calc_variance(char *input) {
    // 边界处理
    if (input == NULL || *input == '\0') {
        return 0.0;
    }

    char vocab[LENGTH][LENGTH / 4];
    int count = process_line(input, vocab);

    // 单词数不足2，方差为0
    if (count <= 1) {
        return 0.0;
    }

    // 第一步：计算平均长度
    long total_len = 0;
    for (int i = 0; i < count; ++i) {
        total_len += strlen(vocab[i]);
    }
    double mean = (double)total_len / count;

    // 第二步：累加差的平方
    double sum_sq_diff = 0.0;
    for (int i = 0; i < count; ++i) {
        double diff = strlen(vocab[i]) - mean;
        sum_sq_diff += diff * diff;   // 不使用 pow，提高效率
    }

    return sum_sq_diff / count;       // 总体方差
}

int calc_num(char *input) {
    if (input == NULL || *input == '\0') {
        return 0;
    }
    char vocab[LENGTH][LENGTH / 4];  // 提供存储数组（内容无需使用）
    return process_line(input, vocab);
}

double calc_vowel_ratio(char *input) {
    if (input == NULL || *input == '\0') {
        return 0.0;
    }

    char vocab[LENGTH][LENGTH / 4];
    int count = process_line(input, vocab);

    if (count <= 0) {
        return 0.0;
    }

    double total_ratio = 0.0;
    for (int i = 0; i < count; ++i) {
        int len = strlen(vocab[i]);
        int vowels = 0;
        for (int j = 0; j < len; ++j) 
        {
            char c = (unsigned char)vocab[i][j];
            if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') {
                vowels++;
            }
        }
        // 避免除零（process_line返回的有效单词长度应均大于0）
        double ratio = (len > 0) ? (double)vowels / len : 0.0;
        total_ratio += ratio;
    }

    return total_ratio / count;
}

double calc_symbol_density(char *input)
{
    if (input == NULL) {
        return 0.0;
    }

    int punct_count = 0;
    int valid_count = 0;

    for (const char *p = input; *p != '\0'; ++p) {
        unsigned char ch = (unsigned char)*p;  // 避免符号扩展导致未定义行为

        if (isspace(ch)) {
            continue;          // 跳过空白字符
        }

        valid_count++;         // 计入有效字符

        if (ispunct(ch)) {
            punct_count++;     // 计入标点符号
        }
    }

    if (valid_count == 0) {
        return 0.0;            // 没有有效字符时返回 0
    }

    return (double)punct_count / (double)valid_count;
}

double calc_upper_density(char *input) {
    if (input == NULL) {
        return 0.0;
    }

    int upper_count = 0;
    int valid_count = 0;

    for (const char *p = input; *p != '\0'; ++p) {
        unsigned char ch = (unsigned char)*p;

        if (isspace(ch)) {
            continue;
        }

        valid_count++;

        if (isupper(ch)) {
            upper_count++;
        }
    }

    if (valid_count == 0) {
        return 0.0;
    }

    return (double)upper_count / (double)valid_count;
}

double calc_num_ratio(char *input) {
    if (input == NULL) {
        return 0.0;
    }

    int digit_count = 0;
    int valid_count = 0;

    for (const char *p = input; *p != '\0'; ++p) {
        unsigned char ch = (unsigned char)*p;

        if (isspace(ch)) {
            continue;
        }

        valid_count++;

        if (isdigit(ch)) {
            digit_count++;
        }
    }

    if (valid_count == 0) {
        return 0.0;
    }

    return (double)digit_count / (double)valid_count;
}

void load_stop_list(void) {
    FILE *fp = fopen("stopList.txt", "r");
    if (fp == NULL) {
        /* 文件打开失败，将第一个元素置为空字符串以示空列表 */
        stop[0][0] = '\0';
        return;
    }

    char line[LENGTH / 4];  // 每行临时缓冲区，与 stop 每行容量一致
    int count = 0;
    int max_words = MAXSIZE * 3;

    // 逐行读取，直到文件结束或数组满
    while (count < max_words && fgets(line, sizeof(line), fp) != NULL) {
        // 去除末尾换行符（兼容 \n 和 \r\n）
        size_t len = strlen(line);
        while (len > 0 && (line[len - 1] == '\n' || line[len - 1] == '\r' || line[len - 1] == ' ')) {
            line[--len] = '\0';
        }

        // 跳过空行（可选，根据文件格式决定）
        if (len == 0) {
            continue;
        }

        // 存入全局数组
        strncpy(stop[count], line, LENGTH / 4 - 1);
        stop[count][LENGTH / 4 - 1] = '\0'; // 确保字符串终止
        count++;
    }

    // 如果数组未填满，将剩余位置置为空字符串
    while (count < max_words) {
        stop[count][0] = '\0';
        count++;
    }

    fclose(fp);
}

int is_stop_list(char *input) {
    if (input == NULL) {
        return 0;
    }

    // 计算有效单词个数（以第一个空字符串为结束标志）
    int n = 0;
    while (n < MAXSIZE * 3 && stop[n][0] != '\0') {
        n++;
    }

    if (n == 0) {
        return 0;   // 列表为空
    }

    // 二分查找（stop 已按 ASCII 升序排列）
    int low = 0, high = n - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        int cmp = strcmp(input, stop[mid]);
        if (cmp == 0) {
            return 1;   // 找到
        } else if (cmp < 0) {
            high = mid - 1;
        } else {
            low = mid + 1;
        }
    }

    return 0;   // 未找到
}

vector *init_vector(int num) {
    if (num <= 0) {
        return NULL;               // 无效维度
    }

    // 为 vector 结构体分配内存
    vector *v = (vector*)malloc(sizeof(vector));
    if (v == NULL) {
        return NULL;               // 结构体内存分配失败
    }

    // 为 double 数组分配内存
    v->data = (double*)malloc(num * sizeof(double));
    if (v->data == NULL) {
        free(v);                   // 释放已分配的结构体内存
        return NULL;               // 数组内存分配失败
    }

    // 初始化向量维度
    v->index = num;

    // 将向量所有元素初始化为 0.0（可选步骤，便于后续使用）
    for (int i = 0; i < num; ++i) {
        v->data[i] = 0.0;
    }

    return v;                      // 返回指向已初始化向量的指针
}

void free_vector(vector *v) {
    if (v != NULL) {
        free(v->data);
        free(v);
    }
}

void L2_vector(vector *input) {
    // 防御性检查：输入指针有效、data 非空、维度大于 0
    if (input == NULL || input->data == NULL || input->index <= 0) {
        return;
    }

    // 1. 计算平方和
    double sum_sq = 0.0;
    int n = input->index;
    for (int i = 0; i < n; ++i) {
        double val = input->data[i];
        sum_sq += val * val;
    }

    // 2. 计算 L2 范数
    double norm = sqrt(sum_sq);

    // 3. 避免除零：若范数接近 0（例如所有元素为 0），则不进行归一化
    const double eps = 1e-12;
    if (norm <= eps) {
        return;   // 范数为零，无法归一化
    }

    // 4. 每个分量除以范数
    for (int i = 0; i < n; ++i) {
        input->data[i] /= norm;
    }
}

void min_max_vector(vector *input) {
    // 防御性检查
    if (input == NULL || input->data == NULL || input->index <= 0) {
        return;
    }

    int n = input->index;
    double *data = input->data;

    // 1. 查找最小值和最大值
    double min_val = data[0];
    double max_val = data[0];
    for (int i = 1; i < n; ++i) {
        if (data[i] < min_val) {
            min_val = data[i];
        }
        if (data[i] > max_val) {
            max_val = data[i];
        }
    }

    // 2. 若最大值等于最小值，无法进行归一化，直接返回
    double range = max_val - min_val;
    const double eps = 1e-12;  // 极小阈值，避免浮点误差
    if (range <= eps) {
        return;   // 所有元素相等，归一化无意义
    }

    // 3. 执行 Min-Max 归一化
    for (int i = 0; i < n; ++i) {
        data[i] = (data[i] - min_val) / range;
    }
}

double calc_cosin(vector input1, vector input2) {
    // 检查维度是否一致，以及维度是否有效
    if (input1.index != input2.index || input1.index <= 0) {
        return 0.0;    // 非法情况，返回0.0
    }

    double dot_product = 0.0;
    double norm1_sq = 0.0;
    double norm2_sq = 0.0;
    int n = input1.index;

    // 一次遍历，计算点积和平方和
    for (int i = 0; i < n; ++i) {
        double a = input1.data[i];
        double b = input2.data[i];
        dot_product += a * b;
        norm1_sq += a * a;
        norm2_sq += b * b;
    }

    // 计算范数
    double norm1 = sqrt(norm1_sq);
    double norm2 = sqrt(norm2_sq);

    // 避免除零：若任一向量长度为0，余弦相似度无定义，返回0.0
    const double eps = 1e-12;
    if (norm1 <= eps || norm2 <= eps) {
        return 0.0;
    }

    // 返回余弦值
    return dot_product / (norm1 * norm2);
}

double calc_S_hybrid(vector semantic1, vector semantic2, 
                     vector structure1, vector structure2, double a) 
{
    // 分别计算两个余弦相似度
    double m = calc_cosin(semantic1, semantic2);
    double n = calc_cosin(structure1, structure2);
    
    // 按权重线性组合
    return a * m + (1.0 - a) * n;
}

int cmp_desc(const void *a, const void *b) {
    int idx1 = *(const int *)a;
    int idx2 = *(const int *)b;
    double v1 = similarity[idx1];
    double v2 = similarity[idx2];

    if (v1 > v2) return -1;   /* 更大的值排在前面 */
    if (v1 < v2) return 1;
    return idx1 - idx2;        /* 值相等时，序号小的排在前面 */
}

int *retreive_top_k(int k) {
    /* 参数检查 */
    if (k <= 0)
        return NULL;

    if (k > MAXSIZE)
        k = MAXSIZE;           /* 若需要的数量超过数组大小，则截断 */

    /* 构建索引数组 0 .. MAXSIZE-1 */
    int *indices = (int *)malloc(line_num * sizeof(int));
    if (!indices)
        return NULL;

    for (int i = 0; i < line_num; ++i)
        indices[i] = i;

    /* 按规则排序索引 */
    qsort(indices, line_num, sizeof(int), cmp_desc);

    /* 取出前 k 个序号 */
    int *result = (int *)malloc(k * sizeof(int));
    if (!result) {
        free(indices);
        return NULL;
    }

    for (int i = 0; i < k; ++i)
        result[i] = indices[i];

    free(indices);
    return result;
}

vector *generate_structure_vector(char *input)
{
    vector *structure_input = init_vector(DIM);

    structure_input -> data[0] = calc_aver_len(input);
    structure_input -> data[1] = calc_variance(input);
    structure_input -> data[2] = calc_num(input);
    structure_input -> data[3] = calc_vowel_ratio(input);
    structure_input -> data[4] = calc_symbol_density(input);
    structure_input -> data[5] = calc_upper_density(input);
    structure_input -> data[6] = calc_num_ratio(input);

    return structure_input;
}

vector *generate_semantice_vector(char *input)
{
    // 用于存放分割后的单词
    char vocab[LENGTH][LENGTH / 4];

    // 创建 dict_num 维的零向量
    vector *vec = init_vector(dict_num);
    if (vec == NULL) {
        return NULL;          // 如果内存分配失败，返回 NULL
    }

    // 分割输入字符串，获得单词列表
    int word_count = process_line(input, vocab);

    // 遍历每个单词
    for (int i = 0; i < word_count; i++) {
        // 在全局字典中查找该单词
        for (int j = 0; j < dict_num; j++) {
            if (strcmp(vocab[i], dict[j]) == 0) {
                vec->data[j] += 1.0;   // 出现次数加 1
                break;                 // 找到后跳出，继续处理下一个单词
            }
        }
    }

    return vec;
}

void print(int num, int *result)
{
    for (int i = 0; i < num; i++)
    {
        printf("%s\n", global[result[i]]);
    }
}
