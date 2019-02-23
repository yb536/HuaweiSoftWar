#pragma once
#include "readfile.h"

class CAnt
{
public:
    CAnt(void);
    ~CAnt(void);

public:

	int m_nPath_ID[300]; //蚂蚁走的自身ID路径
	int m_nPath_No[300]; //蚂蚁编号路径
	int All_Path_ID[300]; //蚂蚁走的自身ID路径
	//int All_Path_No[300]; //蚂蚁编号路径
    double m_dbPathLength; //蚂蚁走过的路径长度
	
    int m_nAllowedPoint[300]; //没去过的城市
    int m_nCurPointNo; //当前所在城市编号
	int Cur_Including_Point_NO;
    int m_nMovedPointCount; //已经去过的城市数量
	int end_NO;//终点城市编号
	bool Stop_Flag;
	//bool Simp_Flag;
	bool Good_Path;
	bool Death_Flag;
	
	//新增4
	

public:

    int ChooseNextPoint(); //选择下一个城市
    void Init(); //初始化
    void Move(); //蚂蚁在城市间移动
	void Simp_Move();
    void Simp_Search(); //搜索路径
    void CalPathLength(); //计算蚂蚁走过的路径长度
	int Simp_ChooseNextPoint();
	bool Stop_Move_Or_Not();
	void Search();
	void Simp_CalPathLength();
	void Simp_Init();
	bool Good_Path_Or_Not();
};

