#ifndef RINGBUFFER_H
#define RINGBUFFER_H
template<typename T>
class RingBuffer {
private:
	T* array = nullptr;
	int max_size = 0;
	int head = 0, tail = 0;
	bool overflow = false;
	RingBuffer();
	template<typename Func>
	void Iterate(Func fun);
public:
	RingBuffer(int max_size);
	RingBuffer(const RingBuffer& other);
	RingBuffer(RingBuffer&& other);
	~RingBuffer();
	void Push(T value);
	void Pop();
	int Size();
	void Print();
	void PrintAll();
	T Head();
	T Tail();
	void ChangeBufferSize(int n);
	T operator[](int index);
	void operator+(RingBuffer& other);
	RingBuffer& operator=(RingBuffer &other);
	void operator<<(int i);
	void operator>>(int i);
};
#endif