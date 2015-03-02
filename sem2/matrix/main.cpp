#include <iostream>
#include <ctime>
#include <stdio.h>
#include "./matrix.h"
using namespace std;

int main(){
	cout << "Hello" << endl;
	Matrix<uint, size_t> m(3, 3), m2(3, 3);
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
			m.getElem(i, j) = rand() % 100;
			cout << m.getElem(i, j) << "\t";
		}
		cout << endl;
	}
	cout << "Second:" << endl;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 3; j++) {
			m2.getElem(i, j) = rand() % 100;
			cout << m2.getElem(i, j) << "\t";
		}
		cout << endl;
	}
	try {
		Matrix<uint, size_t> c = m + m2;
		cout << "Result:" << endl;
		for (int i = 0; i < 3; i++){
			for (int j = 0; j < 3; j++) {
				cout << c.getElem(i, j) << "\t";
			}
			cout << endl;
		}
	}
	catch (MatrixException me) {
		cout << "Catched exception! Message:" << me.desc << endl;
	}
	return 0;
}