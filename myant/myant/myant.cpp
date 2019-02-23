// myant.cpp : �������̨Ӧ�ó������ڵ㡣
//���� ��Ӧ�ڵ㣬 �����Ӧcost

// AO.cpp : �������̨Ӧ�ó������ڵ㡣
#pragma once
#include <iostream>
#include <math.h> 
#include <time.h>

const double ALPHA=1.0; //�������ӣ���Ϣ�ص���Ҫ�̶�
const double BETA=2.0;   //�������ӣ����м�������Ҫ�̶�
const double ROU=0.5; //��Ϣ�ز�������
const int N_CITY_COUNT=4;  //��������
const int N_ANT_COUNT=4; //��������   ���ݳ��������趨 һ�㲻�������о���
const int N_IT_COUNT=10000; //��������


//const int N_CITY_ID[]={0,1,2 ,3 };   //����ID
int N_CITY_ID[N_CITY_COUNT]={0,1,2 ,3};//����ID
const int N_START_CITY_ID=0 ;  //��������ID
const int N_END_CITY_ID= 1;  //�յ����ID
const int N_MUST_ID[]={2,3};        //�ؾ��ڵ�ID

const double DBQ=100.0; //�ܵ���Ϣ��
const double DB_MAX=10e9; //һ����־����10��9�η�

double g_Trial[N_CITY_COUNT][N_CITY_COUNT]; //�����ڵ����Ϣ�أ����ǻ�����Ϣ��
int g_Distance[N_CITY_COUNT][N_CITY_COUNT]={
	{0,1,2,1},
	{-1,0,-1,-1},
	{-1,3,0,1},
	{-1,1,1,0}
}; //�����ڵ�֮���cost




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

    int m_nPath[N_CITY_COUNT]; //�����ߵ�·��
    double m_dbPathLength; //�����߹���·������

    int m_nAllowedCity[N_CITY_COUNT]; //ûȥ���ĳ���
    int m_nCurCityNo; //��ǰ���ڳ��б��
    int m_nMovedCityCount; //�Ѿ�ȥ���ĳ�������

public:

    int ChooseNextCity(); //ѡ����һ������
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

    for (int i=0;i<N_CITY_COUNT;i++)
    {
        m_nAllowedCity[i]=1; //����ȫ������Ϊû��ȥ��       
		m_nAllowedCity[N_END_CITY_ID]=0 ;  //�������սڵ��Ѿ�ȥ��  �޷�ѡ��

        m_nPath[i]=0; //�����ߵ�·��ȫ������Ϊ0
    }
	
    //�����߹���·����������Ϊ0
    m_dbPathLength=0.0; 

    //ѡ���������
	m_nCurCityNo=N_START_CITY_ID;

    //�ѳ������б�����·��������
    m_nPath[0]=m_nCurCityNo;

    //��ʶ��������Ϊ�Ѿ�ȥ����
    m_nAllowedCity[m_nCurCityNo]=0; 

    //�Ѿ�ȥ���ĳ�����������Ϊ1
    m_nMovedCityCount=1; 

}

//ѡ����һ������
//����ֵ Ϊ���б��
int CAnt::ChooseNextCity()
{

    int nSelectedCity=-1; //���ؽ��������ʱ��������Ϊ-1

    //==============================================================================
    //���㵱ǰ���к�ûȥ���ĳ���֮�����Ϣ���ܺ�
    
    double dbTotal=0.0;    
    double prob[N_CITY_COUNT]; //����������б�ѡ�еĸ���

    for (int i=0;i<N_CITY_COUNT;i++)
    {
        if (m_nAllowedCity[i] == 1)  //����ûȥ��
        {
            prob[i]=pow(g_Trial[m_nCurCityNo][i],ALPHA)*pow(1.0/g_Distance[m_nCurCityNo][i],BETA); //�ó��к͵�ǰ���м����Ϣ��   ��������Ż�POW������
			if (prob[i]<0)
			{
              prob[i]=0.0;
			}
            dbTotal=dbTotal+prob[i]; //�ۼ���Ϣ�أ��õ��ܺ�
        }
        else //�������ȥ���ˣ����䱻ѡ�еĸ���ֵΪ0
        {
            prob[i]=0.0;
        }
    }

    //==============================================================================
    //��������ѡ��
    double dbTemp=0.0;
    if (dbTotal > 0.0) //�ܵ���Ϣ��ֵ����0
    {
        dbTemp=rnd(0.0,dbTotal); //ȡһ�������

        for (int i=0;i<N_CITY_COUNT;i++)
        {
            if (m_nAllowedCity[i] == 1) //����ûȥ��
            {
                dbTemp=dbTemp-prob[i]; //��������൱��ת�����̣����������ѡ����Ϥ����ϸ����һ��
                if (dbTemp < 0.0) //����ֹͣת�������³��б�ţ�ֱ������ѭ��
                {
                    nSelectedCity=i;
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
    if (nSelectedCity == -1)
    {
        for (int i=0;i<N_CITY_COUNT;i++)
        {
            if (m_nAllowedCity[i] == 1) //����ûȥ��
            {
                nSelectedCity=i;
                break;
            }
        }
    }

    //==============================================================================
    //���ؽ�������ǳ��еı��
    return nSelectedCity;
}





//�����ڳ��м��ƶ�
void CAnt::Move()
{
    int nCityNo=ChooseNextCity(); //ѡ����һ������
	int x=0;
    m_nPath[m_nMovedCityCount]=nCityNo; //���������ߵ�·��
    m_nAllowedCity[nCityNo]=0;//������������ó��Ѿ�ȥ����

	for (int i=0;i<sizeof(N_MUST_ID)/sizeof(int);i++)
	{
	x=m_nAllowedCity[N_MUST_ID[i]]+x;	
    }
	if (x==0)
	{
		m_nAllowedCity[N_END_CITY_ID]=1;
	}
   
	m_nCurCityNo=nCityNo; //�ı䵱ǰ���ڳ���Ϊѡ��ĳ���
  //  m_nMovedCityCount++; //�Ѿ�ȥ���ĳ���������1
}

//���Ͻ�������һ��
void CAnt::Search()
{
    Init(); //��������ǰ���ȳ�ʼ��

    //������ϵ�ǰ���в����յ���У��ͼ����ƶ�
	while (m_nCurCityNo != N_END_CITY_ID)
    {
        Move();
    }
    //�������������߹���·������
    CalPathLength();
}


//���������߹���·������
void CAnt::CalPathLength()
{

    m_dbPathLength=0.0; //�Ȱ�·��������0
    int m=0;
    int n=0;

	for (int i=1;i<N_CITY_COUNT;i++)
    {
        m=m_nPath[i];
        n=m_nPath[i-1];
        m_dbPathLength=m_dbPathLength+g_Distance[m][n];
    }




    //���ϴ������е��յ���еľ���
    n=m_nPath[N_END_CITY_ID];
    m_dbPathLength=m_dbPathLength+g_Distance[m][n];    

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

    //��ʼ��������Ϣ�أ��Ȱѳ��м����Ϣ�����ó�һ��
    //�������ó�1.0�����óɶ��ٶԽ��Ӱ�첻��̫�󣬶��㷨�����ٶ���ЩӰ��
    for (int i=0;i<N_CITY_COUNT;i++)
    {
        for (int j=0;j<N_CITY_COUNT;j++)
        {
            g_Trial[i][j]=1.0;
        }
    }

}

//���»�����Ϣ��
void CTsp::UpdateTrial()
{
    //��ʱ���飬�����ֻ�������������м������µ���Ϣ��
    double dbTempAry[N_CITY_COUNT][N_CITY_COUNT];
    memset(dbTempAry,0,sizeof(dbTempAry)); //��ȫ������Ϊ0

    //���������ӵ���Ϣ��,���浽��ʱ������
    int m=0;
    int n=0;
    for (int i=0;i<N_ANT_COUNT;i++) //����ÿֻ�������µ���Ϣ��
    {
		for (int j=1;j!=N_END_CITY_ID;j++)
            {
                m=m_cAntAry[i].m_nPath[j];
                n=m_cAntAry[i].m_nPath[j-1];
                dbTempAry[n][m]=dbTempAry[n][m]+DBQ/m_cAntAry[i].m_dbPathLength;
                dbTempAry[m][n]=dbTempAry[n][m];
            }

            //�����к����ճ���֮�����Ϣ��
            n=m_cAntAry[i].m_nPath[N_END_CITY_ID];
            dbTempAry[n][m]=dbTempAry[n][m]+DBQ/m_cAntAry[i].m_dbPathLength;
            dbTempAry[m][n]=dbTempAry[n][m];

    }

    //==================================================================
    //���»�����Ϣ��
    for (int i=0;i<N_CITY_COUNT;i++)
    {
        for (int j=0;j<N_CITY_COUNT;j++)
        {
            g_Trial[i][j]=g_Trial[i][j]*ROU+dbTempAry[i][j]; //���µĻ�����Ϣ�� = �������Ϣ�� + �����µ���Ϣ��
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

    //������
    printf("\nThe best tour is :\n");

    char cBuf[128];
	for (int i=0;i!=N_END_CITY_ID;i++)
    {
        sprintf_s(cBuf,"%02d ",tsp.m_cBestAnt.m_nPath[i]+1);
        if (i % 20 == 0)
        {
            printf("\n");
        }
        printf(cBuf);
    }

    printf("\n\nPress any key to exit!");
    getchar();

    return 0;
}


