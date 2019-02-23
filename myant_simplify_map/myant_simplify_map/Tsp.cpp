#include "Tsp.h"
#include "stdafx.h"
#include "readfile.h"

//extern Inc_Cost g_Including_Cost[50][50];
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
    char cBuf[256]; //��ӡ��Ϣ��
	int it_num=0;
    //�ڵ��������ڽ���ѭ��
	while(it_num<N_IT_COUNT)
	{
        //ÿֻ��������һ��
        for (int j=0;j<N_ANT_COUNT;j++)
        {
			//m_cAntAry[j].m_nCurPointNo=Start_NO;
			//m_cAntAry[j].Simp_Flag=false;
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
        //UpdateTrial();

        //���ĿǰΪֹ�ҵ�������·���ĳ���
		//����8
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
