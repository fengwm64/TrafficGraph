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
	for (int i = 0; i < VexNum; i++)
	{
		Edge[i] = new EdgeType[VexNum];
		Path[i] = new EdgeType[VexNum];
	}

	for (int i = 0; i < ArcNum; i++)
	{
		if (i < VexNum)
			Vex[i] = V[i];
		Edge[GI[i].Vex1 - 1][GI[i].Vex2 - 1] = GI[i].Weight;
		Edge[GI[i].Vex2 - 1][GI[i].Vex1 - 1] = GI[i].Weight;
	}
}
// 交通图析构函数
TrafficGraph::~TrafficGraph()
{
	VexNum = 0;
	ArcNum = 0;
	delete[]Vex;
	for (int i = 0; i < VexNum; i++)
		delete[]Edge[i];
	delete[]Edge;
	delete[]Path;
}
// 打印邻接矩阵（flag选择以什么为权值：0距离，1时间，2花费）
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

void TrafficGraph::Floyed()
{
	EdgeType** A = new EdgeType * [VexNum];
	for (int i = 0; i < VexNum; i++)
		A[i] = new EdgeType[VexNum];

	for (int i = 0; i < VexNum; i++)
	{
		for (int j = 0; j < VexNum; j++)
		{
			A[i][j] = Edge[i][j];
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
				// 当A里的值已经不是最短路径时
				// 更新为通过中转点Vi的路径长
				// ！！！这里体现的是迭代的思想 
				// A里的值永远保持最优（这里和最小生成树的算法非常像）
				if (A[j][k] > Edge[j][i] + Edge[i][k])
				{
					// 更新A[][]~
					A[j][k] = Edge[j][i] + Edge[i][k];
					// 在path里说明是通过谁中转的
					path[j][k] = i;
				}
			}
		}
	}

}