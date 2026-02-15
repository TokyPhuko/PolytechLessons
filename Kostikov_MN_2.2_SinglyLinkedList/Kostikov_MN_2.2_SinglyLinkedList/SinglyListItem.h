#pragma once
template<typename T>
class SinglyListItem {
private:
	SinglyListItem<T>* next = nullptr;
	T data = 0;
public:
	SinglyListItem();
	SinglyListItem(T data, SinglyListItem<T>* head);

	void ChangeData(T new_data);
	void ChangeNext(SinglyListItem<T>* new_next);
	T GetData();
	SinglyListItem<T>* GetNext();
};