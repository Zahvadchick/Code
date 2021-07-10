#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;

struct Node_xll;

Node_xll* Xored(Node_xll* a, Node_xll* b);

class XorLinkedList {
private:
	// указатели на первый и последний элементы
	Node_xll* head;
	Node_xll* last;
	// максимальный и текущий размер
	unsigned int max_size = 10000, size = 0;
public:
	string add_front(int num);

	string add_back(int num);

	string add(int num, unsigned int pos);
	
	bool remove(int num);

	string get(unsigned int pos);

	vector<int> get_all();

	vector<int> reverse();

	int count();

	bool contains(int num);

	void remove_all();

	XorLinkedList(unsigned int m_size);
	XorLinkedList();
};



