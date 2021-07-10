#pragma once

#include <iostream>
#include <string>

using namespace std;

// структура узел, отвечающая за хранение элементов дека. Содержит значение элемента и ссылку на предыдущий и следующий узел
struct Node_d {
	int val;
	Node_d* pre;
	Node_d* next;
	Node_d(int v) : val(v), pre(NULL), next(NULL) {}
};

// класс для структуры данных дек
class Deque {
private:
	// хранит последний элемент дека
	Node_d* last;
	// хранит первый элемент дека
	Node_d* first;
	// максимальный и текущий размер дека
	unsigned int max_size = 10000, size = 0;
public:

	string top();

	string front();

	string push_back(int num);

	string push_front(int num);

	string pop_back();

	string pop_front();

	bool empty();

	Deque(unsigned int m_size) : first(NULL), last(NULL), max_size(m_size) {}
	Deque() : first(NULL), last(NULL) {}
};





