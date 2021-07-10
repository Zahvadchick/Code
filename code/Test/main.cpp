#include <ctype.h>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[]) {
	// ����� � ������� ��������� ���������
	string dir = argv[1];
	// ��������� ���� ��� ����, ����� �������� ��� �� �������� ���������� ������
	ofstream f(dir + "\\report.txt");
	f.close();
	// ������ �������������� ��������
	vector<string> pool = { "Stack", "Queue", "Deque", "PriorityQueue", "LinkedList", "DoubleLinkedList", "XorLinkedList", "BinaryTreeSearch"};
	// ��� ������ �������� ��������� �����
	for (size_t i = 0; i < pool.size(); i++) {
		WIN32_FIND_DATA input, answer;
		// way1 � way2 ���� �� ������ ������� �������� � ����������� �� ���, file ���� �� exe ����� ��������,
		// argument - ��������� ������ ����������, ������������� ��� ������ �����
		string way1 = dir + "\\" + pool[i] + "\\inputs\\*.txt", 
			way2 = dir + "\\" + pool[i] + "\\answers\\*.txt",
			file = dir + char(92) + pool[i] + "\\" + pool[i] + ".exe",
			argument = dir;
		HANDLE inp = FindFirstFile(way1.c_str(), &input),
			ans = FindFirstFile(way2.c_str(), &answer);
		// ���� ������ ��������� ������ �������� ���������
		if (ans != INVALID_HANDLE_VALUE && inp != INVALID_HANDLE_VALUE) {
			// ������������ ������ ��������� ���� �������� � ������������� �����
			do {
				// � ��������� ��������� ������ ��������� ���� ������
				argument += ' ' + string(input.cFileName) + ' ' + string(answer.cFileName);
			} while (FindNextFile(inp, &input) != 0 && FindNextFile(ans, &answer) != 0);
			FindClose(inp);
			FindClose(ans);
			// ������ ������ ����������� exe ��������� (���������� ���������)
			ShellExecute(NULL, "open", file.c_str(), argument.c_str(), NULL, SW_RESTORE);
		}
	}
	return 0;
}