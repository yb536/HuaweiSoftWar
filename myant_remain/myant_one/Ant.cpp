#include "Ant.h"
#include "readfile.h"
#include "stdafx.h"

//���캯��
CAnt::CAnt(void)
{
}

//��������
CAnt::~CAnt(void)
{
}

//��ʼ����������������ǰ����
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
		
		m_nAllowedPoint[i]=1; //����ȫ������Ϊû��ȥ��
        m_nPath[i]=-1; //�����ߵ�·��ȫ������Ϊ0
		m_nPath_No[i]=-1;
    }

    //�����߹���·����������Ϊ0
    m_dbPathLength=0; 
	//m_dbTrialLength=0.0;
    //���ѡ��һ����������
	
    //m_nCurPointNo=N_START_POINT_SELF_ID;
    //�ѳ������б�����·��������
	m_nPath_No[0]=m_nCurPointNo;
    m_nPath[0]=N_START_POINT_SELF_ID;

    //��ʶ��������Ϊ�Ѿ�ȥ����
    m_nAllowedPoint[m_nCurPointNo]=0; 

    //�Ѿ�ȥ���ĳ�����������Ϊ1
    m_nMovedPointCount=1; 
	Path_Including_Num=0;
	Stop_Flag=false;
	//����5
	//Back_Flag=false;

	Death_Flag=false;


}

//ѡ����һ������
//����ֵ Ϊ���б��
int CAnt::ChooseNextPoint()
{

    int nSelectedPoint=-1; //���ؽ��������ʱ��������Ϊ-1
	double ChangeProb=0.0;
    //==============================================================================
    //���㵱ǰ���к�ûȥ���ĳ���֮�����Ϣ���ܺ�
    
    double dbTotal=0.0;    
    double prob[600]; //����������б�ѡ�еĸ���
	ChangeProb=rnd(0.0,1.0);
    for (int i=0;i<N_POINT_COUNT;i++)
    {
        if ((m_nAllowedPoint[i] == 1) && (g_Cost[m_nCurPointNo][i]!=-1)) //����ûȥ��
        {
			//prob[i]=g_Trial[m_nCurPointNo][i]+g_Trial_Init[m_nCurPointNo][i]; 
			prob[i]=g_Trial[m_nCurPointNo][i];//�ó��к͵�ǰ���м����Ϣ��
            dbTotal=dbTotal+prob[i]; //�ۼ���Ϣ�أ��õ��ܺ�
        }
        else //�������ȥ���ˣ����䱻ѡ�еĸ���ֵΪ0
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

	//����1
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
    //��������ѡ��
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

    //==============================================================================
    //������м����Ϣ�طǳ�С ( С����double�ܹ���ʾ����С�����ֻ�ҪС )
    //��ô���ڸ�����������ԭ���������ĸ����ܺͿ���Ϊ0
    //����־�������������û�г��б�ѡ�����
    //��������������Ͱѵ�һ��ûȥ���ĳ�����Ϊ���ؽ��
    
    //���⻰���տ�ʼ����ʱ��������δ����������Һܳ�ʱ�䣬�벻ͨΪ��Ҫ����δ��룬�����Ÿ������
    
	//����3
    //==============================================================================
    //���ؽ�������ǳ��еı��
    return nSelectedPoint;
}





//�����ڳ��м��ƶ�
void CAnt::Move()
{
    int nPointNo=ChooseNextPoint(); //ѡ����һ������
	//����6
	
	//bool flag=false;
	if(Death_Flag==false)
	{
		m_nPath_No[m_nMovedPointCount]=nPointNo;
		m_nPath[m_nMovedPointCount]=N_POINT_SELF_ID[nPointNo];
	
		//m_nPath[m_nMovedPointCount]=nPointNo; //���������ߵ�·��
		m_nAllowedPoint[nPointNo]=0;//������������ó��Ѿ�ȥ����
		m_nCurPointNo=nPointNo; //�ı䵱ǰ���ڳ���Ϊѡ��ĳ���
		m_nMovedPointCount++; //�Ѿ�ȥ���ĳ���������1
	
		if(nPointNo==end_NO)
		{
			Stop_Flag=true;
		}
	}
	
}

//���Ͻ�������һ��
void CAnt::Search()
{
    Init(); //��������ǰ���ȳ�ʼ��

    //�������ȥ���ĳ�������С�ڳ����������ͼ����ƶ�
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
	
    //�������������߹���·������
	//����7
	if(Path_Including_Num==N_INCLUDING_COUNT)
	{
		CalPathLength();
	}
	else
	{
		m_dbPathLength=0xFFFF;
	}
    
}


//���������߹���·������
void CAnt::CalPathLength()
{

    m_dbPathLength=0; //�Ȱ�·��������0
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

	

    //���ϴ������з��س������еľ���
    //n=m_nPath[0];
    //m_dbPathLength=m_dbPathLength+g_Cost[m][n];    

}

