#include "ut_double_linked_list.h"
#include "DoubleLinkedList.h"

using namespace std;

// функция для вывода вектора
ostream& operator<<(ostream& out, const vector<int>& v) {
	for (size_t i = 0; i < v.size(); i++) {
		if (i != 0) {
			out << " ";
		}
		out << to_string(v[i]);
	}
	return out;
}

// функция сравнивающая результат с ответом.
template<class T>
bool AssertInequality(const T& res, const T& ans,
	const string& hint, ofstream& out)
{
	// если результат и ответ не совпали, то выводим сообщение о неверном ответе в выходной файл
	if (res != ans) {
		out << '\n' << "Assertion failed: " << res << " != " << ans << " hint: " << hint;
		return true;
	}
	return false;
}

// класс для вызова юнит тестов
class TestRunner {
public:
	//запускает переданную функцию теста
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name, ofstream& out) {
		out << test_name << ":";
		// запускаем переданный тест, и выводим сообщение в зависимости от кол-ва ошибок
		int error_count = func(out);
		if (error_count == 0) {
			out << " OK" << '\n';
		}
		else {
			out << '\n' << test_name << " has " << to_string(error_count) << " wrong answers" << '\n';
		}
	}

	// деструтор. Если среди запущенных тестов были те, которые не прошли, то выводит в поток ошибок сообщение с количеством проваленных тестов
	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	// количество проваленных юнит тестов
	int fail_count = 0;
};

int DoubleLinkedListAddTest(ofstream& out) {
	int error_count = 0;
	DoubleLinkedList dl = DoubleLinkedList(10000);
	// тест на добавление одного элемента
	dl.add_back(9);
	error_count += AssertInequality(dl.get(0), string("in position 0 is 9"), "Pushing element is 9", out);

	// тест на порядок добавления элементов
	dl.add(3, 0);
	error_count += AssertInequality(dl.get(0), string("in position 0 is 3"), "Pushing element is 3 on 0 position", out);
	dl.add_front(6);
	error_count += AssertInequality(dl.get(0), string("in position 0 is 6"), "Pushing front element is 6", out);
	dl.add(4, 2);
	dl.add_back(8);
	error_count += AssertInequality(dl.get(4), string("in position 4 is 8"), "Pushing back element is 8", out);
	dl.add_front(13);
	dl.add_back(1);
	error_count += AssertInequality(dl.get_all(), { 13, 6, 3, 4, 9, 8, 1}, "", out);
	return error_count;
}

int DoubleLinkedListRemoveTest(ofstream& out) {
	int error_count = 0;
	DoubleLinkedList dl = DoubleLinkedList(10000);

	// удаление единственного элемента
	dl.add_back(1);
	error_count += AssertInequality(dl.remove(1), true, "Remove 1", out);
	error_count += AssertInequality(dl.get(0), string("out of range"), "list is empty", out);

	dl.add_back(3);
	dl.add_back(4);
	dl.add_front(2);

	// попытка удалить не существующий элемент
	error_count += AssertInequality(dl.remove(1), false, "Remove 1", out);
	error_count += AssertInequality(dl.get_all(), { 2, 3, 4 }, "Remove 1", out);

	// удаление нескольких элементов
	error_count += AssertInequality(dl.remove(3), true, "Remove 3", out);
	error_count += AssertInequality(dl.get_all(), { 2, 4 }, "Remove 3", out);
	error_count += AssertInequality(dl.remove(2), true, "Remove 2", out);
	error_count += AssertInequality(dl.get_all(), { 4 }, "Remove 2", out);
	return error_count;
}

int DoubleLinkedListCountTest(ofstream& out) {
	int error_count = 0;
	DoubleLinkedList dl = DoubleLinkedList(10000);

	// проверка на пустоту только что созданного двусвязного списка
	error_count += AssertInequality(dl.count(), 0, "list is empty", out);

	// добавляем 3 элемента
	dl.add_back(1);
	dl.add_back(2);
	dl.add_back(3);
	error_count += AssertInequality(dl.count(), 3, "add 3 new elements", out);

	// добавляем еще 4 элемента
	dl.add_front(4);
	dl.add_back(5);
	dl.add(6, 3);
	dl.add(7, 3);
	error_count += AssertInequality(dl.count(), 7, "add 4 new elements", out);
	error_count += AssertInequality(dl.get_all(), { 4, 1, 2, 7, 6, 3, 5 }, "", out);
	error_count += AssertInequality(dl.reverse(), { 5, 3, 6, 7, 2, 1, 4 }, "", out);

	// удаляем 2 элемента
	dl.remove(4);
	dl.remove(6);
	error_count += AssertInequality(dl.count(), 5, "remove 2 element", out);
	error_count += AssertInequality(dl.get_all(), { 1, 2, 7, 3, 5 }, "", out);
	return error_count;
}

int DoubleLinkedListContainsTest(ofstream& out) {
	int error_count = 0;
	DoubleLinkedList dl = DoubleLinkedList();
	// заполняем список и пытаемся обнаружить существующий и не существующий элемент
	dl.add_back(5);
	dl.add_front(7);
	dl.add_back(8);
	dl.add_front(9);
	dl.add_back(9);
	error_count += AssertInequality(dl.contains(6), false, "list does not contain 6", out);
	error_count += AssertInequality(dl.contains(8), true, "list contain 8", out);

	// удаляем два элемента: один был в единственном экземпляре, а другой в двух. Пытаемся обнаружить оба
	dl.remove(8);
	dl.remove(9);
	error_count += AssertInequality(dl.contains(8), false, "remove 8", out);
	error_count += AssertInequality(dl.contains(9), true, "list contained two copies 9, one of which was deleted", out);
	return error_count;
}

// функция запуска тестов
void double_linked_list_unit_test(ofstream& out) {
	TestRunner runner;
	runner.RunTest(DoubleLinkedListAddTest, "AddTest", out);
	runner.RunTest(DoubleLinkedListRemoveTest, "RemoveTest", out);
	runner.RunTest(DoubleLinkedListCountTest, "CountTest", out);
	runner.RunTest(DoubleLinkedListContainsTest, "ContainsTest", out);
}
