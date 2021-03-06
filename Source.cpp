#define _CRT_SECURE_NO_WARNINGS // ������� ������� � �����

#include "Header.h"

#include <iostream>
#include <iomanip>
#include <string.h>
#include <locale.h>
#include <cstdio>
#include <stdlib.h>
#include <fstream>
#include <thread> // ��������� � ��������!!!
#include "C:\\Users\\User\\Downloads\\Contr.hpp" // ����




using namespace std;

int main() {
	setlocale(LC_ALL, "rus"); // ���������� ����������� ���������
	std::fstream resf; // ���� ��� ������ �����������
	resf.open("results.txt", ios::out); //�������� ����!!!

	cout << "������� ���������� ����������� ��������:\n";
	int n;
	cin >> n;
	while (n <= 0) {
		std::cout << "������������ ���������� ��������, ���������� ��� ���\n";
		cin >> n;
	}

	int way, cores;

	for (int b = 0; b < n; b++) { // ��� ���������� ���������� ��������

		std::cout << "������� ���� � �����-������ ����� ����� ������ ����� �� 0 �� 9\n";
		cin >> way;
		while ((way < 0) || (way >= 10)) {
			std::cout << "������������ ������������ �����, ���������� ��� ���\n";
			cin >> way;
		}

		std::cout << "������� ���������� ������� (��������� 1 ��� 2 ������ ������������)\n";
		cin >> cores;
		while ((cores != 1) && (cores != 2)){
			std::cout << "������������ ���������� �������, ���������� ��� ���\n";
			cin >> cores;
		}

		const auto gf = std::thread::hardware_concurrency(); // ������� ���������� ���������� ����. ����� ������� 0

		//��������� �� ������
		 //������� ���� ����� way, ������ �����
		int time = reading(way);


		cout << "\n������ ����� " << b + 1 << " ���������� �� ����� � " << way << ", ������������� " << cores << " ������� ��� " << gf << " ���������� �����. \n���������� � ������� " << time << " ����������.\n\n";
		resf << b + 1 << endl;
		resf << way << endl;
		resf << cores << endl;
		resf << gf << endl;
		resf << time << '\n' << endl;
	}
	resf.close(); // ������� ���� ����� ������
	return 0;

}