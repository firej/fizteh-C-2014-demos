#include <iostream>
using namespace std;

class Real {
protected:
	int real;
public:
	Real(int param_real = 0): real(param_real){}
	~Real(){}
	virtual void print();
};

void Real::print(){
	cout << "Рациональное число: " << real << endl;
}

class Complex: public Real{
	int image;
public:
	Complex();
	Complex(const Complex &copy_src);
	Complex(int param_real, int param_image = 0);
	~Complex();
	const Complex operator+ (const Complex &operand2);
	// operator = ();
	virtual void print();
};

Complex::Complex(): image(0){
	real = 0;
}

Complex::Complex(const Complex &copy_src){
	cout << "Вызван хитрый конструктор!" << endl;
}

Complex::Complex(int param_real, int param_image): image(param_image){
	real = param_real;
}

Complex::~Complex(){
}

void Complex::print(){
	cout << "Комлексное число: " << real << " + " << image << "*i" << endl;
}

const Complex Complex::operator+ (const Complex &operand2){
	cout << "Вызван оператор +" << endl;
	return Complex(this->real + operand2.real, this->image + operand2.image);
}

Complex func(const Complex &some){
	return some;
}

int main(){
	Complex foo = Complex(5);
	foo.print();

	Complex bar = Complex(1, 4);
	bar.print();

	Complex zetta = foo + bar;
	zetta.print();

	return 0;
}