#ifndef MYCONTAINER
#define MYCONTAINER
#include <iostream>

template <class T>
class  MyContainer {
	
private:

	unsigned int Size;
	unsigned int Capacity;
	unsigned int Log;
	T* Buffer;

public:
	typedef T* Iterator;								
	MyContainer();										
	MyContainer(const MyContainer<T>& source);			
	~MyContainer();										
	unsigned int size() const;
	Iterator begin();
	Iterator end();
	void push(const T& value);
	void pop();
	void reserve(unsigned int capacity);
	T & operator[](unsigned int index);
	MyContainer<T> & operator = (const MyContainer<T> &);

};

template<class T>
MyContainer<T>::MyContainer() {
	Capacity = 0;
	Size = 0;
	Buffer = 0;
	Log = 0;
}

template<class T>
MyContainer<T>::MyContainer(const MyContainer<T> & source) {
	Size = source.Size;
	Log = source.Log;
	Capacity = source.Capacity;
	Buffer = new T[Size];
	for (unsigned int i = 0; i < Size; i++)
		Buffer[i] = source.Buffer[i];
}


template<class T>
MyContainer<T>& MyContainer<T>::operator = (const MyContainer<T> & source) {
	if (this != &source)
	{
		delete[] Buffer;
		Size = source.Size;
		Log = source.Log;
		Capacity = source.Capacity;
		Buffer = new T[Capacity];
		for (unsigned int i = 0; i < Size; i++)
			Buffer[i] = source.Buffer[i];
	}
	return *this;
}

template<class T>
typename MyContainer<T>::Iterator MyContainer<T>::begin() {
	return Buffer;
}

template<class T>
typename MyContainer<T>::Iterator MyContainer<T>::end() {
	return Buffer + size();
}


template<class T>
void MyContainer<T>::push(const T & source) {
	if (Size >= Capacity) {
		reserve(1 << Log);
		Log++;
	}
	Buffer[Size++] = source;
}

template<class T>
void MyContainer<T>::pop() {
	Size--;
}

template<class T>
void MyContainer<T>::reserve(unsigned int capacity) {
	T * newBuffer = new T[capacity];

	for (unsigned int i = 0; i < Size; i++)
		newBuffer[i] = Buffer[i];
	Capacity = capacity;
	delete[] Buffer;
	Buffer = newBuffer;
}

template<class T>
unsigned int MyContainer<T>::size() const {
	return Size;
}

template<class T>
T& MyContainer<T>::operator[](unsigned int index) {
	return Buffer[index];
}


template<class T>
MyContainer<T>::~MyContainer() {
	delete[] Buffer;
}


#endif