#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <assert.h>
#include <time.h>
#include <sys/timeb.h>
#include <errno.h>
#include <signal.h>
#include "readfile.h"
#include <vector>
#define INLINE  static __inline
#define PRINT   printf
#define MAX_RECORD  100
#define MAX_LINE_LEN 4000
using namespace std;
struct Topology topology[5000];
//struct Routeinfo routeinfo;
struct Node NodeInfo[300];
 int N_POINT_COUNT=0;//节点个数
 //int IncludingNode_num = 0;
 //int OpResultNode_num;
 //int Back_num ;
 double g_Trial[300][300]; //两两城市间信息素，就是环境信息素
 //double g_Cost[600][600];
 int g_Cost[300][300];
 //int OpResultNode[600];
int N_POINT_NO[300];
int N_POINT_SELF_ID[300];
int N_START_POINT_SELF_ID ;  //出发城市ID
int N_END_POINT_SELF_ID;  //终点城市ID
int N_INCLUDING_COUNT=0; //必经城市数量//没有读对
int N_INCLUDING_SELF_ID[50];        //必经节点ID   //没有读对
int read_file(char ** const buff, const unsigned int spec, const char * const filename)
{
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        PRINT("Fail to open file %s, %s.\n", filename, strerror(errno));
        return 0;
    }
    PRINT("Open file %s OK.\n", filename);

    char line[MAX_LINE_LEN + 2];
    unsigned int cnt = 0;
    while ((cnt < spec) && !feof(fp))
    {
        line[0] = 0;
        fgets(line, MAX_LINE_LEN + 2, fp);
        if (line[0] == 0)   continue;
        buff[cnt] = (char *)malloc(MAX_LINE_LEN + 2);
        strncpy(buff[cnt], line, MAX_LINE_LEN + 2 - 1);
        buff[cnt][4001] = 0;
        cnt++;
    }
    fclose(fp);
    PRINT("There are %d lines in file %s.\n", cnt, filename);

    return cnt;
}

int readfile(const char * const filename1,const char * const filename2)
{
	char *topo[5000];
    int edge_num;
    char *demand;
    int demand_num;
	int neighbor = 0;
	//unsigned short result[600];
    const char *split = "|";
    char *buf1 = new char[300];
    char *buf2 = new char[300];
    char *buf3 = new char[300];
    char *buf4 = new char[300];
    char *buf5 = new char[300];
    int *buf6 = new int[300];
    

	edge_num = read_file(topo, 5000, filename1);
	demand_num = read_file(&demand, 1, filename2);
	printf("%d\n",edge_num);
	printf("%d\n",demand_num);
	//int *node_sort = new int[2*edge_num];
	vector<int> node_sort(2*edge_num);
	for (int i=0; i<300; i++)
    {
        //OpResultNode[i] = -1;
        //result[i] = 0xFFFF;
		NodeInfo[i].SelfNodeID = -1;
        for (int j=0; j<300; j++)
        {
            NodeInfo[i].NeighborNodeID[j] = -1;
            g_Cost[i][j] = -1;
        }
    }
    for (int i=0; i<edge_num; i++)
    {
        sscanf(topo[i], "%[^,],%[^,],%[^,],%[^,]", buf1, buf2, buf3, buf4);
        //printf("a=%s, b=%s, c=%s, d=%s\n\n", a, b, c, d); 
        topology[i].LinkID = atoi(buf1);
        topology[i].SourceID = atoi(buf2);
        topology[i].DestinationID = atoi(buf3);
        topology[i].Cost = atoi(buf4);
        printf("LinkID=%d, SourceID=%d, DestinationID=%d, cost=%d\n\n", topology[i].LinkID, topology[i].SourceID, topology[i].DestinationID, topology[i].Cost);
    }
    for (int i=0; i<edge_num; i++)
    {
        node_sort[i*2] = topology[i].SourceID;
        node_sort[i*2+1] = topology[i].DestinationID;
        cout<<node_sort[i*2]<<"   "<<node_sort[i*2+1]<<"    ";
    }
	//cout<<endl;
	int sort_temp;
	for(int i=0;i<2*edge_num;i++) 
	{
		for(int j=1;j<2*edge_num-i;j++)
		{
			if (node_sort[j-1]>node_sort[j])
			{
				sort_temp=node_sort[j-1];
				node_sort[j-1]=node_sort[j];
				node_sort[j]=sort_temp;
			}
		 } 
	}
	buf6[0] = node_sort[0];
	for(int i=1; i<2*edge_num; i++)
		{
			if (buf6[N_POINT_COUNT] != node_sort[i])
				buf6[++N_POINT_COUNT] = node_sort[i];						
		}
	N_POINT_COUNT++;
	cout<<"顶点的id:   ";
    //N_ANT_COUNT = Node_num/(1.5);
	for( int i=0,j=0; i<N_POINT_COUNT; i++)
	{
		NodeInfo[j].SelfNodeID = buf6[i];
		cout<<NodeInfo[j].SelfNodeID<<"  ";
		j++;
	}
	cout<<endl;
	cout<<"顶点的个数: "<<N_POINT_COUNT<<endl;
    for(int j=0; j<N_POINT_COUNT; j++)
    {
        neighbor = 0;
    	for (int i=0; i<edge_num; i++)
    	{
		if ( NodeInfo[j].SelfNodeID == topology[i].SourceID )
	   		{
	   			NodeInfo[j].NeighborNodeID[neighbor] = topology[i].DestinationID;
	  			neighbor++;
	   		}
    	}
    }
    int m,n;
    for (int i=0; i<edge_num; i++)
    {
        for(int j=0; j<N_POINT_COUNT; j++)
        {
            if (topology[i].SourceID == NodeInfo[j].SelfNodeID)
                m = j;
            if (topology[i].DestinationID == NodeInfo[j].SelfNodeID)
                n = j;
        }
        g_Cost[m][n] = topology[i].Cost;
    }
    sscanf(demand, "%[^,],%[^,],%[^,]", buf1, buf2, buf5);
    //routeinfo.SourceID = atoi(buf1);
    //routeinfo.DestinationID = atoi(buf2);
	N_START_POINT_SELF_ID = atoi(buf1);
	N_END_POINT_SELF_ID  = atoi(buf2);
    buf5 = strtok(buf5,split); 
    int i = 0;
    while(buf5!=NULL) 
    {  
    	//routeinfo.IncludingSet[i] = atoi(buf5);
		N_INCLUDING_SELF_ID[i] = atoi(buf5);
        i++;
        buf5 = strtok(NULL,split); 
    } 
    N_INCLUDING_COUNT = i;
	/*
    delete [] buf1;
    delete [] buf2;
    delete [] buf3;
    delete [] buf4;
    delete [] buf5;
    delete [] buf6;
    delete [] node_sort;*/

	for(int i=0;i<300;i++)
	{
		if(NodeInfo[i].SelfNodeID!=-1)
		{
			N_POINT_NO[i] = i;
			N_POINT_SELF_ID[i] = NodeInfo[i].SelfNodeID;
		}
		
	}

	return 0;
}


