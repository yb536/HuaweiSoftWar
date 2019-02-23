#pragma once

#include "stdafx.h"
//#include "Common.h"
#include "Tsp.h"
#include "Simplify.h"
#include "readfile.h"
#include "Global_Search.h"
extern int readfile(const char * const filename1,const char * const filename2);
int main()
{
	//��ʼ���������
	time_t tm;
	time(&tm);
	unsigned int nSeed=(unsigned int)tm;
	srand(nSeed);
	readfile("D:\\tcase\\case4\\topo.csv","D:\\tcase\\case4\\demand.csv");
	//��ʼ����
	//CTsp tsp;
	Simplify simp;
	Global_Search glo;
	simp.Search();
	glo.Search();
	//tsp.Search();
	/*
	//������
	printf("\nThe best tour is :\n\n");

	char cBuf[128];
	for (int i=0;i<N_POINT_COUNT;i++)
	{
		sprintf(cBuf,"%d ",tsp.m_cBestAnt.m_nPath[i]+1);
		printf(cBuf);
	}

	sprintf(cBuf,"\n\nThe rand seed is : %d ",nSeed);
	printf(cBuf);

	printf("\n\nPress any key to exit!");
	getchar();
	*/
	
	return 0;
}

