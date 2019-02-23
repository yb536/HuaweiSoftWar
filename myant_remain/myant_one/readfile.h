#pragma once
#include "stdafx.h"



#define ALPHA 2.0  //启发因子，信息素的重要程度
#define BETA 3.0   //期望因子，城市间距离的重要程度
#define ROU 0.3    //信息素残留参数
#define CHANGE 0.00//变异概率
#define N_ANT_COUNT 20 //蚂蚁数量
#define N_IT_COUNT 1000 //迭代次数
#define Simplify_Search_Ant_Count 100
#define DBQ 1.0 //总的信息素
#define DB_MAX 10e9 //一个标志数，10的9次方
#define Including_Trial_Max 10

struct Topology
{
int LinkID;
int SourceID;
int DestinationID;
int Cost;
};
struct Routeinfo
{
int SourceID;
int DestinationID;
int IncludingSet[50];
//std::string IncludingSet;
};
struct Node
{
int SelfNodeID;
int NeighborNodeID[600];
};

extern struct Topology topology[5000];
//struct Routeinfo routeinfo;
extern struct Node NodeInfo[600];
extern int N_POINT_COUNT;//节点个数
 //int IncludingNode_num = 0;
 //int OpResultNode_num;
 //int Back_num ;
 extern double g_Trial[600][600]; //两两城市间信息素，就是环境信息素
 extern double g_Trial_Init[600][600];
 //double g_Cost[600][600];
extern int g_Cost[600][600];
extern double g_Cost_One[600][600];
 //int OpResultNode[600];
extern int N_POINT_NO[600];
extern int N_POINT_SELF_ID[600];
extern int N_START_POINT_SELF_ID ;  //出发城市ID
extern int N_END_POINT_SELF_ID;  //终点城市ID
extern int N_INCLUDING_COUNT; //必经城市数量
extern int N_INCLUDING_SELF_ID[50];        //必经节点ID
 //返回指定范围内的随机整数
inline int rnd(int nLow,int nUpper)
{
    return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);
}

//返回指定范围内的随机浮点数
inline double rnd(double dbLow,double dbUpper)
{
    double dbTemp=rand()/((double)RAND_MAX+1.0);
    return dbLow+dbTemp*(dbUpper-dbLow);
}

//返回浮点数四舍五入取整后的浮点数
inline double ROUND(double dbA)
{
    return (double)((int)(dbA+0.5));
}