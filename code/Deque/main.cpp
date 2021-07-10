#include <algorithm>

#include "Deque.h"
#include "ut_deque.h"

int main(int argc, char *argv[]) {
	// папка в которой распологаются необходимые данные
	string dir = argv[1];
	// открываем файл общего отчёта на дозапись и запускаем юнит тесты
	ofstream report(dir + "\\report.txt", ios::app);
	report << "\nDeque:\nUnit tests:\n";
	deque_unit_test(report);
	report << "\nStdin test : \n";
	// если было переданно меньше трёх аргументов (папка, входной файл и ответы к нему), то передаём осообщение
	// в файл отчёта о том, что входные файлы не были переданны и завершаем работу программы
	if (argc < 4) {
		report << "input files were not passed";
		return 0;
	}
	// далее запускаем std тесты в том порядке, в котором они были переданны
	for (int i = 2; i < argc; i += 2) {
		// открываем файлы с командами и ответами для считывания и создаем файл для вывода ошибок
		ifstream fin(dir + "\\Deque\\inputs\\" + argv[i]);
		ifstream answer(dir + "\\Deque\\answers\\" + argv[i + 1]);
		ofstream output(dir + "\\Deque\\outputs\\deque_result" + to_string(i / 2) + ".txt");
		// номер обрабатываемой строки и кол-во ошибок
		int str_number = 1, err_count = 0;
		// строки для считывания из input и answer соответственно
		string str, ans;
		// создаём дек
		Deque d = Deque(10000);
		// если переданные файлы открылись, то начинаем тестирование
		if (fin && answer) {
			// до тех пор, пока из input.txt есть что считывать
			while (getline(fin, str)) {
				// находим итератор на первый символ пропуска в строке, и с помощью этого отделяем первое слово строки (название команды)
				auto it = find(str.begin(), str.end(), ' ');
				string cur = string(str.begin(), it);
				// в зависимости от переданной команды выполняем соответствующее действие
				// очищает дек полностью
				if (cur == "reset") {
					while (d.empty() == false) {
						d.pop_back();
					}
				}
				// добавляет элемент в стек
				else if (cur == "push") {
					// отделяем переданный элемент
					auto it2 = find(it + 1, str.end(), ' ');
					// сторона в которую будет проведена вставка
					string side = string(it + 1, it2).c_str();
					// число для добавления
					int number = atoi((string(it2 + 1, find(it2 + 1, str.end(), ' '))).c_str());
					// если было переданно целочисленное число, то вставляем его в соответствующую сторону,
					// иначе выводим сообщение об ошибке
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
						// если переданная сторона некорректна, то выводим сообщение об этом
						else {
							output << "input error, expected back or front. String in input file:" << to_string(str_number) << '\n';
						}
					}
				}
				// удаляет элемент из дека
				else if (cur == "pop") {
					// считываем сторону с которой будет произведено удаление
					string side = string(it + 1, find(it + 1, str.end(), ' ')).c_str();
					if (side == "back") {
						d.pop_back();
					}
					else if (side == "front") {
						d.pop_front();
					}
					// если переданная сторона некорректна, то выводим сообщение об этом
					else {
						output << "input error, expected back or front. String in input file:" << to_string(str_number) << '\n';
					}
				}
				// получает последний элемент из дека
				else if (cur == "top") {
					// считываем результат из файла ответов
					getline(answer, ans);
					// сравниваем результат с ответом
					if (ans != d.top()) {
						err_count++;
						string message = "top element is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// получает первый элемент из дека
				else if (cur == "front") {
					// считываем результат из файла ответов
					getline(answer, ans);
					// сравниваем результат с ответом
					if (ans != d.front()) {
						err_count++;
						string message = "front element is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// проверяет стек на пустоту
				else if (cur == "empty") {
					// считываем результат из файла ответов
					getline(answer, ans);
					// сравниваем результат с ответом
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
				// если команда не была распознонна, то выводим сообщение о некорректном вводе
				else {
					string message = "incorrect input. String in input file:" + to_string(str_number) + '\n';
					output << message.c_str();
				}
				str_number++;
			}
			// выводим сообщение в зависимости от кол-ва ошибок
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
		// если файлы не открылись, то пишем об этом
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