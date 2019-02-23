#pragma once

#include "Ant.h"
#include "stdafx.h"
#include "readfile.h"


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
	CAnt Most_Including_Num_Ant[N_ANT_COUNT];
	int Including_NO[50];
	bool Return_remainFlag;
	bool Return_whileFlag;
	bool Return_DiGuiFlag;
	bool Back_Flag;
	int Present_Node_Num;
	double remained;
	double leaving[600];
	int present_node[600];
	int last_node;
public:

    //��ʼ������
    void InitData(); 

    //��ʼ����
    void Search(); 

    //���»�����Ϣ��
    void UpdateTrial();
	int remain(int);

	void Trial_Init();

};

/*
//���캯��
CTsp::CTsp(void)
{
}

CTsp::~CTsp(void)
{
}
*/

struct g_Trial_I
{
	int Path_No[600];
	int Remained;
	int CurPointNo;
	bool stop_flag;
};