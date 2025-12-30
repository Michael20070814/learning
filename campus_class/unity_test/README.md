# 使用unity自动化调试软件

## 使用前准备

确保文件中链接了unity.h

确保程序中定义了setUp、tearDown函数

保证在main函数中，先使用UNITY_BEGIN初始化了测试引擎

记得运行测试函数

返回结果

实例：

```c
#include "src/unity.h"
#include <stdio.h>
#define CALC_ERROR -1

void setUp(void)// 测试开始前运行
{

}

void tearDown(void)// 测试用例结束后运行
{

}

void test_Example(void)// 测试用例
{
    int result = 1 + 1;
    TEST_ASSERT_EQUAL(2, result); // 断言
}

int main(void)
{
    UNITY_BEGIN(); // 初始化测试引擎
    RUN_TEST(test_Example); // 运行测试函数
    return UNITY_END(); // 结束并输出结果
}
```

## 编译说明

### 简化版

> gcc .\first_use.c src\unity.h -o first_use.exe

### 复杂版

目的：查看反馈文件

> gcc -fprofile-arcs -ftest-coverage .\first_use.c src\unity.c -o first_use.exe

在前面多加上几个后缀

## 运行说明

无特殊要求，正常运行即可

> ./first_use.exe

## 生成报告

> gcovr -r . --html-details -o report/index.html

使用gcovr生成可视化报告

最后的report是该项目下的文件夹，用于存放报告，可以自己更换

> mkdir report创建报告文件夹

之后点开index.html即可