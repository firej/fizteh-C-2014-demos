#include <string>
using namespace std;
typedef unsigned int uint;

class MatrixException{
public: string desc;
public: MatrixException(string description) : desc(description){}
};

template <class T, typename sizetype>
class Matrix {
	sizetype	x, y;
	T	*arr;
public:
	Matrix(sizetype px, sizetype py) : x(px), y(py) {
		arr = new T[x*y];
	}
	Matrix(const Matrix& origin) {
		this->x = origin.x;
		this->y = origin.y;
		this->arr = new T[x*y];
		memcpy(this->arr, origin.arr, sizeof(T)*x*y);
	}
	~Matrix() {
		std::cout << "Destructor!" << std::endl;
		delete[] arr;
	}
	T& getElem(sizetype i, sizetype j){
		return arr[x*i + j];
	}

	T getElem(sizetype i, sizetype j) const {
		const_cast<Matrix*>(this)->x = 6;
		return arr[x*i + j];
	}

	T* operator [](const sizetype& i) {
		return arr + i*x;
	}
	const Matrix operator +(const Matrix& b) {
		if (this->x != b.x || this->y != b.y) {
			throw MatrixException("Bad sizes!");
		}

		Matrix c(this->x, this->y);
		for (int i = 0; i < this->x; i++){
			for (int j = 0; j < this->y; j++) {
				T tmp = (*this)[i][j] + b.getElem(i, j);
				c[i][j] = tmp;
			}
		}
		return c;
	}
};