#pragma once

#include <iostream>
#include <string>

using namespace std;

// ��������� ����, ���������� �� �������� ��������� ����. �������� �������� �������� � ������ �� ���������� � ��������� ����
struct Node_d {
	int val;
	Node_d* pre;
	Node_d* next;
	Node_d(int v) : val(v), pre(NULL), next(NULL) {}
};

// ����� ��� ��������� ������ ���
class Deque {
private:
	// ������ ��������� ������� ����
	Node_d* last;
	// ������ ������ ������� ����
	Node_d* first;
	// ������������ � ������� ������ ����
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





