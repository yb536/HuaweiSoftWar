#include "Common.h"
#include "stdafx.h"


double g_Trial[N_POINT_COUNT][N_POINT_COUNT]; //两两城市间信息素，就是环境信息素
double g_Cost[N_POINT_COUNT][N_POINT_COUNT]={
//    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
	{-1,-1,-1,-1, 8,-1,-1,-1,17,-1,-1,-1,-1,15,-1,-1,-1,-1,-1, 1},//0
	{ 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//1
	{-1,-1,-1,20,-1,-1,-1,-1,-1,19,-1,-1,-1,-1,-1, 8,-1,-1,-1,-1},//2
	{14,-1,-1,-1,-1,20,-1,-1,-1,-1,-1,12,-1,-1,-1,-1,-1,-1,-1,-1},//3
	{-1,15,-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//4
	{-1,-1,-1,-1,-1,-1, 2,20,18,14,-1,-1,-1,-1,-1,-1,-1,-1,-1,20},//5
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 4,-1,-1},//6
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,20,-1, 1,-1,-1,19,-1,-1,-1},//7
	{-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,17,-1,-1,-1,-1,-1,-1,-1},//8
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,11,-1,-1,-1,-1,-1},//9
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1},//10
	{-1,-1,-1,-1, 7,-1,-1,12,-1,-1,-1,-1,-1,20,-1,-1,-1,-1,-1,20},//11
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 5,-1,-1,-1,-1,-1},//12
	{-1,-1,-1,-1, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,-1,-1},//13
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 9},//14
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,14,-1,-1,-1,-1,-1,-1,-1, 2,-1},//15
	{-1,-1,-1,-1,-1,-1,-1,-1, 1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1},//16
	{-1,-1,-1,-1,-1,20,-1,-1,-1,14,-1,20,-1,-1,-1,-1,-1,-1,10, 3},//17
	{-1,-1,-1, 8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1, 8,-1,-1,-1,-1},//18
	{-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,12,-1} //19
//    0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19
}; //两两城市间距离

//eil51.tsp城市坐标数据


//返回指定范围内的随机整数
int rnd(int nLow,int nUpper)
{
    return nLow+(nUpper-nLow)*rand()/(RAND_MAX+1);
}

//返回指定范围内的随机浮点数
double rnd(double dbLow,double dbUpper)
{
    double dbTemp=rand()/((double)RAND_MAX+1.0);
    return dbLow+dbTemp*(dbUpper-dbLow);
}

//返回浮点数四舍五入取整后的浮点数
double ROUND(double dbA)
{
    return (double)((int)(dbA+0.5));
}
