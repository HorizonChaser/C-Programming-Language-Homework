//Windows系统下time()，clock()，timeGetTime()，GetTickCount()，QueryPerformanceCounter()来计时 by MoreWindows
#include <stdio.h>
#include <windows.h>
#include <time.h> //time_t time()  clock_t clock()
#include <Mmsystem.h>             //timeGetTime()
#pragma comment(lib, "Winmm.lib")   //timeGetTime()
 
int main()
{

	//用QueryPerformanceCounter()来计时  微秒
	LARGE_INTEGER  large_interger;
	double dff;
	__int64  c1, c2;
	QueryPerformanceFrequency(&large_interger);
	dff = large_interger.QuadPart;
	QueryPerformanceCounter(&large_interger);
	c1 = large_interger.QuadPart;
	Sleep(800);
	QueryPerformanceCounter(&large_interger);
	c2 = large_interger.QuadPart;
	printf("本机高精度计时器频率%lf\n", dff);
	printf("第一次计时器值%I64d 第二次计时器值%I64d 计时器差%I64d\n", c1, c2, c2 - c1);
	printf("计时%lf毫秒\n", (c2 - c1) * 1000 / dff);
	
	printf("By MoreWindows\n");
	return 0;
}