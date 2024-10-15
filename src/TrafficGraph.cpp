// TrafficGraph.cpp
#include "TrafficGraph.h"
#include <iostream>
using namespace std;

///////////////////////////////////图操作///////////////////////////////////
// 交通图构造函数
TrafficGraph::TrafficGraph(VertexType V[], GraphInfo GI[], int n, int e)
{
	// 点数、边数
	VexNum = n;
	ArcNum = e;
	// 动态数组初始化
	Vex = new VertexType[VexNum];
	Edge = new EdgeType *[VexNum];
	Path = new EdgeType *[VexNum];
	Dist = new EdgeType *[VexNum];
	for (int i = 0; i < VexNum; i++)
	{
		Edge[i] = new EdgeType[VexNum];
		Path[i] = new EdgeType[VexNum];
		Dist[i] = new EdgeType[VexNum];
	}
	// 复制输入的边信息
	for (int i = 0; i < ArcNum; i++)
	{
		if (i < VexNum)
			Vex[i] = V[i];
		GI[i].Weight.len = 1;
		Edge[GI[i].Vex1 - 1][GI[i].Vex2 - 1] = GI[i].Weight;
		Edge[GI[i].Vex2 - 1][GI[i].Vex1 - 1] = GI[i].Weight;
	}
}
// 交通图析构函数
TrafficGraph::~TrafficGraph()
{
	VexNum = 0;
	ArcNum = 0;
	for (int i = 0; i < VexNum; i++)
	{
		delete[] Edge[i];
		delete[] Dist[i];
	}
	delete[] Vex;
	delete[] Dist;
	delete[] Edge;
	delete[] Path;
}
// 编辑现有边
void TrafficGraph::EidtEdge(int start, int end, int flag, int weight)
{
	switch (flag)
	{
	case 1:
		Edge[start][end].distance = weight;
		return;
	case 2:
		Edge[start][end].time = weight;
		return;
	case 3:
		Edge[start][end].cost = weight;
		return;
	case 4:
		Edge[start][end].len = weight;
		return;
	}
}
// 增加新边
void TrafficGraph::AddEdge(int start, int end, EdgeType e)
{
	Edge[start][end] = e;
}
// 打印起点终点城市
void TrafficGraph::PrintCity(int v1, int v2)
{
	cout << Vex[v1] << " -> " << Vex[v2];
}
// 打印邻接矩阵（flag选择以什么为权值：1距离，2时间，3花费，4中转）
void TrafficGraph::PrintGraphMat(int flag)
{
	cout << "\n\t\t\tGraphMat" << endl;
	switch (flag)
	{
	case 1:
		cout << "\t\t\tdistance" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Edge[i][k].distance == INFINITY)
					cout << "∞\t";
				else
					cout << Edge[i][k].distance << "\t";
			}
			cout << endl;
		}
		return;
	case 2:
		cout << "\t\t\ttime" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Edge[i][k].time == INFINITY)
					cout << "∞\t";
				else
					cout << Edge[i][k].time << "\t";
			}
			cout << endl;
		}
		return;
	case 3:
		cout << "\t\t\tcost" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Edge[i][k].cost == INFINITY)
					cout << "∞\t";
				else
					cout << Edge[i][k].cost << "\t";
			}
			cout << endl;
		}
		return;
	case 4:
		cout << "\t\t\t最少中转" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Edge[i][k].len == INFINITY)
					cout << "∞\t";
				else
					cout << Edge[i][k].len << "\t";
			}
			cout << endl;
		}
		return;
	}
}
// 打印Dist矩阵（flag选择以什么为权值：1距离，2时间，3花费，4中转）
void TrafficGraph::PrintDistMat(int flag)
{
	cout << "\n\t\t\tDistMat" << endl;
	switch (flag)
	{
	case 1:
		cout << "\t\t\tdistance" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Dist[i][k].distance == INFINITY)
					cout << "∞\t";
				else
					cout << Dist[i][k].distance << "\t";
			}
			cout << endl;
		}
		return;
	case 2:
		cout << "\t\t\ttime" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Dist[i][k].time == INFINITY)
					cout << "∞\t";
				else
					cout << Dist[i][k].time << "\t";
			}
			cout << endl;
		}
		return;
	case 3:
		cout << "\t\t\tcost" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Dist[i][k].cost == INFINITY)
					cout << "∞\t";
				else
					cout << Dist[i][k].cost << "\t";
			}
			cout << endl;
		}
		return;
	case 4:
		cout << "\t\t\t最少中转" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Dist[i][k].len == INFINITY)
					cout << "∞\t";
				else
					cout << Dist[i][k].len << "\t";
			}
			cout << endl;
		}
		return;
	}
}
// 打印Path矩阵（flag选择以什么为权值：1距离，2时间，3花费，4中转）
void TrafficGraph::PrintPathMat(int flag)
{
	cout << "\n\t\t\tPathMat" << endl;
	switch (flag)
	{
	case 1:
		cout << "\t\t\tdistance" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Path[i][k].distance == INFINITY)
					cout << "∞\t";
				else
					cout << Path[i][k].distance << "\t";
			}
			cout << endl;
		}
		return;
	case 2:
		cout << "\t\t\ttime" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Path[i][k].time == INFINITY)
					cout << "∞\t";
				else
					cout << Path[i][k].time << "\t";
			}
			cout << endl;
		}
		return;
	case 3:
		cout << "\t\t\tcost" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Path[i][k].cost == INFINITY)
					cout << "∞\t";
				else
					cout << Path[i][k].cost << "\t";
			}
			cout << endl;
		}
		return;
	case 4:
		cout << "\t\t\t最少中转" << endl;
		for (int i = 0; i < VexNum; i++)
		{
			cout << "\t\t\t";
			for (int k = 0; k < VexNum; k++)
			{
				if (Path[i][k].len == INFINITY)
					cout << "∞\t";
				else
					cout << Path[i][k].len << "\t";
			}
			cout << endl;
		}
		return;
	}
}
// 打印带权路径和
void TrafficGraph::PrintInfo(int start, int end, int flag)
{
	switch (flag)
	{
	case 1:
		cout << " 距离仅为 " << Dist[start][end].distance << " 公里" << endl;
		break;
	case 2:
		cout << " 花费仅为 " << Dist[start][end].cost << " 元" << endl;
		break;
	case 3:
		cout << " 用时仅为 " << Dist[start][end].time << " 小时" << endl;
		break;
	case 4:
		cout << " 中转次数仅有 " << Dist[start][end].len - 1 << " 次" << endl;
		break;
	default:
		return;
	}
}
// floyed算法计算多源最短路径
void TrafficGraph::Floyed()
{
	for (int i = 0; i < VexNum; i++)
	{
		for (int j = 0; j < VexNum; j++)
		{
			Dist[i][j] = Edge[i][j];
			Path[i][j].cost = -1;
			Path[i][j].distance = -1;
			Path[i][j].time = -1;
			Path[i][j].len = -1;
		}
	}
	// 外层循环表示添加一个顶点Vi作为中转
	for (int i = 0; i < VexNum; i++)
	{
		// 内层双循环用来遍历整个矩阵
		for (int j = 0; j < VexNum; j++)
		{
			for (int k = 0; k < VexNum; k++)
			{
				// 当Dist里的值已经不是最短路径时
				// 更新为通过中转点Vi的路径长
				// ！！！这里体现的是迭代的思想
				// Dist里的值永远保持最优（这里和最小生成树的算法非常像）
				if (Dist[j][k].distance > Dist[j][i].distance + Dist[i][k].distance)
				{
					// 更新Dist[][]~
					Dist[j][k].distance = Dist[j][i].distance + Dist[i][k].distance;
					// 在path里说明是通过谁中转的
					Path[j][k].distance = i;
				}
				if (Dist[j][k].cost > Dist[j][i].cost + Dist[i][k].cost)
				{
					Dist[j][k].cost = Dist[j][i].cost + Dist[i][k].cost;
					Path[j][k].cost = i;
				}
				if (Dist[j][k].time > Dist[j][i].time + Dist[i][k].time)
				{
					Dist[j][k].time = Dist[j][i].time + Dist[i][k].time;
					Path[j][k].time = i;
				}
				if (Dist[j][k].len > Dist[j][i].len + Dist[i][k].len)
				{
					Dist[j][k].len = Edge[j][i].len + Edge[i][k].len;
					Path[j][k].len = i;
				}
			}
		}
	}
}

// 记录程序一开始的终点（方便输出）
int destination = -1;
// 记录上一次输出的节点编号，防止重复输出
int out = -1;
// 初始化查找路径
void TrafficGraph::InitFind(int end)
{
	destination = end;
	out = -1;
}
// 打印输出最短路径（flag为考虑什么因素）
void TrafficGraph::FindPath(int start, int end, int flag)
{
	// 中转点
	int mid = -1;
	switch (flag)
	{
	case 0:
		return;
	case 1:
		mid = Path[start][end].distance;
		break;
	case 2:
		mid = Path[start][end].cost;
		break;
	case 3:
		mid = Path[start][end].time;
	case 4:
		mid = Path[start][end].len;
		break;
	default:
		cout << "\t\t\t输入错误！" << endl;
		return;
	}
	// 如果起点终点没有中间点了，就输出起点
	if (mid == -1)
	{
		// 要看看起点是不是已经输出了，是就不用输出
		if (out != start)
			cout << Vex[start] << " -> ";
	}
	// 还有中间点就递归
	else
	{
		FindPath(start, mid, flag);
		FindPath(mid, end, flag);
	}
	// 要看看终点是不是已经输出了，是就不用输出
	if (out != end)
	{
		cout << Vex[end];
		// 当没有到达真正终点时打印->
		if (destination != end)
			cout << " -> ";
		out = end;
	}
}

///////////////////////////////////显示菜单///////////////////////////////////
// 显示交通图菜单
void ShowGraph()
{
	cout << "\t\t\t*********************************************************" << endl;
	cout << "\t\t\t*\t\t  欢迎使用交通查询系统!                 *" << endl;
	cout << "\t\t\t*                                                       *\n";
	cout << "\t\t\t*\t\t\t北京(1)                         *" << endl;
	cout << "\t\t\t*                                                       *\n";
	cout << "\t\t\t*                                                       *\n";
	cout << "\t\t\t*\t西安(2)\t\t\t\t徐州(4)         *" << endl;
	cout << "\t\t\t*                                                       *\n";
	cout << "\t\t\t*                                                       *\n";
	cout << "\t\t\t*\t\t\t郑州(3)                         *" << endl;
	cout << "\t\t\t*                                                       *\n";
	cout << "\t\t\t*                                                       *\n";
	cout << "\t\t\t*\t成都(5)\t\t\t\t上海(7)         *" << endl;
	cout << "\t\t\t*                                                       *\n";
	cout << "\t\t\t*                                                       *\n";
	cout << "\t\t\t*\t\t\t广州(6)                         *" << endl;
	cout << "\t\t\t*********************************************************" << endl;
}
// 显示选择权重菜单
void LowcostMenu()
{
	cout << endl;
	cout << "\t\t\t*---------------------您最关心的是----------------------*\n";
	cout << "\t\t\t*   1) 最短里程                                         *\n";
	cout << "\t\t\t*   2) 最低花费                                         *\n";
	cout << "\t\t\t*   3) 最短时间                                         *\n";
	cout << "\t\t\t*   4) 最少中转                                         *\n";
	// cout << "\t\t\t*   5) 综合考虑                                         *\n";
	cout << "\t\t\t*                                                       *\n";
	cout << "\t\t\t*   0) 返回                                             *\n";
	cout << "\t\t\t*-------------------------------------------------------*\n";
	cout << "\t\t\t请输入：";
}
// 主菜单
void MainMenu()
{
	cout << endl;
	cout << "\t\t\t*------------------------主菜单-------------------------*\n";
	cout << "\t\t\t*   1) 交通查询                                         *\n";
	cout << "\t\t\t*   2) 管理员模式                                       *\n";
	cout << "\t\t\t*   0) 退出                                             *\n";
	cout << "\t\t\t*-------------------------------------------------------*\n";
	cout << "\t\t\t请输入：";
}
// 管理员菜单
void AdminMenu()
{
	cout << endl;
	cout << "\t\t\t*------------------这是一个奇怪的菜单-------------------*\n";
	cout << "\t\t\t*   1) 打印                                             *\n";
	cout << "\t\t\t*   2) 修改边                                           *\n";
	cout << "\t\t\t*   3) 添加边                                           *\n";
	cout << "\t\t\t*   0) 退出                                             *\n";
	cout << "\t\t\t*-------------------------------------------------------*\n";
	cout << "\t\t\t请输入-^_^-：";
}

// void TrafficGraph::Min_Max(GraphInfo GI[])
//{
//	// 0最小；1最大
//	double dis[2] = { 99999,-1 };
//	double cost[2] = { 99999,-1 };
//	double time[2] = { 99999, -1 };
//	for (int i = 0; i < VexNum; i++)
//	{
//		if (dis[0] > GI[i].Weight.distance)
//			dis[0] = GI[i].Weight.distance;
//		if (dis[1] < GI[i].Weight.distance)
//			dis[1] = GI[i].Weight.distance;
//		if (time[0] > GI[i].Weight.time)
//			time[0] = GI[i].Weight.time;
//		if (time[1] < GI[i].Weight.time)
//			time[1] = GI[i].Weight.time;
//		if (cost[0] > GI[i].Weight.cost)
//			cost[0] = GI[i].Weight.cost;
//		if (cost[1] < GI[i].Weight.cost)
//			cost[1] = GI[i].Weight.cost;
//	}
//
//	double* _dis = new double[VexNum];
//	double* _time = new double[VexNum];
//	double* _cost = new double[VexNum];
//	for (int i = 0; i < VexNum; i++)
//	{
//		_dis[i] = ((double)GI[i].Weight.distance - dis[0]) / (dis[1] - dis[0]);
//		_time[i] = ((double)GI[i].Weight.time - time[0]) / (time[1] - time[0]);
//		_cost[i] = ((double)GI[i].Weight.cost - cost[0]) / (cost[1] - cost[0]);
//	}
//	for (int i = 0; i < VexNum; i++)
//		GI[i].Weight.best = _dis[i] + _time[i] + _cost[i];
//	delete[]_dis;
//	delete[]_time;
//	delete[]_cost;
// }