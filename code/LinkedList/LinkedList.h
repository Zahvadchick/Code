#pragma once
#include <vector>
#include <iostream>
#include <string>

using namespace std;

// ��������� ���������� �������� � ��������� �� ��������� �������
struct Node_ll {
	int val;
	Node_ll* next;
	Node_ll(int v) : val(v), next(NULL) {}
};

class LinkedList {
private:
	// ������ � ��������� �������
	Node_ll* head;
	Node_ll* last;
	// ������������ � ������� ������
	unsigned int max_size = 10000, size = 0;
public:
	string add(int num);

	string add(int num, size_t pos);

	bool remove(int num);

	bool contains(int num);

	int count();

	string get(unsigned int pos);

	vector<int> get_all();

	void remove_all();

	LinkedList(unsigned int m_size);
	LinkedList();
};