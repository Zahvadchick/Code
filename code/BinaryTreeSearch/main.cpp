#include <algorithm>
#include <sstream>

#include "BinaryTreeSearch.h"
#include "ut_binary_tree_search.h"

// ���������� �� ������� � ������. ����� ��� �������� ������������ ������ �������
ostringstream& operator<<(ostringstream& out, vector<int> v) {
	for (size_t i = 0; i < v.size(); i++) {
		if (i != 0) {
			out << " ";
		}
		out << to_string(v[i]);
	}
	return out;
}

int main(int argc, char *argv[]) {
	// ����� � ������� ������������� ����������� ������
	string dir = argv[1];
	// ��������� ���� ������ ������ �� �������� � ��������� ���� �����
	ofstream report(dir + "\\report.txt", ios::app);
	report << "\nBinaryTreeSearch:\nUnit tests:\n";
	binary_tree_search_unit_test(report);
	report << "\nStdin test : \n";
	// ���� ���� ��������� ������ ��� ���������� (�����, ������� ���� � ������ � ����), �� ������� ����������
	// � ���� ������ � ���, ��� ������� ����� �� ���� ��������� � ��������� ������ ���������
	if (argc < 4) {
		report << "input files were not passed";
		return 0;
	}
	// ����� ��������� std ����� � ��� �������, � ������� ��� ���� ���������
	for (int i = 2; i < argc; i += 2) {
		// ��������� ����� � ��������� � �������� ��� ���������� � ������� ���� ��� ������ ������
		ifstream fin(dir + "\\BinaryTreeSearch\\inputs\\" + argv[i]);
		ifstream answer(dir + "\\BinaryTreeSearch\\answers\\" + argv[i + 1]);
		ofstream output(dir + "\\BinaryTreeSearch\\outputs\\binary_tree_search_result" + to_string(i / 2) + ".txt");
		// ����� �������������� ������ � ���-�� ������
		int str_number = 1, err_count = 0;
		// ������ ��� ���������� �� input � answer ��������������
		string str, ans;
		BinaryTreeSearch bts = BinaryTreeSearch();
		if (fin && answer) {
			// �� ��� ���, ���� �� input.txt ���� ��� ���������
			while (getline(fin, str)) {
				// ������� �������� �� ������ ������ �������� � ������, � � ������� ����� �������� ������ ����� ������ (�������� �������)
				auto it = find(str.begin(), str.end(), ' ');
				string cur = string(str.begin(), it);
				// � ����������� �� ���������� ������� ��������� ��������������� ��������
				// ������� ���� ���������
				if (cur == "reset") {
					bts.remove_all();
				}
				// ��������� �������
				else if (cur == "add") {
					// �������� ���������� �������
					auto it2 = find(it + 1, str.end(), ' ');
					string word = string(it + 1, it2);
					int num = atoi(word.c_str());
					// ���� ��������� �� ����� �����, ������� ��������� �� ����, ����� �������� ������� add
					if (word != to_string(num)) {
						output << "error, expected number. String in input file:" << to_string(str_number) << '\n';
					}
					else {
						bts.add(num);
					}
				}
				// ������� �������
				else if (cur == "remove") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					// �������� ���������� �������
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// ���� ��������� �� �����, �������� �� ������
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					// �������� ������� �������� � ��������� ���������
					bool res = bts.remove(number);
					if (res && ans == "false") {
						err_count++;
						string message = "number must not be removed. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
					else if (!res && ans == "true") {
						err_count++;
						string message = "number must be removed. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
					// �������� ������� ������� �� �����
				}
				// ������ ������������ �������
				else if (cur == "get") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					auto it2 = find(it + 1, str.end(), ' ');
					string word = string(it + 1, it2);
					int number;
					// � ����������� �� ����������� ��������� ����� ��������, ����������� ��� ������������ �������
					if (word == "head") {
						number = bts.get_head()->val;
					}
					else if (word == "min") {
						number = bts.get_min()->val;
					}
					else if (word == "max") {
						number = bts.get_max()->val;
					}
					// ���� �������� �� ������ �� � ����� �� 3 �������� ����, �� ������� ������ �������
					else {
						output << "wrong command. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					// ���� ����� �� ������, ������ ��������� �� ������
					if (atoi(ans.c_str()) != number) {
						output << "wrong getting element. String in input file:" << to_string(str_number) << '\n';
					}
				}
				// ����� �������� � �������� ���������
				else if (cur == "find") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// ������� ��������� �� ������ ���� � �������� ��������� ��������� �� ����� �����
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					// ���� ����� � ���������� � ������� (��� ���� ������� ��� ��� ���)
					bool res = bts.find(number) != NULL ? true : false;
					if (res && ans == "false") {
						err_count++;
						string message = "number should not be found. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
					else if (!res && ans == "true") {
						err_count++;
						string message = "number should be found. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// ������ �����
				else if (cur == "preorder") {
					getline(answer, ans);
					vector<int> v;
					bts.preorder(bts.get_head(), v);
					ostringstream s;
					s << v;
					if (s.str() != ans) {
						err_count++;
						string message = "preorder is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// �������������� �����
				else if (cur == "inorder") {
					getline(answer, ans);
					vector<int> v;
					bts.inorder(bts.get_head(), v);
					ostringstream s;
					s << v;
					if (s.str() != ans) {
						err_count++;
						string message = "inorder is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// �������� �����
				else if (cur == "postorder") {
					getline(answer, ans);
					vector<int> v;
					bts.postorder(bts.get_head(), v);
					ostringstream s;
					s << v;
					if (s.str() != ans) {
						err_count++;
						string message = "postorder is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// ��������� �� ������������ �������� ������ ������
				else if (cur == "valid") {
					if (!is_valid(bts.get_head())) {
						err_count++;
						string message = "This isn't binary tree search. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// ����� ���������� ������� �� ���������������, ������� ��������� � ������������ �����
				else {
				string message = "incorrect input. String in input file:" + to_string(str_number) + '\n';
				output << message.c_str();
				}
				str_number++;
			}
			// ������� ��������� � ����������� �� ���-�� ������
			if (err_count == 0) {
				string message = "all tests were successful\n";
				output << message.c_str();
				report << "Test" << to_string(i / 2) << " gave the correct answers\n";
			}
			else {
				string message = to_string(err_count) + " wrong answers\n";
				output << message.c_str();
				report << "Test" << to_string(i / 2) << " has " << to_string(err_count) << " wrong answers\n";
			}
		}
		// ���� ����� �� ���������, �� ����� �� ����
		else {
			output << "failed to open one or more of the transferred files\n";
			report << "Test" << to_string(i / 2) << " failed to open one or more of the transferred files\n";
		}
		fin.close();
		answer.close();
		output.close();
	}
	report.close();
	return 0;
}