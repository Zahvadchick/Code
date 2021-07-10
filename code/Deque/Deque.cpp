#include "Deque.h"

// ���� ��� �� ����, ���������� ��������� �������, ����� �������� � ���, ��� ��� ����
string Deque::top() {
	if (last != NULL) {
		return "top element is " + to_string(last->val);
	}
	else {
		return "Deque is empty";
	}
}

// ���� ��� �� ����, ���������� ������ �������, ����� �������� � ���, ��� ��� ����
string Deque::front() {
	if (first != NULL) {
		return "front element is " + to_string(first->val);
	}
	else {
		return "Deque is empty";
	}
}

// ��������� ������� � ����� ����. �� ������� ����� ����, ��������� ��� ��������� �
// ��������� ���������� ��������� ������� ��� �������������� ������
string Deque::push_back(int num) {
	if (size != max_size) {
		Node_d* node = new Node_d(num);
		if (size == 0) {
			first = node;
		}
		else {
			node->pre = last;
			last->next = node;
		}
		last = node;
		size++;
		return "push successfully";
	}
	else {
		return "push error: deque is full";
	}
}

// ��������� ������� � ������ ����. �� ������� ����� ����, ��������� ��� ������ 
// � ��������� ���������� ������ ������� ��� ��������� �� �����
string Deque::push_front(int num) {
	if (size != max_size) {
		Node_d* node = new Node_d(num);
		if (size == 0) {
			last = node;
		}
		else {
			node->next = first;
			first->pre = node;
		}
		first = node;
		size++;
		return "push successfully";
	}
	else {
		return "push error: deque is full";
	}
}

// ���� ��� ����, �������� �� ����, ����� ������� ��������� ������� ����� �������������� � last ��������������� ��������.
string Deque::pop_back() {
	if (size != 0) {
		// ������� ��������� �� ��������� �������, ����� ����� �������� �� ���� ������
		Node_d* n = last;
		if (size == 1) {
			first = NULL;
			last = NULL;
		}
		else {
			last = last->pre;
		}
		size--;
		delete n;
		return "pop successfully";
	}
	else {
		return "pop error: deque is empty";
	}
}

// ���� ��� ����, �������� �� ����, ����� ������� ������ ������� ����� �������������� � first ���������� ��������.
string Deque::pop_front() {
	if (size != 0) {
		// ������� ��������� �� ��������� �������, ����� ����� �������� �� ���� ������
		Node_d* n = first;
		if (size == 1) {
			first = NULL;
			last = NULL;
		}
		else {
			first = first->next;
		}
		size--;
		delete n;
		return "pop successfully";
	}
	else {
		return "pop error: deque is empty";
	}
}

// �������� ���� �� �������. ���� ������ �������, �� ��� ����
bool Deque::empty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}