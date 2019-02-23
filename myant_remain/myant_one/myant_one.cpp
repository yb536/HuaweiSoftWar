// myant.cpp : 定义控制台应用程序的入口点。
//

// AO.cpp : 定义控制台应用程序的入口点。
#pragma once

#include <iostream>
#include <math.h> 
#include <time.h>
#include "readfile.h"
#include "Ant.h"
#include "Tsp.h"

extern int readfile(const char * const filename1,const char * const filename2);



int main()
{
    //用当前时间点初始化随机种子，防止每次运行的结果都相同
    time_t tm;
	time(&tm);
	unsigned int nSeed=(unsigned int)tm;
	srand(nSeed);
	readfile("D:\\tcase\\case1\\topo.csv","D:\\tcase\\case1\\demand.csv");

    //开始搜索
    CTsp tsp;

    tsp.InitData(); //初始化
    tsp.Search(); //开始搜索
	//新增9
	if(tsp.m_cBestAnt.m_dbPathLength==0xFFFF)
	{
		printf("没有找到最优路径");
	}
	else
	{
		printf("\nThe best tour is :\n");

		char cBuf[128];
		for (int i=0;i<N_POINT_COUNT;i++)
		{
			if(tsp.m_cBestAnt.m_nPath[i]!=-1)
			{
				sprintf_s(cBuf,"%02d ",tsp.m_cBestAnt.m_nPath[i]);
			}
			else
			{
				break;
			}
        
			if (i % 20 == 0)
			{
				printf("\n");
			}
			printf(cBuf);
		}
	}
    //输出结果

    

    printf("\n\nPress any key to exit!");
    getchar();

    return 0;
}



