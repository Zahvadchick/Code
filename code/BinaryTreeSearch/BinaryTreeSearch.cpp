#include "BinaryTreeSearch.h"

// рекурсивная функция, которая ищет место для вставки и, после нахождения, вставляет элемент
void BinaryTreeSearch::rec(Node_bts* root, Node_bts* node) {
	if (node->val < root->val) {
		if (root->left == NULL) {
			root->left = node;
		}
		else {
			rec(root->left, node);
		}
	}
	else {
		if (root->right == NULL) {
			root->right = node;
		}
		else {
			rec(root->right, node);
		}
	}
}

// добавление элемента
bool BinaryTreeSearch::add(int num) {
	// если размерность максимальна, то вставка не возможна
	if (size == max_size) {
		return false;
	}
	Node_bts* node = new Node_bts(num);
	// если дерево пусто, то добавляемый элемент становится корневым
	if (size == 0) {
		head = node;
	}
	// иначе вызываем рекурсивную функцию для вставки элемента на нужное место
	else {
		rec(head, node);
	}
	size++;
	return true;
}

// удаление элемента
bool BinaryTreeSearch::remove(int num) {
	Node_bts* root = head;
	Node_bts* par = NULL;
	bool is_right;
	// ищим удаляемый элемент. На каждой итерации запоминаем в какую сторону мы идем (нужно для переназначения детей после удаления)
	while (root) {
		if (root->val == num) {
			break;
		}
		else if (root->val > num) {
			par = root;
			root = root->left;
			is_right = false;
		}
		else {
			par = root;
			root = root->right;
			is_right = true;
		}
	}
	// если элемент не найдем - удаление не удалось
	if (root == NULL) {
		return false;
	}
	// если элемент был единственным, то удаляем его
	else if (size == 1) {
		head = NULL;
	}
	// если элемент является корневым, переназначим корень на правого потомка и вставим левого потомка (если он не нолевой)
	// на самый левый узел правого поддерева, если правый потомок пуст, то корнем обозначим левого
	else if (root == head) {
		if (!root->left) {
			head = root->right;
		}
		else if (root->right) {
			Node_bts* node = root->right;
			while (node->left) {
				node = node->left;
			}
			node->left = root->left;
			head = root->left;
		}
		else {
			head = root->left;
		}
	}
	// если элемент не коревой, расмотрим четыре случая
	else {
		// у элемента не было ни одного потомка, тогда просто зануляем потомка, соответствующему элементу, у родителя
		if (!root->right && !root->left) {
			if (par != NULL) {
				if (is_right) {
					par->right = NULL;
				}
				else {
					par->left = NULL;
				}
			}
		}
		// у элемента были оба потомка, тогда на его место вставляем правого потомка, 
		// а левого назначаем как самый левый элемент в правом подереве
		else if (root->right && root->left) {
			Node_bts* node = root->right;
			while (node->left) {
				node = node->left;
			}
			node->left = root->left;
			if (par) {
				if (is_right) {
					par->right = root->right;
				}
				else {
					par->left = root->right;
				}
			}
		}
		// у элемента только правый потомок. Назначаем потомка на место переданного элемента
		else if (root->right) {
			if (par) {
				if (is_right) {
					par->right = root->right;
				}
				else {
					par->left = root->right;
				}
			}
		}
		// у элемента только лувый потомок. Назначаем потомка на место переданного элемента
		else if (root->left) {
			if (par) {
				if (is_right) {
					par->right = root->left;
				}
				else {
					par->left = root->left;
				}
			}
		}
	}
	// очищаем память и сообщаем об успешном удалении
	delete root;
	size--;
	return true;
}

// поиск элемента
Node_bts* BinaryTreeSearch::find(int num) {
	Node_bts* root = head;
	// ищим элемент в дереве. Идем налево если элемент меньше текущего и направо если наоборот.
	while (root) {
		if (root->val == num) {
			break;
		}
		else if (root->val > num) {
			root = root->left;
		}
		else {
			root = root->right;
		}
	}
	// если элемент не был найден, то будет выведен NULL
	return root;
}

// выдает указатель на корневой элемент
Node_bts* BinaryTreeSearch::get_head() {
	return head;
}

// выдает указатель на минимальный элемент (самый левый)
Node_bts* BinaryTreeSearch::get_min() {
	Node_bts* root = head;
	while (root->left) {
		root = root->left;
	}
	return root;
}

// выдает указатель на наибольший элемент (самый правый)
Node_bts* BinaryTreeSearch::get_max() {
	Node_bts* root = head;
	while (root->right) {
		root = root->right;
	}
	return root;
}

// прямой обход дерева
void BinaryTreeSearch::preorder(Node_bts* node, vector<int>& v) {
	if (!node) {
		return;
	}
	// добавляем элемент
	v.push_back(node->val);
	// обходим левое поддерево
	preorder(node->left, v);
	// обходим правое поддерево
	preorder(node->right, v);
}

// центрированный обход дерева
void BinaryTreeSearch::inorder(Node_bts* node, vector<int>& v) {
	if (!node) {
		return;
	}
	// обходим левое поддерево
	inorder(node->left, v);
	// добавляем элемент
	v.push_back(node->val);
	// обходит правое поддерево
	inorder(node->right, v);
}

// обратный обход дерева
void BinaryTreeSearch::postorder(Node_bts* node, vector<int>& v) {
	if (!node) {
		return;
	}
	// обходим левое поддерево
	postorder(node->left, v);
	// обходим правое поддерево
	postorder(node->right, v);
	// добавляем элемент
	v.push_back(node->val);
}

// очищаем дерево
void BinaryTreeSearch::remove_all() {
	size = 0;
	// очищаем память от узлов
	remove_node(head);
	head = NULL;
}

// рекурсивная функция очистки памяти дерева
void BinaryTreeSearch::remove_node(Node_bts* node) {
	// очищаем память от левого поддерева
	if (node->left) {
		remove_node(node->left);
	}
	// очищаем память от правого поддерева
	if (node->right) {
		remove_node(node->right);
	}
	// очищаем память от текущего элемента
	delete node;
}

// конструктор бинарного дерева поиска с максимальны размером 10000
BinaryTreeSearch::BinaryTreeSearch() : head(NULL){}
// конструктор бинарного дерева поиска с заданным максимальны размером
BinaryTreeSearch::BinaryTreeSearch(int m_size) : head(NULL), max_size(m_size) {}
