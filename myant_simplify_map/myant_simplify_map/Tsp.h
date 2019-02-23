#pragma once
#include "Ant.h"
#include "readfile.h"


class CTsp
{
public:
    CTsp(void);
    ~CTsp(void);

public:
    CAnt m_cAntAry[N_ANT_COUNT]; //蚂蚁数组
    CAnt m_cBestAnt; //定义一个蚂蚁变量，用来保存搜索过程中的最优结果
                                        //该蚂蚁不参与搜索，只是用来保存最优结果
	int Start_NO;
	int End_NO;
	bool Stop_Flag;

public:

    //初始化数据
    void InitData(); 

    //开始搜索
    void Search(); 

    //更新环境信息素
    void UpdateTrial();


};
