#include <iostream>
#include <exception>

class OutOfRange {};

template <class T>
class Array {
	T*		ptr;
	size_t	size;
	size_t  capacity;
public:
	Array(): size(0), ptr(NULL), capacity(0){}
	Array(const T* array){
	}
	class iterator {
	private:
		Array*	master;
		size_t	position;
	public:
		iterator(Array *param) : master(param), position(0) {}
		iterator(Array *param, size_t pos) : master(param), position(pos) {}
		iterator(const iterator &from) {
			this->master = from.master;
			this->position = from.position;
		}
		bool operator < (const iterator &second) {
			return this->position < second.position;
		}
		const iterator operator++ (int){
			iterator tmp = *this;
			if (this->position < master->size) {
				this->position++;
				return tmp;
			}
			else {
				throw OutOfRange();
			}
		}
		T& get() {
			if (position >= master->size) {
				throw OutOfRange();
			}
			return *(master->ptr + position);
		}
		const iterator& operator= (const iterator &from) {
			this->master = from.master;
			this->position = from.position;
			return *this;
		}
	};

	iterator begin() {
		if (this->size == 0) {
			return iterator(this, 1);
		}
		return iterator(this);
	}
	iterator end() {
		return iterator(this, this->size);
	}

	size_t	push(T param){
		if (!ptr) {
			capacity = 100;
			ptr = (T*)malloc(sizeof(T) * capacity);
		}
		if (capacity < size + 1) {
			capacity = capacity << 1;
			ptr = (T*)realloc(ptr, sizeof(T) * capacity);
		}
		ptr[size++] = param;
		return size;
	}
};

int main(){
	Array<int> a;
	a.push(1);
	a.push(2);
	a.push(3);
	a.push(4);
	a.push(5);
	//Array<int>::iterator iter = a.begin();
	for (Array<int>::iterator i = a.begin(); i < a.end(); i++) {
		std::cout << "Hello!" << i.get() << std::endl;
	}
	return 0;
}