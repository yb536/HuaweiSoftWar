#include "Ant.h"
#include "readfile.h"
#include "stdafx.h"
#include "Simplify.h"
extern Inc_Cost g_Including_Cost[50][50];


CAnt::CAnt(void)
{
}


CAnt::~CAnt(void)
{
}

//初始化函数，蚂蚁搜索前调用
void CAnt::Simp_Init()
{
	for (int i=0;i<N_POINT_COUNT;i++)
    {
		m_nAllowedPoint[i]=1; //设置全部节点为没有去过
        m_nPath_ID[i]=-1; //路径ID数组全部设-1
		m_nPath_No[i]=-1; //路径NO数组全部设-1
		//All_Path_ID[i]=-1; //
		//All_Path_No[i]=-1; //
    }
	//起始节点设置为去过
	m_nAllowedPoint[m_nCurPointNo]=0;
	//起始节点ID保存到路径ID数组中
	m_nPath_ID[0]=N_POINT_SELF_ID[m_nCurPointNo]; 
	//起始节点NO保存到路径NO数组中
	m_nPath_No[0]=m_nCurPointNo;
	//蚂蚁走过的路径长度初始化
    m_dbPathLength=0.0; 
	//已经去过的城市数量
    m_nMovedPointCount=1; 
	Good_Path=false;
	Stop_Flag=false;
}

//选择下一个城市
//返回值 为城市编号
int CAnt::Simp_ChooseNextPoint()
{
	int nSelectedPoint=-1;
	double dbTotal=0.0;    
    double prob[600]; //保存各个城市被选中的概率

    for (int i=0;i<N_POINT_COUNT;i++)
    {
        if ((m_nAllowedPoint[i] == 1) && (g_Cost[m_nCurPointNo][i]!=-1)) //城市没去过
        {
            prob[i]=1.0;
            dbTotal=dbTotal+prob[i]; //累加信息素，得到总和
        }
        else //如果城市去过了，则其被选中的概率值为0
        {
            prob[i]=0.0;
        }
    }
	double dbTemp=0.0;
	//新增2
    if ((dbTotal > 0.0)&&(Stop_Flag==false)) //总的信息素值大于0
    {
        dbTemp=rnd(0.0,dbTotal); //取一个随机数

        for (int i=0;i<N_POINT_COUNT;i++)
        {
            if ((m_nAllowedPoint[i] == 1) && (g_Cost[m_nCurPointNo][i]!=-1)) //城市没去过
            {
                dbTemp=dbTemp-prob[i]; //这个操作相当于转动轮盘，如果对轮盘选择不熟悉，仔细考虑一下
                if (dbTemp < 0.0) //轮盘停止转动，记下城市编号，直接跳出循环
				{
                    nSelectedPoint=i;
                    break;
                }
            }
        }
    }

	if (nSelectedPoint == -1)
	{
		for (int i=0;i<N_POINT_COUNT;i++)
		{
			if (m_nAllowedPoint[i] == 1) //城市没去过
			{
				nSelectedPoint=i;
				break;
			}
		}
	}
    
    return nSelectedPoint;
    
}





//蚂蚁在城市间移动
void CAnt::Simp_Move()
{
    int nPointNo=Simp_ChooseNextPoint(); //选择下一个城市
	//新增6
	
	
	
	m_nPath_No[m_nMovedPointCount]=nPointNo;
	m_nPath_ID[m_nMovedPointCount]=N_POINT_SELF_ID[nPointNo];
	/*
	for(int i=0;i<N_POINT_COUNT;i++)
	{
		if(N_POINT_NO[i]==nPointNo)
		{
			m_nPath[m_nMovedPointCount]=N_POINT_SELF_ID;
			break;
		}
	}
	*/
	//m_nPath[m_nMovedPointCount]=nPointNo; //保存蚂蚁走的路径
	m_nAllowedPoint[nPointNo]=0;//把这个城市设置成已经去过了
	m_nCurPointNo=nPointNo; //改变当前所在城市为选择的城市
	m_nMovedPointCount++; //已经去过的城市数量加1
	
	Stop_Flag=Stop_Move_Or_Not();
	
}

//蚂蚁进行搜索一次
void CAnt::Simp_Search()
{
	Simp_Init(); //蚂蚁搜索前，先初始化

    //如果蚂蚁去过的城市数量小于城市数量，就继续移动
    while ((m_nMovedPointCount < N_POINT_COUNT)&&(Stop_Flag==false))
    {
        Simp_Move();
    }
    Simp_CalPathLength();
}


//计算蚂蚁走过的路径长度
void CAnt::Simp_CalPathLength()
{

    m_dbPathLength=0.0; //先把路径长度置0
    int m=0;
    int n=0;

    for (int i=1;i<N_POINT_COUNT;i++)
    {
		if(m_nPath_No[i]!=-1)
		{
			m=m_nPath_No[i];
			n=m_nPath_No[i-1];
			m_dbPathLength=m_dbPathLength+g_Cost[n][m];	
		}
    }

    //加上从最后城市返回出发城市的距离
    //n=m_nPath[0];
    //m_dbPathLength=m_dbPathLength+g_Cost[m][n];    

}


bool CAnt::Stop_Move_Or_Not()
{
	bool result=false;
	/*
	if(N_POINT_SELF_ID[m_nCurPointNo]==N_START_POINT_SELF_ID)
	{
		return true;
	}
	*/
	if(N_POINT_SELF_ID[m_nCurPointNo]==N_END_POINT_SELF_ID)
	{
		result=true;
	}

	for(int i=0;i<N_INCLUDING_COUNT;i++)
	{
		if(N_POINT_SELF_ID[m_nCurPointNo]==N_INCLUDING_SELF_ID[i])
		{
			result=true;
		}
	}	

	return result;
}


void CAnt::Search()
{
	Init(); //蚂蚁搜索前，先初始化

    //如果蚂蚁去过的城市数量小于城市数量，就继续移动
    while ((m_nMovedPointCount < N_INCLUDING_COUNT+2)&&(Stop_Flag==false))
    {
        Move();
    }
	//m_nPath_ID;
	if(Death_Flag==false)
	{
		Good_Path=Good_Path_Or_Not();
	}
	

	if(Good_Path)
	{
		CalPathLength();
	}
	else
	{
		m_dbPathLength=0xFFFF;
	}
    
	
    
}

void CAnt::CalPathLength()
{
	m_dbPathLength=0.0; //先把路径长度置0
    int m=0;
    int n=0;

	for (int i=1;i<N_INCLUDING_COUNT+2;i++)
    {
		if(m_nPath_No[i]!=-1)
		{
			m=m_nPath_No[i];
			n=m_nPath_No[i-1];
			m_dbPathLength=m_dbPathLength+g_Including_Cost[n][m].cost;	
		}
    }
}

bool CAnt::Good_Path_Or_Not()
{
	bool result=false;
	bool flag=true;

	int m=0;
	
	for(int i=1;i<N_INCLUDING_COUNT+2;i++)
	{
		for(int j=0;j<N_POINT_COUNT;j++)
		{
			if(g_Including_Cost[m_nPath_No[i-1]][m_nPath_No[i]].m_nPath_ID[j]!=-1)
			{
				All_Path_ID[m]=g_Including_Cost[m_nPath_No[i-1]][m_nPath_No[i]].m_nPath_ID[j];
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
	All_Path_ID[m]=N_END_POINT_SELF_ID;

	for(int i=0;i<m;i++)
	{ 
		for(int j=i+1;j<m+1;j++)
		{
			if(All_Path_ID[i]==All_Path_ID[j])
			{
				flag=false;
				break; 
			}
		}
	}

	if(flag)
	{
		result=true;
	}
	
	return result;
}

int CAnt::ChooseNextPoint()
{
	int nSelectedPoint=-1;
	double dbTotal=0.0;    
    double prob[300]; //保存各个城市被选中的概率
	int num=0;

	

    for (int i=0;i<N_INCLUDING_COUNT+2;i++)
    {
		if ((m_nAllowedPoint[i] == 1) && (g_Including_Cost[m_nCurPointNo][i].cost!=-1)) //城市没去过
        {
            prob[i]=1.0;
            dbTotal=dbTotal+prob[i]; //累加信息素，得到总和
        }
        else //如果城市去过了，则其被选中的概率值为0
        {
            prob[i]=0.0;
        }
    }

	for (int i=0;i<N_INCLUDING_COUNT+2;i++)
	{
		if(prob[i]==0)
		{
			num++;
		}
	}
	if(num==N_INCLUDING_COUNT+2)
	{
		Stop_Flag=true;
		Death_Flag=true;
	}

	double dbTemp=0.0;
	//新增2
    if ((dbTotal > 0.0)&&(Stop_Flag==false)) //总的信息素值大于0
    {
        dbTemp=rnd(0.0,dbTotal); //取一个随机数

        for (int i=0;i<N_INCLUDING_COUNT+2;i++)
        {
            if ((m_nAllowedPoint[i] == 1) && (g_Including_Cost[m_nCurPointNo][i].cost!=-1)) //城市没去过
            {
                dbTemp=dbTemp-prob[i]; //这个操作相当于转动轮盘，如果对轮盘选择不熟悉，仔细考虑一下
                if (dbTemp < 0.0) //轮盘停止转动，记下城市编号，直接跳出循环
				{
                    nSelectedPoint=i;
                    break;
                }
            }
        }
    }

	if (nSelectedPoint == -1)
	{
		for (int i=0;i<N_POINT_COUNT;i++)
		{
			if (m_nAllowedPoint[i] == 1) //城市没去过
			{
				nSelectedPoint=i;
				break;
			}
		}
	}
    
    return nSelectedPoint;
    
}

void CAnt::Move()
{
    int nPointNo=ChooseNextPoint(); //选择下一个城市
	//新增6
	if(Death_Flag==false)
	{
		int num=0;
	
	
		m_nPath_No[m_nMovedPointCount]=nPointNo;
		if(nPointNo==N_INCLUDING_COUNT+1)
		{
			m_nPath_ID[m_nMovedPointCount]=N_END_POINT_SELF_ID;
			Stop_Flag=true;
		}
		else
		{
			m_nPath_ID[m_nMovedPointCount]=N_INCLUDING_SELF_ID[nPointNo-1];
		}
	
	
		//m_nPath[m_nMovedPointCount]=nPointNo; //保存蚂蚁走的路径
		m_nAllowedPoint[nPointNo]=0;//把这个城市设置成已经去过了
		m_nCurPointNo=nPointNo; //改变当前所在城市为选择的城市
		m_nMovedPointCount++; //已经去过的城市数量加1
	
		//Stop_Flag=Stop_Move_Or_Not();
		for(int i=0;i<N_INCLUDING_COUNT;i++)
		{
			for(int j=0;j<N_INCLUDING_COUNT+2;j++)
			{
				if(N_INCLUDING_SELF_ID[i]==m_nPath_ID[j])
				{
					num++;
					break;
				}
			}
		}
		if((num==N_INCLUDING_COUNT)&&(nPointNo!=N_INCLUDING_COUNT+1))
		{
			m_nAllowedPoint[N_INCLUDING_COUNT+1]=1;
		}
	}
	
}

void CAnt::Init()
{
	for (int i=0;i<N_INCLUDING_COUNT+2;i++)
    {
		m_nAllowedPoint[i]=1; //设置全部节点为没有去过
        m_nPath_ID[i]=-1; //路径ID数组全部设-1
		m_nPath_No[i]=-1; //路径NO数组全部设-1
		//All_Path_ID[i]=-1; //
		//All_Path_No[i]=-1; //
    }
	for (int i=0;i<N_POINT_COUNT;i++)
    {
		All_Path_ID[i]=-1; //
    }
	m_nCurPointNo=0;
	//起始节点设置为去过
	m_nAllowedPoint[m_nCurPointNo]=0;
	m_nAllowedPoint[N_INCLUDING_COUNT+1]=0;
	//起始节点ID保存到路径ID数组中
	m_nPath_ID[0]=N_START_POINT_SELF_ID; 
	//起始节点NO保存到路径NO数组中
	m_nPath_No[0]=m_nCurPointNo;
	//蚂蚁走过的路径长度初始化
    m_dbPathLength=0.0; 
	//已经去过的城市数量
    m_nMovedPointCount=1; 
	Good_Path=false;
	Stop_Flag=false;
	Death_Flag=false;
}
