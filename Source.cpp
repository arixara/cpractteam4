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

using namespace std;

int main() {
	setlocale(LC_ALL, "rus"); // ���������� ����������� ���������
	fstream resf; // ���� ��� ������ �����������
	resf.open("C:\\Users\\User\\Downloads\\results.txt"); //�������� ����!!!

	cout << "������� ���������� ����������� ��������:\n";
	int n;
	cin >> n;
	int g, s;

	for (int b = 0; b < n; b++) { // ��� ���������� ���������� ��������
		s, g = parametric(); // ������ ��������� �������
		const auto gf = std::thread::hardware_concurrency(); // ������� ���������� ���������� ����. ����� ������� 0

		int reading(s); //������� ���� ����� s
		//������ �������?

		//��������� �� ������

		// ������ �� ���� ������ + ��������� �������
		
		// ������ ���������
		// ��������� ������
		// ������ �����, ������ � ������ �������
		// ����������

		//���� �������

		// � ���� ������� �������� �� ����� �������!!!
		cout << "\n������ ����� " << b + 1 << " �������� " << s << " �����, ������������� ���� - "<< g <<", �� ��� ���������� ���������� - " << gf <<" \n ���������� � ������� << timer<< ����������.\n\n";
		resf << b + 1 << endl;
		resf << s << endl;
		resf << g << endl;
		resf << gf << endl;
		// resf << timer << '\n' << endl;
		// ������� ������, ��������������� ��� ���������
	}
	resf.close(); // ������� ���� ����� ������
	return 0;
}