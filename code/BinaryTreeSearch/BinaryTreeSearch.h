#pragma once

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// структура узла, содержащая значение элемента и указатели на левого и правого потомка
struct Node_bts {
	int val;
	Node_bts* left;
	Node_bts* right;
	Node_bts(int v) : val(v), left(NULL), right(NULL) {}
};

class BinaryTreeSearch {
private:
	// указатель на корневой элемент
	Node_bts* head;
    // текущий и максимальный размер
	int size = 0, max_size = 10000;
	void rec(Node_bts* cur, Node_bts* node);

public:

	bool add(int num);

	bool remove(int num);

	Node_bts* find(int num);

	Node_bts* get_head();

	Node_bts* get_min();
	
	Node_bts* get_max();

	void preorder(Node_bts* node, vector<int>& v);

	void inorder(Node_bts* node, vector<int>& v);

	void postorder(Node_bts* node, vector<int>& v);
	
	void remove_all();

	void remove_node(Node_bts* node);

	BinaryTreeSearch();
	BinaryTreeSearch(int m_size);
};
