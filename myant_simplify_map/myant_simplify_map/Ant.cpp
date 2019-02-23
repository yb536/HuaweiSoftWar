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

//��ʼ����������������ǰ����
void CAnt::Simp_Init()
{
	for (int i=0;i<N_POINT_COUNT;i++)
    {
		m_nAllowedPoint[i]=1; //����ȫ���ڵ�Ϊû��ȥ��
        m_nPath_ID[i]=-1; //·��ID����ȫ����-1
		m_nPath_No[i]=-1; //·��NO����ȫ����-1
		//All_Path_ID[i]=-1; //
		//All_Path_No[i]=-1; //
    }
	//��ʼ�ڵ�����Ϊȥ��
	m_nAllowedPoint[m_nCurPointNo]=0;
	//��ʼ�ڵ�ID���浽·��ID������
	m_nPath_ID[0]=N_POINT_SELF_ID[m_nCurPointNo]; 
	//��ʼ�ڵ�NO���浽·��NO������
	m_nPath_No[0]=m_nCurPointNo;
	//�����߹���·�����ȳ�ʼ��
    m_dbPathLength=0.0; 
	//�Ѿ�ȥ���ĳ�������
    m_nMovedPointCount=1; 
	Good_Path=false;
	Stop_Flag=false;
}

//ѡ����һ������
//����ֵ Ϊ���б��
int CAnt::Simp_ChooseNextPoint()
{
	int nSelectedPoint=-1;
	double dbTotal=0.0;    
    double prob[600]; //����������б�ѡ�еĸ���

    for (int i=0;i<N_POINT_COUNT;i++)
    {
        if ((m_nAllowedPoint[i] == 1) && (g_Cost[m_nCurPointNo][i]!=-1)) //����ûȥ��
        {
            prob[i]=1.0;
            dbTotal=dbTotal+prob[i]; //�ۼ���Ϣ�أ��õ��ܺ�
        }
        else //�������ȥ���ˣ����䱻ѡ�еĸ���ֵΪ0
        {
            prob[i]=0.0;
        }
    }
	double dbTemp=0.0;
	//����2
    if ((dbTotal > 0.0)&&(Stop_Flag==false)) //�ܵ���Ϣ��ֵ����0
    {
        dbTemp=rnd(0.0,dbTotal); //ȡһ�������

        for (int i=0;i<N_POINT_COUNT;i++)
        {
            if ((m_nAllowedPoint[i] == 1) && (g_Cost[m_nCurPointNo][i]!=-1)) //����ûȥ��
            {
                dbTemp=dbTemp-prob[i]; //��������൱��ת�����̣����������ѡ����Ϥ����ϸ����һ��
                if (dbTemp < 0.0) //����ֹͣת�������³��б�ţ�ֱ������ѭ��
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
			if (m_nAllowedPoint[i] == 1) //����ûȥ��
			{
				nSelectedPoint=i;
				break;
			}
		}
	}
    
    return nSelectedPoint;
    
}





//�����ڳ��м��ƶ�
void CAnt::Simp_Move()
{
    int nPointNo=Simp_ChooseNextPoint(); //ѡ����һ������
	//����6
	
	
	
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
	//m_nPath[m_nMovedPointCount]=nPointNo; //���������ߵ�·��
	m_nAllowedPoint[nPointNo]=0;//������������ó��Ѿ�ȥ����
	m_nCurPointNo=nPointNo; //�ı䵱ǰ���ڳ���Ϊѡ��ĳ���
	m_nMovedPointCount++; //�Ѿ�ȥ���ĳ���������1
	
	Stop_Flag=Stop_Move_Or_Not();
	
}

//���Ͻ�������һ��
void CAnt::Simp_Search()
{
	Simp_Init(); //��������ǰ���ȳ�ʼ��

    //�������ȥ���ĳ�������С�ڳ����������ͼ����ƶ�
    while ((m_nMovedPointCount < N_POINT_COUNT)&&(Stop_Flag==false))
    {
        Simp_Move();
    }
    Simp_CalPathLength();
}


//���������߹���·������
void CAnt::Simp_CalPathLength()
{

    m_dbPathLength=0.0; //�Ȱ�·��������0
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

    //���ϴ������з��س������еľ���
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
	Init(); //��������ǰ���ȳ�ʼ��

    //�������ȥ���ĳ�������С�ڳ����������ͼ����ƶ�
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
	m_dbPathLength=0.0; //�Ȱ�·��������0
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
    double prob[300]; //����������б�ѡ�еĸ���
	int num=0;

	

    for (int i=0;i<N_INCLUDING_COUNT+2;i++)
    {
		if ((m_nAllowedPoint[i] == 1) && (g_Including_Cost[m_nCurPointNo][i].cost!=-1)) //����ûȥ��
        {
            prob[i]=1.0;
            dbTotal=dbTotal+prob[i]; //�ۼ���Ϣ�أ��õ��ܺ�
        }
        else //�������ȥ���ˣ����䱻ѡ�еĸ���ֵΪ0
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
	//����2
    if ((dbTotal > 0.0)&&(Stop_Flag==false)) //�ܵ���Ϣ��ֵ����0
    {
        dbTemp=rnd(0.0,dbTotal); //ȡһ�������

        for (int i=0;i<N_INCLUDING_COUNT+2;i++)
        {
            if ((m_nAllowedPoint[i] == 1) && (g_Including_Cost[m_nCurPointNo][i].cost!=-1)) //����ûȥ��
            {
                dbTemp=dbTemp-prob[i]; //��������൱��ת�����̣����������ѡ����Ϥ����ϸ����һ��
                if (dbTemp < 0.0) //����ֹͣת�������³��б�ţ�ֱ������ѭ��
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
			if (m_nAllowedPoint[i] == 1) //����ûȥ��
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
    int nPointNo=ChooseNextPoint(); //ѡ����һ������
	//����6
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
	
	
		//m_nPath[m_nMovedPointCount]=nPointNo; //���������ߵ�·��
		m_nAllowedPoint[nPointNo]=0;//������������ó��Ѿ�ȥ����
		m_nCurPointNo=nPointNo; //�ı䵱ǰ���ڳ���Ϊѡ��ĳ���
		m_nMovedPointCount++; //�Ѿ�ȥ���ĳ���������1
	
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
		m_nAllowedPoint[i]=1; //����ȫ���ڵ�Ϊû��ȥ��
        m_nPath_ID[i]=-1; //·��ID����ȫ����-1
		m_nPath_No[i]=-1; //·��NO����ȫ����-1
		//All_Path_ID[i]=-1; //
		//All_Path_No[i]=-1; //
    }
	for (int i=0;i<N_POINT_COUNT;i++)
    {
		All_Path_ID[i]=-1; //
    }
	m_nCurPointNo=0;
	//��ʼ�ڵ�����Ϊȥ��
	m_nAllowedPoint[m_nCurPointNo]=0;
	m_nAllowedPoint[N_INCLUDING_COUNT+1]=0;
	//��ʼ�ڵ�ID���浽·��ID������
	m_nPath_ID[0]=N_START_POINT_SELF_ID; 
	//��ʼ�ڵ�NO���浽·��NO������
	m_nPath_No[0]=m_nCurPointNo;
	//�����߹���·�����ȳ�ʼ��
    m_dbPathLength=0.0; 
	//�Ѿ�ȥ���ĳ�������
    m_nMovedPointCount=1; 
	Good_Path=false;
	Stop_Flag=false;
	Death_Flag=false;
}
