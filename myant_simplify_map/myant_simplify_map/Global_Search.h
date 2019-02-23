#pragma once
class Global_Search
{
public:
	Global_Search(void);
	~Global_Search(void);

public:
	int CurPointNo;
	int PathLength;
	int MovedPointCount;
	int end_NO;
	int Path_Num;
	double BestPathLength;
	int BestPath[300];
	bool Death_Flag;
	bool Good_Path;
	int Temp_Path_No[300];
	int Temp_Path_ID[300];
	int Temp_AllowedPoint[300];


public:
	void Init();
	void Search();
	void Move();
	void Good_Path_Or_Not(int);
	void CalPathLength(int);
	bool Next_Death_Path_Or_Not(int);
	bool Next_Good_Path_Or_Not(int);
	bool Last_Good_Path_Or_Not(int);
	void Get_Best_Path(int);
};


struct Global_Path
{
	int Path_No[300];
	int Path_ID[300];
	int AllowedPoint[300];
	bool Succ_Flag;
	//bool Good_Path;
	//int All_Path_ID[300];
};


