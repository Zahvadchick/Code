#include "BinaryTreeSearch.h"

// ����������� �������, ������� ���� ����� ��� ������� �, ����� ����������, ��������� �������
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

// ���������� ��������
bool BinaryTreeSearch::add(int num) {
	// ���� ����������� �����������, �� ������� �� ��������
	if (size == max_size) {
		return false;
	}
	Node_bts* node = new Node_bts(num);
	// ���� ������ �����, �� ����������� ������� ���������� ��������
	if (size == 0) {
		head = node;
	}
	// ����� �������� ����������� ������� ��� ������� �������� �� ������ �����
	else {
		rec(head, node);
	}
	size++;
	return true;
}

// �������� ��������
bool BinaryTreeSearch::remove(int num) {
	Node_bts* root = head;
	Node_bts* par = NULL;
	bool is_right;
	// ���� ��������� �������. �� ������ �������� ���������� � ����� ������� �� ���� (����� ��� �������������� ����� ����� ��������)
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
	// ���� ������� �� ������ - �������� �� �������
	if (root == NULL) {
		return false;
	}
	// ���� ������� ��� ������������, �� ������� ���
	else if (size == 1) {
		head = NULL;
	}
	// ���� ������� �������� ��������, ������������ ������ �� ������� ������� � ������� ������ ������� (���� �� �� �������)
	// �� ����� ����� ���� ������� ���������, ���� ������ ������� ����, �� ������ ��������� ������
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
	// ���� ������� �� �������, ��������� ������ ������
	else {
		// � �������� �� ���� �� ������ �������, ����� ������ �������� �������, ���������������� ��������, � ��������
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
		// � �������� ���� ��� �������, ����� �� ��� ����� ��������� ������� �������, 
		// � ������ ��������� ��� ����� ����� ������� � ������ ��������
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
		// � �������� ������ ������ �������. ��������� ������� �� ����� ����������� ��������
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
		// � �������� ������ ����� �������. ��������� ������� �� ����� ����������� ��������
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
	// ������� ������ � �������� �� �������� ��������
	delete root;
	size--;
	return true;
}

// ����� ��������
Node_bts* BinaryTreeSearch::find(int num) {
	Node_bts* root = head;
	// ���� ������� � ������. ���� ������ ���� ������� ������ �������� � ������� ���� ��������.
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
	// ���� ������� �� ��� ������, �� ����� ������� NULL
	return root;
}

// ������ ��������� �� �������� �������
Node_bts* BinaryTreeSearch::get_head() {
	return head;
}

// ������ ��������� �� ����������� ������� (����� �����)
Node_bts* BinaryTreeSearch::get_min() {
	Node_bts* root = head;
	while (root->left) {
		root = root->left;
	}
	return root;
}

// ������ ��������� �� ���������� ������� (����� ������)
Node_bts* BinaryTreeSearch::get_max() {
	Node_bts* root = head;
	while (root->right) {
		root = root->right;
	}
	return root;
}

// ������ ����� ������
void BinaryTreeSearch::preorder(Node_bts* node, vector<int>& v) {
	if (!node) {
		return;
	}
	// ��������� �������
	v.push_back(node->val);
	// ������� ����� ���������
	preorder(node->left, v);
	// ������� ������ ���������
	preorder(node->right, v);
}

// �������������� ����� ������
void BinaryTreeSearch::inorder(Node_bts* node, vector<int>& v) {
	if (!node) {
		return;
	}
	// ������� ����� ���������
	inorder(node->left, v);
	// ��������� �������
	v.push_back(node->val);
	// ������� ������ ���������
	inorder(node->right, v);
}

// �������� ����� ������
void BinaryTreeSearch::postorder(Node_bts* node, vector<int>& v) {
	if (!node) {
		return;
	}
	// ������� ����� ���������
	postorder(node->left, v);
	// ������� ������ ���������
	postorder(node->right, v);
	// ��������� �������
	v.push_back(node->val);
}

// ������� ������
void BinaryTreeSearch::remove_all() {
	size = 0;
	// ������� ������ �� �����
	remove_node(head);
	head = NULL;
}

// ����������� ������� ������� ������ ������
void BinaryTreeSearch::remove_node(Node_bts* node) {
	// ������� ������ �� ������ ���������
	if (node->left) {
		remove_node(node->left);
	}
	// ������� ������ �� ������� ���������
	if (node->right) {
		remove_node(node->right);
	}
	// ������� ������ �� �������� ��������
	delete node;
}

// ����������� ��������� ������ ������ � ����������� �������� 10000
BinaryTreeSearch::BinaryTreeSearch() : head(NULL){}
// ����������� ��������� ������ ������ � �������� ����������� ��������
BinaryTreeSearch::BinaryTreeSearch(int m_size) : head(NULL), max_size(m_size) {}
