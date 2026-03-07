#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() 
{
    char line[1000];
    fgets(line, sizeof(line), stdin);
    
    // 去除'='及之后的内容
    for (int i = 0; line[i]; i++) 
    {
        if (line[i] == '=')
        {   
            line[i] = '\0';
            break; 
        }
    }
    
    int nums[500];
    char operator[500];
    int num_Top = 0, operator_Top = 0;
    
    int i = 0;
    int len = strlen(line);
    
    while (i < len) 
    {
        // 跳过空格
        if (isspace(line[i]))
        {
            i++; 
            continue;
        }
        
        // 读取数字
        if (isdigit(line[i]))
        {
            int num = 0;
            while (i < len && isdigit(line[i]))
            {
                num = num * 10 + (line[i] - '0');
                i++;
            }
            nums[num_Top++] = num;
            
            while (operator_Top > 0 && (operator[operator_Top-1] == '*' || operator[operator_Top-1] == '/'))
            {
                int b = nums[--num_Top];
                int a = nums[--num_Top];
                char op = operator[--operator_Top];
                if (op == '*') 
                    nums[num_Top++] = a * b;
                else           
                    nums[num_Top++] = a / b;
            }
        }
        // 读取运算符
        else if (line[i] == '+' || line[i] == '-' || line[i] == '*' || line[i] == '/')
        {
            operator[operator_Top++] = line[i];
            i++;
        }
        else 
        {
            i++;
        }
    }
    
    int result = nums[0];
    for (int j = 0; j < operator_Top; j++)
    {
        if (operator[j] == '+')
            result += nums[j+1];
        else               
            result -= nums[j+1];
    }
    
    printf("%d\n", result);
    return 0;
}