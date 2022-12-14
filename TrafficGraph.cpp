#include "TrafficGraph.h"
#include <iostream>
using namespace std;

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
	cout << "\t\t\t*--------------------您最关心的是：---------------------*\n";
	cout << "\t\t\t*   1) 最短里程                                         *\n";
	cout << "\t\t\t*   2) 最低花费                                         *\n";
	cout << "\t\t\t*   3) 最短时间                                         *\n";
	cout << "\t\t\t*   4) 最少中转                                         *\n";
	cout << "\t\t\t*   5) 综合考虑                                         *\n";
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

// 交通图构造函数
TrafficGraph::TrafficGraph(VertexType V[], GraphInfo GI[], int n, int e)
{
	VexNum = n;
	ArcNum = e;
	
	Vex = new VertexType[VexNum];
	Edge = new EdgeType * [VexNum];
	Path = new EdgeType * [VexNum];
	Dist = new EdgeType * [VexNum];
	for (int i = 0; i < VexNum; i++)
	{
		Edge[i] = new EdgeType[VexNum];
		Path[i] = new EdgeType[VexNum];
		Dist[i] = new EdgeType[VexNum];
	}
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
		delete[]Edge[i];
		delete[]Dist[i];
	}
	delete[]Vex;
	delete[]Dist;
	delete[]Edge;
	delete[]Path;
}
// 打印邻接矩阵（flag选择以什么为权值：0距离，1时间，2花费）
void TrafficGraph::PrintCity(int v1, int v2)
{
	cout << Vex[v1] << " -> " << Vex[v2];
}
void TrafficGraph::PrintGraphMat(int flag)
{
	switch (flag)
	{
	case 0:
		for (int i = 0; i < VexNum; i++)
		{
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
	case 1:
		for (int i = 0; i < VexNum; i++)
		{
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
	case 2:
		for (int i = 0; i < VexNum; i++)
		{
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
	}
}
void TrafficGraph::PrintInfo(int start, int end, int flag)
{
	switch (flag)
	{
	case 0:
		return;
	case 1:
		cout << " 距离仅为 " << Dist[start][end].distance << " 公里" << endl;
		break;
	case 2:
		cout << " 用时仅为 " << Dist[start][end].time << " 小时" << endl;
		break;
	case 3:
		cout << " 花费仅为 " << Dist[start][end].cost << " 元" << endl;
		break;
	case 4:
		cout << " 中转次数仅有 " << Dist[start][end].len << " 次" << endl;
		break;
	case 5:
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
				if (Dist[j][k].distance > Edge[j][i].distance + Edge[i][k].distance)
				{
					// 更新Dist[][]~
					Dist[j][k].distance = Edge[j][i].distance + Edge[i][k].distance;
					// 在path里说明是通过谁中转的
					Path[j][k].distance = i;
				}
				if (Dist[j][k].cost > Edge[j][i].cost + Edge[i][k].cost)
				{
					// 更新Dist[][]~
					Dist[j][k].cost = Edge[j][i].cost + Edge[i][k].cost;
					// 在path里说明是通过谁中转的
					Path[j][k].cost = i;
				}
				if (Dist[j][k].time > Edge[j][i].time + Edge[i][k].time)
				{
					// 更新Dist[][]~
					Dist[j][k].time = Edge[j][i].time + Edge[i][k].time;
					// 在path里说明是通过谁中转的
					Path[j][k].time = i;
				}
			}
		}
	}
}
// 打印输出最短路径（flag为考虑什么因素）
void TrafficGraph::FindPath(int start, int end, int flag)
{
	static int destination = end;
	//
	static int out = -1;
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
		break;
	case 4:
		mid = Path[start][end].len;
		break;
	case 5:
		mid = Path[start][end].composite;
		break;
	default:
		cout << "\t\t\t输入错误！" << endl;
		return;
	}
	if (mid == -1)
	{
		if (out != start)
			cout << Vex[start] << " -> ";
	}
	else
	{
		FindPath(start, mid, flag);
		FindPath(mid, end, flag);
	}
	if (out != end)
	{
		cout << Vex[end];
		if (destination != end)
			cout << " -> ";
		out = end;
	}
}