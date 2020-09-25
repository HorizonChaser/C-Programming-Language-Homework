/***************************************************
作业要求：
		求 k 阶斐波那契序列的第 m 项值的函数算法

完成日期：
		2013年9月3日
***************************************************/
#include <stdio.h>
#include <stdlib.h>

// 函数原型
int fibnocci_1(int m, int k);
int fibnocci_2(int m, int k);
int fibnocci_3(int m, int k);

// main函数
int main(void)
{
	// 求3阶fibnocci数列第8项的值
	// 0 0 1 1 2 4 7 13 24 ……
	printf("%d\n", fibnocci_1(25, 6));
	printf("%d\n", fibnocci_2(25, 6));
	printf("%d\n", fibnocci_3(8, 3));

	return 0;
}

/****************************************************
函数功能：
		求k阶fibnocci数列的第m项值
算法思想：
		(1) 根据m和k的值，先返回特殊情况下的值；
		(2) 首先初始化前k项值；
		(3) 按照公式求第k+1项至第m项的值。
函数参数：
		int		m		待求fibnocci数列项数
		int		k		fibnocci数列的阶数
返回值：
		返回k阶fibnocci数列第m项的值
时间复杂度：
		O(m * k)：双重循环（外层为m-k，内层为k）
空间复杂度：
		O(m)：	开辟的辅助存储空间总共有m+3个（f、i、j、result）
*****************************************************/
int fibnocci_1(int m, int k)
{
	int i, j, result;
	int *f;				// 辅助数组空间
	// 特殊情况
	if (m < k-1)
	{
		return 0;
	}
	else if (m == k-1 || m == k)
	{
		return 1;
	}

	// 一般情况

	// 动态内存分配辅助空间
	f = (int *) malloc(sizeof(int) * (m+1));

	// 初始化前k项的值
	for (i = 0; i < k-1; ++i)
	{
		f[i] = 0;
	}
	f[k-1] = f[k] = 1;

	// 求第m项值
	for (i = k+1; i <= m; ++i)
	{
		f[i] = 0;
		for (j = 1; j <= k; ++j)
		{
			f[i] += f[i - j];
		}
	}
	result = f[m];

	// 释放辅助空间
	free(f);

	return result;
}

/****************************************************
函数功能：
		求k阶fibnocci数列的第m项值
算法思想：
		(1) 根据m和k的值，先返回特殊情况下的值；
		(2) 首先初始化前k项值；
		(3) 按照公式求第k+1项至第m项的值（借助数学运算简化求解）。
函数参数：
		int		m		待求fibnocci数列项数
		int		k		fibnocci数列的阶数
返回值：
		返回k阶fibnocci数列第m项的值
时间复杂度：
		O(m)：	计算第m项时，借助数学公式取消内层循环
空间复杂度：
		O(m)：	开辟的辅助存储空间总共有m+3个（f、i、j、result）
*****************************************************/
int fibnocci_2(int m, int k)
{
	int i, j, result;
	int *f;				// 辅助数组空间
	// 特殊情况
	if (m < k-1)
	{
		return 0;
	}
	else if (m == k-1 || m == k)
	{
		return 1;
	}

	// 一般情况

	// 动态内存分配辅助空间
	f = (int *) malloc(sizeof(int) * (m+1));

	// 初始化前k项的值
	for (i = 0; i < k-1; ++i)
	{
		f[i] = 0;
	}
	f[k-1] = f[k] = 1;

	// 求第m项值
	for (i = k+1; i <= m; ++i)
	{
		// 按照数学公式计算
		f[i] = 2 * f[i - 1] - f[i - k - 1];
	}
	result = f[m];

	// 释放辅助空间
	free(f);

	return result;
}

/****************************************************
函数功能：
		求k阶fibnocci数列的第m项值
算法思想：
		递归求解。
函数参数：
		int		m		待求fibnocci数列项数
		int		k		fibnocci数列的阶数
返回值：
		返回k阶fibnocci数列第m项的值
时间复杂度：
		O(k^m)：	由递归式：f(m) = k * f(m-1)，
		则f(m) = k * k * f(m-2)，以此类推可得，
		f(m) = k^m
空间复杂度：
		O(m * k)：	每一次递归调用过程中需要求得其前k项的值，
		共需递归调用m次，故总共的辅助空间约为 m * k个。
*****************************************************/
int fibnocci_3(int m, int k)
{
	int i, result = 0;
	if (m < k - 1)
	{
		return 0;
	}
	else if (m == k - 1 || m == k)
	{
		return 1;
	}
	else
	{
		for (i = 1; i <= k; ++i)
		{
			result += fibnocci_3(m - i, k);
		}
		return result;
	}
}