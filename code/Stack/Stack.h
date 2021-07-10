#pragma once

#include <iostream>
#include <string>

using namespace std;

struct Node_s;

// ����� ��� ��������� ������ ����
class Stack {
private:
	// ������ ������� ������� �����
	Node_s* head;
	// ������������ � ������� ������ �����
	unsigned int max_size = 10000, size = 0;
public:

	string top();

	string push(int num);

	string pop();

	bool empty();

	Stack(unsigned int m_size);
	Stack();
};





