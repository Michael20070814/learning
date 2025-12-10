// calc.h
#ifndef CALC_H // 头文件守卫，防止重复包含
#define CALC_H

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

/* calc_math */
#define M_PI acos(-1)
/**
 * @brief 返回x的绝对值
 * @param x 输入数值
 * @return double x的绝对值
 * @note 如果x是负数，返回其相反数；否则直接返回x
 */
double ABS(double x);

/**
 * @brief 计算x的y次幂
 * @param x 底数
 * @param y 指数
 * @return double x的y次幂结果
 * @note 当 x 小于 0 时 , y的绝对值不能小于1
 */
double POWER(double x, double y);

/**
 * @brief 计算x的平方根
 * @param x 输入数值（必须为非负数）
 * @return double x的平方根
 * @note 如果x为负数，将返回-1
 */
double SQRT(double x);

/**
 * @brief 返回a对b取模结果
 * @param a 被除数
 * @param b 除数
 * @return int a除以b的余数
 * @note 标准的C语言截断取余。若b为0，则返回-1
 */
int MOD(int a, int b);

/**
 * @brief 返回a对b取模结果
 * @param a 被除数
 * @param b 除数
 * @return int a除以b的余数
 * @note 这是基于地板除法的模运算（Modulo）
 */
int FMOD(int a, int b);


/**
 * @brief 计算二维点间距离
 * @param x1 第一个点的x坐标
 * @param y1 第一个点的y坐标
 * @param x2 第二个点的x坐标
 * @param y2 第二个点的y坐标
 * @return double 两点之间的欧几里得距离
 * @see EUCLIDEAN_DISTANCE
 */
double DISTANCE(double x1, double y1, double x2, double y2);
/**
 * @brief 计算n维向量距离
 * @param arr1 第一个向量数组
 * @param arr2 第二个向量数组
 * @param n 向量维度
 * @return double 两个n维向量之间的欧几里得距离
 * @pre arr1和arr2必须至少有n个元素
 * @see DISTANCE
 */
double EUCLIDEAN_DISTANCE(double arr1[], double arr2[], int n);

/**
 * @brief 计算加权和
 * @param arr 数值数组
 * @param weights 权重数组
 * @param n 数组长度
 * @return double 加权和结果
 * @pre arr和weights必须至少有n个元素
 */
double WEIGHTED_SUM(double arr[], double weights[], int n);

/**
 * @brief 数组每元素先取模再取幂
 * @param arr 输入数组
 * @param n 数组长度
 * @param m 模数
 * @return double* 新分配的数组指针，包含每个元素先取模m再取m次幂的结果
 * @note 调用者负责释放返回的数组内存
 * @retval NULL 内存分配失败
 */
double* CYCLE_POWER(double arr[], int n, int m);
/**
 * @brief 将数字向下舍入到最接近的整数
 * @param x 输入数值
 * @return double 向下舍入后的整数
 * @see CEILING, FLOOR
 */
int INT(double x);

/**
 * @brief 返回0和1之间的随机数
 * @return double [0,1)范围内的随机浮点数
 * @note 使用标准库rand()函数，使用前需调用srand()设置种子
 */
double RAND();

/**
 * @brief 返回指定范围内的随机整数
 * @param bottom 范围下限（包含）
 * @param top 范围上限（包含）
 * @return int [bottom, top]范围内的随机整数
 * @note 使用标准库rand()函数，使用前需调用srand()设置种子
 */
int RANDBETWEEN(int bottom, int top);
/**
 * @brief 返回参数的乘积
 * @param numbers 数值数组
 * @param count 数组元素个数
 * @return double 所有元素的乘积
 * @pre count必须大于0
 */
double PRODUCT(double numbers[], int count);
/**
 * @brief CEILING.MATH 函数的 C 语言实现
 * @param number 要舍入的数字
 * @param significance 舍入基数（可选，默认为1）
 * @param mode 负数舍入模式（可选，默认为0）
 * @return double 舍入后的数字
 * @details 
 * - 正数：总是向上舍入到最接近的 significance 倍数
 * - 负数（mode=0）：向绝对值更大的方向舍入（更负）
 * - 负数（mode=1）：向零方向舍入（更接近零）
 * @see CEILING
 */
double CEILING(double number, double significance, int mode);


/**
 * @brief 向下舍入到指定倍数
 * @param number 要舍入的数字
 * @param significance 舍入基数,正数
 * @param mode 负数舍入模式（可选，默认为0）
 * @return double 舍入后的数字
 * @details 
 * - 正数：总是向下舍入到最接近的 significance 倍数
 * - 负数（mode=0）：向绝对值更大的方向舍入（更负）
 * - 负数（mode=1）：向零方向舍入（更接近零）
 * @note 如果significance为0，直接返回number
 * @see FLOOR
 */
double FLOOR(double number, double significance, int mode);
/**
 * @brief 返回除法的整数部分
 * @param numerator 分子
 * @param denominator 分母
 * @return int 除法的整数部分
 * @warning 如果分母为0，返回0
 */
int QUOTIENT(double numerator, double denominator);

/**
 * @brief 返回圆周率π的值
 * @return double 圆周率π的近似值
 */
double PI();

/**
 * @brief 返回给定角度的正弦值
 * @param angle 角度（弧度）
 * @return double 正弦值
 * @see COS, TAN
 */
double SIN(double angle);

/**
 * @brief 返回数字的余弦值
 * @param angle 角度（弧度）
 * @return double 余弦值
 * @see SIN, TAN
 */
double COS(double angle);
/**
 * @brief 返回数字的正切值
 * @param angle 角度（弧度）
 * @return double 正切值
 * @warning 当角度为π/2 + kπ时，结果可能为无穷大
 * @see SIN, COS
 */
double TAN(double angle);

/**
 * @brief 将弧度转换为度
 * @param radians 弧度值
 * @return double 角度值
 * @see RADIANS
 */
double DEGREES(double radians);

/**
 * @brief 将度转换为弧度
 * @param degrees 角度值
 * @return double 弧度值
 * @see DEGREES
 */
double RADIANS(double degrees);


//************************************************************************************************************* */
//************************************************************************************************************* */
//************************************************************************************************************* */
//************************************************************************************************************* */
/*stat */
// 条件函数指针类型定义
typedef int (*condition_func)(double);
/**
 * @brief 求数组元素和
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 数组所有元素的和
 */
double SUM(double arr[], int n);
/**
 * @brief 求满足条件元素和
 * @param arr 数值数组
 * @param n 数组长度
 * @param condition 条件判断函数
 * @return double 满足条件的元素之和
 */
double SUM_IF(double arr[], int n, condition_func condition);
/**
 * @brief 升序冒泡排序算法
 * @param arr 要排序的数组
 * @param n 数组长度
 * @note 此函数会直接修改原数组
 */
void BUBBLE_SORT(double arr[], int n);
/**
 * @brief 冒泡排序算法
 * @param arr 要排序的数组
 * @param n 数组长度
 * @note 此函数会直接修改原数组
 */
void BUBBLE_SORT_FLOAT(float arr[], int n);
/**
 * @brief 去掉最大最小 k 个元素求平均
 * @param arr 数值数组
 * @param n 数组长度
 * @param k 要修剪的极值个数
 * @return double 修剪后的平b均值
 * @note 修剪掉最大和最小的k个元素后计算剩余元素的平均值
 */
double TRIMMED_MEAN(double arr[], int n, int k);

/**
 * @brief 计算参数列表中数字的个数
 * @param arr 数值数组
 * @param n 数组长度
 * @return int 数组中元素的个数
 * @note 此函数简单返回数组长度，实际应统计有效数值个数
 */
int COUNT(double arr[], int n); 

/**
 * @brief 返回其参数的平均值
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 数组元素的算术平均值
 * @pre n > 0
 */
double AVERAGE(double arr[], int n);

/**
 * @brief 返回区域中满足给定条件的所有单元格的平均值
 * @param arr 数值数组
 * @param n 数组长度
 * @param condition 条件判断函数
 * @return double 满足条件的元素的平均值
 */
double AVERAGEIF(double arr[], int n, condition_func condition);

/**
 * @brief 计算区域内符合给定条件的单元格的数量
 * @param arr 数值数组
 * @param n 数组长度
 * @param condition 条件判断函数
 * @return int 满足条件的元素个数
 */
int COUNTIF(double arr[], int n, condition_func condition);

/**
 * @brief 返回参数列表中的最大值
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 数组中的最大值
 * @pre n > 0
 */
double MAX(double arr[], int n);

/**
 * @brief 返回参数列表中的最小值
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 数组中的最小值
 * @pre n > 0
 */
double MIN(double arr[], int n);

/**
 * @brief 计算区域内符合多个条件的单元格的数量
 * @param arr 数值数组
 * @param n 数组长度
 * @param conditions 条件判断函数数组
 * @param condition_count 条件个数
 * @return int 满足所有条件的元素个数
 * @note 简化实现，实际Excel中每个条件可针对不同范围
 */
int COUNTIFS(double arr[], int n, condition_func conditions[], int condition_count);

/**
 * @brief 返回给定数值集合的中值
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 数组的中位数
 */
double MEDIAN(double arr[], int n);

/**
 * @brief 基于样本估算标准偏差
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 样本标准偏差
 * @see STDEV_P
 */
double STDEV_S(double arr[], int n);
/**
 * @brief 基于样本估算标准偏差
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 样本标准偏差
 * @see STDEV_P
 */
float STDEV_S_FLOAT(float arr[], int n);
/**
 * @brief 基于整个样本总体计算标准偏差
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 总体标准偏差
 * @see STDEV_S
 */
double STDEV_P(double arr[], int n);

/**
 * @brief 基于样本估算方差
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 样本方差
 * @see VAR_P
 */
double VAR_S(double arr[], int n);

/**
 * @brief 计算基于样本总体的方差
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 总体方差
 * @see VAR_S
 */
double VAR_P(double arr[], int n);

/**
 * @brief 返回一个数字的数字排位
 * @param number 要排位的数字
 * @param arr 参考数组
 * @param n 数组长度
 * @param order 排序方式（0-降序，1-升序）
 * @return int 数字在数组中的排位
 */
int RANK_EQ(double number, double arr[], int n, int order);

/**
 * @brief 返回数据集中第 k 个最大值
 * @param arr 数值数组
 * @param n 数组长度
 * @param k 要返回的排名（1表示最大值）
 * @param type 数组数据类型，0表示int型数组，1表示double型数组
 * @return double 第k个最大值
 * @note 0< k <= n,若k不在范围内,则返回-1.0
 */
double LARGE(void* arr, int n, int k,int type);

/**
 * @brief 返回数据集中的第 k 个最小值
 * @param arr 数值数组
 * @param n 数组长度
 * @param k 要返回的排名（1表示最小值）
 * @param type 数组数据类型
 * @return double 第k个最小值
 * @pre k > 0 && k <= n
 */
double SMALL(double arr[], int n, int k);

/**
 * @brief 返回在数据集内出现次数最多的值
 * @param arr 数值数组
 * @param n 数组长度
 * @return double 众数
 */
double MODE_SNGL(double arr[], int n);

/**
 * @brief 返回区域中数值的第 k 个百分点的值
 * @param arr 数值数组
 * @param n 数组长度
 * @param k 百分点值（0-1之间）
 * @return double 第k个百分点的值
 */
double PERCENTILE_INC(double arr[], int n, double k);

/**
 * @brief 返回一组数据的四分位点
 * @param arr 数值数组
 * @param n 数组长度
 * @param quart 四分位数（0-最小值，1-第一四分位数，2-中位数，3-第三四分位数，4-最大值）
 * @return double 指定的四分位点值
 */
double QUARTILE_INC(double arr[], int n, int quart);

/**
 * @brief 返回两个数据集之间的相关系数
 * @param array1 第一个数据集数组
 * @param array2 第二个数据集数组
 * @param n 数组长度（两个数组必须等长）
 * @return double 相关系数（-1到1之间）
 * @pre n > 0, array1和array2不能为NULL
 * @note 使用Pearson相关系数公式
 */
double CORREL(double array1[], double array2[], int n);

//************************************************************************************************************* */
//************************************************************************************************************* */
//************************************************************************************************************* */
//************************************************************************************************************* */
// calc_text 

/**
 * @brief 返回字符串长度
 * @test  status:True
 * @param text
 * @return int 
 */
int LEN(char* text);

/**
 * @brief   转换为大写
 * @test    status:True
 * @param   text 
 * @return  char* 
 */
char* UPPER(char* text);

/**
 * @brief   转换为小写
 * @test    status:True
 * @param   text 
 * @return  char* 
 */
char* LOWER(char* text);

/**
 * @brief   去除前后空格
 * @test    status:True
 * @param   text 
 * @return  char* 
 */
char* TRIM(char* text);

/**
 * @brief   返回左n个字符
 * @test    status:True
 * @param   text
 * @param   n 
 * @return  char* 
 */
char* LEFT(char* text, int n);

/**
 * @brief   返回右n个字符 
 * @test    status:True
 * @param   text 
 * @param   n 
 * @return  char* 
 */
char* RIGHT(char* text, int n);

/**
 * @brief   拼接字符串
 * @test    status:True
 * @param   a 
 * @param   b
 * @return  char* 
 */
char* CONCAT(char* a, char* b);

/**
 * @brief   返回子串
 * @test    status:True
 * @param   text 
 * @param   start
 * @param   len
 * @return  char* 
 */
char* MIDDLE(char* text, int start, int len);

/**
 * @brief   重复字符串n次
 * @test    status:True
 * @param   text
 * @param   n 
 * @return  char* 
 */
char* REPEAT(char* text, int n);

/**
 * @brief   提取符合模式的子串
 * @test    status:True ---------------?但是这么写对吗
 * @param   text
 * @param   pattern 
 * @return  char* 
 */
char* EXTRACT(char* text, char* pattern);

/**
 * @brief   拼接并去空格
 * @test    status:True
 * @param   strings 需要被拼接去掉空格的元素
 * @param   n 字符串的长度
 * @param   delimiter 拼接后元素间的分隔符 
 * @return  char* 
 */
char* JOIN_AND_TRIM(char** strings, int n, char* delimiter);

/**
 * @brief   拼接不重复字符串
 * @test    status:false-----------------------?
 * @param   text 
 * @return  char* 
 */
char* CONCAT_UNIQUE(char** strings, int n);

/**
 * @brief   去掉符合正则的字符
 * @test    status:false
 * @param   text 
 * @return  char* 
 */
char* TRIM_REGEX(char* text, char* pattern);

//************************************************************************************************************* */
//************************************************************************************************************* */
//************************************************************************************************************* */
//************************************************************************************************************* */
//time_date

/**
 * @brief 判断是否为闰年
 * @param year 年份
 * @return int 闰年返回1，否则返回0
 */
int is_leap_year(int year);/*  */

/**
 * @brief 获取月份的天数
 * @param year 年份
 * @param month 月份（1-12）
 * @return int 该月的天数
 */
int days_in_month(int year, int month);

/**
 * @brief 返回特定日期的连续序列号
 * @param year 年份（1900-9999）
 * @param month 月份（1-12）
 * @param day 日（1-31）
 * @return double 日期序列号
 * @note Excel日期序列号从1900-01-01开始
 */
double DATE(int year, int month, int day); //

/**
 * @brief 计算两个日期之间的天数、月数或年数
 * @param start_date 开始日期序列号
 * @param end_date 结束日期序列号
 * @param unit 单位代码（"Y"-年，"M"-月，"D"-天）
 * @return double 时间差
 */
double DATEDIF(double start_date, double end_date, const char* unit);//

/**
 * @brief 将文本格式的日期转换为序列号
 * @param date_text 日期文本（格式：YYYY-MM-DD）
 * @return double 日期序列号
 */
double DATEVALUE(const char* date_text);//

/**
 * @brief 返回某日期的天数（1-31）
 * @param serial_number 日期序列号
 * @return int 天数
 * @note 使用精确的日期计算算法，不进行简化
 */
int DAY(double serial_number);//

/**
 * @brief 返回两个日期之间的天数
 * @param end_date 结束日期序列号
 * @param start_date 开始日期序列号
 * @return double 天数差
 */
double DAYS(double end_date, double start_date);//

// double DAYS360(double start_date, double end_date, int method);

// double EDATE(double start_date, int months);

// double EOMONTH(double start_date, int months);

/**
 * @brief 返回时间值的小时数（0-23）
 * @param serial_number 时间序列号
 * @return int 小时数
 */
int HOUR(double serial_number);//

/**
 * @brief 返回给定日期的 ISO 周数
 * @param date 日期序列号
 * @return int ISO周数
 */
int ISOWEEKNUM(double date);//

/**
 * @brief 返回时间值的分钟数（0-59）
 * @param serial_number 时间序列号
 * @return int 分钟数
 */
int MINUTE(double serial_number);//

/**
 * @brief 返回日期的月份（1-12）
 * @param serial_number 日期序列号
 * @return int 月份
 */
int MONTH(double serial_number);//

/**
 * @brief 返回两个日期之间的完整工作日的天数
 * @param start_date 开始日期序列号
 * @param end_date 结束日期序列号
 * @param holidays 假日数组（可选）
 * @param holiday_count 假日数量
 * @return double 工作日天数
 */
double NETWORKDAYS(double start_date, double end_date, double holidays[], int holiday_count);//

/**
 * @brief 返回当前日期和时间的序列号
 * @return double 当前日期时间序列号
 */
double NOW();//

/**
 * @brief 返回时间值的秒数（0-59）
 * @param serial_number 时间序列号
 * @return int 秒数
 */
int SECOND(double serial_number);//

/**
 * @brief 返回特定时间的序列号
 * @param hour 小时（0-23）
 * @param minute 分钟（0-59）
 * @param second 秒（0-59）
 * @return double 时间序列号（小数部分）
 */
double TIME(int hour, int minute, int second);//

/**
 * @brief 将文本格式的时间转换为序列号
 * @param time_text 时间文本（格式：HH:MM:SS）
 * @return double 时间序列号
 */
double TIMEVALUE(const char* time_text);//

/**
 * @brief 返回当前日期的序列号
 * @return double 当前日期序列号
 */
double TODAY();//

/**
 * @brief 返回某日期为星期几
 * @param serial_number 日期序列号
 * @return int 星期几
 */
int WEEKDAY(double serial_number);//

/**
 * @brief 返回一年中的周数
 * @param serial_number 日期序列号
 * @param return_type 返回类型（1=周日开始，2=周一开始）
 * @return int 周数
 */
int WEEKNUM(double serial_number);//

// double WORKDAY(double start_date, int days, double holidays[], int holiday_count);

/**
 * @brief 返回日期的年份
 * @param serial_number 日期序列号
 * @return int 年份
 */
int YEAR(double serial_number);//

/**
 * @brief 返回两个日期之间的天数占全年天数的比例
 * @param start_date 开始日期序列号
 * @param end_date 结束日期序列号
 * @return double 年份比例
 */
double YEARFRAC(double start_date, double end_date);//

#endif