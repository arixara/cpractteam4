#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <utility>


using namespace std; // �� ���� � ����?

/* class taskDi { //���������� ������ �����
public:
	int sizen; // ������ �������
	int strs; // ����� ������ ��������
	int fins; // �����, � ������� ����� �������
	vector < vector <int> > mtrx;
	taskDi(int k = 0, int a = 0, int b = 0, int c = 0) {
		sizen = k;
		strs = a;
		fins = b;
		mtrx = { c };
	}
}; */

int reading(int numb); // ������ ����� � ���������. ��������� ������!!!
void dijkstra(const vector<vector<int> >& g, int s, int v);
int readDi(string way);
int readODU(string way);
