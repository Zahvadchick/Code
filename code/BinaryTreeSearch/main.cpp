#include <algorithm>
#include <sstream>

#include "BinaryTreeSearch.h"
#include "ut_binary_tree_search.h"

// считывание из вектора в строку. Нужно для проверки корректности работы обходов
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
	report << "\nBinaryTreeSearch:\nUnit tests:\n";
	binary_tree_search_unit_test(report);
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
		ifstream fin(dir + "\\BinaryTreeSearch\\inputs\\" + argv[i]);
		ifstream answer(dir + "\\BinaryTreeSearch\\answers\\" + argv[i + 1]);
		ofstream output(dir + "\\BinaryTreeSearch\\outputs\\binary_tree_search_result" + to_string(i / 2) + ".txt");
		// номер обрабатываемой строки и кол-во ошибок
		int str_number = 1, err_count = 0;
		// строки для считывания из input и answer соответственно
		string str, ans;
		BinaryTreeSearch bts = BinaryTreeSearch();
		if (fin && answer) {
			// до тех пор, пока из input.txt есть что считывать
			while (getline(fin, str)) {
				// находим итератор на первый символ пропуска в строке, и с помощью этого отделяем первое слово строки (название команды)
				auto it = find(str.begin(), str.end(), ' ');
				string cur = string(str.begin(), it);
				// в зависимости от переданной команды выполняем соответствующее действие
				// очищает стек полностью
				if (cur == "reset") {
					bts.remove_all();
				}
				// добавляет элемент
				else if (cur == "add") {
					// отделяем переданный элемент
					auto it2 = find(it + 1, str.end(), ' ');
					string word = string(it + 1, it2);
					int num = atoi(word.c_str());
					// если переданно не целое число, выводим сообщение об этом, иначе вызываем функцию add
					if (word != to_string(num)) {
						output << "error, expected number. String in input file:" << to_string(str_number) << '\n';
					}
					else {
						bts.add(num);
					}
				}
				// удаляет элемент
				else if (cur == "remove") {
					// считываем результат из файла ответов
					getline(answer, ans);
					// отделяем переданный элемент
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// если переданно не число, сообщаем об ошибке
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					// вызываем функцию удаления и проверяем результат
					bool res = bts.remove(number);
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
					// получает верхний элемент из стека
				}
				// выдает определенный элемент
				else if (cur == "get") {
					// считываем результат из файла ответов
					getline(answer, ans);
					auto it2 = find(it + 1, str.end(), ' ');
					string word = string(it + 1, it2);
					int number;
					// в зависимости от переданного аргумента выдаём корневой, минимальный или максимальный элемент
					if (word == "head") {
						number = bts.get_head()->val;
					}
					else if (word == "min") {
						number = bts.get_min()->val;
					}
					else if (word == "max") {
						number = bts.get_max()->val;
					}
					// если аргумент не совпал ни с одним из 3 ключевых слов, то выводим ошибку команды
					else {
						output << "wrong command. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					// если ответ не совпал, выдаем сообщение об ошибке
					if (atoi(ans.c_str()) != number) {
						output << "wrong getting element. String in input file:" << to_string(str_number) << '\n';
					}
				}
				// поиск элемента с заданным значением
				else if (cur == "find") {
					// считываем результат из файла ответов
					getline(answer, ans);
					auto it2 = find(it + 1, str.end(), ' ');
					int number = atoi(string(it + 1, it2).c_str());
					// выводим сообщение об ошибке если в качестве аргумента переданно не целое число
					if (string(it + 1, it2) != to_string(number)) {
						output << "error number. String in input file:" << to_string(str_number) << '\n';
						str_number++;
						continue;
					}
					// ищем число и сравниваем с ответом (сам факт нашлось оно или нет)
					bool res = bts.find(number) != NULL ? true : false;
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
				// прямой обход
				else if (cur == "preorder") {
					getline(answer, ans);
					vector<int> v;
					bts.preorder(bts.get_head(), v);
					ostringstream s;
					s << v;
					if (s.str() != ans) {
						err_count++;
						string message = "preorder is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// центрированный обход
				else if (cur == "inorder") {
					getline(answer, ans);
					vector<int> v;
					bts.inorder(bts.get_head(), v);
					ostringstream s;
					s << v;
					if (s.str() != ans) {
						err_count++;
						string message = "inorder is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// обратный обход
				else if (cur == "postorder") {
					getline(answer, ans);
					vector<int> v;
					bts.postorder(bts.get_head(), v);
					ostringstream s;
					s << v;
					if (s.str() != ans) {
						err_count++;
						string message = "postorder is wrong. String in input file:" + to_string(str_number) + '\n';
						output << message.c_str();
					}
				}
				// проверяет на корректность бинарное дерево поиска
				else if (cur == "valid") {
					if (!is_valid(bts.get_head())) {
						err_count++;
						string message = "This isn't binary tree search. String in input file:" + to_string(str_number) + '\n';
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