#pragma once

#include "Ant.h"
#include "stdafx.h"
#include "readfile.h"
class Simplify
{
public:
	Simplify(void);
	~Simplify(void);
public:
	CAnt Simp_Ant[Simplify_Search_Ant_Count];
	//CAnt Simp_Best_Ant;
	int Start_NO;
	int End_NO;
	bool Simplify_Success;
	bool Output_Flag;
	bool Input_Flag;
	//double g_Including_Cost[N_INCLUDING_COUNT+2][N_INCLUDING_COUNT+2];


public:
	void InitSimp();
	void Search();
	//void Move();
	void Start_Point_Search();
	//int Choose_Next_Point();
	void Save_Start_Info(int);
	void Including_Point_Search();
	void Save_Including_Info(int,int);
	bool Simplify_Success_Or_Not();

};

struct Inc_Cost
{
	int m_nPath_No[300];
	int m_nPath_ID[300];
	double cost;
};

