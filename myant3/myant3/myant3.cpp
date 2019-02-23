// myant.cpp : �������̨Ӧ�ó������ڵ㡣
//

// AO.cpp : �������̨Ӧ�ó������ڵ㡣
#pragma once
#include "stdafx.h"
#include <iostream>
#include <math.h>
#include <time.h>

const double ALPHA=1.0; //�������ӣ���Ϣ�ص���Ҫ�̶�
const double BETA=2.0;   //�������ӣ����м�������Ҫ�̶�
const double ROU=0.5; //��Ϣ�ز�������

const double Pbest=0.05; //����һ�������ҵ�����·���ĸ���


const int N_ANT_COUNT=2; //��������
const int N_IT_COUNT=100; //��������
const int N_POINT_COUNT=20; //��������

const int N_POINT_NO[N_POINT_COUNT]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};
const int N_POINT_SELF_ID[N_POINT_COUNT]={0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19};//�ڵ�����ID
const int N_START_POINT_SELF_ID=2 ;  //��������IDg_Prob
const int N_END_POINT_SELF_ID= 19;  //�յ����ID
const int N_INCLUDING_SELF_ID[]={3,5,7,11,13,17};        //�ؾ��ڵ�ID

const double DBQ=100.0; //�ܵ���Ϣ��
const double DB_MAX=10e9; //һ����־����10��9�η�


double g_Prob[N_POINT_COUNT][N_POINT_COUNT];
int rnd(int nLow,int nUpper); //���������
double rnd(double dbLow,double dbUpper);
double ROUND(double dbA);
double g_CostBeta[N_POINT_COUNT][N_POINT_COUNT];


double g_Trial[N_POINT_COUNT][N_POINT_COUNT]; //�������м���Ϣ�أ����ǻ�����Ϣ��
double g_Cost[N_POINT_COUNT][N_POINT_COUNT]={
//    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
	{-1,-1,-1,-1, 8,-1,-1,-1,17,-1,-1,-1,-1,15,-1,-1,-1,-1,-1, 1},//0
	{ 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//1
	{-1,-1,-1,20,-1,-1,-1,-1,-1,19,-1,-1,-1,-1,-1, 8,-1,-1,-1,-1},//2
	{14,-1,-1,-1,-1,20,-1,-1,-1,-1,-1,12,-1,-1,-1,-1,-1,-1,-1,-1},//3
	{-1,15,-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//4
	{-1,-1,-1,-1,-1,-1, 2,20,18,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,20},//5
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 4,-1,-1},//6
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,-1, 1,-1,-1,19,-1,-1,-1},//7
	{-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1},//8
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,-1,-1,-1,-1,-1},//9
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1},//10
	{-1,-1,-1,-1, 7,-1,-1,12,-1,-1,-1,-1,-1,20,-1,-1,-1,-1,-1,20},//11
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5,-1,-1,-1,-1,-1},//12
	{-1,-1,-1,-1, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,-1,-1},//13
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 9},//14
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,-1,-1,-1,-1,-1, 2,-1},//15
	{-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//16
	{-1,-1,-1,-1,-1,20,-1,-1,-1,14,-1,20,-1,-1,-1,-1,-1,-1,10, 3},//17
	{-1,-1,-1, 8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,-1,-1,-1,-1},//18
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,-1} //19
//    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19

}; //�������м����

//eil51.tsp������������


//����ָ����Χ�ڵ��������
int rnd(int nLow,int nUpper)
{
    return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);
}

//����ָ����Χ�ڵ����������
double rnd(double dbLow,double dbUpper)
{
    double dbTemp=rand()/((double)RAND_MAX+1.0);
    return dbLow+dbTemp*(dbUpper-dbLow);
}

//���ظ�������������ȡ����ĸ�����
double ROUND(double dbA)
{
    return (double)((int)(dbA+0.5));
}





//����������
class CAnt
{
public:
    CAnt(void);
    ~CAnt(void);

public:

	int m_nPath[N_POINT_COUNT]; //�����ߵ�����ID·��
	int m_nPath_No[N_POINT_COUNT]; //���ϱ��·��
    double m_dbPathLength; //�����߹���·������

    int m_nAllowedPoint[N_POINT_COUNT]; //ûȥ���ĳ���
    int m_nCurPointNo; //��ǰ���ڳ��б��
    int m_nMovedPointCount; //�Ѿ�ȥ���ĳ�������
	int end_NO;//�յ���б��
	bool Stop_Flag;
	bool Back_Flag;

	bool m_blGreedSearch; //�Ƿ�ʹ��̰��ԭ��ѡ����һ����


public:

    int ChooseNextPoint(); //ѡ����һ������

	int GreedChooseNextCity(); //̰��ԭ��ѡ����һ������

    void Init(); //��ʼ��
    void Move(); //�����ڳ��м��ƶ�
    void Search(); //����·��
    void CalPathLength(); //���������߹���·������

};

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
		if(i==end_NO)
		{
			m_nAllowedPoint[i]=0;
		}
		else
		{
			m_nAllowedPoint[i]=1; //����ȫ������Ϊû��ȥ��
		}
        m_nPath[i]=-1; //�����ߵ�·��ȫ������Ϊ0
		m_nPath_No[i]=-1;
    }

    //�����߹���·����������Ϊ0
    m_dbPathLength=0.0; 

    //���ѡ��һ����������
	
    //m_nCurPointNo=N_START_POINT_SELF_ID;
    //�ѳ������б�����·��������
	m_nPath_No[0]=m_nCurPointNo;
    m_nPath[0]=N_START_POINT_SELF_ID;

    //��ʶ��������Ϊ�Ѿ�ȥ����
    m_nAllowedPoint[m_nCurPointNo]=0; 

    //�Ѿ�ȥ���ĳ�����������Ϊ1
    m_nMovedPointCount=1; 
	Stop_Flag=false;
	
	Back_Flag=false;
	//��ʹ��̰��ԭ��ѡ����һ����
	m_blGreedSearch=false;
}


// ̰��ԭ��ѡ����һ������
int CAnt::GreedChooseNextCity()
{
	int nSelectedCity=-1; //���ؽ��������ʱ��������Ϊ-1
	double dbLen=DB_MAX;

	for (int i=0;i<N_POINT_COUNT;i++)
	{
		//����3
		if ((m_nAllowedPoint[i] == 1) && (g_Cost[m_nCurPointNo][i]!=-1)) //����ûȥ��
		{
			if ((g_Cost[m_nCurPointNo][i] < dbLen)&&(g_Cost[m_nCurPointNo][i] !=-1))
			{
				dbLen=g_Cost[m_nCurPointNo][i];
				nSelectedCity=i;
			}
		}
	}
	//����5
	if(nSelectedCity==-1)
	{
		Back_Flag=true;

	}
	return nSelectedCity;
}


//ѡ����һ������
//����ֵ Ϊ���б��
int CAnt::ChooseNextPoint()
{

    int nSelectedPoint=-1; //���ؽ��������ʱ��������Ϊ-1

    //==============================================================================
    //���㵱ǰ���к�ûȥ���ĳ���֮�����Ϣ���ܺ�
    
    double dbTotal=0.0;    
    double prob[N_POINT_COUNT]; //����������б�ѡ�еĸ���

    for (int i=0;i<N_POINT_COUNT;i++)
    {
        if ((m_nAllowedPoint[i] == 1) && (g_Cost[m_nCurPointNo][i]!=-1)) //����ûȥ��
        {
       //   prob[i]=pow(g_Trial[m_nCurPointNo][i],ALPHA)*pow(1.0/g_Cost[m_nCurPointNo][i],BETA); //�ó��к͵�ǰ���м����Ϣ��
			prob[i]=g_Prob[m_nCurPointNo][i];
            dbTotal=dbTotal+prob[i]; //�ۼ���Ϣ�أ��õ��ܺ�
        }
        else //�������ȥ���ˣ����䱻ѡ�еĸ���ֵΪ0
        {
            prob[i]=0.0;
        }
    }
	for(int i=0;i<N_POINT_COUNT;i++)
	{
		if(prob[i]>0)
		{
			break;
		}
		if(i==N_POINT_COUNT-1)
		{

			//Stop_Flag=true;
			Back_Flag=true;
		}
	}

    //==============================================================================
    //��������ѡ��
    double dbTemp=0.0;

    if ((dbTotal > 0.0)&&(Back_Flag==false)) //�ܵ���Ϣ��ֵ����0
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
    
	
    //==============================================================================
    //���ؽ�������ǳ��еı��
    return nSelectedPoint;
}





//�����ڳ��м��ƶ�
void CAnt::Move()
{


    int nPointNo=0; //ѡ����һ������
	if (m_blGreedSearch == true)
		nPointNo=GreedChooseNextCity(); 
	else
		nPointNo=ChooseNextPoint();



	if(Back_Flag==false)
	{
		bool flag=false;
		
		m_nPath_No[m_nMovedPointCount]=nPointNo;
		m_nPath[m_nMovedPointCount]=N_POINT_SELF_ID[nPointNo];
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
		for(int i=0;i<sizeof(N_INCLUDING_SELF_ID)/sizeof(N_INCLUDING_SELF_ID[0]);i++)
		{
			for(int j=0;j<N_POINT_COUNT;j++)
			{
				if(N_INCLUDING_SELF_ID[i]==m_nPath[j])
				{
					break;
				}
				if(j==N_POINT_COUNT-1)
				{
					flag=true;
				}
			
			}
			if(flag)
			{
				break;
			}
			if(i==sizeof(N_INCLUDING_SELF_ID)/sizeof(N_INCLUDING_SELF_ID[0])-1)
			{
				m_nAllowedPoint[end_NO]=1;
			}
		}
		if(nPointNo==end_NO)
		{
			Stop_Flag=true;
		}
	}
	//����4
	else
	{
		m_nAllowedPoint[m_nPath_No[m_nMovedPointCount-1]]=0;
		m_nPath_No[m_nMovedPointCount-1]=nPointNo;
		m_nPath[m_nMovedPointCount-1]=nPointNo;//������������ó��Ѿ�ȥ����
		m_nCurPointNo=m_nPath_No[m_nMovedPointCount-2];
		m_nMovedPointCount--;
		Back_Flag=false;
	}
	
}

//���Ͻ�������һ��
void CAnt::Search()
{
	//����1
	if(m_blGreedSearch==false)
		Init(); //��������ǰ���ȳ�ʼ��

    //�������ȥ���ĳ�������С�ڳ����������ͼ����ƶ�
    while ((m_nMovedPointCount < N_POINT_COUNT)&&(Stop_Flag==false))
    {
        Move();
    }

    //�������������߹���·������
	//����
	CalPathLength();

    
}


//���������߹���·������
void CAnt::CalPathLength()
{

    m_dbPathLength=0.0; //�Ȱ�·��������0
    int m=0;
    int n=0;

    for (int i=1;i<N_POINT_COUNT;i++)
    {
		//����cost
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




//tsp��
class CTsp
{
public:
    CTsp(void);
    ~CTsp(void);

public:
    CAnt m_cAntAry[N_ANT_COUNT]; //��������
    CAnt m_cBestAnt; //����һ�����ϱ����������������������е����Ž��
                                        //�����ϲ�����������ֻ�������������Ž��
	
	
	
	double m_dbRate; //�����Ϣ�غ���С��Ϣ�صı�ֵ

public:

    //��ʼ������
    void InitData(); 

    //��ʼ����
    void Search(); 

    //���»�����Ϣ��
    void UpdateTrial();


};


//���캯��
CTsp::CTsp(void)
{
	
}

CTsp::~CTsp(void)
{
}


//��ʼ������
void CTsp::InitData() 
{

    //�Ȱ��������ϵ�·���������ó�һ���ܴ��ֵ
    m_cBestAnt.m_dbPathLength=DB_MAX; 

    //�����������м����
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

	for (int i=0;i<N_POINT_COUNT;i++)
    {
        for (int j=0;j<N_POINT_COUNT;j++)
        {
			if(g_Cost[i][j]!=-1)
			{
				g_CostBeta[i][j]=pow(1.0/g_Cost[i][j],BETA);
			}
			else
			{
				g_CostBeta[i][j]=-1;
			}
				
		}
	}
	//��̰���㷨�����ʼ�Ľ�
	m_cBestAnt.Init();
	m_cBestAnt.m_blGreedSearch=true;
	m_cBestAnt.Search();
	double Imax=1.0/(m_cBestAnt.m_dbPathLength*(1.0-ROU));
	// ��ʼ��������Ϣ��
    for (int i=0;i<N_POINT_COUNT;i++)
    {
        for (int j=0;j<N_POINT_COUNT;j++)
        {
			if(g_Cost[i][j]!=-1)
			{
				g_Trial[i][j]=Imax;

				g_Prob[i][j]=pow(Imax,ALPHA)*g_CostBeta[i][j];
			}
			else
			{
				g_Trial[i][j]=0.0;
				g_Prob[i][j]=0.0;
			}
            
        }
    }
	//����������С��Ϣ��֮��ı�ֵ
	//dbTemp=pow(Pbest,1.0/(double)N_CITY_COUNT); //��Pbest��N_CITY_COUNT�η�
	double dbTemp=0.0;
	dbTemp=exp(log(Pbest)/(double)N_POINT_COUNT); //��Pbest��N_CITY_COUNT�η�
	double dbFz=2.0*(1.0-dbTemp);
	double dbFm=((double)N_POINT_COUNT-2.0)*dbTemp;
	m_dbRate=dbFz/dbFm;
}

//���»�����Ϣ��
void CTsp::UpdateTrial()
{
    //��ʱ���飬�����ֻ�������������м������µ���Ϣ��
    double dbTempAry[N_POINT_COUNT][N_POINT_COUNT];
    memset(dbTempAry,0,sizeof(dbTempAry)); //��ȫ������Ϊ0

    //���������ӵ���Ϣ��,���浽��ʱ������
    int m=0;
    int n=0;
	int Path_num=0;
	/*
	for(int i=0;i<N_POINT_COUNT;i++)
	{
		for(int j=0;j<N_POINT_COUNT;j++)
		{
			dbTempAry[i][j]=0.0;
		}
	}
	*/
    for (int i=0;i<N_ANT_COUNT;i++) //����ÿֻ�������µ���Ϣ��
    {
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

        for (int j=1;j<Path_num;j++)
        {
            m=m_cBestAnt.m_nPath[j];
			n=m_cBestAnt.m_nPath[j-1];
			dbTempAry[n][m]=dbTempAry[n][m]+1.0/m_cBestAnt.m_dbPathLength;			
            //dbTempAry[m][n]=dbTempAry[n][m];
        }

            //�����кͿ�ʼ����֮�����Ϣ��
        //n=m_cAntAry[i].m_nPath[0];
        //dbTempAry[n][m]=dbTempAry[n][m]+DBQ/m_cAntAry[i].m_dbPathLength;
        //dbTempAry[m][n]=dbTempAry[n][m];

    }

    //==================================================================
    //���»�����Ϣ��
    for (int i=0;i<N_POINT_COUNT;i++)
    {
        for (int j=0;j<N_POINT_COUNT;j++)
        {
            g_Trial[i][j]=g_Trial[i][j]*ROU+dbTempAry[i][j]; //���µĻ�����Ϣ�� = �������Ϣ�� + �����µ���Ϣ��
        }
    }
		//==================================================================
	//��黷����Ϣ�أ��������С�����ֵ�����棬�������µ���
	double Imax=1.0/(m_cBestAnt.m_dbPathLength*(1.0-ROU));
	double Imin=Imax*m_dbRate;

	for (int i=0;i<N_POINT_COUNT;i++)
	{
		for (int j=0;j<N_POINT_COUNT;j++)
		{
			if (g_Trial[i][j] < Imin)
			{
				g_Trial[i][j] = Imin;
			}

			if (g_Trial[i][j] > Imax)
			{
				g_Trial[i][j] = Imax;
			}

		}
	}


	for (int i=0;i<N_POINT_COUNT;i++)
	{
		for (int j=0;j<N_POINT_COUNT;j++)
		{
			if(g_Cost[i][j]!=-1)
			{
				g_Prob[i][j]=pow(g_Trial[i][j],ALPHA)*g_CostBeta[i][j];
			}
			else
			{
				g_Prob[i][j]=0.0;
			}
		}
	}
}


void CTsp::Search()
{

    char cBuf[256]; //��ӡ��Ϣ��

    //�ڵ��������ڽ���ѭ��
    for (int i=0;i<N_IT_COUNT;i++)
    {
        //ÿֻ��������һ��
        for (int j=0;j<N_ANT_COUNT;j++)
        {
			//����2
			m_cAntAry[j].m_blGreedSearch==false;
            m_cAntAry[j].Search(); 
        }

        //������ѽ��
        for (int j=0;j<N_ANT_COUNT;j++)
        {
            if (m_cAntAry[j].m_dbPathLength < m_cBestAnt.m_dbPathLength)
            {
                m_cBestAnt=m_cAntAry[j];
            }
        }

        //���»�����Ϣ��
        UpdateTrial();

        //���ĿǰΪֹ�ҵ�������·���ĳ���
	
			sprintf_s(cBuf,"\n[%d] %.0f",i+1,m_cBestAnt.m_dbPathLength);
			printf(cBuf);
		
        
    }

}

int main()
{
    //�õ�ǰʱ����ʼ��������ӣ���ֹÿ�����еĽ������ͬ
    time_t tm;
    time(&tm);
    unsigned int nSeed=(unsigned int)tm;
    srand(nSeed);

    //��ʼ����
    CTsp tsp;

    tsp.InitData(); //��ʼ��
    tsp.Search(); //��ʼ����
	/*
	if(tsp.m_cBestAnt.m_dbPathLength==0xFFFF)
	{
		printf("û���ҵ�����·��");
	}
	else
	{
	*/
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

	//}
    //������

    

    printf("\n\nPress any key to exit!");
    getchar();

    return 0;
}



