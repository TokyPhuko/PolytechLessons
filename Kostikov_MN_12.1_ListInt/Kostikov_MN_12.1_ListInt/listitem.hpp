#include "listitem.h"
#include "list_int.h"

template <typename T>
ListItem<T>::ListItem<T>(T newValue, ListItem* p, ListItem* n) {
	value = newValue;
	prev = p;
	next = n;
}