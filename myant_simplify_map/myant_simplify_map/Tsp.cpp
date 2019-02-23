#include "Tsp.h"
#include "stdafx.h"
#include "readfile.h"

//extern Inc_Cost g_Including_Cost[50][50];
//构造函数
CTsp::CTsp(void)
{
}

CTsp::~CTsp(void)
{
}


//初始化数据
void CTsp::InitData() 
{

    //先把最优蚂蚁的路径长度设置成一个很大的值
    m_cBestAnt.m_dbPathLength=0xFFFF; 
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
	Stop_Flag=false;
    

}




void CTsp::Search()
{
	InitData();
    char cBuf[256]; //打印信息用
	int it_num=0;
    //在迭代次数内进行循环
	while(it_num<N_IT_COUNT)
	{
        //每只蚂蚁搜索一遍
        for (int j=0;j<N_ANT_COUNT;j++)
        {
			//m_cAntAry[j].m_nCurPointNo=Start_NO;
			//m_cAntAry[j].Simp_Flag=false;
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
        //UpdateTrial();

        //输出目前为止找到的最优路径的长度
		//新增8
		if(m_cBestAnt.m_dbPathLength==0xFFFF)
		{
			sprintf_s(cBuf,"\n[%d] %s",it_num+1,"NANA");
			printf(cBuf);
		}
		else
		{
			sprintf_s(cBuf,"\n[%d] %.0f",it_num+1,m_cBestAnt.m_dbPathLength);
			printf(cBuf);
		}
		it_num++;
	}

	printf("\nThe best tour is :\n\n");

	for (int i=0;i<N_POINT_COUNT;i++)
	{
		sprintf(cBuf,"%d ",m_cBestAnt.All_Path_ID[i]);
		printf(cBuf);
	}

}
