#include <algorithm>

#include "Stack.h"
#include "unit_test.h"

int main(int argc, char *argv[]) {
	// папка в которой распологаются необходимые данные
	string dir = argv[1];
	// открываем файл общего отчёта на дозапись и запускаем юнит тесты
	ofstream report(dir + "\\report.txt", ios::app);
	report << "\nStack:\nUnit tests:\n";
	stack_unit_test(report);
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
		ifstream fin(dir + "\\Stack\\inputs\\" + argv[i]);
		ifstream answer(dir + "\\Stack\\answers\\" + argv[i + 1]);
		ofstream output(dir + "\\Stack\\outputs\\stack_result" + to_string(i / 2) + ".txt");
		// номер обрабатываемой строки и кол-во ошибок
		int str_number = 1, err_count = 0;
		// строки для считывания из input и answer соответственно
		string str, ans;
		// создаём стек
		Stack s = Stack();
		// если переданные файлы открылись, то работаем с ними 
		if (fin && answer) {
			// до тех пор, пока из input.txt есть что считывать
			while (getline(fin, str)) {
				// находим итератор на первый символ пропуска в строке, и с помощью этого отделяем первое слово строки (название команды)
				auto it = find(str.begin(), str.end(), ' ');
				string cur = string(str.begin(), it);
				// в зависимости от переданной команды выполняем соответствующее действие
				// очищает стек полностью
				if (cur == "reset") {
					while (s.empty() == false) {
						s.pop();
					}
				}
				// добавляет в стек переданный элемент
				else if (cur == "push") {
					// отделяем переданный элемент и проверяем его на корректность
					int number = atoi((string(it + 1, find(it + 1, str.end(), ' '))).c_str());
					if (string(it + 1, find(it + 1, str.end(), ' ')) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
					}
					// если элемент является целым числом, добавляем его в стек
					else {
						s.push(number);
					}
				}
				// удаляет элемент из стека
				else if (cur == "pop") {
					s.pop();
				}
				// получает верхний элемент из стека
				else if (cur == "top") {
					// считываем результат из файла ответов
					getline(answer, ans);
					// сравниваем результат с ответом, если он не совпал пишем об этом в выходном файле
					if (ans != s.top()) {
						err_count++;
						string message = "top element is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// проверяет стек на пустоту
				else if (cur == "empty") {
					// считываем результат из файла ответов
					getline(answer, ans);
					// сравниваем результат с ответом, если не совпал, выводим в выходной файл сообщение об этом
					if (ans == "true" && !s.empty()) {
						err_count++;
						string message = "stack must be empty. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
					else if (ans == "false" && s.empty()) {
						err_count++;
						string message = "stack must has elements. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// иначе переданная команда не индифицированна, выводим сообщение о некорректном вводе
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