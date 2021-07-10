#include <algorithm>

#include "Deque.h"
#include "ut_deque.h"

int main(int argc, char *argv[]) {
	// ����� � ������� ������������� ����������� ������
	string dir = argv[1];
	// ��������� ���� ������ ������ �� �������� � ��������� ���� �����
	ofstream report(dir + "\\report.txt", ios::app);
	report << "\nDeque:\nUnit tests:\n";
	deque_unit_test(report);
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
		ifstream fin(dir + "\\Deque\\inputs\\" + argv[i]);
		ifstream answer(dir + "\\Deque\\answers\\" + argv[i + 1]);
		ofstream output(dir + "\\Deque\\outputs\\deque_result" + to_string(i / 2) + ".txt");
		// ����� �������������� ������ � ���-�� ������
		int str_number = 1, err_count = 0;
		// ������ ��� ���������� �� input � answer ��������������
		string str, ans;
		// ������ ���
		Deque d = Deque(10000);
		// ���� ���������� ����� ���������, �� �������� ������������
		if (fin && answer) {
			// �� ��� ���, ���� �� input.txt ���� ��� ���������
			while (getline(fin, str)) {
				// ������� �������� �� ������ ������ �������� � ������, � � ������� ����� �������� ������ ����� ������ (�������� �������)
				auto it = find(str.begin(), str.end(), ' ');
				string cur = string(str.begin(), it);
				// � ����������� �� ���������� ������� ��������� ��������������� ��������
				// ������� ��� ���������
				if (cur == "reset") {
					while (d.empty() == false) {
						d.pop_back();
					}
				}
				// ��������� ������� � ����
				else if (cur == "push") {
					// �������� ���������� �������
					auto it2 = find(it + 1, str.end(), ' ');
					// ������� � ������� ����� ��������� �������
					string side = string(it + 1, it2).c_str();
					// ����� ��� ����������
					int number = atoi((string(it2 + 1, find(it2 + 1, str.end(), ' '))).c_str());
					// ���� ���� ��������� ������������� �����, �� ��������� ��� � ��������������� �������,
					// ����� ������� ��������� �� ������
					if (string(it2 + 1, find(it2 + 1, str.end(), ' ')) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
					}
					else {
						if (side == "back") {
							d.push_back(number);
						}
						else if (side == "front") {
							d.push_front(number);
						}
						// ���� ���������� ������� �����������, �� ������� ��������� �� ����
						else {
							output << "input error, expected back or front. String in input file:" << to_string(str_number) << '\n';
						}
					}
				}
				// ������� ������� �� ����
				else if (cur == "pop") {
					// ��������� ������� � ������� ����� ����������� ��������
					string side = string(it + 1, find(it + 1, str.end(), ' ')).c_str();
					if (side == "back") {
						d.pop_back();
					}
					else if (side == "front") {
						d.pop_front();
					}
					// ���� ���������� ������� �����������, �� ������� ��������� �� ����
					else {
						output << "input error, expected back or front. String in input file:" << to_string(str_number) << '\n';
					}
				}
				// �������� ��������� ������� �� ����
				else if (cur == "top") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					// ���������� ��������� � �������
					if (ans != d.top()) {
						err_count++;
						string message = "top element is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// �������� ������ ������� �� ����
				else if (cur == "front") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					// ���������� ��������� � �������
					if (ans != d.front()) {
						err_count++;
						string message = "front element is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// ��������� ���� �� �������
				else if (cur == "empty") {
					// ��������� ��������� �� ����� �������
					getline(answer, ans);
					// ���������� ��������� � �������
					if (ans == "true" && !d.empty()) {
						err_count++;
						string message = "queue must be empty. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
					else if (ans == "false" && d.empty()) {
						err_count++;
						string message = "queue must has elements. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// ���� ������� �� ���� �����������, �� ������� ��������� � ������������ �����
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