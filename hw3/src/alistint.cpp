#include "../lib/alistint.h"

// default constructor, cap to 5
AListInt::AListInt() {
	this->_data = new int[5];
	this->_size = 0;
	this->_cap = 5;

}

// constructor for a given cap
AListInt::AListInt(int cap) {
	this->_data = new int[cap];
	this->_size = 0;
	this->_cap = cap;
} 


// copy constructor
AListInt::AListInt(const AListInt& other) {
	this->_size = other._size;
	this->_cap = other._cap;
	this->_data = new int[_cap];
	for(unsigned int i = 0; i < _size; ++i) {
		_data[i] = other._data[i];
	}

}

// destructor, clear dynamic memory
AListInt::~AListInt() {
	delete[] _data;
}

// Asignment operator
AListInt& AListInt::operator=(const AListInt& other) {
	// to prevent self asignment
	if(this == &other)
		return *this;

	// copy data of other to this
	_cap = other._cap;
	_size = other._size;
	int* temp = _data;
	delete[] temp;
	_data = new int[_cap];

	for(unsigned int i = 0; i<_size; ++i) {
		_data[i] = other._data[i];
	}
	return *this;
}


int AListInt::size() const {
	return _size;
}

bool AListInt::empty() const {
	if(_size == 0) {
		return true;
	}
	
	return false;
}

void AListInt::resize() {

	int* newData = new int[_cap*2];
	for(unsigned int i = 0; i <_size; ++i) {
		newData[i] = _data[i];
	}
	int *temp = _data;
	delete[] temp;
	_data = newData;
	_cap *= 2;

}

/*
	
	 if pos is = size, append value to back of list.
	 If pos < 0, do nothing
	 If pos > size, do nothing

*/
void AListInt::insert(int pos, const int& val) {
	if(pos < 0) {
		return;
	}
	unsigned int temp = pos;
	if(temp > _size)
		return;
	if(_size == _cap) {
		resize();
	}
	for(int i = _size; i > pos; --i) {
		_data[i] = _data[i-1]; 
	}
	_data[pos] = val;
	++_size;
}

/*

	Function to remove an element at index pos.
	If pos is greater than array's size, function will do nothing.
	If pos is less than zero, function will do nothing.
	If called on an empty list, function will do nothing.
	
*/
void AListInt::remove(int pos) {
	if(pos < 0) {
		return;
	}
	unsigned int temp = pos;
	if(temp > _size-1)
		return;
	for(unsigned int i = pos; i<_size-1; ++i) {
		_data[i] = _data[i+1];
	}
	_size--;
}

/*

	Fucntion to set the value of an element at index position.
	If pos is greater than array's size, function will do nothing.
	If pos is less than zero, function will do nothing.
	If called on an empty list, function will do nothing.

*/
void AListInt::set(int position, const int& val) {
	if(position < 0) {
		return;
	}
	unsigned int temp = position;
	if(temp > _size-1) {
		return;
	}
	_data[position] = val;
}

/*

	Get element at position.
	If called on empty list, function's return will be unpredictable
	If position is less than zero, function will return element at position 0.
	If position is greater than size-1, function will return element at size -1.
	
*/	
int& AListInt::get(int position) {

	if(position < 0) {
		return _data[0];
	}
	unsigned int temp = position;
	if(temp > _size-1) {
		if(_size==0) {
			return _data[0];
		}
		return _data[_size-1];
	}
	return _data[position];
}

/*

	Get element at position.
	If called on empty list, function's return will be unpredictable
	If position is less than zero, function will return element at position 0.
	If position is greater than size-1, function will return element at size -1.
	
*/	
int const & AListInt::get(int position) const {
	if(position < 0) {
		return _data[0];
	}
	unsigned int temp = position;
	if(temp > _size-1) {
		if(_size==0) {
			return _data[0];
		}
		return _data[_size-1];
	}
	return _data[position];
}  

/*

	Overload operator+ to return the concatenation of two lists

*/
AListInt AListInt::operator+(const AListInt& other) const {
	AListInt combo(this->_size + other._size);
	int current_pos = 0;
	if(!this->empty()) {
		for(unsigned int i =0; i < this->_size; ++i) {
			combo.insert(current_pos, this->_data[i]);
			current_pos++;
		}
	}
	if(!other.empty()) {
		for(unsigned int i=0; i <other._size; ++i) {
			combo.insert(current_pos, other._data[i]);
			current_pos++;
		}
	}
	return combo;
}

// Overload Operator[] to access an element at a given location
int const & AListInt::operator[](int position) const {
	return this->get(position);
}

// Overload Operator[] to access an element at a given location
int& AListInt::operator[](int position) {
	return this->get(position);
}

