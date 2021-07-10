#include "XorLinkedList.h"

/* xor ���� ������� ����� ������.
  �������� �� ������ ������������ � ������� ������������� ������ ������� � �������� ����������� 
  link �������� ���� � ��������� �� �������� ������� (������ �� ���������� �������, ����� �� ���������)*/
Node_xll* Xored(Node_xll* a, Node_xll* b) {
	return (Node_xll*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

// ��������� �������� ������������� �������� � xor ������� �������� ���������
struct Node_xll {
	int val;
	Node_xll* link;
	Node_xll(int v, Node_xll* pre, Node_xll* next) : val(v), link(Xored(pre, next)) {}
};

// ��������� ������� � ����� ������
string XorLinkedList::add_back(int num) {
	if (size == max_size) {
		return "Xor linked list has max elements";
	}
	// ���� ����������� ������� ��������� ������� ������ � ���������, ����� ������ ���������
	else if (size == 0) {
		Node_xll* node = new Node_xll(num, NULL, NULL);
		head = node;
		last = node;
	}
	else {
		Node_xll* pre = Xored(last->link, NULL);
		Node_xll* node = new Node_xll(num, last, NULL);
		last->link = Xored(pre, node);
		last = node;
	}
	size++;
	return "push successfully";
}

// �������� ������� � ������ ������
string XorLinkedList::add_front(int num) {
	if (size == max_size) {
		return "Xor linked list has max elements";
	}
	// ���� ����������� ������� ��������� ������� ������ � ���������, ����� ������ ������
	else if (size == 0) {
		Node_xll* node = new Node_xll(num, NULL, NULL);
		head = node;
		last = node;
	}
	else {
		Node_xll* next = Xored(NULL, head->link);
		Node_xll* node = new Node_xll(num, NULL, head);
		head->link = Xored(node, next);
		head = node;
	}
	size++;
	return "push successfully";
}

// ���������� �������� �� �������� �������
string XorLinkedList::add(int num, unsigned int pos) {
	// ���������� � ������
	if (pos == 0) {
		return add_front(num);
	}
	// ���������� � �����
	else if (pos == size) {
		return add_back(num);
	}
	// ������ �����
	if (size == max_size) {
		return "Xor linked list has max elements";
	}
	// ��������� ������� ��������� �����������
	if (pos > size) {
		return "out of range";
	}
	// ����� ������� �� �������� ������� � ��������� ���� ������� ����� �������������� ����� link � �����
	else {
		Node_xll* pre = NULL;
		Node_xll* cur = head;
		Node_xll* next = Xored(pre, cur->link);
		for (unsigned int i = 0; i < pos; i++) {
			pre = cur;
			cur = next;
			next = Xored(pre, cur->link);
		}
		Node_xll* node = new Node_xll(num, pre, cur);
		if (cur != NULL) {
			cur->link = Xored(node, next);
		}
		if (pre != NULL) {
			pre->link = Xored(Xored(pre->link, cur), node);
		}
		size++;
		return "push successfully";
	}
}

// �������� �������� � �������� ��������
bool XorLinkedList::remove(int num) {
	/*if (size == 0) {
		return false;
	}*/
	Node_xll* pre = NULL;
	Node_xll* cur = head;
	Node_xll* next = NULL;
	// ���� ������� � �������� ���������
	for (size_t i = 0; i < size; i++) {
		next = Xored(pre, cur->link);
		if (cur->val == num) {
			break;
		}
		pre = cur;
		cur = next;
	}
	// ���� �� �����, �� ������� ����
	if (cur == NULL) {
		return false;
	}
	// ���� ������� �������, ������� ��� ������������ ���������
	if (cur == head || cur == last) {
		if (cur == head) {
			if (next != NULL) {
				next->link = Xored(NULL, Xored(next->link, cur));
			}
			head = next;
		}
		if (cur == last) {
			if (pre != NULL) {
				pre->link = Xored(Xored(pre->link, cur), NULL);
			}
			last = pre;
		}
	}
	// ����� ������������� ���� link � ��������� �������
	else {
		if (pre != NULL) {
			pre->link = Xored(Xored(pre->link, cur), next);
		}
		if (next != NULL) {
			next->link = Xored(pre, Xored(next->link, cur));
		}
	}
	// ������� ������
	delete cur;
	size--;
	return true;
}

// ������ �������� �������� �� �������� �������
string XorLinkedList::get(unsigned int pos) {
	if (pos >= size) {
		return "out of range";
	}
	Node_xll* pre = NULL;
	Node_xll* cur = head;
	Node_xll* next;
	for (size_t i = 0; i < pos; i++) {
		next = Xored(pre, cur->link);
		pre = cur;
		cur = next;
	}
	return "in position " + to_string(pos) + " is " + to_string(cur->val);;
}

// ������ ������ �� ��������� ������ � ������ �������
vector<int> XorLinkedList::get_all() {
	vector<int> v;
	Node_xll* pre = NULL;
	Node_xll* cur = head;
	Node_xll* next = NULL;
	for (size_t i = 0; i < size; i++) {
		next = Xored(pre, cur->link);
		v.push_back(cur->val);
		pre = cur;
		cur = next;
	}
	return v;
}

// ������ ������ �� ��������� ������ � �������� �������
vector<int> XorLinkedList::reverse() {
	vector<int> v;
	Node_xll* pre = NULL;
	Node_xll* cur = last;
	Node_xll* next;;
	for (size_t i = 0; i < size; i++) {
		next = Xored(pre, cur->link);
		v.push_back(cur->val);
		pre = cur;
		cur = next;
	}
	return v;
}

// ������ ������
int XorLinkedList::count() {
	return size;
}

// ��������, ���� �� ������ ������� � ������
bool XorLinkedList::contains(int num) {
	Node_xll* pre = NULL;
	Node_xll* cur = head;
	Node_xll* next;
	// �������� �� ������ �� ��� ��� ���� �� ����� �������, ���� �� �� ��� ������, ������ false
	for (size_t i = 0; i < size; i++) {
		if (cur->val == num) {
			return true;
		}
		next = Xored(pre, cur->link);
		pre = cur;
		cur = next;
	}
	return false;
}

// ������� ������
void XorLinkedList::remove_all() {
	while (head != NULL) {
		Node_xll* next = Xored(NULL, head->link);
		remove(head->val);
		head = next;
	}
}

// ����������� xor ������ �������� �����
XorLinkedList::XorLinkedList(unsigned int m_size) : max_size(m_size), head(NULL) {}
// ����������� xor ������ ����� 10000
XorLinkedList::XorLinkedList() : head(NULL) {}



