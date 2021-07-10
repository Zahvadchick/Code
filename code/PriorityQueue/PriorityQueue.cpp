#include "PriorityQueue.h"

using namespace std;

// ���� ������� �� �����, ���������� ��������� �������, ����� �������� � ���, ��� ������� �����
string PriorityQueue::top() {
	if (size != 0) {
		return "top element is " + to_string(last->val) + ", has max priority equal " + to_string(last->priority);
	}
	else {
		return "Priority queue is empty";
	}
}

// ��������� ������� � �������. �� ������� ����� ���� � ���������� ��������� � �����������.
// ����� �������� ����, ��������� ��� � ������������ � �������� ����������.
string PriorityQueue::push(int num, int prior) {
	if (size != max_size) {
		Node_qp* node = new Node_qp(num, prior);
		// ���� ������� �����, �� ������� ��������� ��� ������ � ��������� ������������
		if (size == 0) {
			first = node;
			last = node;
		}
		else {
			// ������� ��������� ��� ����������� �� �������
			Node_qp* it = first;
			// ���� ����� ��� ����������� ��������
			while (it != NULL && it->priority < node->priority) {
				it = it->next;
			}
			// ���� ��� ��������� ����������, �� ��������� ��� ������
			if (it == first) {
				first->pre = node;
				node->next = first;
				first = node;
			}
			// ���� �� ������� ��������, ��� ��������� ����������� ����������, �� ��������� ��� � �����
			else if (it == NULL) {
				last->next = node;
				node->pre = last;
				last = node;
			}
			// ����� ��������� ��� ����� ����� ������� ����������
			else {
				node->next = it;
				if (it->pre != NULL) {
					node->pre = it->pre;
					it->pre->next = node;
				}
				it->pre = node;
			}
		}
		size++;
		return "push successfully";
	}
	else {
		return "push error: priority queue is full";
	}
}

// ��������� ������� ������������ ������ ��������
string PriorityQueue::push(int num) {
	return push(num, num);
}

// ���� ������� �����, �������� �� ����, ����� ������� ������� ����� �������������� � last ��������������� ��������.
string PriorityQueue::pop() {
	if (size != 0) {
		// �������� ��������� �� ��������� ������� ��� ����, ����� ����� �������� �� ���� ������
		Node_qp* n = last;
		if (size == 1) {
			first = NULL;
			last = NULL;
		}
		else {
			last = last->pre;
			last->next = NULL;
		}
		size--;
		delete n;
		return "pop successfully";
	}
	else {
		return "pop error: priority queue is empty";
	}
}

// �������� ������� �� �������. ���� ������ �������, �� ������� �����
bool PriorityQueue::empty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

// ����������� ��������� ������� � ����������� �������� �����
PriorityQueue::PriorityQueue(unsigned int m_size) : first(NULL), last(NULL), max_size(m_size) {}
// ����������� ��������� ������� � ����������� ������ 10000
PriorityQueue::PriorityQueue() : first(NULL), last(NULL) {}

