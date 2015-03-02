#include "./matrix.h"
#include <cstring>
#include <iostream>

//Matrix::Matrix(size_t px, size_t py) : x(px), y(py) {
//	arr = new uint[x*y];
//}
//
//Matrix::Matrix(const Matrix& origin) {
//	this->x = origin.x;
//	this->y = origin.y;
//	this->arr = new uint[x*y];
//	memcpy(this->arr, origin.arr, sizeof(uint)*x*y);
//}
//
//Matrix::~Matrix() {
//	std::cout << "Destructor!" << std::endl;
//	delete[] arr;
//}
//
//uint& Matrix::getElem(size_t i, size_t j) {
//	return arr[x*i + j];
//}
//
//uint Matrix::getElem(size_t i, size_t j) const {
//	return arr[x*i + j];
//}
//
//uint* Matrix::operator[](const size_t& i) {
//	return arr + i*x;
//}
//
//const Matrix Matrix::operator+(const Matrix& b) {
//	if (this->x != b.x || this->y != b.y) {
//		throw MatrixException("Bad sizes!");
//	}
//	Matrix c(this->x, this->y);
//	for (int i = 0; i < this->x; i++){
//		for (int j = 0; j < this->y; j++) {
//			uint tmp = (*this)[i][j] + b.getElem(i, j);
//			c[i][j] = tmp;
//		}
//	}
//	return c;
//}