// myant.cpp : �������̨Ӧ�ó������ڵ㡣
//

// AO.cpp : �������̨Ӧ�ó������ڵ㡣
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
    //�õ�ǰʱ����ʼ��������ӣ���ֹÿ�����еĽ������ͬ
    time_t tm;
	time(&tm);
	unsigned int nSeed=(unsigned int)tm;
	srand(nSeed);
	readfile("D:\\tcase\\case1\\topo.csv","D:\\tcase\\case1\\demand.csv");

    //��ʼ����
    CTsp tsp;

    tsp.InitData(); //��ʼ��
    tsp.Search(); //��ʼ����
	//����9
	if(tsp.m_cBestAnt.m_dbPathLength==0xFFFF)
	{
		printf("û���ҵ�����·��");
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
    //������

    

    printf("\n\nPress any key to exit!");
    getchar();

    return 0;
}



