#define _CRT_SECURE_NO_WARNINGS
#include "Header.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <time.h>
#include <fstream>
#include <string>



using namespace std; // �� ��������

int parametric() { //���������� � �������
	int way, cores;
	std::cout << "������� ���� � �����-������ (����� �� 0 �� )\n"; // �� ������� ������ ������������?
	cin >> way;
	// �������� �� ������������

	std::cout << "������� ���������� ������� ��� ���������� ������\n";
	cin >> cores;
	return way, cores;
}

int reading(int numb) { //������� ������ ����� � ������ � ������
	fstream file;

	string way = to_string(numb) + ".txt";
	
	file.open(way, ios::in); //������� �� ������ ���� � ������� ������

	// ��������� ������ ��� ������ �����, ������ � ���

	file.close(); // ������� ���� ����� ���������
}