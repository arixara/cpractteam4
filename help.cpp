#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>



using namespace std; // мб поменять

int parametric() { //информация о запуске
	int way, cores;
	std::cout << "Задайте путь к файлу-задаче (номер от 0 до )\n"; // на сколько файлов рассчитывать?
	cin >> way;
	// проверка на корректность

	std::cout << "Укажите количество потоков для выполнения задачи\n";
	cin >> cores;
	return way, cores;
}

int reading(int numb) { //функция чтения файла и записи в массив
	fstream file;

	string way = to_string(numb) + ".txt";
	
	file.open(way, ios::in); //открыть на чтение файл с данными команд

	// выделение памяти под чтение файла, работа с ним

	file.close(); // закрыть файл после прочтения
}