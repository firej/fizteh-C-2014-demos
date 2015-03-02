#include <string>
using namespace std;
typedef unsigned int uint;

class MatrixException{
public: string desc;
public: MatrixException(string description) : desc(description){}
};

class Matrix {
	size_t	x, y;
	uint	*arr;
public:
	Matrix(size_t px, size_t py);
	Matrix(const Matrix& origin);
	~Matrix();
	uint& getElem(size_t i, size_t j);
	uint getElem(size_t i, size_t j) const;
	uint* operator [](const size_t&);
	const Matrix operator +(const Matrix&);
	const Matrix operator *(const Matrix&);
};