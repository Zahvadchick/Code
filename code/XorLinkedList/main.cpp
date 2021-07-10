#include <algorithm>
#include <sstream>

#include "XorLinkedList.h"
#include "ut_xor_linked_list.h"

// функция для считывания из строки ответа вектор содержащий элементы списка
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
	report << "\nXorLinkedList:\nUnit tests:\n";
	xor_linked_list_unit_test(report);
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
		ifstream fin(dir + "\\XorLinkedList\\inputs\\" + argv[i]);
		ifstream answer(dir + "\\XorLinkedList\\answers\\" + argv[i + 1]);
		ofstream output(dir + "\\XorLinkedList\\outputs\\xor_linked_list_result" + to_string(i / 2) + ".txt");
		// номер обрабатываемой строки и кол-во ошибок
		int str_number = 1, err_count = 0;
		// строки для считывания из input и answer соответственно
		string str, ans;
		// создаём стек
		XorLinkedList xl = XorLinkedList();
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
					xl.remove_all();
				}
				// добавляет элемент
				else if (cur == "add") {
					// отделяем переданный элемент
					auto it2 = find(it + 1, str.end(), ' ');
					string word = string(it + 1, it2);
					int num = atoi(word.c_str());
					// если это не целое число, ключевое слово front или back, то пишем сообщение о неверном формате
					if (word != to_string(num)) {
						int number = atoi(string(it2 + 1, str.end()).c_str());
						if (string(it2 + 1, str.end()) != to_string(number)) {
							output << "error, expected number, back or top. String in input file:" << to_string(str_number) << '\n';
						}
						// добавление вперед xor списка
						else if (word == "front") {
							xl.add_front(number);
						}
						// добавление в конец xor списка
						else if (word == "back") {
							xl.add_back(number);
						}
					}
					// добавление элемента на заданную позицию
					else {
						int position = atoi(string(it2 + 1, str.end()).c_str());
						// выводим сообщение об ошибке, если позиция не целое число
						if (string(it2 + 1, str.end()) != to_string(position)) {
							output << "error position. String in input file:" << to_string(str_number) << '\n';
						}
						else {
							xl.add(num, position);
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
					// если переданно не число, выводим сообщение об ошибке
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					// удаляем элемент и сравниваем результат
					bool res = xl.remove(number);
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
				// получить элемент или список целеком
				else if (cur == "get") {
					// считываем результат из файла ответов
					getline(answer, ans);
					auto it2 = find(it + 1, str.end(), ' ');
					string word = string(it + 1, it2);
					int position = atoi(word.c_str());
					// если переданно не целое число или ключевое слово all, то вывести сообщение об ошибке
					if (word != to_string(position)) {
						// выводим список через вектор и сверяем с ответом
						if (word == "all") {
							vector<int> v = xl.get_all();
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
					else if (ans != xl.get(position)) {
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
					if (ans != to_string(xl.count())) {
						err_count++;
						string message = "count of elemets is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// сообщает о том, есть ли в xor списке заданное число
				else if (cur == "contains") {
					// считываем результат из файла ответов
					getline(answer, ans);
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// если было переданно не целое число, вывести сообщение об ошибке
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					// запускаем функцию и сравниваем с ответом
					bool res = xl.contains(number);
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
				// выводит вектор из элементов списка в обратном порядке
				else if (cur == "reverse") {
					getline(answer, ans);
					vector<int> v = xl.reverse();
					ostringstream s;
					s << v;
					// сравниваем с ответом
					if (s.str() != ans) {
						err_count++;
						string message = "reverse list is wrong. String in input file:" + to_string(str_number) + '\n';
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