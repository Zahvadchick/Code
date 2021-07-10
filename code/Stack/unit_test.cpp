#include <cstdlib>
#include <typeinfo>
#include <sstream>

#include "unit_test.h"
#include "Stack.h"

// функци€ сравнивающа€ результат с ответом.
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

// класс дл€ вызова юнит тестов
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
		} else {
			out << '\n' << test_name << " has " << to_string(error_count) << " wrong answers" << '\n';
		}
	}

	// деструтор. ≈сли среди запущенных тестов были те, которые не прошли, то выводит в поток ошибок сообщение с количеством проваленных тестов
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

int StackPushTest(ofstream& out) {
	int error_count = 0;
	Stack s = Stack();
	// добавление одного элемента
	s.push(9);
	error_count += AssertInequality(s.top(), string("top element is 9"), "Pushing element is 9", out);

	// добавлени€ двух элементов, провер€€ пор€док
	s.push(5);
	error_count += AssertInequality(s.top(), string("top element is 5"), "Pushing element is 5", out);
	s.push(3);
	error_count += AssertInequality(s.top(), string("top element is 3"), "Pushing element is 3", out);

	// поведение стека при добалении множества новых элементов
	for (int i = 0; i < 5000; i++) {
		s.push(i * 2);
	}
	error_count += AssertInequality(s.top(), string("top element is 9998"), "many pushing elements",out);

	// заполнение до лимита
	for (int i = 0; i < 4997; i++) {
		s.push(i * 3);
	}
	error_count += AssertInequality(s.push(1), string("push error: stack is full"), "adding to the full stack", out);
	return error_count;
}

int StackPopTest(ofstream& out) {
	int error_count = 0;
	Stack s = Stack();
	// удаление добавленного элемента
	s.push(13);
	s.pop();
	error_count += AssertInequality(s.top(), string("Stack is empty"), "Deleting last element", out);

	// удаление из пустого стека
	error_count += AssertInequality(s.pop(), string("pop error: stack is empty"), "Deleting from an empty stack", out);

	// проверка на пор€док удалени€ (должен удалитьс€ последний добавленный элемент
	s.push(12);
	s.push(14);
	s.pop();
	error_count += AssertInequality(s.top(), string("top element is 12"), "After deleting element, last element remains", out);

	// проверка на поведение стека при множественном добавлении и удалении элементов
	for (int i = 1001; i <= 10000; i++) {
		s.push(i);
	}
	for (int i = 0; i < 8998; i++) {
		s.pop();
	}
	error_count += AssertInequality(s.top(), string("top element is 1002"), "Many pushing and deleting elements", out);
	s.push(3);
	error_count += AssertInequality(s.top(), string("top element is 3"), "Many pushing and deleting elements", out);
	s.pop();
	s.pop();
	error_count += AssertInequality(s.top(), string("top element is 1001"), "Many pushing and deleting elements", out);
	return error_count;
}

int StackEmptyTest(ofstream& out) {
	int error_count = 0;
	Stack s = Stack();
	// тест дл€ новосозданного стека. ќн должен быть пустым
	error_count += AssertInequality(s.empty(), true, "New stack is empty", out);

	// тест на непустой стек (из одного элемента)
	s.push(5);
	error_count += AssertInequality(s.empty(), false, "Pushing new element, stack is not empty", out);

	// тест на пустой стек
	s.pop();
	error_count += AssertInequality(s.empty(), true, "Deleting all elements, stack is empty", out);

	// тест на поведение функции после добавлени€ множества новых элементов
	for (int i = 5; i < 6000; i++) {
		s.push(i + 10);
	}
	error_count += AssertInequality(s.empty(), false, "Pushing many elements, stack is not empty", out);

	// удаление всех раннее добавленных элементов, кроме одного
	for (int i = 6; i < 6000; i++) {
		s.pop();
	}
	error_count += AssertInequality(s.empty(), false, "Deleting all elements except one, stack is not empty", out);

	// удал€ем последний элемент
	s.pop();
	error_count += AssertInequality(s.empty(), true, "Deleting last element, stack is empty", out);
	return error_count;
}

// обычно стек используетс€ дл€ того, чтобы обработать некоторые элементы в обратном пор€дке.
// ћы заполн€ем стек, после чего совершаем некоторые действи€ с головным элементом до тех пор, пока стек не опустеет.
// ¬ этом тесте выполн€ютс€ действи€, указанные выше.
int StackMainTest(ofstream& out) {
	Stack s = Stack(100);
	for (int i = 1; i <= 10; i++) {
		s.push(i);
	}
	int x = 10;
	while (!s.empty()) {
		if (AssertInequality(s.top(), string("top element is " + to_string(x)), "", out)) {
			return 1;
		}
		s.pop();
		x--;
	}
	return 0;
}

// функци€ дл€ запуска тестов
void stack_unit_test(ofstream& out) {
	TestRunner runner;
	runner.RunTest(StackPushTest, "PushTest", out);
	runner.RunTest(StackPopTest, "PopTest", out);
	runner.RunTest(StackEmptyTest, "EmptyTest", out);
	runner.RunTest(StackMainTest, "MainTest", out);
}
