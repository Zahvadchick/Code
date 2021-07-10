#pragma once
#include <fstream>

#include "BinaryTreeSearch.h"

bool is_valid(Node_bts* root);

int BinaryTreeSearchAddTest(ofstream& out);

int BinaryTreeSearchRemoveTest(ofstream& out);

int BinaryTreeSearchFindTest(ofstream& out);

void binary_tree_search_unit_test(ofstream& out);
