// main.cpp
#include <iostream>
#include "TrafficGraph.h"
using namespace std;

int main()
{
	EdgeType e;
	// val~为菜单选项
	int val1 = 1, val2 = 1, val3 = 1;
	// 起点终点城市编号
	int start = -1, end = -1;
	// 建立交通图
	int arc = 10, vex = 7;
	GraphInfo Traffic[10] =
		{{1, 2, {2553, 8, 885}},
		 {1, 4, {704, 2.5, 225}},
		 {1, 3, {696, 2.3, 202}},
		 {2, 3, {511, 1.5, 148}},
		 {3, 4, {349, 1.2, 112}},
		 {2, 5, {812, 3, 283}},
		 {4, 7, {651, 2, 162}},
		 {5, 6, {2368, 7, 684}},
		 {6, 7, {1385, 4, 386}},
		 {3, 6, {1579, 5, 495}}};
	VertexType V[7] = {"北京", "西安", "郑州", "徐州", "成都", "广州", "上海"};
	TrafficGraph TG(V, Traffic, vex, arc);
	TG.Floyed();
	while (val1)
	{
		ShowGraph();
		MainMenu();
		cin >> val1;
		switch (val1)
		{
		case 0: // 退出
			cout << "\n\t\t\t\t\t程序退出，欢迎下次使用！\n";
			break;
		case 1: // 交通查询
		query:
			cout << "\n\t\t\t--------------------\n";
			cout << "\t\t\t请输入您的始发地编号：";
			cin >> start;
			cout << "\t\t\t请输入您的目的地编号：";
			cin >> end;
			// 检查输入
			if (start == end || start < 0 || start > 7 || end < 0 || end > 7)
			{
				cout << "\t\t\t输入错误！！！" << endl;
				goto query;
			}
			LowcostMenu();
			cin >> val2;
			// val2==0返回
			if (!val2)
				goto query;
			cout << "\n\t\t\t-----------------------------\n";
			cout << "\t\t\t已为您选择";
			TG.PrintCity(start - 1, end - 1);
			cout << "最佳路线\n\n\t\t\t";
			TG.InitFind(end - 1);
			TG.FindPath(start - 1, end - 1, val2);
			TG.PrintInfo(start - 1, end - 1, val2);
			system("pause");
			system("cls");
			break;
		case 2: // 管理员模式
		admin:
			system("cls");
			AdminMenu();
			cin >> val2;
			switch (val2)
			{
			case 1:
				cout << "\n\t\t\t1距离，2时间，3花费，4中转" << endl;
				cout << "\t\t\t请选择打印的权值：";
				cin >> val3;
				TG.PrintGraphMat(val3);
				TG.PrintPathMat(val3);
				TG.PrintDistMat(val3);
				system("pause");
				system("cls");
				break;
			// 修改边
			case 2:
				int temp;
				cout << "\n\t\t\t修改模式：\n"
					 << endl;
				cout << "\t\t\t请输入起点：";
				cin >> start;
				cout << "\t\t\t请输入终点：";
				cin >> end;
				cout << "\n\t\t\t1距离，2时间，3花费，4中转\n";
				cout << "\t\t\t您要修改什么：";
				cin >> val3;
				cout << "\t\t\t修改为：";
				cin >> temp;
				TG.EidtEdge(start, end, val3, temp);
				system("pause");
				system("cls");
				break;
			case 3:
				cout << "\n\t\t\t添加模式：\n"
					 << endl;
				cout << "\t\t\t请输入起点：";
				cin >> start;
				cout << "\t\t\t请输入终点：";
				cin >> end;
				cout << "\t\t\t请输入距离，时间，花费：";
				cin >> e.distance >> e.time >> e.cost;
				TG.AddEdge(start, end, e);
				system("pause");
				system("cls");
				break;
			case 0:
				system("cls");
				break;
			default:
				goto admin;
			}
			break;
		default:
			break;
		}
	}

	return 0;
}