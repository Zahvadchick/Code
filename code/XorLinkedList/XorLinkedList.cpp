#include "XorLinkedList.h"

/* xor двух адресов узлов списка.
  »тераци€ по списку производитс€ с помощью использовани€ данной функции с входными параметрами 
  link текущего узла и указател€ на соседний элемент (вперед на предыдущий элемент, назад на следующий)*/
Node_xll* Xored(Node_xll* a, Node_xll* b) {
	return (Node_xll*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

// структура хран€ща€ целочисленное значение и xor адресов соседних элементов
struct Node_xll {
	int val;
	Node_xll* link;
	Node_xll(int v, Node_xll* pre, Node_xll* next) : val(v), link(Xored(pre, next)) {}
};

// добавл€ет элемент в конец списка
string XorLinkedList::add_back(int num) {
	if (size == max_size) {
		return "Xor linked list has max elements";
	}
	// если размерность нолева€ назначаем элемент первый и последним, иначе только последним
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

// добавить элемент в начало списка
string XorLinkedList::add_front(int num) {
	if (size == max_size) {
		return "Xor linked list has max elements";
	}
	// если размерность нолева€ назначаем элемент первым и последним, иначе только первым
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

// добавление элемента на заданную позицию
string XorLinkedList::add(int num, unsigned int pos) {
	// добавление в начало
	if (pos == 0) {
		return add_front(num);
	}
	// добавление в конец
	else if (pos == size) {
		return add_back(num);
	}
	// список полон
	if (size == max_size) {
		return "Xor linked list has max elements";
	}
	// переданн€ позици€ превышает размерность
	if (pos > size) {
		return "out of range";
	}
	// иначе доходим до заданной позиции у вставл€ем туда элемент путем переназначени€ св€зи link у узлов
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

// удаление элемента с заданной позицией
bool XorLinkedList::remove(int num) {
	/*if (size == 0) {
		return false;
	}*/
	Node_xll* pre = NULL;
	Node_xll* cur = head;
	Node_xll* next = NULL;
	// ищим элемент с заданным значением
	for (size_t i = 0; i < size; i++) {
		next = Xored(pre, cur->link);
		if (cur->val == num) {
			break;
		}
		pre = cur;
		cur = next;
	}
	// если не нашли, то выводим ложь
	if (cur == NULL) {
		return false;
	}
	// если элемент краевой, удал€ем его переназначив указатель
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
	// иначе переназначаем поле link у ненулевых соседей
	else {
		if (pre != NULL) {
			pre->link = Xored(Xored(pre->link, cur), next);
		}
		if (next != NULL) {
			next->link = Xored(pre, Xored(next->link, cur));
		}
	}
	// очищаем пам€ть
	delete cur;
	size--;
	return true;
}

// выдает значение элемента на заданной позиции
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

// выдает вектор из элементов списка в пр€мом пор€дке
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

// выдает вектор из элементов списка в обратном пор€дке
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

// выдает размер
int XorLinkedList::count() {
	return size;
}

// сообщает, есть ли данный элемент в списке
bool XorLinkedList::contains(int num) {
	Node_xll* pre = NULL;
	Node_xll* cur = head;
	Node_xll* next;
	// проходим по списку до тех пор пока не нашли элемент, если он не был найден, выдаем false
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

// очищает список
void XorLinkedList::remove_all() {
	while (head != NULL) {
		Node_xll* next = Xored(NULL, head->link);
		remove(head->val);
		head = next;
	}
}

// конструктор xor списка заданной длины
XorLinkedList::XorLinkedList(unsigned int m_size) : max_size(m_size), head(NULL) {}
// конструктор xor списка длины 10000
XorLinkedList::XorLinkedList() : head(NULL) {}



