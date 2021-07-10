#pragma once

#include <iostream>
#include <string>

using namespace std;

// ��������� ����, ���������� �� �������� ��������� �������. �������� �������� �������� � ������ �� ���������� � ��������� ����
struct Node_q {
	int val;
	Node_q* pre;
	Node_q* next;
	Node_q(int v) : val(v), pre(NULL), next(NULL) {}
};

// ����� ��� ��������� ������ �������
class Queue {
private:
	// ������ ��������� ������� �������
	Node_q* last;
	// ������ ������ ������� �������
	Node_q* first;
	// ������������ � ������� ������ �������
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

