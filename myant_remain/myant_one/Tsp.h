#pragma once

#include "Ant.h"
#include "stdafx.h"
#include "readfile.h"


//tsp类
class CTsp
{
public:
    CTsp(void);
    ~CTsp(void);

public:
    CAnt m_cAntAry[N_ANT_COUNT]; //蚂蚁数组
    CAnt m_cBestAnt; //定义一个蚂蚁变量，用来保存搜索过程中的最优结果
                                        //该蚂蚁不参与搜索，只是用来保存最优结果
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

    //初始化数据
    void InitData(); 

    //开始搜索
    void Search(); 

    //更新环境信息素
    void UpdateTrial();
	int remain(int);

	void Trial_Init();

};

/*
//构造函数
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