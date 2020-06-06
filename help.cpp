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

using namespace std; // �� ��������


const int INF = 10e6; // ������������ ��� ����� � �����

// �����: �������� ������� �� ������� ���������
// s --- �������, ������ ����
// v --- �������, ����� ����������� ���� �� ������� ����

int dijkstra(const vector<vector<int> >& g, int s, int v) { // ��������� �������
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
	if (d[v] == INF) return -1;

	// ����� ������ ���������� �� ���
	return d[v];
}

int reading(int numb) { //������� ������ ����� � ������ � ������
	std:: fstream file;
	int size;
	string way = to_string(numb) + ".txt";
	
	file.open(way, ios::in); //������� �� ������ ���� ��������� ������ � �������

	file.getline(size); //������� ������



	//��������� ������

	int time; // ������� �������
	clock_t t;
	t = clock();

	// ����� ��������� ������

	time = clock() - t;
	file.close(); // ������� ���� ����� ���������
	return time;

	file.close(); // ������� ���� ����� ���������
	return time;
}