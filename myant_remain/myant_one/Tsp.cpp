
#include "stdafx.h"
#include "Tsp.h"
#include "Ant.h"
#include "readfile.h"

//g_Trial_I g_Trial_Init_Struct[300000];

CTsp::CTsp(void)
{
}

CTsp::~CTsp(void)
{
}


//初始化数据
void CTsp::InitData() 
{
	//int Remained=Including_Trial;
    //先把最优蚂蚁的路径长度设置成一个很大的值
	
    m_cBestAnt.m_dbPathLength=0xFFFF; 
	for(int i=0;i<N_ANT_COUNT;i++)
	{
		Most_Including_Num_Ant[i].Path_Including_Num=0;
	}
	
	int temp;
	
    //计算两两城市间距离
	/*
    double dbTemp=0.0;
    for (int i=0;i<N_POINT_COUNT;i++)
    {
        for (int j=0;j<N_POINT_COUNT;j++)
        {
            dbTemp=(x_Ary[i]-x_Ary[j])*(x_Ary[i]-x_Ary[j])+(y_Ary[i]-y_Ary[j])*(y_Ary[i]-y_Ary[j]);
            dbTemp=pow(dbTemp,0.5);
            g_Cost[i][j]=ROUND(dbTemp);
        }
    }
	*/

    //初始化环境信息素，先把城市间的信息素设置成一样
    //这里设置成1.0，设置成多少对结果影响不是太大，对算法收敛速度有些影响
    for (int i=0;i<N_POINT_COUNT;i++)
    {
        for (int j=0;j<N_POINT_COUNT;j++)
        {
			g_Trial_Init[i][j]=0.0;
			if(g_Cost[i][j]!=-1)
			{
				g_Trial[i][j]=1.0;
				//g_Cost_One[i][j]=1.0;
			}
			else
			{
				g_Trial[i][j]=0.0;
				//g_Cost_One[i][j]=-1;
			}
            
        }
    }
	
	for(int i=0;i<N_INCLUDING_COUNT;i++)
	{
		for(int j=0;j<N_POINT_COUNT;j++)
		{
			if(N_INCLUDING_SELF_ID[i]==N_POINT_SELF_ID[j])
			{
				Including_NO[i]=j;
			}
		}
	}
	for(int i=0;i<N_POINT_COUNT;i++)
	{
		for(int j=0;j<i;j++)
		{
			temp=g_Cost[i][j];
			g_Cost[i][j]=g_Cost[j][i];
			g_Cost[j][i]=temp;
		}
	}
	Trial_Init();

	for(int i=0;i<N_POINT_COUNT;i++)
	{
		for(int j=0;j<i;j++)
		{
			temp=g_Cost[i][j];
			g_Cost[i][j]=g_Cost[j][i];
			g_Cost[j][i]=temp;
		}
	}
	Trial_Init();
	
}

void CTsp::Trial_Init()
{
	for(int i=0;i<N_INCLUDING_COUNT;i++)
	{
		Return_remainFlag = false;
		Return_whileFlag = false;
		Return_DiGuiFlag = false;
		Back_Flag = false;
		Present_Node_Num = 0;
		remained = Including_Trial_Max;
		//leaving[600];
		//present_node[600];
		//last_node;
		remain(Including_NO[i]);
	}
}

int CTsp::remain(int current_node)
{
        leaving[Present_Node_Num] = remained;
        //remained = leaving[j]-g_cost[current_node][i];
        //cout<<"the leaving value of current node is: "<<remained<<endl;
        present_node[Present_Node_Num] = current_node;
        for (int m=0;m<Present_Node_Num;m++)
        {
			g_Trial_Init[present_node[Present_Node_Num-1]][current_node] += 1/(double)g_Cost[present_node[m]][present_node[m+1]] ;
        }
		Present_Node_Num++;
        //DiGui_num++;
       // cout<<"present node is: "<<present_node[Present_Node_Num-1]<<endl;
        //cout<<"current node is: "<<current_node<<endl;
        for (int i=0;i<N_POINT_COUNT;i++)
        {
            Return_remainFlag = false;
            while (remained >= 0 && Return_remainFlag != true)
            {
                //cout<<"current remained value is: "<<remained<<endl;
                if ( g_Cost[current_node][i] != -1 && g_Cost[current_node][i] <= remained)
                {
					
						current_node = i;
                        Back_Flag = true;
                        //DiGui_num++;
                        remained = leaving[Present_Node_Num-1] - g_Cost[present_node[Present_Node_Num-1]][i];
						
                        Return_DiGuiFlag = remain(current_node);
                        if (Return_DiGuiFlag)
                        {
                            //DiGui_num--;
                            Return_DiGuiFlag = false;
                            //current_node = present_node[DiGui_num-1];
                            current_node = present_node[Present_Node_Num-1];
                        }                        
						if (i ==N_POINT_COUNT-1)
							last_node = i;
                }
                else if ( g_Cost[current_node][i] == -1 || g_Cost[current_node][i] > remained)
                {                   
                    if (i != N_POINT_COUNT-1)
                    {
                        Return_whileFlag = true;
                    }
                    else if (i == N_POINT_COUNT-1 )
                    {
                        Return_whileFlag = false;
                        Return_remainFlag = true;
                        if (Back_Flag == true)
                        {                            
                            //remained = adding[j-1] + g_cost[present_node[j-1]][current_node];
                            //cout<<"adding remained value is: "<<remained<<endl;
							present_node[Present_Node_Num-1] = -1;
                            leaving[Present_Node_Num-1] = -1;
							Present_Node_Num--;
                            current_node = present_node[Present_Node_Num-1];
							remained = leaving[Present_Node_Num-1];
							
                            
							//remained = -1;
                            //cout<<"Back node is: "<<current_node<<endl;
                            //DiGui_num--;
                            //DiGui_num++;
                        }
                        
                        if (Return_remainFlag == true)
                        {
                            return true ;
                        }
                            
                    }  
                }
                //
               if (Return_whileFlag == true)
                    break;
            }
        }
		if (last_node == N_POINT_COUNT-1)
		{
			if (Back_Flag == true)
            {                            
				present_node[Present_Node_Num-1] = -1;
                leaving[Present_Node_Num-1] = -1;
				Present_Node_Num--;
                current_node = present_node[Present_Node_Num-1];
				remained = leaving[Present_Node_Num-1];
                //cout<<"Back node is: "<<current_node<<endl;
            }
		}
    
}

/*
void CTsp::Trial_Init()
{
	int Path_Num=0;
	int Last_Path_Num=0;
	int Temp_Path_No[600];
	int Temp_Remained;
	int Temp_CurPointNo;
	int MovedPointCount=1;
	bool First_Next;
	bool finish_flag=false;
	for(int i=0;i<N_INCLUDING_COUNT;i++)
	{
		for(int j=0;j<N_POINT_COUNT;j++)
		{
			g_Trial_Init_Struct[0].Path_No[j]=-1;
		}
		g_Trial_Init_Struct[0].Path_No[0]=Including_NO[i];
		g_Trial_Init_Struct[0].Remained=Including_Trial;
		g_Trial_Init_Struct[0].stop_flag=false;
		g_Trial_Init_Struct[0].CurPointNo=Including_NO[i];
		Path_Num=1;
		MovedPointCount=1;
		finish_flag=false;
		while(finish_flag==false)
		{
			Last_Path_Num=Path_Num;
			for(int j=0;j<Last_Path_Num;j++)
			{
				First_Next=true;
				if(g_Trial_Init_Struct[j].stop_flag==false)
				{

					memcpy(Temp_Path_No,g_Trial_Init_Struct[j].Path_No,sizeof(Temp_Path_No));
					Temp_Remained=g_Trial_Init_Struct[j].Remained;
					Temp_CurPointNo=g_Trial_Init_Struct[j].CurPointNo;

					for(int k=0;k<N_POINT_COUNT;k++)
					{
						if((g_Cost[Temp_CurPointNo][k]!=-1)&&(g_Cost[Temp_CurPointNo][k]<=Temp_Remained))
						{
							if(First_Next)
							{
								g_Trial_Init_Struct[j].Path_No[MovedPointCount]=k;
								g_Trial_Init_Struct[j].Remained=Temp_Remained-g_Cost[Temp_CurPointNo][k];
								g_Trial_Init_Struct[j].CurPointNo=k;
								First_Next=false;
							}
							else
							{
								memcpy(g_Trial_Init_Struct[Path_Num].Path_No,Temp_Path_No,sizeof(Temp_Path_No));
								g_Trial_Init_Struct[Path_Num].Path_No[MovedPointCount]=k;
								g_Trial_Init_Struct[Path_Num].Remained=Temp_Remained-g_Cost[Temp_CurPointNo][k];
								g_Trial_Init_Struct[Path_Num].CurPointNo=k;
								g_Trial_Init_Struct[Path_Num].stop_flag=false;
								Path_Num++;
							 }
							g_Trial_Init[Temp_CurPointNo][k]+=1/(double)g_Cost[Temp_CurPointNo][k];
						}
					}
			
				}
				if(First_Next)
				{
					g_Trial_Init_Struct[j].stop_flag=true;	
				}
			}
			MovedPointCount++;
			for(int j=0;j<Last_Path_Num;j++)
			{
				if(g_Trial_Init_Struct[j].stop_flag==false)
				{
					break;
				}
				if(j==Last_Path_Num-1)
				{
					finish_flag=true;
				}
			}
		}
	}
}
*/
/*
int CTsp::remain(int current_node)
{
    int remained = Including_Trial;
	int num;
    while (remained >= 0)
    {
		for(int i=0;i<N_POINT_COUNT;i++)
		{
			if((g_Cost[current_node][i]!=-1)&&(g_Cost[current_node][i] < remained))
			{
				remained = remained - g_Cost[current_node][i];
                current_node = i;
                remain(current_node);
			}
		}
            
    }
}
*/
//更新环境信息素
void CTsp::UpdateTrial()
{
    //临时数组，保存各只蚂蚁在两两城市间新留下的信息素
    double dbTempAry[600][600];
    memset(dbTempAry,0,sizeof(dbTempAry)); //先全部设置为0

    //计算新增加的信息素,保存到临时数组里
    int m=0;
    int n=0;
	int num=1;
	bool First_Ant=true;
	//int Path_num=0;
	/*
	for(int i=0;i<N_POINT_COUNT;i++)
	{
		for(int j=0;j<N_POINT_COUNT;j++)
		{
			dbTempAry[i][j]=0.0;
		}
	}
	*/

    for (int i=0;i<N_ANT_COUNT;i++) //计算每只蚂蚁留下的信息素
    {
		if(m_cAntAry[i].Death_Flag==false)
		{
			
			for (int j=1;j<m_cAntAry[i].m_nMovedPointCount;j++)
			{
				m=m_cAntAry[i].m_nPath_No[j];
				n=m_cAntAry[i].m_nPath_No[j-1];
				g_Trial[n][m]=g_Trial[n][m]*(1-ROU*((double)N_INCLUDING_COUNT-(double)m_cAntAry[i].Path_Including_Num)/(double)N_INCLUDING_COUNT);
				//g_Trial[n][m]=g_Trial[n][m]*(m_cAntAry[i].Path_Including_Num)/N_INCLUDING_COUNT;
				//dbTempAry[m][n]=dbTempAry[n][m];
			}
			if(First_Ant)
			{
				Most_Including_Num_Ant[0]=m_cAntAry[i];
				First_Ant=false;
			}
			if(m_cAntAry[i].Path_Including_Num>Most_Including_Num_Ant[0].Path_Including_Num)
			{
				Most_Including_Num_Ant[0]=m_cAntAry[i];
				num=1;
				continue;
			}
			if(m_cAntAry[i].Path_Including_Num==Most_Including_Num_Ant[0].Path_Including_Num)
			{
				Most_Including_Num_Ant[num]=m_cAntAry[i];
				num++;
			}
			
		}
		
		/*
		for (int i=0;i<N_POINT_COUNT;i++)
		{
			for (int j=0;j<N_POINT_COUNT;j++)
			{
				g_Trial[i][j]=g_Trial[i][j]*; //最新的环境信息素 = 留存的信息素 + 新留下的信息素
			}
		}
		*/
		/*
		for(int j=1;j<N_POINT_COUNT;j++)
		{
			if(m_cAntAry[i].m_nPath[j]==-1)
			{
				Path_num=j;
				break;
			}
			if(j==N_POINT_COUNT-1)
			{
				Path_num=N_POINT_COUNT;
				break;
			}
		}
		*/
		/*
        for (int j=1;j<Path_num;j++)
        {
            m=m_cAntAry[i].m_nPath_No[j];
            n=m_cAntAry[i].m_nPath_No[j-1];
			dbTempAry[n][m]+=DBQ/m_cAntAry[i].m_dbTrialLength;
            //dbTempAry[m][n]=dbTempAry[n][m];
        }
		*/
            //最后城市和开始城市之间的信息素
        //n=m_cAntAry[i].m_nPath[0];
        //dbTempAry[n][m]=dbTempAry[n][m]+DBQ/m_cAntAry[i].m_dbPathLength;
        //dbTempAry[m][n]=dbTempAry[n][m];

    }
	if(Most_Including_Num_Ant[0].Path_Including_Num>0)
	{
		for(int i=0;i<num;i++)
		{
			for (int j=1;j<Most_Including_Num_Ant[i].m_nMovedPointCount;j++)
			{
				m=Most_Including_Num_Ant[i].m_nPath_No[j];
				n=Most_Including_Num_Ant[i].m_nPath_No[j-1];
				g_Trial[n][m]+=g_Trial[n][m]*(double)Most_Including_Num_Ant[i].Path_Including_Num/(double)N_INCLUDING_COUNT;
				//g_Trial[n][m]=g_Trial[n][m]*(m_cAntAry[i].Path_Including_Num)/N_INCLUDING_COUNT;
				//dbTempAry[m][n]=dbTempAry[n][m];
			}
		}
	}
    //==================================================================
    //更新环境信息素
    

}


void CTsp::Search()
{

    char cBuf[256]; //打印信息用

    //在迭代次数内进行循环
    for (int i=0;i<N_IT_COUNT;i++)
    {
        //每只蚂蚁搜索一遍
        for (int j=0;j<N_ANT_COUNT;j++)
        {
            m_cAntAry[j].Search(); 
        }

        //保存最佳结果
        for (int j=0;j<N_ANT_COUNT;j++)
        {
            if (m_cAntAry[j].m_dbPathLength < m_cBestAnt.m_dbPathLength)
            {
                m_cBestAnt=m_cAntAry[j];
            }
        }

        //更新环境信息素
        UpdateTrial();

        //输出目前为止找到的最优路径的长度
		//新增8
		if(m_cBestAnt.m_dbPathLength==0xFFFF)
		{
			sprintf_s(cBuf,"\n[%d] %s",i+1,"NANA");
			printf(cBuf);
		}
		else
		{
			sprintf_s(cBuf,"\n[%d] %d",i+1,m_cBestAnt.m_dbPathLength);
			printf(cBuf);
		}
        
    }

}


