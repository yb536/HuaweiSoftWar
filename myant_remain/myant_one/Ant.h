#pragma once
#include "readfile.h"

class CAnt
{
public:
    CAnt(void);
    ~CAnt(void);

public:

	int m_nPath[600]; //�����ߵ�����ID·��
	int m_nPath_No[600]; //���ϱ��·��
    int m_dbPathLength; //�����߹���·������
	double m_dbTrialLength;
    int m_nAllowedPoint[600]; //ûȥ���ĳ���
    int m_nCurPointNo; //��ǰ���ڳ��б��
    int m_nMovedPointCount; //�Ѿ�ȥ���ĳ�������
	int end_NO;//�յ���б��
	bool Stop_Flag;
	//����4
	bool Back_Flag;
	bool Death_Flag;
	int Path_Including_Num;

public:

    int ChooseNextPoint(); //ѡ����һ������
    void Init(); //��ʼ��
    void Move(); //�����ڳ��м��ƶ�
    void Search(); //����·��
    void CalPathLength(); //���������߹���·������

};
/*
//���캯��
CAnt::CAnt(void)
{
}

//��������
CAnt::~CAnt(void)
{
}
*/

