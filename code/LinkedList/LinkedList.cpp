#include "LinkedList.h"

// добавляет элемент в конец списка
string LinkedList::add(int num) {
	Node_ll* node = new Node_ll(num);
	// если список пуст, назначаем переданный элемент первым и последним
	if (size == 0) {
		head = node;
		last = node;
		size++;
		return "push successfully";
	}
	// если размерность позволяет, добавляем элемент в конец
	else if (size < max_size) {
		last->next = node;
		last = node;
		size++;
		return "push successfully";
	}
	else {
		return "Linked list is full";
	}
}

// добавляет элемент на заданную позицию
string LinkedList::add(int num, size_t pos) {
	// если позиция превышает размер, то возвращаем сообщение об этом
	if (pos > size) {
		return "input position more than linked list size";
	}
	Node_ll* node = new Node_ll(num);
	// если список пуст, назначаем переданный элемент первым и последним
	if (size == 0) {
		head = node;
		last = node;
		size++;
		return "push successfully";
	}
	// если размерность позволяет, добавляем элемент на заданную позицию
	else if (size < max_size) {
		size++;
		// если позиция нолевая, то добавляем в начало
		if (pos == 0) {
			node->next = head;
			head = node;
		}
		// иначе добавляем его на заданную позицию и переназначаем ссылки соседей
		else {
			Node_ll* cur = head;
			for (size_t i = 0; i < pos - 1; i++) {
				cur = cur->next;
			}
			node->next = cur->next;
			cur->next = node;
			if (cur == last) {
				last = cur;
			}
		}
		return "push successfully";
	}
	else {
		return "Linked list is full";
	}
}

// удаляет элемент с заданным значением
bool LinkedList::remove(int num) {
	Node_ll* pre = NULL;
	Node_ll* cur = head;
	// проходим по всем элементам до тех пор, пока не найдем нужный
	while (cur != NULL) {
		// если мы его нашли, то переназначаем указатели и удаляем элемент
		if (cur->val == num) {
			if (cur != head && cur != last) {
				pre->next = cur->next;
			}
			else {
				if (cur == head) {
					head = head->next;
				}
				if (cur == last) {
					if (pre != NULL) {
						pre->next = NULL;
					}
					last = pre;
				}
			}
			delete cur;
			size--;
			return true;
		}
		pre = cur;
		cur = cur->next;
	}
	return false;
}

// ищет элемент с переданным значением в списке
bool LinkedList::contains(int num) {
	Node_ll* cur = head;
	while (cur != NULL) {
		if (cur->val == num) {
			return true;
		}
		cur = cur->next;
	}
	return false;
}

// выводит размер
int LinkedList::count() {
	return size;
}

// выводит значение элемента на заданной позиции
string LinkedList::get(unsigned int pos) {
	if (pos >= size) {
		return "out of range";
	}
	Node_ll* node = head;
	for (size_t i = 0; i < pos; i++) {
		node = node->next;
	}
	return "in position " + to_string(pos) + " is " + to_string(node->val);
}

// выводит вектор из элементов списка, сохраняя их порядок
vector<int> LinkedList::get_all() {
	Node_ll* node = head;
	vector<int> v;
	while (node != NULL) {
		v.push_back(node->val);
		node = node->next;
	}
	return v;
}

// удаляет все элементы из списка
void LinkedList::remove_all() {
	Node_ll* node = head;
	while (node != NULL) {
		Node_ll* next = node->next;
		delete node;
		node = next;
	}
	size = 0;
}

// конструктор списка с заданной максимальной длиной
LinkedList::LinkedList(unsigned int m_size) : max_size(m_size), head(NULL), last(NULL) {}
// конструктор списка с длиной 10000
LinkedList::LinkedList() : head(NULL), last(NULL) {}

