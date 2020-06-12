#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <utility>


using namespace std; // мб уйти с него?

/* class taskDi { //объ€вление класса задач
public:
	int sizen; // размер матрицы
	int strs; // точка начала движени€
	int fins; // точка, в которую нужно попасть
	vector < vector <int> > mtrx;
	taskDi(int k = 0, int a = 0, int b = 0, int c = 0) {
		sizen = k;
		strs = a;
		fins = b;
		mtrx = { c };
	}
}; */

int reading(int numb); // чтение файла с командами. заполнить скобки!!!
void dijkstra(const vector<vector<int> >& g, int s, int v);
int readDi(string way);
int readODU(string way);
