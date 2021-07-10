#include "Queue.h"

using namespace std;

// если очередь не пуста, возвращает последний элемент, иначе сообщает о том, что очередь пуста
string Queue::top() {
	if (size != 0) {
		return "top element is " + to_string(last->val);
	}
	else {
		return "Queue is empty";
	}
}

// если очередь не пуста, возвращает первый элемент, иначе сообщает о том, что очередь пуста
string Queue::front() {
	if (size != 0) {
		return "front element is " + to_string(first->val);
	}
	else {
		return "Queue is empty";
	}
}

// добавляет элемент в очередь. Мы создаем новый узел, назначаем его первым и 
// сохраняем предыдущий первый элемент как следующий после нового
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

// если очередь пуста, сообщаем об этом, иначе удаляем элемент путем переназначения 
// в last предшествующего элемента и очищением памяти удаленного.
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

// проверка очереди на пустоту. Если размер равен нолю, то очередь пуст
bool Queue::empty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

// конструктор создающий очередь заданной длины
Queue::Queue(unsigned int m_size) : first(NULL), last(NULL), max_size(m_size) {}
// конструктор создающий очередь длины 10000
Queue::Queue() : first(NULL), last(NULL) {}
