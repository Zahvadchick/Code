#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Node_s;

// класс для структуры данных стек
class Stack {
private:
	// хранит верхний элемент стека
	Node_s* head;
	// максимальный и текущий размер стека
	unsigned int max_size = 10000, size = 0;
public:

	string top();

	string push(int num);

	string pop();

	bool empty();

	Stack(unsigned int m_size);
	Stack();
};





