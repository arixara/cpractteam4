#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <utility>


using namespace std; // мб уйти с него?

class task { //объ€вление класса задач
};

int reading(int numb); // чтение файла с командами. заполнить скобки!!!
void dijkstra(const vector<vector<int> >& g, int s, int v);
int readDi(string way);
int readODU(string way);
