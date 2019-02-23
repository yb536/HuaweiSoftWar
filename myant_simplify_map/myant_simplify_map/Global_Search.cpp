#include "Global_Search.h"
#include "Simplify.h"
#include "readfile.h"

extern Inc_Cost g_Including_Cost[50][50];
Global_Path Glo_Path[30000];
Global_Search::Global_Search(void)
{
}


Global_Search::~Global_Search(void)
{
}



void Global_Search::Init()
{
	CurPointNo=0;
	MovedPointCount=1;
	Path_Num=1;
	BestPathLength=0xFFFF;
	//BestPath=-1;
	Death_Flag=false;
	Good_Path=true;
	for(int j=0;j<N_POINT_COUNT;j++)
	{
		BestPath[j]=-1;
	}
	/*
	for(int i=0;i<300000;i++)
	{
		for(int j=0;j<N_INCLUDING_COUNT+2;j++)
		{
			Glo_Path[i].Path_ID[j]=-1;
			Glo_Path[i].Path_No[j]=-1;
			//Glo_Path[i].All_Path_ID[j]=-1;
			Glo_Path[i].AllowedPoint[j]=1;
		}
		
		Glo_Path[i].Succ_Flag=true;
		//Glo_Path[i].Good_Path=true;
		//Glo_Path[i].AllowedPoint[0]=0;
		//Glo_Path[i].Path_ID[0]=N_START_POINT_SELF_ID;
		//Glo_Path[i].Path_No[0]=0;
	}
	*/
	for(int j=0;j<N_INCLUDING_COUNT+2;j++)
	{
		Glo_Path[0].Path_ID[j]=-1;
		Glo_Path[0].Path_No[j]=-1;
		//Glo_Path[i].All_Path_ID[j]=-1;
		Glo_Path[0].AllowedPoint[j]=1;
	}
	Glo_Path[0].Succ_Flag=true;
	Glo_Path[0].AllowedPoint[0]=0;
	Glo_Path[0].AllowedPoint[N_INCLUDING_COUNT+1]=0;
	Glo_Path[0].Path_ID[0]=N_START_POINT_SELF_ID;
	Glo_Path[0].Path_No[0]=0;
	
	for(int i=0;i<N_INCLUDING_COUNT+2;i++)
	{
		for(int j=0;j<N_INCLUDING_COUNT+2;j++)
		{
			if(g_Including_Cost[i][j].cost>40)
			{
				g_Including_Cost[i][j].cost=-1;
			}
		}
		
	}
	
}


void Global_Search::Search()
{
	int num=0;
	Init();
	char cBuf[256]; //打印信息用
	while(MovedPointCount<N_INCLUDING_COUNT+2)
	{
		
		Move();
		
	}
	
	for(int i=0;i<Path_Num;i++)
	{
		if(Glo_Path[i].Succ_Flag)
		{
			CalPathLength(i);
			sprintf_s(cBuf,"\n[%d] %.0f",num+1,BestPathLength);
			printf(cBuf);
			num++;
		}

		
		
		

	}

	printf("\nPath_Num is  %d",Path_Num);	
	printf("\nNum of Good Path is  %d",num);	
	
	printf("\nThe best tour is :\n\n");
	if(BestPathLength==0xFFFF)
	{
		printf("NA");
	}
	else
	{
		for (int i=0;i<N_POINT_COUNT;i++)
		{
			if(BestPath[i]!=-1)
			{
				sprintf(cBuf,"%d ",BestPath[i]);
				printf(cBuf);
			}
			else
			{
				break;
			}
		}
	}
		
	

	


	
}

void Global_Search::Move()
{
	if(Path_Num>50000)
	{
		Path_Num=10000;

	}
	int Last_Path_Num=Path_Num;
	
	bool First_Next;
	for(int i=0;i<Last_Path_Num;i++)
	{
		if(Path_Num>280000)
		{
			break;
		}
		First_Next=true;
		if(Glo_Path[i].Succ_Flag)
		{
			if(MovedPointCount==N_INCLUDING_COUNT+1)
			{
				Glo_Path[i].AllowedPoint[N_INCLUDING_COUNT+1]=1;
			}
		
			for(int j=0;j<N_INCLUDING_COUNT+2;j++)
			{
				if(Glo_Path[i].Path_No[j]==-1)
				{
					CurPointNo=Glo_Path[i].Path_No[j-1];
					break;
				}
			
			}


			memcpy(Temp_Path_No,Glo_Path[i].Path_No,sizeof(Temp_Path_No));
			memcpy(Temp_Path_ID,Glo_Path[i].Path_ID,sizeof(Temp_Path_ID));
			memcpy(Temp_AllowedPoint,Glo_Path[i].AllowedPoint,sizeof(Temp_AllowedPoint));


			for(int j=0;j<N_INCLUDING_COUNT+2;j++)
			{
				if((g_Including_Cost[CurPointNo][j].cost!=-1)&&(Temp_AllowedPoint[j]==1))
				{
					Death_Flag=false;
					if(j!=N_INCLUDING_COUNT+1)
					{
						Death_Flag=Next_Death_Path_Or_Not(j);
					}
					if(Death_Flag==false)
					{
						Good_Path=true;
						if(j==N_INCLUDING_COUNT+1)
						{
							Good_Path=Last_Good_Path_Or_Not(j);
						}
						else
						{
							Good_Path=Next_Good_Path_Or_Not(j);
						}
						
						if(Good_Path)
						{
							if(First_Next)
							{
								Glo_Path[i].Path_No[MovedPointCount]=j;
								Glo_Path[i].Path_ID[MovedPointCount]=N_INCLUDING_SELF_ID[j-1]; 
								Glo_Path[i].AllowedPoint[j]=0;
								Glo_Path[i].Succ_Flag=true;
								First_Next=false;
							}
							else
							{
								for(int r=0;r<Path_Num;r++)
								{
									if(Glo_Path[r].Succ_Flag==false)
									{
										memcpy(Glo_Path[r].Path_ID,Temp_Path_ID,sizeof(Temp_Path_ID));
										memcpy(Glo_Path[r].Path_No,Temp_Path_No,sizeof(Temp_Path_No));
										memcpy(Glo_Path[r].AllowedPoint,Temp_AllowedPoint,sizeof(Temp_AllowedPoint));
										Glo_Path[r].Path_No[MovedPointCount]=j;
										Glo_Path[r].Path_ID[MovedPointCount]=N_INCLUDING_SELF_ID[j-1];
										Glo_Path[r].AllowedPoint[j]=0;
										Glo_Path[r].Succ_Flag=true;
										break;
									}
									if(r==Path_Num-1)
									{
										memcpy(Glo_Path[Path_Num].Path_ID,Temp_Path_ID,sizeof(Temp_Path_ID));
										memcpy(Glo_Path[Path_Num].Path_No,Temp_Path_No,sizeof(Temp_Path_No));
										memcpy(Glo_Path[Path_Num].AllowedPoint,Temp_AllowedPoint,sizeof(Temp_AllowedPoint));
										Glo_Path[Path_Num].Path_No[MovedPointCount]=j;
										Glo_Path[Path_Num].Path_ID[MovedPointCount]=N_INCLUDING_SELF_ID[j-1];
										Glo_Path[Path_Num].AllowedPoint[j]=0;
										Glo_Path[Path_Num].Succ_Flag=true;
										Path_Num++;
										break;
									}
								}
								

							}
						}
					}
				
				}
			}
			
		}
		if(First_Next)
		{
			Glo_Path[i].Succ_Flag=false;	
		}
		
	}
	MovedPointCount++;
}

bool Global_Search::Last_Good_Path_Or_Not(int next_no)
{
	int m=0;
	bool result=true;
	int Path_No[300];
	int All_Path_ID[300];
	bool flag=false;
	memcpy(Path_No,Temp_Path_No,sizeof(Path_No));
	Path_No[MovedPointCount]=next_no;
	for(int i=1;i<=MovedPointCount;i++)
	{
		for(int j=0;j<N_POINT_COUNT;j++)
		{
			if(g_Including_Cost[Path_No[i-1]][Path_No[i]].m_nPath_ID[j]!=-1)
			{
				All_Path_ID[m]=g_Including_Cost[Path_No[i-1]][Path_No[i]].m_nPath_ID[j];
				m++;
			}
			else
			{
				break;
			}
		}
		m--;
		All_Path_ID[m]=-1;
	}
	if(MovedPointCount==N_INCLUDING_COUNT+1)
	{
		All_Path_ID[m]=N_END_POINT_SELF_ID;
	}
	else
	{
		All_Path_ID[m]=N_INCLUDING_SELF_ID[next_no-1];
	}
	

	for(int i=0;i<m;i++)
	{ 
		for(int j=i+1;j<m+1;j++)
		{
			if(All_Path_ID[i]==All_Path_ID[j])
			{
				result=false;
				break; 
			}
		}
	}

	return result;
}

bool Global_Search::Next_Good_Path_Or_Not(int next_no)
{
	int m=0;
	bool result=true;
	int Path_No[300];
	int All_Path_ID[300];
	int AllowedPoint[300];

	memcpy(AllowedPoint,Temp_AllowedPoint,sizeof(AllowedPoint));
	AllowedPoint[next_no]=0;
	if(MovedPointCount==N_INCLUDING_COUNT)
	{
		AllowedPoint[N_INCLUDING_COUNT+1]=1;
	}
	bool flag=true;
	memcpy(Path_No,Temp_Path_No,sizeof(Path_No));
	Path_No[MovedPointCount]=next_no;
	for(int i=0;i<N_INCLUDING_COUNT+2;i++)
	{

		if((g_Including_Cost[next_no][i].cost!=-1)&&(AllowedPoint[i]==1)&&(flag))
		{
			flag=false;
			Path_No[MovedPointCount+1]=i;
			m=0;
			for(int j=1;j<=MovedPointCount+1;j++)
			{
				for(int k=0;k<N_POINT_COUNT;k++)
				{
					if(g_Including_Cost[Path_No[j-1]][Path_No[j]].m_nPath_ID[k]!=-1)
					{
						All_Path_ID[m]=g_Including_Cost[Path_No[j-1]][Path_No[j]].m_nPath_ID[k];
						m++;
					}
					else
					{
						break;
					}
				}
				m--;
				All_Path_ID[m]=-1;
			}

			if(MovedPointCount==N_INCLUDING_COUNT)
			{
				All_Path_ID[m]=N_END_POINT_SELF_ID;
			}
			else
			{
				All_Path_ID[m]=N_INCLUDING_SELF_ID[i-1];
			}
			for(int n=0;n<m;n++)
			{ 
				for(int j=n+1;j<m+1;j++)
				{
					if(All_Path_ID[n]==All_Path_ID[j])
					{
						flag=true;
						break; 
					}
				}
			}
		}
		
	}
	if(flag)
	{
		result=false;
	}
	

	return result;
}
/*
void Global_Search::Good_Path_Or_Not(int path_n)
{

	int m=0;
	
	for(int i=1;i<N_INCLUDING_COUNT+2;i++)
	{
		for(int j=0;j<N_POINT_COUNT;j++)
		{
			if(g_Including_Cost[Glo_Path[path_n].Path_No[i-1]][Glo_Path[path_n].Path_No[i]].m_nPath_ID[j]!=-1)
			{
				Glo_Path[path_n].All_Path_ID[m]=g_Including_Cost[Glo_Path[path_n].Path_No[i-1]][Glo_Path[path_n].Path_No[i]].m_nPath_ID[j];
				m++;
			}
			else
			{
				break;
			}
		}
		m--;
		Glo_Path[path_n].All_Path_ID[m]=-1;
	}
	Glo_Path[path_n].All_Path_ID[m]=N_END_POINT_SELF_ID;

	for(int i=0;i<m;i++)
	{ 
		for(int j=i+1;j<m+1;j++)
		{
			if(Glo_Path[path_n].All_Path_ID[i]==Glo_Path[path_n].All_Path_ID[j])
			{
				Glo_Path[path_n].Good_Path=false;
				break; 
			}
		}
	}

}

*/
void Global_Search::CalPathLength(int path_n)
{
	double m_dbPathLength=0.0; //先把路径长度置0
    int m=0;
    int n=0;

	for (int i=1;i<N_INCLUDING_COUNT+2;i++)
    {
		if(Glo_Path[path_n].Path_No[i]!=-1)
		{
			m=Glo_Path[path_n].Path_No[i];
			n=Glo_Path[path_n].Path_No[i-1];
			m_dbPathLength=m_dbPathLength+g_Including_Cost[n][m].cost;	
		}
    }
	if(m_dbPathLength<BestPathLength)
	{
		BestPathLength=m_dbPathLength;
		Get_Best_Path(path_n);
		//BestPath=path_n;
	}
}

bool Global_Search::Next_Death_Path_Or_Not(int next_no)
{
	bool result=false;
	int AllowedPoint[300];
	bool flag=false;
	memcpy(AllowedPoint,Temp_AllowedPoint,sizeof(AllowedPoint));
	AllowedPoint[next_no]=0;
	if(MovedPointCount==N_INCLUDING_COUNT)
	{
		AllowedPoint[N_INCLUDING_COUNT+1]=1;
	}
	for(int i=0;i<N_INCLUDING_COUNT+2;i++)
	{
		if((g_Including_Cost[next_no][i].cost!=-1)&&(AllowedPoint[i]==1))
		{
			flag=true;
			break;
		}
		
	}
	if(flag==false)
	{
		result=true;
	}
	return result;
}


void Global_Search::Get_Best_Path(int path_n)
{
	int m=0;
	for(int i=0;i<N_POINT_COUNT;i++)
	{
		BestPath[i]=-1;
	}
	for(int i=1;i<N_INCLUDING_COUNT+2;i++)
	{
		for(int j=0;j<N_POINT_COUNT;j++)
		{
			if(g_Including_Cost[Glo_Path[path_n].Path_No[i-1]][Glo_Path[path_n].Path_No[i]].m_nPath_ID[j]!=-1)
			{
				BestPath[m]=g_Including_Cost[Glo_Path[path_n].Path_No[i-1]][Glo_Path[path_n].Path_No[i]].m_nPath_ID[j];
				m++;
			}
			else
			{
				break;
			}
		}
		m--;
		BestPath[m]=-1;
	}
	BestPath[m]=N_END_POINT_SELF_ID;
}
