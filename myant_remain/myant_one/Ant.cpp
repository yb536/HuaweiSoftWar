#include "Ant.h"
#include "readfile.h"
#include "stdafx.h"

//构造函数
CAnt::CAnt(void)
{
}

//析构函数
CAnt::~CAnt(void)
{
}

//初始化函数，蚂蚁搜索前调用
void CAnt::Init()
{
	for(int i=0;i<N_POINT_COUNT;i++)
	{
		if(N_POINT_SELF_ID[i]==N_START_POINT_SELF_ID)
		{
			m_nCurPointNo=i;
			//break;
		}
		if(N_POINT_SELF_ID[i]==N_END_POINT_SELF_ID)
		{
			end_NO=i;
		}
		
	}

    for (int i=0;i<N_POINT_COUNT;i++)
    {
		
		m_nAllowedPoint[i]=1; //设置全部城市为没有去过
        m_nPath[i]=-1; //蚂蚁走的路径全部设置为0
		m_nPath_No[i]=-1;
    }

    //蚂蚁走过的路径长度设置为0
    m_dbPathLength=0; 
	//m_dbTrialLength=0.0;
    //随机选择一个出发城市
	
    //m_nCurPointNo=N_START_POINT_SELF_ID;
    //把出发城市保存入路径数组中
	m_nPath_No[0]=m_nCurPointNo;
    m_nPath[0]=N_START_POINT_SELF_ID;

    //标识出发城市为已经去过了
    m_nAllowedPoint[m_nCurPointNo]=0; 

    //已经去过的城市数量设置为1
    m_nMovedPointCount=1; 
	Path_Including_Num=0;
	Stop_Flag=false;
	//新增5
	//Back_Flag=false;

	Death_Flag=false;


}

//选择下一个城市
//返回值 为城市编号
int CAnt::ChooseNextPoint()
{

    int nSelectedPoint=-1; //返回结果，先暂时把其设置为-1
	double ChangeProb=0.0;
    //==============================================================================
    //计算当前城市和没去过的城市之间的信息素总和
    
    double dbTotal=0.0;    
    double prob[600]; //保存各个城市被选中的概率
	ChangeProb=rnd(0.0,1.0);
    for (int i=0;i<N_POINT_COUNT;i++)
    {
        if ((m_nAllowedPoint[i] == 1) && (g_Cost[m_nCurPointNo][i]!=-1)) //城市没去过
        {
			//prob[i]=g_Trial[m_nCurPointNo][i]+g_Trial_Init[m_nCurPointNo][i]; 
			prob[i]=g_Trial[m_nCurPointNo][i];//该城市和当前城市间的信息素
            dbTotal=dbTotal+prob[i]; //累加信息素，得到总和
        }
        else //如果城市去过了，则其被选中的概率值为0
        {
            prob[i]=0.0;
        }
    }

	bool flag=true;
	int no1=0;
	double a=0.0,b=0.0;
	
	if(ChangeProb< CHANGE )
	{
		for (int i=0;i<N_POINT_COUNT;i++)
		{
			if(prob[i]!=0.0)
			{
				if(flag)
				{
					no1=i;
					flag=false;
				}
				a=prob[i];
				prob[i]=b;
				b=a;
			}	
		}
		prob[no1]=b;
	}

	//新增1
	for(int i=0;i<N_POINT_COUNT;i++)
	{
		if(prob[i]>0)
		{
			break;
		}
		if(i==N_POINT_COUNT-1)
		{

			Stop_Flag=true;
			//Back_Flag=true;
			Death_Flag=true;
		}
	}

    //==============================================================================
    //进行轮盘选择
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

    //==============================================================================
    //如果城市间的信息素非常小 ( 小到比double能够表示的最小的数字还要小 )
    //那么由于浮点运算的误差原因，上面计算的概率总和可能为0
    //会出现经过上述操作，没有城市被选择出来
    //出现这种情况，就把第一个没去过的城市作为返回结果
    
    //题外话：刚开始看的时候，下面这段代码困惑了我很长时间，想不通为何要有这段代码，后来才搞清楚。
    
	//新增3
    //==============================================================================
    //返回结果，就是城市的编号
    return nSelectedPoint;
}





//蚂蚁在城市间移动
void CAnt::Move()
{
    int nPointNo=ChooseNextPoint(); //选择下一个城市
	//新增6
	
	//bool flag=false;
	if(Death_Flag==false)
	{
		m_nPath_No[m_nMovedPointCount]=nPointNo;
		m_nPath[m_nMovedPointCount]=N_POINT_SELF_ID[nPointNo];
	
		//m_nPath[m_nMovedPointCount]=nPointNo; //保存蚂蚁走的路径
		m_nAllowedPoint[nPointNo]=0;//把这个城市设置成已经去过了
		m_nCurPointNo=nPointNo; //改变当前所在城市为选择的城市
		m_nMovedPointCount++; //已经去过的城市数量加1
	
		if(nPointNo==end_NO)
		{
			Stop_Flag=true;
		}
	}
	
}

//蚂蚁进行搜索一次
void CAnt::Search()
{
    Init(); //蚂蚁搜索前，先初始化

    //如果蚂蚁去过的城市数量小于城市数量，就继续移动
    while ((m_nMovedPointCount < N_POINT_COUNT)&&(Stop_Flag==false))
    {
        Move();
    }

	if(Death_Flag==false)
	{
		for(int i=0;i<N_INCLUDING_COUNT;i++)
		{
			for(int j=0;j<m_nMovedPointCount;j++)
			{
				if(N_INCLUDING_SELF_ID[i]==m_nPath[j])
				{
					Path_Including_Num++;
				}
			}
		}
	}
	
    //完成搜索后计算走过的路径长度
	//新增7
	if(Path_Including_Num==N_INCLUDING_COUNT)
	{
		CalPathLength();
	}
	else
	{
		m_dbPathLength=0xFFFF;
	}
    
}


//计算蚂蚁走过的路径长度
void CAnt::CalPathLength()
{

    m_dbPathLength=0; //先把路径长度置0
	m_dbTrialLength=0.0;
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
		else
		{
			break;
		}
    }

	

    //加上从最后城市返回出发城市的距离
    //n=m_nPath[0];
    //m_dbPathLength=m_dbPathLength+g_Cost[m][n];    

}

