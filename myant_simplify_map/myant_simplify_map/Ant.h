#pragma once
#include "readfile.h"

class CAnt
{
public:
    CAnt(void);
    ~CAnt(void);

public:

	int m_nPath_ID[300]; //�����ߵ�����ID·��
	int m_nPath_No[300]; //���ϱ��·��
	int All_Path_ID[300]; //�����ߵ�����ID·��
	//int All_Path_No[300]; //���ϱ��·��
    double m_dbPathLength; //�����߹���·������
	
    int m_nAllowedPoint[300]; //ûȥ���ĳ���
    int m_nCurPointNo; //��ǰ���ڳ��б��
	int Cur_Including_Point_NO;
    int m_nMovedPointCount; //�Ѿ�ȥ���ĳ�������
	int end_NO;//�յ���б��
	bool Stop_Flag;
	//bool Simp_Flag;
	bool Good_Path;
	bool Death_Flag;
	
	//����4
	

public:

    int ChooseNextPoint(); //ѡ����һ������
    void Init(); //��ʼ��
    void Move(); //�����ڳ��м��ƶ�
	void Simp_Move();
    void Simp_Search(); //����·��
    void CalPathLength(); //���������߹���·������
	int Simp_ChooseNextPoint();
	bool Stop_Move_Or_Not();
	void Search();
	void Simp_CalPathLength();
	void Simp_Init();
	bool Good_Path_Or_Not();
};

