#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define SIZE 1024

typedef struct ExprNode
{
    char token[32];
    struct ExprNode *left;
    struct ExprNode *right;
} ExprNode;

char *infix_to_postfix(const char *infix); // 中缀表达式转换为后缀表达式
ExprNode *expr_build_from_postfix(const char *postfix); // 从后缀表达式中构建表达式
int calc_from_expr(ExprNode *root); // 从表达树中计算算式的值
void print(ExprNode *root); // 打印表达式的根的值以及左右子节点的值
int is_operator(char c); // 判断c是否是一个计算式
int is_op_token(char *s); // 判断字符串中是否有运算符号
ExprNode *expr_new(const char *token); // 创建一个表达式的节点
int get_num(const char *p); // 返回数字的长度

int main(void)
{
    char buffer[SIZE];

    // test0
    // int a = is_operator('+');
    // int b = is_operator('-');
    // int c = is_operator('*');
    // int d = is_operator('/');
    // int e = is_operator('1');
    // int f = is_operator('f');

    // test0.5
    // int a = get_num("123");
    // int b = get_num("2345");

    // test1
    // char *p = infix_to_postfix("24 / ( 1 + 2 + 36 / 6 / 2 - 2) * ( 12 / 2 / 2 ) =");

    // test2
    // char *p = infix_to_postfix("12 + 65 * 64");
    // ExprNode *root = expr_build_from_postfix("");

    // test3
    // fgets(buffer, SIZE - 1, stdin);
    // char *p = infix_to_postfix(buffer);
    // printf("%s", p);

    fgets(buffer, SIZE - 1, stdin); // 读入文字

    char *p = infix_to_postfix(buffer);
    ExprNode *root = expr_build_from_postfix(p);

    int result = calc_from_expr(root);
    print(root);
    printf("\n%d", result);

    return 0;
}

char *infix_to_postfix(const char *infix)
{
    char operator[SIZE];
    char *result = (char *)malloc(sizeof(char) * SIZE);
    int index = 0; int iter = 0;
    int top = -1;

    while (infix[iter] != '=')
    {
        if (is_operator(infix[iter]))
        {
            // infix[iter]是当前运算符
            while (top > -1 && ((infix[iter] == '+' || infix[iter] == '-') 
            || ((infix[iter] == '*' || infix[iter] == '/') && 
            (operator[top] == '*' || operator[top] == '/'))) && operator[top] != '(')
            {
                char c = operator[top--];
                result[index++] = c;
                result[index++] = ' ';
            }
            operator[++top] = infix[iter];
        }
        else if (infix[iter] == '(')
        {
            operator[++top] = infix[iter];
        }
        else if (infix[iter] == ')')
        {
            do
            {
                char c = operator[top--];
                result[index++] = c;
                result[index++] = ' ';
            } while (operator[top] != '(');

            top--; // 弹出左括号
        }
        else if (isdigit(infix[iter]))
        {
            int temp = get_num(&infix[iter]);

            for (int i = 0; i < temp; i++)
                result[index++] = infix[iter++];

            result[index++] = ' '; // 保持空格

            iter--; // 本身自然会往后进位，所以进位减少一格 这里因为有空格所以可去掉
        }
        iter++;
    }

    while (top != -1)
    {
        if (operator[top] == '(')
        {
            top--;
            continue;
        }
        result[index++] = operator[top--];
        result[index++] = ' ';
    }

    result[index] = '\0';

    return result;
}

int is_operator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return 1;
    return 0;
}

int get_num(const char *p)
{
    int result = 0;
    int times = 0;
    while (isdigit(*p))
    {
        p++;
        result = result * 10 + *p - '0';
        times++;
    }

    return times;
}

ExprNode *expr_build_from_postfix(const char *postfix)
{
    char buf[512];
    snprintf(buf, sizeof(buf), "%s", postfix);
    ExprNode *stack[128];

    int top = -1;
    char *tok = strtok(buf, " \t\n");
    while (tok)
    {
        ExprNode *node = expr_new(tok);
        if (is_op_token(tok))
        {
            if (top < 1)
            {
                fprintf(stderr, "bad postfix expression\n");
                return NULL;
            }
            node -> right = stack[top--];
            node -> left = stack[top--];
        }
        stack[++top] = node;
        tok = strtok(NULL, " \t\n");
    }

    return stack[top];
}

int calc_from_expr(ExprNode *root)
{
    if (root == NULL)
        return 0;
    if (is_op_token(root -> token) == 0)
        return strtol(root -> token, NULL, 10);

    int a = calc_from_expr(root -> left);
    int b = calc_from_expr(root -> right);

    switch (root -> token[0])
    {
        case '+':
        return a + b;
        case '-':
        return a - b;
        case '*':
        return a * b;
        case '/':
        return a / b;
        default: 
        return 0;
    }
}

void print(ExprNode *root)
{
    printf("%s %s %s\n", root -> token, root -> left -> token, root -> right -> token);
}

ExprNode *expr_new(const char *token)
{
    ExprNode *p = (ExprNode *)calloc(1, sizeof(ExprNode));

    if (p == NULL)
        return NULL;

    snprintf(p -> token, sizeof(p -> token), "%s", token);
    return p;
}

int is_op_token(char *s)
{
    return strlen(s) == 1 && strchr("+-*/", s[0]) != NULL;
}