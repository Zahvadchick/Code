#pragma once
#include <iostream>
#include <vector>
#include <string>

using namespace std;

// ��������� �������� ������������� �������� � ��������� �� ���������� � ��������� ��������
struct Node_dll {
	int val;
	Node_dll* next;
	Node_dll* pre;
	Node_dll(int v) : val(v), next(NULL), pre(NULL) {}
};

class DoubleLinkedList {
private:
	// ��������� �� ������ � ��������� ��������
	Node_dll* head;
	Node_dll* last;
	// ������������ � ������� ������
	unsigned int max_size = 10000, size = 0;
public:
	string add_back(int num);

	string add_front(int num);

	string add(int num, unsigned int pos);

	bool remove(int num);

	bool contains(int num);

	int count();

	string get(unsigned int pos);

	vector<int> get_all();

	vector<int> reverse();

	void remove_all();

	DoubleLinkedList(unsigned int m_size);
	DoubleLinkedList();
};
