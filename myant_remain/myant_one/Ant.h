#pragma once
#include "readfile.h"

class CAnt
{
public:
    CAnt(void);
    ~CAnt(void);

public:

	int m_nPath[600]; //蚂蚁走的自身ID路径
	int m_nPath_No[600]; //蚂蚁编号路径
    int m_dbPathLength; //蚂蚁走过的路径长度
	double m_dbTrialLength;
    int m_nAllowedPoint[600]; //没去过的城市
    int m_nCurPointNo; //当前所在城市编号
    int m_nMovedPointCount; //已经去过的城市数量
	int end_NO;//终点城市编号
	bool Stop_Flag;
	//新增4
	bool Back_Flag;
	bool Death_Flag;
	int Path_Including_Num;

public:

    int ChooseNextPoint(); //选择下一个城市
    void Init(); //初始化
    void Move(); //蚂蚁在城市间移动
    void Search(); //搜索路径
    void CalPathLength(); //计算蚂蚁走过的路径长度

};
/*
//构造函数
CAnt::CAnt(void)
{
}

//析构函数
CAnt::~CAnt(void)
{
}
*/

