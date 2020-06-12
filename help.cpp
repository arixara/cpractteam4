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
//#include "C:\\Users\\User\\Downloads\\Contr_1.hpp" // ����
#include "C:\\Users\\User\\Downloads\\Matrix.h" // ����

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

int readDi(string way) {
	std::fstream file;

	file.open(way, ios::in); //������� �� ������ ���� ��������� ������ � �������

	int time; // ������� �������
	int t = clock();

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

	int time; // ������� �������
	int t = clock();

	//������ �����
	//���������� ���������
	// ���
	// ������ ������
	
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

	/*	 char line[100];
	int k;
	int i, ctr = 0;
	double** narray;
	while (file.getline(line, 100)) {
		ctr += 1;
		if (size == -1) {
			size == (int)(line);
			narray = new double* [size];
			for (i; i < size; i++) {
				narray[i] = new double[4];
			}
			i = 0;
		}
		while ((line[i] != ',') || (line[i] != '\n')) {
			if (line[i] == ',') {
				k += 1;
			}
//			narray[ctr * 4 + k] = (double)(line[k])
			// ��������� ����� � ������

			// ������������� ��� ��������
			
		}
	} */
	return t;
}