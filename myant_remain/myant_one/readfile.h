#pragma once
#include "stdafx.h"



#define ALPHA 2.0  //�������ӣ���Ϣ�ص���Ҫ�̶�
#define BETA 3.0   //�������ӣ����м�������Ҫ�̶�
#define ROU 0.3    //��Ϣ�ز�������
#define CHANGE 0.00//�������
#define N_ANT_COUNT 20 //��������
#define N_IT_COUNT 1000 //��������
#define Simplify_Search_Ant_Count 100
#define DBQ 1.0 //�ܵ���Ϣ��
#define DB_MAX 10e9 //һ����־����10��9�η�
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
extern int N_POINT_COUNT;//�ڵ����
 //int IncludingNode_num = 0;
 //int OpResultNode_num;
 //int Back_num ;
 extern double g_Trial[600][600]; //�������м���Ϣ�أ����ǻ�����Ϣ��
 extern double g_Trial_Init[600][600];
 //double g_Cost[600][600];
extern int g_Cost[600][600];
extern double g_Cost_One[600][600];
 //int OpResultNode[600];
extern int N_POINT_NO[600];
extern int N_POINT_SELF_ID[600];
extern int N_START_POINT_SELF_ID ;  //��������ID
extern int N_END_POINT_SELF_ID;  //�յ����ID
extern int N_INCLUDING_COUNT; //�ؾ���������
extern int N_INCLUDING_SELF_ID[50];        //�ؾ��ڵ�ID
 //����ָ����Χ�ڵ��������
inline int rnd(int nLow,int nUpper)
{
    return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);
}

//����ָ����Χ�ڵ����������
inline double rnd(double dbLow,double dbUpper)
{
    double dbTemp=rand()/((double)RAND_MAX+1.0);
    return dbLow+dbTemp*(dbUpper-dbLow);
}

//���ظ�������������ȡ����ĸ�����
inline double ROUND(double dbA)
{
    return (double)((int)(dbA+0.5));
}