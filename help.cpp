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
//#include "C:\\Users\\User\\Downloads\\Contr_1.hpp" // путь
#include "C:\\Users\\User\\Downloads\\Matrix.h" // путь

using namespace std; // мб поменять


double INF = 10e6; // Максимальный вес ребра в графе

// ВАЖНО: Дейкстра написан на списках смежности
// s --- вершина, откуда идем
// v --- вершина, длину кратчайшего пути до которой ищем

void dijkstra(const vector<vector<int> >& g, int s, int v) { // Мацулевич Валерий
	// Вектор кратчайших расстояний от s до всех остальных вершин в графе
	vector<int> d(g.size(), INF);

	// По дефолту расстояние от s до s равно нулю
	d[s] = 0;

	// Заводим очередь вершин, которые будем перебирать
	// Элемент очереди --- вершина и расстояние до нее
	priority_queue<pair<int, int> > q;

	// Добавляем туда исходную вершину
	q.emplace(0, s);

	// Пока можем куда-то сходить
	while (!q.empty()) {
		// Достанем расстояние до следующей вершины
		int len = -q.top().first;
		// Достанем ее номер
		int u = q.top().second;
		// Удалим вершину из очереди
		q.pop();

		// Если известное минимальное расстояние до этой вершины меньше, чем len
		if (d[u] <= len) {
			// Переберем все пути из этой вершины до остальных
			for (int i = 0; i < g.size(); ++i) {
				int dist = g[u][i]; // Возьмем расстояние от этой вершины до i-ой
				// Если оно положительное и минимальное расстояние до i-ой вершины больше, чем минимальное расстояние до u +dist
				if (dist > 0 && d[i] > d[u] + dist) {
					// Обновим это минимальное расстояние
					d[i] = d[u] + dist;

					// Будем потом искать пути из этой вершины
					q.emplace(-d[i], i);
				}
			}
		}
	}

	// Если вершина лежит в другой компоненте связности вернем отрицательное расстояние
	if (d[v] == INF) {
		std::cout << "-1" << endl;
	}
	else {
		std::cout << d[v] << endl;
	}

	// Иначе вернем расстояние до нее
}

int readDi(string way) {
	std::fstream file;

	file.open(way, ios::in); //открыть на чтение файл заданного номера с данными

	int time; // счетчик времени
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
		dijkstra(mtrx, mstrt, mfin); // до сюда доходит
		file.getline(line, 10);
		file.getline(line, 10);

}

	time = clock() - t;
	file.close(); // закрыть файл после прочтения
	free(line);
	return time;
}

int readODU(string way) {
	std::fstream file;
	
	file.open(way, ios::in); //открыть на чтение файл заданного номера с данными

	int time; // счетчик времени
	int t = clock();

	//чтение файла
	//сохранение построчно
	// ОДУ
	// обнули строку
	
	time = clock() - t;
	file.close(); // закрыть файл после прочтения
	return time;
}

int reading(int numb) { //функция чтения файла и записи в массив

	int choice;
	std::cout << "Чтобы перейти к решению ОДУ, введите 1. \nЧтобы перейти к алгоритму Дейкстры, введите 2. \n" << endl;
	std::cin >> choice;
	while ((choice != 1) && (choice != 2)) {
		std::cout << "Некорректный выбор задачи, попробуйте еще раз\n";
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
			// сохранить слово в массив

			// преобразовать под дейкстру
			
		}
	} */
	return t;
}