#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <utility>


using namespace std; // �� ���� � ����?

class task { //���������� ������ �����
};

int reading(int numb); // ������ ����� � ���������. ��������� ������!!!
void dijkstra(const vector<vector<int> >& g, int s, int v);
int readDi(string way);
int readODU(string way);
