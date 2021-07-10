#include <ctype.h>
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[]) {
	// папка в которой находится программа
	string dir = argv[1];
	// открываем файл для того, чтобы очистить его от прошлого результата работы
	ofstream f(dir + "\\report.txt");
	f.close();
	// список обрабатываемых структур
	vector<string> pool = { "Stack", "Queue", "Deque", "PriorityQueue", "LinkedList", "DoubleLinkedList", "XorLinkedList", "BinaryTreeSearch"};
	// для каждой струтуры запускаем тесты
	for (size_t i = 0; i < pool.size(); i++) {
		WIN32_FIND_DATA input, answer;
		// way1 и way2 пути до файлов входных действий и результатов на них, file путь до exe файла струтуры,
		// argument - аргументы вызова реализации, первоначально там только папка
		string way1 = dir + "\\" + pool[i] + "\\inputs\\*.txt", 
			way2 = dir + "\\" + pool[i] + "\\answers\\*.txt",
			file = dir + char(92) + pool[i] + "\\" + pool[i] + ".exe",
			argument = dir;
		HANDLE inp = FindFirstFile(way1.c_str(), &input),
			ans = FindFirstFile(way2.c_str(), &answer);
		// если списки текстовых файлов получены корректно
		if (ans != INVALID_HANDLE_VALUE && inp != INVALID_HANDLE_VALUE) {
			// обрабатываем каждую считанную пару входного и результатного файла
			do {
				// в аргументы командной строки добавляем пару файлов
				argument += ' ' + string(input.cFileName) + ' ' + string(answer.cFileName);
			} while (FindNextFile(inp, &input) != 0 && FindNextFile(ans, &answer) != 0);
			FindClose(inp);
			FindClose(ans);
			// запуск работы посторонней exe программы (реализации структуры)
			ShellExecute(NULL, "open", file.c_str(), argument.c_str(), NULL, SW_RESTORE);
		}
	}
	return 0;
}