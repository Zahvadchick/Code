#include <algorithm>
#include <sstream>

#include "LinkedList.h"
#include "ut_linked_list.h"

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
	report << "\nLinkedList:\nUnit tests:\n";
	linked_list_unit_test(report);
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
		ifstream fin(dir + "\\LinkedList\\inputs\\" + argv[i]);
		ifstream answer(dir + "\\LinkedList\\answers\\" + argv[i + 1]);
		ofstream output(dir + "\\LinkedList\\outputs\\linked_list_result" + to_string(i / 2) + ".txt");
		// ����� �������������� ������ � ���-�� ������
		int str_number = 1, err_count = 0;
		// ������ ��� ���������� �� input � answer ��������������
		string str, ans;
		// ������ ������
		LinkedList l = LinkedList();
		// ���� ���������� ����� ���������, �� �������� �� ���������
		if (fin && answer) {
			// �� ��� ���, ���� �� input.txt ���� ��� ���������
			while (getline(fin, str)) {
				// ������� �������� �� ������ ������ �������� � ������, � � ������� ����� �������� ������ ����� ������ (�������� �������)
				auto it = find(str.begin(), str.end(), ' ');
				string cur = string(str.begin(), it);
				// � ����������� �� ���������� ������� ��������� ��������������� ��������
				// ������� ������ ���������
				if (cur == "reset") {
					l.remove_all();
				}
				// ��������� �������
				else if (cur == "add") {
					// �������� ���������� �������
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// ���� ��������� �� ����� �����, �� ������� ��������� �� ������
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
					}
					else {
						// ���� ���� ��� ���������� �������, �� ��� �������, �� ������� ����� ��������� �������
						if (it2 != str.end()) {
							int position = atoi(string(it2 + 1, str.end()).c_str());
							// ���� �� ����� ������� �� ����� �����, �� ������� ������
							if (string(it2 + 1, str.end()) != to_string(position)) {
								output << "error position. String in input file:" << to_string(str_number) << '\n';
							}
							else {
								l.add(number, position);
							}
						}
						// ����� ��������� � �����
						else {
							l.add(number);
						}
					}
				}
				// ������� �������
				else if (cur == "remove") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					// �������� ���������� �������
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// ���� ��������� �� ����� �����, �� �������� �� ������, ����� ��������� ��������
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					bool res = l.remove(number);
					// ������� ��������� � �������
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
				}
				// ������ �������� �������� �� �������� �������
				else if (cur == "get") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					auto it2 = find(it + 1, str.end(), ' ');
					string word = string(it + 1, it2);
					int position = atoi(word.c_str());
					// ���� � �������� ����������� �������� ���� �� ����� ����� � �� �������� ����� all,
					// �� ������� ��������� �� ������
					if (word != to_string(position)) {
						// ���� ��������� �������� ����� all, �� �� ��������� ������ �� ��������� ������ � ���������� ��� � �������
						if (word == "all") {
							vector<int> v = l.get_all();
							ostringstream s;
							s << v;
							if (s.str() != ans) {
								err_count++;
								string message = "getting list is wrong. String in input file:" + to_string(str_number) + '\n';
								output << message.c_str();
							}
						}
						else {
							output << "error position. String in input file:" << to_string(str_number) << '\n';
						}
					}
					// ���������� ��������� � �������
					else if (ans != l.get(position)) {
						err_count++;
						string message = "getting element is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// ������ ���-�� ��������� � ������
				else if (cur == "count") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					// ���������� ��������� � �������
					if (ans != to_string(l.count())) {
						err_count++;
						string message = "count of elemets is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// ���������, ���� �� ������� � �������� ��������� � ������
				else if (cur == "contains") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// ���� ���� ��������� �� ����� �����, �� �������� �� ������
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					// �������� ������� � ���������� ��������� � �������
					bool res = l.contains(number);
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
				// ����� ���� ��������� ������������ �������
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