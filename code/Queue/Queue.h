#pragma once

#include <iostream>
#include <string>

using namespace std;

// структура узел, отвечающая за хранение элементов очереди. Содержит значение элемента и ссылку на предыдущий и следующий узел
struct Node_q {
	int val;
	Node_q* pre;
	Node_q* next;
	Node_q(int v) : val(v), pre(NULL), next(NULL) {}
};

// класс для структуры данных очередь
class Queue {
private:
	// хранит последний элемент очереди
	Node_q* last;
	// хранит первый элемент очереди
	Node_q* first;
	// максимальный и текущий размер очереди
	unsigned int max_size = 10000, size = 0;
public:
	string top();

	string front();

	string push(int num);

	string pop();

	bool empty();

	Queue(unsigned int m_size);
	Queue();
};

