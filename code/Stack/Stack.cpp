#include "Stack.h"

// структура узел, отвечающая за хранение элементов стека. Содержит значение элемента и ссылку на предыдущий узел
struct Node_s {
	int val;
	Node_s* pre;
	Node_s(int v) : val(v), pre(NULL) {}
};

// если стек не пустой, возвращает верхний элемент, иначе сообщает о том, что стек пуст
string Stack::top() {
	if (head != NULL) {
		return "top element is " + to_string(head->val);
	}
	else {
		return "Stack is empty";
	}
}

// добавляет элемент в стек. Мы создаем новый узел, назначаем его верхним и сохраняем
// предыдущий верхний элемент как предшествующий новому
string Stack::push(int num) {
	if (size != max_size) {
		Node_s* node = new Node_s(num);
		node->pre = head;
		head = node;
		size++;
		return "push successfully";
	}
	else {
		return "push error: stack is full";
	}
}

// если стек пуст, сообщаем об этом, иначе удаляем элемент путем переназначения в head
// предшествующего элемента и очищения выделенной под элемент памяти.
string Stack::pop() {
	if (head != NULL) {
		Node_s* n = head;
		head = head->pre;
		size--;
		delete n;
		return "pop successfully";
	}
	else {
		return "pop error: stack is empty";
	}
}

// проверка стека на пустоту. Если размер равен нолю, то стек пуст
bool Stack::empty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

// конструктор создающий стек заданной длины
Stack::Stack(unsigned int m_size) : head(NULL), max_size(m_size) {}
// конструктор создающий стек длины 10000
Stack::Stack() : head(NULL) {}





