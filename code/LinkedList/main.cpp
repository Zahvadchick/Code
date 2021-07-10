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
	// папка в которой распологаются необходимые данные
	string dir = argv[1];
	// открываем файл общего отчёта на дозапись и запускаем юнит тесты
	ofstream report(dir + "\\report.txt", ios::app);
	report << "\nLinkedList:\nUnit tests:\n";
	linked_list_unit_test(report);
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
		ifstream fin(dir + "\\LinkedList\\inputs\\" + argv[i]);
		ifstream answer(dir + "\\LinkedList\\answers\\" + argv[i + 1]);
		ofstream output(dir + "\\LinkedList\\outputs\\linked_list_result" + to_string(i / 2) + ".txt");
		// номер обрабатываемой строки и кол-во ошибок
		int str_number = 1, err_count = 0;
		// строки для считывания из input и answer соответственно
		string str, ans;
		// создаём список
		LinkedList l = LinkedList();
		// если переданные файлы открылись, то начинаем их обработку
		if (fin && answer) {
			// до тех пор, пока из input.txt есть что считывать
			while (getline(fin, str)) {
				// находим итератор на первый символ пропуска в строке, и с помощью этого отделяем первое слово строки (название команды)
				auto it = find(str.begin(), str.end(), ' ');
				string cur = string(str.begin(), it);
				// в зависимости от переданной команды выполняем соответствующее действие
				// очищает список полностью
				if (cur == "reset") {
					l.remove_all();
				}
				// добавляет элемент
				else if (cur == "add") {
					// отделяем переданный элемент
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// если переданно не целое число, то выводим сообщения об ошибке
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
					}
					else {
						// если есть еще переданный элемент, то это позиция, на которую нужно поставить элемент
						if (it2 != str.end()) {
							int position = atoi(string(it2 + 1, str.end()).c_str());
							// если на месте позиции не целое число, то выводим ошибку
							if (string(it2 + 1, str.end()) != to_string(position)) {
								output << "error position. String in input file:" << to_string(str_number) << '\n';
							}
							else {
								l.add(number, position);
							}
						}
						// инчае добавляем в конец
						else {
							l.add(number);
						}
					}
				}
				// удаляет элемент
				else if (cur == "remove") {
					// считываем результат из файла ответов
					getline(answer, ans);
					// отделяем переданный элемент
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// если переданно не целое число, то сообщаем об ошибке, иначе совершаем удаление
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					bool res = l.remove(number);
					// сверяем результат с ответом
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
				// выдает значение элемента на заданной позиции
				else if (cur == "get") {
					// считываем результат из файла ответов
					getline(answer, ans);
					auto it2 = find(it + 1, str.end(), ' ');
					string word = string(it + 1, it2);
					int position = atoi(word.c_str());
					// если в качестве переданного элемента было не целое число и не ключевое слово all,
					// то выводим сообщение об ошибке
					if (word != to_string(position)) {
						// если переданно ключевое слово all, то мы формируем вектор из элементов списка и сравниваем его с ответом
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
					// сравниваем результат с ответом
					else if (ans != l.get(position)) {
						err_count++;
						string message = "getting element is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// выдает кол-во элементов в списке
				else if (cur == "count") {
					// считываем результат из файла ответов
					getline(answer, ans);
					// сравниваем результат с ответом
					if (ans != to_string(l.count())) {
						err_count++;
						string message = "count of elemets is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// проверяет, есть ли элемент с заданным значением в списке
				else if (cur == "contains") {
					// считываем результат из файла ответов
					getline(answer, ans);
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// если было переданно не целое число, то сообщаем об ошибке
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					// вызываем функцию и сравниваем результат с ответом
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
				// иначе была переданна некорректная команда
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