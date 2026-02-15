#include "RingBuffer.h"
template<typename T>
RingBuffer<T>::RingBuffer(int max_size) : array(new T[max_size]), max_size(max_size) {}
template<typename T>
RingBuffer<T>::RingBuffer(const RingBuffer<T>& other) {
	std::cout << "Copy" << std::endl;
	this->max_size = other.max_size;
	this->head = other.head;
	this->tail = other.tail;
	this->overflow = other.overflow;
	if (max_size > 0) {
		this->array = new T[max_size];
		Iterate([this, &other](int index) { this->array[index] = other.array[index]; });
	}
}
template<typename T>
RingBuffer<T>::RingBuffer(RingBuffer&& other) {
	std::cout << "Move" << std::endl;
	this->max_size = other.max_size;
	this->head = other.head;
	this->tail = other.tail;
	this->overflow = other.overflow;
	this->array = other.array;
	other.array = nullptr;
}
template<typename T>
RingBuffer<T>::~RingBuffer() {
	std::cout << "Destructor" << std::endl;
	delete[] array;
}
template<typename T>
void RingBuffer<T>::Push(T value) {
	// Store value
	array[head] = value;
	// Advance head
	head++;
	head %= max_size;
	// Advance tail
	if (head == tail) {
		overflow = true;
		tail++;
	}
	tail %= max_size;
}
template<typename T>
void RingBuffer<T>::Pop() {
	if (head != tail) {
		// Advance tail
		tail++;
		tail %= max_size;
	}
	else
		overflow = false;
}
template<typename T>
int RingBuffer<T>::Size() {
	if (head >= tail)
		return head - tail + overflow;
	else
		return max_size + head - tail + overflow;
}
template<typename T>
template<typename Func>
void RingBuffer<T>::Iterate(Func fun) {
	for (int i = 0; i < Size(); i++)
		fun((tail + i - overflow + max_size) % max_size);
}
template<typename T>
void RingBuffer<T>::Print() {
	Iterate([this](int index) {std::cout << this->array[index] << " ";});
	std::cout << std::endl;
}
template<typename T>
void RingBuffer<T>::PrintAll() {
	std::cout << "Size = " << Size() << "; head = " << head << "; tail = " << tail << "; Head()= " << Head() << "; Tail() = " << Tail() << "; ";
		for (int i = 0; i < max_size; i++)
			std::cout << array[i] << " ";
	std::cout << std::endl;
}
template<typename T>
T RingBuffer<T>::Head() {
	return array[(head - 1 + max_size) % max_size];
}
template<typename T>
T RingBuffer<T>::Tail() {
	int offset = overflow ? tail - 1 : tail;
	return array[(offset + max_size) % max_size];
}
template<typename T>
void RingBuffer<T>::ChangeBufferSize(int n) {
	T* new_array = new T[n];
	memcpy(new_array, this->array, sizeof(T) * this->max_size);
	int z = this->max_size;
	delete[] this-> array;

	this->array = new_array;
	this->max_size = n;
	this->tail = 1;
	this->head = z;
}
template<typename T>
T RingBuffer<T>::operator[](int index) {
	if (this->array != nullptr) {
		return array[index];
	}
	return 0;
}
template<typename T>
void RingBuffer<T>::operator+(RingBuffer<T>& other) {
	this->ChangeBufferSize(this->max_size + other.max_size);
	for (int i = 0; i < other.Size(); i++)
		this->Push(other[(other.tail + i - other.overflow + other.max_size) % other.max_size]);
}
template<typename T>
RingBuffer<T>& RingBuffer<T>::operator=(RingBuffer<T> &other) {
	if (this->max_size > 0) {
		delete[] this->array;
	}
	this->max_size = other.max_size;
	this->head = other.head;
	this->tail = other.tail;
	this->overflow = other.overflow;
	if (max_size > 0) {
		this->array = new T[max_size];
		Iterate([this, &other](int index) { this->array[index] = other.array[index]; });
	}
	return *this;
};
template<typename T>
void RingBuffer<T>::operator<<(int i) {
	int actual_i = i % max_size;

	if (actual_i != max_size) {
		T* new_array = new T[max_size];
		int k = 0;

		for (int j = actual_i; j < max_size; j++) {
			new_array[k] = array[j];
			k++;
		}
		for (int j = 0; j < actual_i; j++) {
			new_array[k] = array[j];
			k++;
		}

		memcpy(this->array, new_array, max_size*sizeof(T));
		delete[] new_array;
	}
}
template<typename T>
void RingBuffer<T>::operator>>(int i) {
	int actual_i = (max_size - (i % max_size));

	if (actual_i != max_size) {
		T* new_array = new T[max_size];
		int k = 0;

		
		for (int j = actual_i; j < max_size; j++) {
			new_array[k] = array[j];
			k++;
		}
		for (int j = 0; j < actual_i; j++) {
			new_array[k] = array[j];
			k++;
		}

		memcpy(this->array, new_array, max_size * sizeof(T));
		delete[] new_array;
	}
}