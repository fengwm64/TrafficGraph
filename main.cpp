#include <iostream>
#include "TrafficGraph.h"
using namespace std;

int main()
{
	// 
	int val1 = 1, val2 = 1, val3 = 1;
	int start = -1, end = -1;
	// 建立交通图
	int arc = 10, vex = 7;
	GraphInfo Traffic[10] =
	{	{1,2,{2553,8,885}},
		{1,4,{704,2.5,225}},
		{1,3,{696,2.3,202}},
		{2,3,{511,1.5,148}},
		{3,4,{349,1.2,112}},
		{2,5,{812,3,283}},
		{4,7,{651,2,162}},
		{5,6,{2368,7,684}},
		{6,7,{1385,4,386}},
		{3,6,{1579,5,495}} };
	VertexType V[7] = { "北京","西安","郑州","徐州","成都","广州","上海" };
	TrafficGraph TG(V, Traffic, vex, arc);
	while (val1)
	{
		ShowGraph();
		MainMenu();
		cin >> val1;
		switch (val1)
		{
		case 0:	// 退出
			cout << "\n\t\t\t\t\t程序退出，欢迎下次使用！\n";
			break;
		case 1:	// 交通查询
			cout << "\n\t\t\t--------------------\n";
			cout << "\t\t\t请输入您的始发地编号：";
			cin >> start;
			cout << "\t\t\t请输入您的目的地编号：";
			cin >> end;
			LowcostMenu();
			cin >> val2;
			TG.Floyed();
			cout << "\n\t\t\t-----------------------------\n";
			cout << "\t\t\t已为您选择";
			TG.PrintCity(start - 1, end - 1);
			cout << "最佳路线\n\n\t\t\t";
			TG.FindPath(start - 1, end - 1, val2);
			TG.PrintInfo(start - 1, end - 1, val2);
			system("pause");
			system("cls");
			break;
		case 2:	// 管理员模式
			cin >> val2;
			switch (val2)
			{
			default:
				TG.PrintGraphMat(2);
				break;
			}
			break;
		default:
			break;
		}
	}
	
	return 0;
}