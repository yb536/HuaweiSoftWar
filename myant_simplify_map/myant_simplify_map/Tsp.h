#pragma once
#include "Ant.h"
#include "readfile.h"


class CTsp
{
public:
    CTsp(void);
    ~CTsp(void);

public:
    CAnt m_cAntAry[N_ANT_COUNT]; //��������
    CAnt m_cBestAnt; //����һ�����ϱ����������������������е����Ž��
                                        //�����ϲ�����������ֻ�������������Ž��
	int Start_NO;
	int End_NO;
	bool Stop_Flag;

public:

    //��ʼ������
    void InitData(); 

    //��ʼ����
    void Search(); 

    //���»�����Ϣ��
    void UpdateTrial();


};
