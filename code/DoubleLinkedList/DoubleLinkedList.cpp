#include "DoubleLinkedList.h"

// добавляет элемент в конец списка
string DoubleLinkedList::add_back(int num) {
	// если список полон, выводим сообщение об этом
	if (size == max_size) {
		return "Double linked list has max elements";
	}
	Node_dll* node = new Node_dll(num);
	// если размерность нулевая, то элемент становится первым и последним
	if (size == 0) {
		head = node;
	}
	// иначе переназначаем элемент в конец
	else {
		last->next = node;
		node->pre = last;
	}
	last = node;
	size++;
	return "push successfully";
}

// добавляет элемент в начало списка
string DoubleLinkedList::add_front(int num) {
	// если список полон, выводим сообщение об этом
	if (size == max_size) {
		return "Double linked list has max elements";
	}
	Node_dll* node = new Node_dll(num);
	// если размерность нулевая, то элемент становится первым и последним
	if (size == 0) {
		last = node;
	}
	// иначе переназначаем элемент в начало
	else {
		head->pre = node;
		node->next = head;
	}
	head = node;
	size++;
	return "push successfully";
}

// добавляет элемент на заданную позицию
string DoubleLinkedList::add(int num, unsigned int pos) {
	// если переданная позиция больше чем размерность, сообщаем об этом
	if (pos > size) {
		return "input position more than linked list size";
	}
	// если список полон, выводим сообщение об этом
	if (size == max_size) {
		return "Double linked list has max elements";
	}
	Node_dll* node = new Node_dll(num);
	// вставка вначало
	if (pos == 0) {
		return add_front(num);
	}
	// вставка вконец
	else if (pos == size) {
		return add_back(num);
	}
	// ищим место с заданной позицией и, путем переназначения указателей, вставляем туда переданный элемент
	else {
		Node_dll* cur = head;
		for (size_t i = 0; i < pos - 1; i++) {
			cur = cur->next;
		}
		node->next = cur->next;
		cur->next->pre = node;
		node->pre = cur;
		cur->next = node;
		size++;
		return "push successfully";
	}
}

// удаление элемента
bool DoubleLinkedList::remove(int num) {
	Node_dll* cur = head;
	// проходим список до тех пор, пока не найдем нужный элемент.
	while (cur != NULL) {
		if (cur->val == num) {
			// переназначаем указатели в зависимости от того, является краевым заданный элемент или нет
			if (cur != head && cur != last) {
				cur->pre->next = cur->next;
				cur->next->pre = cur->pre;
			}
			else {
				if (cur == head) {
					head = head->next;
					if (head != NULL) {
						head->pre = NULL;
					}
				}
				if (cur == last) {
					last = last->pre;
					if (last != NULL) {
						last->next = NULL;
					}
				}
			}
			// очищаем память от удаленного элемента, понижаем размерность
			delete cur;
			size--;
			return true;
		}
		cur = cur->next;
	}
	// если не найдем элемент с заданным значением, то удаление не удалось
	return false;
}

// сообщает есть ли элемент с переданным значением
bool DoubleLinkedList::contains(int num) {
	Node_dll* cur = head;
	while (cur != NULL) {
		if (cur->val == num) {
			return true;
		}
		cur = cur->next;
	}
	return false;
}

// выдает кол-во элементов
int DoubleLinkedList::count() {
	return size;
}

// выдает элемент на заданной позиции
string DoubleLinkedList::get(unsigned int pos) {
	if (pos >= size) {
		return "out of range";
	}
	Node_dll* node = head;
	for (size_t i = 0; i < pos; i++) {
		node = node->next;
	}
	return "in position " + to_string(pos) + " is " + to_string(node->val);
}

// вывод вектора с элементами списка сохраняя порядок
vector<int> DoubleLinkedList::get_all() {
	Node_dll* node = head;
	vector<int> v;
	while (node != NULL) {
		v.push_back(node->val);
		node = node->next;
	}
	return v;
}

// вывод вектора с элементами списка в обратном порядке
vector<int> DoubleLinkedList::reverse() {
	Node_dll* node = last;
	vector<int> v;
	while (node != NULL) {
		v.push_back(node->val);
		node = node->pre;
	}
	return v;
}

// удаляет все элемента из списка
void DoubleLinkedList::remove_all() {
	Node_dll* node = head;
	while (node != NULL) {
		Node_dll* next = node->next;
		delete node;
		node = next;
	}
	size = 0;
}

// конструктор двусвязного списка с заданным максимальным размером
DoubleLinkedList::DoubleLinkedList(unsigned int m_size) : max_size(m_size), head(NULL), last(NULL) {}
// конструктор двусвязного списка с размером 10000
DoubleLinkedList::DoubleLinkedList() : head(NULL), last(NULL) {}
