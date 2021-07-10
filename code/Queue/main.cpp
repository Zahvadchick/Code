#include <algorithm>

#include "Queue.h"
#include "ut_queue.h"

int main(int argc, char *argv[]) {
	// папка в которой распологаются необходимые данные
	string dir = argv[1];
	// открываем файл общего отчёта на дозапись и запускаем юнит тесты
	ofstream report(dir + "\\report.txt", ios::app);
	report << "\nQueue:\nUnit tests:\n";
	queue_unit_test(report);
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
		ifstream fin(dir + "\\Queue\\inputs\\" + argv[i]);
		ifstream answer(dir + "\\Queue\\answers\\" + argv[i + 1]);
		ofstream output(dir + "\\Queue\\outputs\\queue_result" + to_string(i / 2) + ".txt");
		// номер обрабатываемой строки и кол-во ошибок
		int str_number = 1, err_count = 0;
		// строки для считывания из input и answer соответственно
		string str, ans;
		// создаём очередь
		Queue q = Queue();
		// если переданные файлы открылись
		if (fin && answer) {
			// до тех пор, пока из input.txt есть что считывать
			while (getline(fin, str)) {
				// находим итератор на первый символ пропуска в строке, и с помощью этого отделяем первое слово строки (название команды)
				auto it = find(str.begin(), str.end(), ' ');
				string cur = string(str.begin(), it);
				// в зависимости от переданной команды выполняем соответствующее действие
				// очищает очередь полностью
				if (cur == "reset") {
					while (q.empty() == false) {
						q.pop();
					}
				}
				// добавляет элемент
				else if (cur == "push") {
					// отделяем переданный элемент
					int number = atoi((string(it + 1, find(it + 1, str.end(), ' '))).c_str());
					// если переданно целое число, добавляем его, иначе выводим сообщение об ошибке
					if (string(it + 1, find(it + 1, str.end(), ' ')) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
					}
					else {
						q.push(number);
					}
				}
				// удаляет элемент
				else if (cur == "pop") {
					q.pop();
				}
				// получает последний элемент из очереди
				else if (cur == "top") {
					// считываем результат из файла ответов
					getline(answer, ans);
					// сравниваем результат с ответом
					if (ans != q.top()) {
						err_count++;
						string message = "top element is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// получает первый элемент из очереди
				else if (cur == "front") {
					// считываем результат из файла ответов
					getline(answer, ans);
					// сравниваем результат с ответом
					if (ans != q.front()) {
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
					if (ans == "true" && !q.empty()) {
						err_count++;
						string message = "queue must be empty. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
					else if (ans == "false" && q.empty()) {
						err_count++;
						string message = "queue must has elements. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// если переданн некорректный файл, то выводим сообщение об этом
				else {
					string message = "incorrect input. String in input file:" + to_string(str_number) + '\n';
					output << message.c_str();
				}
				str_number++;
			}
			// выводим сообщение в зависимости от кол-ва ошибок
			if (err_count == 0) {
				string message = "all tests were successful\n";
				output << message.c_str(); message.c_str();
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