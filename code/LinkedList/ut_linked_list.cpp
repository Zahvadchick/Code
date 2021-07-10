#include "ut_linked_list.h"
#include "LinkedList.h"

using namespace std;

ostream& operator<<(ostream& out, const vector<int>& v) {
	for (size_t i = 0; i < v.size(); i++) {
		if (i != 0) {
			out << " ";
		}
		out << to_string(v[i]);
	}
	return out;
}

template<class T>
bool AssertInequality(const T& res, const T& ans,
	const string& hint, ofstream& out)
{
	// если результат и ответ не совпали, то выводим соответствующее сообщение
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
		// запускаем тест и выводим сообщение в зависимости от кол-ва ошибок
		int error_count = func(out);
		if (error_count == 0) {
			out << " OK\n";
		}
		else {
			out << '\n' << test_name << " has " << to_string(error_count) << " wrong answers\n";
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
	// кол-во ошибок
	int fail_count = 0;
};

int LinkedListAddTest(ofstream& out) {
	int error_count = 0;
	LinkedList l = LinkedList(10000);
	// тест на добавление одного элемента
	l.add(9);
	error_count += AssertInequality(l.get(0), string("in position 0 is 9"), "Pushing element is 9", out);

	// тест на добавление по позициям
	l.add(3, 0);
	error_count += AssertInequality(l.get(0), string("in position 0 is 3"), "Pushing element is 3 on 0 position", out);
	l.add(6);
	error_count += AssertInequality(l.get(2), string("in position 2 is 6"), "Pushing element is 6", out);
	l.add(4, 2);
	error_count += AssertInequality(l.get_all(), { 3, 9, 4, 6 }, "Pushing element is 4 on 2 position", out);
	return error_count;
}

int LinkedListRemoveTest(ofstream& out) {
	int error_count = 0;
	LinkedList l = LinkedList(10000);

	// удаление добавленного элемента
	l.add(1);
	error_count += AssertInequality(l.remove(1), true, "Remove 1", out);
	error_count += AssertInequality(l.get(0), string("out of range"), "list is empty", out);

	l.add(2);
	l.add(3);
	l.add(4);
	// пытаемся удалить не существующий жлемент
	error_count += AssertInequality(l.remove(1), false, "Remove 1", out);
	error_count += AssertInequality(l.get_all(), { 2, 3, 4 }, "Remove 1", out);

	// удаляем существующие элементы и наблюдаем, как изменяется список
	error_count += AssertInequality(l.remove(3), true, "Remove 3", out);
	error_count += AssertInequality(l.get_all(), { 2, 4 }, "Remove 3", out);
	error_count += AssertInequality(l.remove(2), true, "Remove 2", out);
	error_count += AssertInequality(l.get_all(), { 4 }, "Remove 2", out);
	return error_count;
}

int LinkedListCountTest(ofstream& out) {
	int error_count = 0;
	LinkedList l = LinkedList(10000);

	// только что созданный список должен быть пустым
	error_count += AssertInequality(l.count(), 0, "list is empty", out);

	// добавим три элемента, а затем еще 2
	l.add(1);
	l.add(2);
	l.add(3);
	error_count += AssertInequality(l.count(), 3, "add 3 new elements", out);
	l.add(4);
	l.add(5);
	error_count += AssertInequality(l.count(), 5, "add 2 new elements", out);

	// удалим элемент и проверим, уменьшился ли размер
	l.remove(4);
	error_count += AssertInequality(l.count(), 4, "remove 1 element", out);
	error_count += AssertInequality(l.get_all(), { 1, 2, 3, 5 }, "", out);
	return error_count;
}

int LinkedListContainsTest(ofstream& out) {
	int error_count = 0;
	LinkedList l = LinkedList();

	// добавим несколько элементов и вызовим функцию contains для существующего и не существующего элемента
	l.add(5);
	l.add(7);
	l.add(8);
	l.add(9);
	l.add(9);
	error_count += AssertInequality(l.contains(6), false, "list does not contain 6", out);
	error_count += AssertInequality(l.contains(8), true, "list contain 8", out);

	// удалим два элемента: один из них содержался в единственно экземпляре, а другой в двух. Вызовим для них функцию contains
	l.remove(8);
	l.remove(9);
	error_count += AssertInequality(l.contains(8), false, "remove 8", out);
	error_count += AssertInequality(l.contains(9), true, "list contained two copies 9, one of which was deleted", out);
	return error_count;
}

// функция для запуска тестов
void linked_list_unit_test(ofstream& out) {
	TestRunner runner;
	runner.RunTest(LinkedListAddTest, "AddTest", out);
	runner.RunTest(LinkedListRemoveTest, "RemoveTest", out);
	runner.RunTest(LinkedListCountTest, "CountTest", out);
	runner.RunTest(LinkedListContainsTest, "ContainsTest", out);
}
