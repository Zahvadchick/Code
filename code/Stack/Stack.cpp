#include "Stack.h"

// ��������� ����, ���������� �� �������� ��������� �����. �������� �������� �������� � ������ �� ���������� ����
struct Node_s {
	int val;
	Node_s* pre;
	Node_s(int v) : val(v), pre(NULL) {}
};

// ���� ���� �� ������, ���������� ������� �������, ����� �������� � ���, ��� ���� ����
string Stack::top() {
	if (head != NULL) {
		return "top element is " + to_string(head->val);
	}
	else {
		return "Stack is empty";
	}
}

// ��������� ������� � ����. �� ������� ����� ����, ��������� ��� ������� � ���������
// ���������� ������� ������� ��� �������������� ������
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

// ���� ���� ����, �������� �� ����, ����� ������� ������� ����� �������������� � head
// ��������������� �������� � �������� ���������� ��� ������� ������.
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

// �������� ����� �� �������. ���� ������ ����� ����, �� ���� ����
bool Stack::empty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

// ����������� ��������� ���� �������� �����
Stack::Stack(unsigned int m_size) : head(NULL), max_size(m_size) {}
// ����������� ��������� ���� ����� 10000
Stack::Stack() : head(NULL) {}





