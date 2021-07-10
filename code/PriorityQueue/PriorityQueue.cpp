#include "PriorityQueue.h"

using namespace std;

// если очередь не пуста, возвращает последний элемент, иначе сообщает о том, что очередь пуста
string PriorityQueue::top() {
	if (size != 0) {
		return "top element is " + to_string(last->val) + ", has max priority equal " + to_string(last->priority);
	}
	else {
		return "Priority queue is empty";
	}
}

// добавляет элемент в очередь. Мы создаем новый узел с переданным значением и приоритетом.
// После создания узла, вставляем его в соответствии с порядком приоритета.
string PriorityQueue::push(int num, int prior) {
	if (size != max_size) {
		Node_qp* node = new Node_qp(num, prior);
		// если очередь пуста, то элемент вставляем как первый и последний одновременно
		if (size == 0) {
			first = node;
			last = node;
		}
		else {
			// создаем указатель для перемещение по очереди
			Node_qp* it = first;
			// ищем место для переданного элемента
			while (it != NULL && it->priority < node->priority) {
				it = it->next;
			}
			// если его приоритет наименьший, то назначаем его первым
			if (it == first) {
				first->pre = node;
				node->next = first;
				first = node;
			}
			// если не нашлось элемента, чей приоритет превосходит переданный, то вставляем его в конец
			else if (it == NULL) {
				last->next = node;
				node->pre = last;
				last = node;
			}
			// иначе вставляем его между двумя другими элементами
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

// добавляет элемент сприоритетом равным значению
string PriorityQueue::push(int num) {
	return push(num, num);
}

// если очередь пуста, сообщаем об этом, иначе удаляем элемент путем переназначения в last предшествующего элемента.
string PriorityQueue::pop() {
	if (size != 0) {
		// создадим указатель на удаляемый элемент для того, чтобы потом очистить от него память
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

// проверка очереди на пустоту. Если размер нолевой, то очередь пуста
bool PriorityQueue::empty() {
	if (size == 0) {
		return true;
	}
	else {
		return false;
	}
}

// конструктор создающий очередь с приоритетом заданной длины
PriorityQueue::PriorityQueue(unsigned int m_size) : first(NULL), last(NULL), max_size(m_size) {}
// конструктор создающий очередь с приоритетом длинны 10000
PriorityQueue::PriorityQueue() : first(NULL), last(NULL) {}

