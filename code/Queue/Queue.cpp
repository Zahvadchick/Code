#include "Queue.h"

using namespace std;

// ���� ������� �� �����, ���������� ��������� �������, ����� �������� � ���, ��� ������� �����
string Queue::top() {
	if (size != 0) {
		return "top element is " + to_string(last->val);
	}
	else {
		return "Queue is empty";
	}
}

// ���� ������� �� �����, ���������� ������ �������, ����� �������� � ���, ��� ������� �����
string Queue::front() {
	if (size != 0) {
		return "front element is " + to_string(first->val);
	}
	else {
		return "Queue is empty";
	}
}

// ��������� ������� � �������. �� ������� ����� ����, ��������� ��� ������ � 
// ��������� ���������� ������ ������� ��� ��������� ����� ������
string Queue::push(int num) {
	if (size != max_size) {
		Node_q* node = new Node_q(num);
		if (size == 0) {
			first = node;
		}
		else {
			last->next = node;
			node->pre = last;
		}
		last = node;
		size++;
		return "push successfully";
	}
	else {
		return "push error: queue is full";
	}
}

// ���� ������� �����, �������� �� ����, ����� ������� ������� ����� �������������� 
// � last ��������������� �������� � ��������� ������ ����������.
string Queue::pop() {
	if (size != 0) {
		Node_q* n = first;
		if (size == 1) {
			first = NULL;
			last = NULL;
		}
		else {
			first = first->next;
			first->pre = NULL;
		}
		size--;
		delete n;
		return "pop successfully";
	}
	else {
		return "pop error: queue is empty";
	}
}

// �������� ������� �� �������. ���� ������ ����� ����, �� ������� ����
bool Queue::empty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

// ����������� ��������� ������� �������� �����
Queue::Queue(unsigned int m_size) : first(NULL), last(NULL), max_size(m_size) {}
// ����������� ��������� ������� ����� 10000
Queue::Queue() : first(NULL), last(NULL) {}
