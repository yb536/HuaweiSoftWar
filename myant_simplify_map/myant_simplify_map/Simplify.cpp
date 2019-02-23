#include "Simplify.h"
#include "readfile.h"
#include <iostream>
using namespace std;
//Inc_Cost g_Including_Cost[N_INCLUDING_COUNT+2][N_INCLUDING_COUNT+2];
Inc_Cost g_Including_Cost[50][50];
Simplify::Simplify(void)
{
}


Simplify::~Simplify(void)
{
}


void Simplify::InitSimp()
{
	//g_Including_Cost[N_INCLUDING_COUNT+2][N_INCLUDING_COUNT+2]
	for(int i=0;i<N_INCLUDING_COUNT+2;i++)
	{
		for(int j=0;j<N_INCLUDING_COUNT+2;j++)
		{
			g_Including_Cost[i][j].cost=-1;
			for(int k=0;k<N_POINT_COUNT;k++)
			{
				g_Including_Cost[i][j].m_nPath_No[k]=-1;
				g_Including_Cost[i][j].m_nPath_ID[k]=-1;
			}
		}
	}
	for(int i=0;i<N_POINT_COUNT;i++)
	{
		if(N_POINT_SELF_ID[i]==N_START_POINT_SELF_ID)
		{
			Start_NO=i;
			//break;
		}
		if(N_POINT_SELF_ID[i]==N_END_POINT_SELF_ID)
		{
			End_NO=i;
		}
		
	}
	Simplify_Success=false;
	Output_Flag=false;
	Input_Flag=false;
	

}


void Simplify::Search()
{

	InitSimp();
	
	while(Simplify_Success==false)
	{
		Start_Point_Search();
		Including_Point_Search();
		Simplify_Success=Simplify_Success_Or_Not();
		if(Simplify_Success==false)
		{
			printf("Simplify Map Fail!");
		}
		else
		{
			printf("Simplify Map Success!");
		}
	}
	
	cout<<endl;
	for(int i=0;i<N_INCLUDING_COUNT+2;i++)
	{
		for(int j=0;j<N_INCLUDING_COUNT+2;j++)
		{
			cout<<g_Including_Cost[i][j].cost<<"  ";
		}
		cout<<endl;
	}
	
	
}

bool Simplify::Simplify_Success_Or_Not()
{
	bool result=false;
	int num=0;
	if(Output_Flag==false)
	{
		for(int i=0;i<N_INCLUDING_COUNT+1;i++)
		{
			for(int j=0;j<N_INCLUDING_COUNT+2;j++)
			{
				if(g_Including_Cost[i][j].cost!=-1)
				{
					num++;
					break;
				}
			}
		}
		if(num==N_INCLUDING_COUNT+1)
		{
			Output_Flag=true;
		
		}
	}
	num=0;

	if(Input_Flag==false)
	{
		for(int i=1;i<N_INCLUDING_COUNT+2;i++)
		{
			for(int j=0;j<N_INCLUDING_COUNT+2;j++)
			{
				if(g_Including_Cost[j][i].cost!=-1)
				{
					num++;
					break;
				}
			}
		}
		if(num==N_INCLUDING_COUNT+1)
		{
			Input_Flag=true;
		
		}
	}
	if((Output_Flag)&&(Input_Flag))
	{
		result=true;
	}
	return result;
	
}


void Simplify::Start_Point_Search()
{
	for(int i=0;i<Simplify_Search_Ant_Count;i++)
	{
		Simp_Ant[i].m_nCurPointNo=Start_NO;
		//Simp_Ant[i].Simp_Flag=true;
		Simp_Ant[i].Simp_Search();
		Save_Start_Info(i);
	}
	
}

void Simplify::Save_Start_Info(int i_Ant)
{
	int column;
	for(int i=0;i<N_INCLUDING_COUNT;i++)
	{
		if(N_POINT_SELF_ID[Simp_Ant[i_Ant].m_nCurPointNo]==N_INCLUDING_SELF_ID[i])
		{
			column=i;
			break;
		}
	}
	if(N_POINT_SELF_ID[Simp_Ant[i_Ant].m_nCurPointNo]==N_END_POINT_SELF_ID)
	{
		column=N_INCLUDING_COUNT;
	}
	if((g_Including_Cost[0][column+1].cost==-1)||(g_Including_Cost[0][column+1].cost>=Simp_Ant[i_Ant].m_dbPathLength))
	{
		g_Including_Cost[0][column+1].cost=Simp_Ant[i_Ant].m_dbPathLength;
		memcpy(g_Including_Cost[0][column+1].m_nPath_ID,Simp_Ant[i_Ant].m_nPath_ID,sizeof(Simp_Ant[i_Ant].m_nPath_ID));
		memcpy(g_Including_Cost[0][column+1].m_nPath_No,Simp_Ant[i_Ant].m_nPath_No,sizeof(Simp_Ant[i_Ant].m_nPath_ID));
	}
	
	
}

void Simplify::Including_Point_Search()
{

	for(int i=0;i<N_INCLUDING_COUNT;i++)
	{
		for(int j=0;j<Simplify_Search_Ant_Count;j++)
		{
			Simp_Ant[j].m_nCurPointNo=N_INCLUDING_SELF_ID[i];
			//Simp_Ant[i].Simp_Flag=true;
			Simp_Ant[j].Simp_Search();							
			Save_Including_Info(i,j);
		}
	}
}

void Simplify::Save_Including_Info(int i_Including,int j_Ant)
{
	int column;
	for(int i=0;i<N_INCLUDING_COUNT;i++)
	{
		if(N_POINT_SELF_ID[Simp_Ant[j_Ant].m_nCurPointNo]==N_INCLUDING_SELF_ID[i])
		{
			column=i;
			break;
		}
	}
	if(N_POINT_SELF_ID[Simp_Ant[j_Ant].m_nCurPointNo]==N_END_POINT_SELF_ID)
	{
		column=N_INCLUDING_COUNT;
	}
	if((g_Including_Cost[i_Including+1][column+1].cost==-1)||(g_Including_Cost[i_Including+1][column+1].cost>=Simp_Ant[j_Ant].m_dbPathLength))
	{
		g_Including_Cost[i_Including+1][column+1].cost=Simp_Ant[j_Ant].m_dbPathLength;
		memcpy(g_Including_Cost[i_Including+1][column+1].m_nPath_ID,Simp_Ant[j_Ant].m_nPath_ID,sizeof(Simp_Ant[j_Ant].m_nPath_ID));
		memcpy(g_Including_Cost[i_Including+1][column+1].m_nPath_No,Simp_Ant[j_Ant].m_nPath_No,sizeof(Simp_Ant[j_Ant].m_nPath_No));
	}
	
	
}

