#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <utility>
#include <Windows.h>
#include "C:\\Users\\User\\Downloads\\Contr_1.hpp" // ����
#include "C:\\Users\\User\\Downloads\\Matrix.h" // ����
#include "C:\\Users\\User\\Downloads\\IntegratorEquasion.h" // ����

using namespace std; // �� ��������


double INF = 10e6; // ������������ ��� ����� � �����

// �����: �������� ������� �� ������� ���������
// s --- �������, ������ ����
// v --- �������, ����� ����������� ���� �� ������� ����

void dijkstra(const vector<vector<int> >& g, int s, int v) { // ��������� �������
	// ������ ���������� ���������� �� s �� ���� ��������� ������ � �����
	vector<int> d(g.size(), INF);

	// �� ������� ���������� �� s �� s ����� ����
	d[s] = 0;

	// ������� ������� ������, ������� ����� ����������
	// ������� ������� --- ������� � ���������� �� ���
	priority_queue<pair<int, int> > q;

	// ��������� ���� �������� �������
	q.emplace(0, s);

	// ���� ����� ����-�� �������
	while (!q.empty()) {
		// �������� ���������� �� ��������� �������
		int len = -q.top().first;
		// �������� �� �����
		int u = q.top().second;
		// ������ ������� �� �������
		q.pop();

		// ���� ��������� ����������� ���������� �� ���� ������� ������, ��� len
		if (d[u] <= len) {
			// ��������� ��� ���� �� ���� ������� �� ���������
			for (int i = 0; i < g.size(); ++i) {
				int dist = g[u][i]; // ������� ���������� �� ���� ������� �� i-��
				// ���� ��� ������������� � ����������� ���������� �� i-�� ������� ������, ��� ����������� ���������� �� u +dist
				if (dist > 0 && d[i] > d[u] + dist) {
					// ������� ��� ����������� ����������
					d[i] = d[u] + dist;

					// ����� ����� ������ ���� �� ���� �������
					q.emplace(-d[i], i);
				}
			}
		}
	}

	// ���� ������� ����� � ������ ���������� ��������� ������ ������������� ����������
	if (d[v] == INF) {
		std::cout << "-1" << endl;
	}
	else {
		std::cout << d[v] << endl;
	}

	// ����� ������ ���������� �� ���
}

int mainODU_A(Vector<double> y) {
	// ��������� ���������� ��� ������ RKMethodA
	RKIntegrator<DoublePendulum, RKMethodA> integrator;
	// ��������� ���������

	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	COLORREF COLOR = 2372346;
	COLORREF COLOR_1 = 123634;
	COLORREF GREEN_COLOR = RGB(0, 255, 0);
	COLORREF BLUE_COLOR = RGB(0, 0, 255);

	// �������������� � �������� b_main
	for (size_t i = 0; i < 800; ++i)
	{
		y = integrator.make_step(0, 0.02, y);
			SetPixel(mydc, i, 150 - y[0] * 50, COLOR_1);
			SetPixel(mydc, i, 150 - y[1] * 50, COLOR);
			SetPixel(mydc, i, 150 - y[2] * 10, GREEN_COLOR);
			SetPixel(mydc, i, 150 - y[3] * 10, BLUE_COLOR);
	}
	return 1;
}


int mainODU_B(Vector<double> y) {
	// ��������� ���������� ��� ������ RKMethodB
	RKIntegrator<DoublePendulum, RKMethodB> integrator;
	// ��������� ���������

	HWND myconsole = GetConsoleWindow();
	HDC mydc = GetDC(myconsole);
	COLORREF COLOR = 2372346;
	COLORREF COLOR_1 = 123634;
	COLORREF GREEN_COLOR = RGB(0, 255, 0);
	COLORREF BLUE_COLOR = RGB(0, 0, 255);

	// �������������� � �������� b_main
	for (size_t i = 0; i < 800; ++i)
	{
		y = integrator.make_step(0, 0.02, y);
		SetPixel(mydc, i, 150 - y[0] * 50, COLOR_1);
		SetPixel(mydc, i, 150 - y[1] * 50, COLOR);
		SetPixel(mydc, i, 150 - y[2] * 10, GREEN_COLOR);
		SetPixel(mydc, i, 150 - y[3] * 10, BLUE_COLOR);
	}
	return 1;
}


int readDi(string way) {
	std::fstream file;

	file.open(way, ios::in); //������� �� ������ ���� ��������� ������ � �������

	int time; // ������� �������
	int t = clock();
	std::cout << "������ �������\n";

	int cycles = 0;
	char line[100];
	file.getline(line, 100);
	if (cycles == 0) {
		cycles = (int)(line);
	}
	for (int k = 0; k < cycles; k++) {
		file.getline(line, 100);
		string a = line;
		int msize, mstrt, mfin;
		msize = atoi((cin, a).c_str());
		a.erase(0, a.find_first_of(" "));
		mstrt = atoi((cin, a).c_str());
		a.erase(0, a.find_first_of(" "));
		mfin = atoi((cin, a).c_str());
		std::vector<vector <int>> mtrx;
		for (int i = 0; i < msize; i++) {
			std::vector <int> row;
			file.getline(line, 100);
			a = line;
			for (int j = 0; j < msize; j++) {
				row.push_back(atoi((cin, a).c_str()));
				a.erase(0, a.find_first_of(" "));
			}
			mtrx.push_back(row);
		}
		dijkstra(mtrx, mstrt, mfin); // �� ���� �������
		file.getline(line, 10);
		file.getline(line, 10);

}

	time = clock() - t;
	file.close(); // ������� ���� ����� ���������
	free(line);
	return time;
}

int readODU(string way) {
	std::fstream file;
	
	file.open(way, ios::in); //������� �� ������ ���� ��������� ������ � �������
	
	std::cout << "������� ����� ������� ��� (��� RKMethodA ������� 1, ��� RKMethodB ������� 2)" << endl;
	int met;
	cin >> met;
	while ((met != 1) && (met != 2)) {
		std::cout << "������������ ����� ������, ���������� ��� ���\n";
		cin >> met;
	} 
	int time, t; // ������� �������
	
	if (met == 1) {
		t = clock();
		std::cout << "������ �������\n";
		char line[200];
		file.getline(line, 100);
		int cycles = (int)(line);
		for (int i = 0; i < cycles; i++) {
			Vector<double>cordy;
			file.getline(line, 200);
			double a, b, c, d;
			string k;
			a = atof((cin, k).c_str());
			k.erase(0, k.find_first_of(" "));
			b = atof((cin, k).c_str());
			k.erase(0, k.find_first_of(" "));
			c = atof((cin, k).c_str());
			k.erase(0, k.find_first_of(" "));
			d = atof((cin, k).c_str());
			k.erase(0, k.find_first_of(" "));
			cordy = { a, b, c, d };
			mainODU_A(cordy);
		}
	}
	else {
		t = clock();
		std::cout << "������ �������\n";
			char line[200];
			file.getline(line, 100);
			int cycles = (int)(line);
			for (int i = 0; i < cycles; i++) {
				Vector<double>cordy;
				file.getline(line, 200);
				double a, b, c, d;
				string k;
				a = atof((cin, k).c_str());
				k.erase(0, k.find_first_of(" "));
				b = atof((cin, k).c_str());
				k.erase(0, k.find_first_of(" "));
				c = atof((cin, k).c_str());
				k.erase(0, k.find_first_of(" "));
				d = atof((cin, k).c_str());
				k.erase(0, k.find_first_of(" "));
				cordy = { a, b, c, d };
				mainODU_B(cordy);
			}
	}
	
	time = clock() - t;
	file.close(); // ������� ���� ����� ���������
	return time;
}

int reading(int numb) { //������� ������ ����� � ������ � ������
	int choice;
		std::cout << "����� ������� � ������� ���, ������� 1. \n����� ������� � ��������� ��������, ������� 2. \n" << endl;
		std::cin >> choice;
		while ((choice != 1) && (choice != 2)) {
			std::cout << "������������ ����� ������, ���������� ��� ���\n";
			cin >> choice;
		}

	string way = to_string(numb) + ".txt";
	
	int t;

	if (choice == 1) {
		t = readODU(way);
	}
	else {
		t = readDi(way);
	}
	return t;
}