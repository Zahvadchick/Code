#include "Deque.h"

// если дек не пуст, возвращает последний элемент, иначе сообщает о том, что дек пуст
string Deque::top() {
	if (last != NULL) {
		return "top element is " + to_string(last->val);
	}
	else {
		return "Deque is empty";
	}
}

// если дек не пуст, возвращает первый элемент, иначе сообщает о том, что дек пуст
string Deque::front() {
	if (first != NULL) {
		return "front element is " + to_string(first->val);
	}
	else {
		return "Deque is empty";
	}
}

// добавл€ет элемент в конец дека. ћы создаем новый узел, назначаем его последним и
// сохран€ем предыдущий последний элемент как предшествующий новому
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

// добавл€ет элемент в начало дека. ћы создаем новый узел, назначаем его первым 
// и сохран€ем предыдущий первый элемент как следующий за новым
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

// если дек пуст, сообщаем об этом, иначе удал€ем последний элемент путем переназначени€ в last предшествующего элемента.
string Deque::pop_back() {
	if (size != 0) {
		// создаем указатель на удал€емый элемент, чтобы затем очистить от него пам€ть
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

// если дек пуст, сообщаем об этом, иначе удал€ем первый элемент путем переназначени€ в first следующего элемента.
string Deque::pop_front() {
	if (size != 0) {
		// создаем указатель на удал€емый элемент, чтобы затем очистить от него пам€ть
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

// проверка дека на пустоту. ≈сли размер нолевой, то дек пуст
bool Deque::empty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}