#include "ut_deque.h"
#include "Deque.h"

using namespace std;
template<class T>
bool AssertInequality(const T& res, const T& ans,
	const string& hint, ofstream& out)
{
	// если результат и ответ не совпали, то выводим сообщение об этом
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

int DequePushTest(ofstream& out) {
	int error_count = 0;
	Deque d = Deque(5003);
	// тест на добавление одного элемента
	d.push_back(9);
	error_count += AssertInequality(d.front(), string("front element is 9"), "Pushing element is 9", out);

	// тест на порядок добавления элементов
	d.push_front(5);
	error_count += AssertInequality(d.front(), string("front element is 5"), "Pushing element is 5", out);
	d.push_back(3);
	error_count += AssertInequality(d.top(), string("top element is 3"), "Pushing element is 3", out);
	error_count += AssertInequality(d.front(), string("front element is 5"), "Pushing element is 3", out);

	// тест на поведение дека после добаления множества новых элементов
	for (int i = 0; i < 5000; i++) {
		d.push_back(i * 2);
	}
	error_count += AssertInequality(d.front(), string("front element is 5"), "many pushing elements", out);
	error_count += AssertInequality(d.top(), string("top element is 9998"), "many pushing elements", out);

	// тест на добавление элемента в полный дек
	error_count += AssertInequality(d.push_back(1), string("push error: deque is full"), "adding to the full stack", out);
	error_count += AssertInequality(d.push_front(1), string("push error: deque is full"), "adding to the full stack", out);
	return error_count;
}

int DequePopTest(ofstream& out) {
	int error_count = 0;
	Deque d = Deque();
	// тест на удаление добавленного элемента
	d.push_back(13);
	d.pop_back();
	error_count += AssertInequality(d.top(), string("Deque is empty"), "Deleting last element", out);

	// удаление с пустого дека
	error_count += AssertInequality(d.pop_back(), string("pop error: deque is empty"), "Deleting from an empty Deque", out);

	// тест на порядок удаления
	d.push_back(12);
	d.push_back(14);
	d.push_back(4);
	d.push_back(7);
	error_count += AssertInequality(d.top(), string("top element is 7"), "After deleting element, last added element remains", out);
	error_count += AssertInequality(d.front(), string("front element is 12"), "After deleting element, last added element remains", out);
	d.pop_back();
	error_count += AssertInequality(d.top(), string("top element is 4"), "After deleting element, last added element remains", out);
	d.pop_front();
	error_count += AssertInequality(d.front(), string("front element is 14"), "After deleting element, last added element remains", out);
	d.pop_back();
	error_count += AssertInequality(d.top(), string("top element is 14"), "After deleting element, last added element remains", out);

	// проверка на поведение дека при множественном добавлении и удалении элементов
	for (int i = 1001; i <= 10000; i++) {
		d.push_back(i);
	}
	for (int i = 0; i < 8998; i++) {
		d.pop_front();
	}
	error_count += AssertInequality(d.top(), string("top element is 10000"), "Many pushing and deleting elements", out);
	error_count += AssertInequality(d.front(), string("front element is 9998"), "Many pushing and deleting elements", out);
	d.push_back(3);
	error_count += AssertInequality(d.top(), string("top element is 3"), "Many pushing and deleting elements", out);
	d.pop_front();
	d.pop_front();
	error_count += AssertInequality(d.front(), string("front element is 10000"), "Many pushing and deleting elements", out);
	return error_count;
}

int DequeEmptyTest(ofstream& out) {
	int error_count = 0;
	Deque d = Deque(10000);
	// тест для новосозданного дека. Он должен быть пустым
	error_count += AssertInequality(d.empty(), true, "New Deque is empty", out);

	// тест на непустой дек (из одного элемента)
	d.push_back(5);
	error_count += AssertInequality(d.empty(), false, "Pushing new element, Deque is not empty", out);

	// тест на пустой дек
	d.pop_back();
	error_count += AssertInequality(d.empty(), true, "Deleting all elements, Deque is empty", out);

	// тест на поведение функции после добавления множества новых элементов
	for (int i = 5; i < 6000; i++) {
		d.push_front(i + 10);
	}
	error_count += AssertInequality(d.empty(), false, "Pushing many elements, Deque is not empty", out);

	// удаление всех раннее добавленных элементов, кроме одного
	for (int i = 6; i < 6000; i++) {
		d.pop_back();
	}
	error_count += AssertInequality(d.empty(), false, "Deleting all elementq except one, Deque is not empty", out);

	// удаляем последний элемент
	d.pop_front();
	error_count += AssertInequality(d.empty(), true, "Deleting last element, Deque is empty", out);
	return error_count;
}

// проход по деку с двух разных сторон
int DequeMainTest(ofstream& out) {
	Deque d = Deque(100);
	for (int i = 1; i <= 10; i++) {
		d.push_back(i);
	}
	int x = 1;
	while (!d.empty()) {
		if (AssertInequality(d.front(), string("front element is " + to_string(x)), "Top element is " + to_string(x), out)) {
			return 1;
		}
		if (AssertInequality(d.top(), string("top element is " + to_string(11 - x)), "Top element is " + to_string(x), out)) {
			return 1;
		}
		d.pop_back();
		d.pop_front();
		x++;
	}
	return 0;
}

// функция для запуска тестов
void deque_unit_test(ofstream& out) {
	TestRunner runner;
	runner.RunTest(DequePushTest, "PushTest", out);
	runner.RunTest(DequePopTest, "PopTest", out);
	runner.RunTest(DequeEmptyTest, "EmptyTest", out);
	runner.RunTest(DequeMainTest, "MainTest", out);
}
