#define _CRT_SECURE_NO_WARNINGS // навести порядок в шапке

#include "Header.h"

#include <iostream>
#include <iomanip>
#include <string.h>
#include <locale.h>
#include <cstdio>
#include <stdlib.h>
#include <fstream>
#include <thread> // осторожно с версиями!!!

using namespace std;

int main() {
	setlocale(LC_ALL, "rus"); // корректное отображение кириллицы
	fstream resf; // файл для записи результатов
	resf.open("C:\\Users\\User\\Downloads\\results.txt"); //поменять путь!!!

	cout << "Введите количество планируемых запусков:\n";
	int n;
	cin >> n;
	int g, s;

	for (int b = 0; b < n; b++) { // для выбранного количества запусков
		s, g = parametric(); // задать параметры запуска
		const auto gf = std::thread::hardware_concurrency(); // считать количество физических ядер. может вернуть 0

		int reading(s); //открыть файл номер s
		//запуск таймера?

		//разделить на потоки

		// расход по типу задачи + структура решения
		
		// массив уравнений
		// выделение памяти
		// чтение файла, запись в массив классов
		// выполнение

		//стоп таймера

		// В СЛЕД СТРОЧКЕ ПОВЕСИТЬ НА ВРЕМЯ КАВЫЧКИ!!!
		cout << "\nЗапуск номер " << b + 1 << " содержал " << s << " строк, задействовано ядер - "<< g <<", из них обнаружено физических - " << gf <<" \n Выполнялся в течение << timer<< милисекунд.\n\n";
		resf << b + 1 << endl;
		resf << s << endl;
		resf << g << endl;
		resf << gf << endl;
		// resf << timer << '\n' << endl;
		// очистка памяти, задействованной под уравнения
	}
	resf.close(); // закрыть файл после записи
	return 0;
}