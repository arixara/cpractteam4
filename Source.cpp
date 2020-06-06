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

	int way, cores;

	for (int b = 0; b < n; b++) { // для выбранного количества запусков
		
		std::cout << "Задайте путь к файлу-задаче (номер от 0 до 9)\n";
		cin >> way;
		while ((way < 0) || (way >= 10)) {
			std::cout << "Некорректное расположение файла, попробуйте еще раз\n";
			cin >> way;
		}

		std::cout << "Укажите количество потоков для выполнения задачи\n";
		cin >> cores;
		while ((cores != 1) || (cores != 2) || (cores != 4) || (cores != 8)) {
			std::cout << "Некорректное количество потоков, попробуйте еще раз\n";
			cin >> cores;
		}

		const auto gf = std::thread::hardware_concurrency(); // считать количество физических ядер. может вернуть 0

		//разделить на потоки

		int time = reading(way); //открыть файл номер way, засечь время

		cout << "\nЗапуск номер " << b + 1 << " выполнялся на файле № " << way << ", задействовано " << cores << " потоков при " << gf <<" физических ядрах. \n Выполнялся в течение" << time << "милисекунд.\n\n";
		resf << b + 1 << endl;
		resf << way << endl;
		resf << cores << endl;
		resf << gf << endl;
		resf << time << '\n' << endl;
		// очистка памяти, задействованной под уравнения
	}
	resf.close(); // закрыть файл после записи
	return 0;
}