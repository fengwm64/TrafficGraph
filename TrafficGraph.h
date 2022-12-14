#pragma once
#include <string>
using namespace std;
#define INFINITY 888880	// 无穷
typedef string VertexType;

// 顶点的数据类型
// 带权图边权值的数据类型
struct EdgeType
{
	int distance = INFINITY;		// 路线的距离
	double time = INFINITY;		// 路线所需要的时间
	int cost = INFINITY;				// 路线的花费
	short len = 9999;
	double composite = 0;
};

// 为了便捷使用，定义一个结构体来输入图
struct GraphInfo
{
	int Vex1;					// 起点
	int Vex2;					// 终点
	EdgeType Weight = { INFINITY,INFINITY,INFINITY,1,0 };	// 权值
};

//  邻接矩阵储存交通图 
class TrafficGraph
{
public:
	TrafficGraph(VertexType V[], GraphInfo GI[], int n, int e);
	~TrafficGraph();
	void PrintGraphMat(int flag);
	void PrintInfo(int start, int end, int flag);
	void PrintCity(int v1, int v2);
	void Floyed();
	void FindPath(int start, int end, int flag);

private:
	VertexType* Vex;			// 顶点表
	EdgeType** Edge;			// 邻接矩阵，边表
	EdgeType** Dist;
	EdgeType** Path;
	int VexNum;							// 当前顶点数 
	int ArcNum;							// 当前弧数
};

// 定义
void ShowGraph();
void LowcostMenu();
void MainMenu();