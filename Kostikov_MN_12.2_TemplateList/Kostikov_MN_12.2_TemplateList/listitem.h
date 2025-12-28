#ifndef LISTITEM_H
#define LISTITEM_H
template <typename T>
struct ListItem {
	T value;
	ListItem<T>* prev, * next;
	// Конструктор с параметрами
	ListItem<T>(T newValue, ListItem* p, ListItem* n);
};
#endif LISTITEM_H