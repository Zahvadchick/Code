#include <algorithm>

#include "PriorityQueue.h"
#include "ut_priority_queue.h"

int main(int argc, char *argv[]) {
	// ����� � ������� ������������� ����������� ������
	string dir = argv[1];
	// ��������� ���� ������ ������ �� �������� � ��������� ���� �����
	ofstream report(dir + "\\report.txt", ios::app);
	report << "\nPriorityQueue:\nUnit tests:\n";
	priority_queue_unit_test(report);
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
		ifstream fin(dir + "\\PriorityQueue\\inputs\\" + argv[i]);
		ifstream answer(dir + "\\PriorityQueue\\answers\\" + argv[i + 1]);
		ofstream output(dir + "\\PriorityQueue\\outputs\\priority_queue_result" + to_string(i / 2) + ".txt");
		// ����� �������������� ������ � ���-�� ������
		int str_number = 1, err_count = 0;
		// ������ ��� ���������� �� input � answer ��������������
		string str, ans;
		// ������ ������� � �����������
		PriorityQueue pq = PriorityQueue(10000);
		// ���� ���������� ����� ���������, �� �������� �� ���������
		if (fin && answer) {
			// �� ��� ���, ���� �� input.txt ���� ��� ���������
			while (getline(fin, str)) {
				// ������� �������� �� ������ ������ �������� � ������, � � ������� ����� �������� ������ ����� ������ (�������� �������)
				auto it = find(str.begin(), str.end(), ' ');
				string cur = string(str.begin(), it);
				// � ����������� �� ���������� ������� ��������� ��������������� ��������
				// ������� ������� ���������
				if (cur == "reset") {
					while (pq.empty() == false) {
						pq.pop();
					}
				}
				// ��������� �������
				else if (cur == "push") {
					// �������� ���������� �������
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// ���� ��������� �� ����� �����, �� �������� ��������� �� ������
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
					}
					else {
						// ���� ����� ����� ��������� ���-�� ���, �� ���������, �������� ��� ����� ������ ��� ���.
						// ���� ��������� ����� �����, �� ��� ��������� ������������ ��������
						if (it2 != str.end()) {
							int prior = atoi(string(it2 + 1, str.end()).c_str());
							if (string(it2 + 1, str.end()) != to_string(prior)) {
								output << "error priority. String in input file:" << to_string(str_number) << '\n';
							}
							// ��������� ������� � �������� �����������
							else {
								pq.push(number, prior);
							}
						}
						// ����� ��������� ������� � ����������� ������ ��� ��������
						else {
							pq.push(number);
						}
					}
				}
				// ������� ������� � ����� �������
				else if (cur == "pop") {
					pq.pop();
				}
				// �������� ������� � ��������� �����������
				else if (cur == "top") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					// ���������� ��������� � �������
					if (ans != pq.top()) {
						err_count++;
						string message = "top element is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// ��������� ������� �� �������
				else if (cur == "empty") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					// ���������� ��������� � �������
					if (ans == "true" && !pq.empty()) {
						err_count++;
						string message = "queue must be empty. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
					else if (ans == "false" && pq.empty()) {
						err_count++;
						string message = "queue must has elements. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// ���� ��������� �� ���������� �������, �� ������� ��������� �� ����
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