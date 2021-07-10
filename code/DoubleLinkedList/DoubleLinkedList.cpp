#include "DoubleLinkedList.h"

// ��������� ������� � ����� ������
string DoubleLinkedList::add_back(int num) {
	// ���� ������ �����, ������� ��������� �� ����
	if (size == max_size) {
		return "Double linked list has max elements";
	}
	Node_dll* node = new Node_dll(num);
	// ���� ����������� �������, �� ������� ���������� ������ � ���������
	if (size == 0) {
		head = node;
	}
	// ����� ������������� ������� � �����
	else {
		last->next = node;
		node->pre = last;
	}
	last = node;
	size++;
	return "push successfully";
}

// ��������� ������� � ������ ������
string DoubleLinkedList::add_front(int num) {
	// ���� ������ �����, ������� ��������� �� ����
	if (size == max_size) {
		return "Double linked list has max elements";
	}
	Node_dll* node = new Node_dll(num);
	// ���� ����������� �������, �� ������� ���������� ������ � ���������
	if (size == 0) {
		last = node;
	}
	// ����� ������������� ������� � ������
	else {
		head->pre = node;
		node->next = head;
	}
	head = node;
	size++;
	return "push successfully";
}

// ��������� ������� �� �������� �������
string DoubleLinkedList::add(int num, unsigned int pos) {
	// ���� ���������� ������� ������ ��� �����������, �������� �� ����
	if (pos > size) {
		return "input position more than linked list size";
	}
	// ���� ������ �����, ������� ��������� �� ����
	if (size == max_size) {
		return "Double linked list has max elements";
	}
	Node_dll* node = new Node_dll(num);
	// ������� �������
	if (pos == 0) {
		return add_front(num);
	}
	// ������� ������
	else if (pos == size) {
		return add_back(num);
	}
	// ���� ����� � �������� �������� �, ����� �������������� ����������, ��������� ���� ���������� �������
	else {
		Node_dll* cur = head;
		for (size_t i = 0; i < pos - 1; i++) {
			cur = cur->next;
		}
		node->next = cur->next;
		cur->next->pre = node;
		node->pre = cur;
		cur->next = node;
		size++;
		return "push successfully";
	}
}

// �������� ��������
bool DoubleLinkedList::remove(int num) {
	Node_dll* cur = head;
	// �������� ������ �� ��� ���, ���� �� ������ ������ �������.
	while (cur != NULL) {
		if (cur->val == num) {
			// ������������� ��������� � ����������� �� ����, �������� ������� �������� ������� ��� ���
			if (cur != head && cur != last) {
				cur->pre->next = cur->next;
				cur->next->pre = cur->pre;
			}
			else {
				if (cur == head) {
					head = head->next;
					if (head != NULL) {
						head->pre = NULL;
					}
				}
				if (cur == last) {
					last = last->pre;
					if (last != NULL) {
						last->next = NULL;
					}
				}
			}
			// ������� ������ �� ���������� ��������, �������� �����������
			delete cur;
			size--;
			return true;
		}
		cur = cur->next;
	}
	// ���� �� ������ ������� � �������� ���������, �� �������� �� �������
	return false;
}

// �������� ���� �� ������� � ���������� ���������
bool DoubleLinkedList::contains(int num) {
	Node_dll* cur = head;
	while (cur != NULL) {
		if (cur->val == num) {
			return true;
		}
		cur = cur->next;
	}
	return false;
}

// ������ ���-�� ���������
int DoubleLinkedList::count() {
	return size;
}

// ������ ������� �� �������� �������
string DoubleLinkedList::get(unsigned int pos) {
	if (pos >= size) {
		return "out of range";
	}
	Node_dll* node = head;
	for (size_t i = 0; i < pos; i++) {
		node = node->next;
	}
	return "in position " + to_string(pos) + " is " + to_string(node->val);
}

// ����� ������� � ���������� ������ �������� �������
vector<int> DoubleLinkedList::get_all() {
	Node_dll* node = head;
	vector<int> v;
	while (node != NULL) {
		v.push_back(node->val);
		node = node->next;
	}
	return v;
}

// ����� ������� � ���������� ������ � �������� �������
vector<int> DoubleLinkedList::reverse() {
	Node_dll* node = last;
	vector<int> v;
	while (node != NULL) {
		v.push_back(node->val);
		node = node->pre;
	}
	return v;
}

// ������� ��� �������� �� ������
void DoubleLinkedList::remove_all() {
	Node_dll* node = head;
	while (node != NULL) {
		Node_dll* next = node->next;
		delete node;
		node = next;
	}
	size = 0;
}

// ����������� ����������� ������ � �������� ������������ ��������
DoubleLinkedList::DoubleLinkedList(unsigned int m_size) : max_size(m_size), head(NULL), last(NULL) {}
// ����������� ����������� ������ � �������� 10000
DoubleLinkedList::DoubleLinkedList() : head(NULL), last(NULL) {}
