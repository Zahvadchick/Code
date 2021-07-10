#include "ut_queue.h"
#include "Queue.h"

using namespace std;
template<class T>
bool AssertInequality(const T& res, const T& ans,
	const string& hint, ofstream& out)
{
	// ���� ��������� � ����� �� �������, �� ������� ��������������� ���������
	if (res != ans) {
		out << '\n' << "Assertion failed: " << res << " != " << ans << " hint: " << hint;
		return true;
	}
	return false;
}

// ����� ��� ������ ���� ������
class TestRunner {
public:
	//��������� ���������� ������� �����
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name, ofstream& out) {
		out << test_name << ":";
		// ��������� ���������� ���� � ������� ��������� � ����������� �� ���-�� ������
		int error_count = func(out);
		if (error_count == 0) {
			out << " OK\n";
		} else {
			out << '\n' << test_name << " has " << to_string(error_count) << " wrong answers\n";
		}
	}

	// ���������. ���� ����� ���������� ������ ���� ��, ������� �� ������, �� ������� � ����� ������ ��������� � ����������� ����������� ������
	~TestRunner() {
		if (fail_count > 0) {
			cerr << fail_count << " unit tests failed. Terminate" << endl;
			exit(1);
		}
	}

private:
	// ���-�� ������
	int fail_count = 0;
};

int QueuePushTest(ofstream& out) {
	int error_count = 0;
	Queue q = Queue(5003);
	// ���� �� ���������� ������ ��������
	q.push(9);
	error_count += AssertInequality(q.front(), string("front element is 9"), "Pushing element is 9", out);

	// ���� �� ������� ���������� ���������
	q.push(5);
	error_count += AssertInequality(q.top(), string("top element is 5"), "Pushing element is 5", out);
	q.push(3);
	error_count += AssertInequality(q.top(), string("top element is 3"), "Pushing element is 3", out);
	error_count += AssertInequality(q.front(), string("front element is 9"), "Pushing element is 3", out);

	// ���� �� ��������� ������� ����� ��������� ��������� ����� ���������
	for (int i = 0; i < 5000; i++) {
		q.push(i * 2);
	}
	error_count += AssertInequality(q.front(), string("front element is 9"), "many pushing elements", out);
	error_count += AssertInequality(q.push(1), string("push error: queue is full"), "adding to the full stack", out);
	return error_count;
}

int QueuePopTest(ofstream& out) {
	int error_count = 0;
	Queue q = Queue(10000);
	// ���� �� �������� ������������ ��������
	q.push(13);
	q.pop();
	error_count += AssertInequality(q.top(), string("Queue is empty"), "Deleting last element", out);

	// �������� �� ������ �������
	error_count += AssertInequality(q.pop(), string("pop error: queue is empty"), "Deleting from an empty queue", out);

	// ���� �� ������� �������� (������ ��������� ������ �������)
	q.push(12);
	q.push(14);
	q.pop();
	error_count += AssertInequality(q.front(), string("front element is 14"), "After deleting element, last added element remains", out);

	// �������� �� ��������� ������� ��� ������������� ���������� � �������� ���������
	for (int i = 1001; i <= 10000; i++) {
		q.push(i);
	}
	for (int i = 0; i < 8998; i++) {
		q.pop();
	}
	error_count += AssertInequality(q.top(), string("top element is 10000"), "Many pushing and deleting elements", out);
	error_count += AssertInequality(q.front(), string("front element is 9998"), "Many pushing and deleting elements", out);
	q.push(3);
	error_count += AssertInequality(q.top(), string("top element is 3"), "Many pushing and deleting elements", out);
	q.pop();
	q.pop();
	error_count += AssertInequality(q.front(), string("front element is 10000"), "Many pushing and deleting elements", out);
	return error_count;
}

int QueueEmptyTest(ofstream& out) {
	int error_count = 0;
	Queue q = Queue(10000);
	// ���� ��� ������������� �������. ��� ������ ���� ������
	error_count += AssertInequality(q.empty(), true, "New Queue is empty", out);

	// ���� �� �������� ������� (�� ������ ��������)
	q.push(5);
	error_count += AssertInequality(q.empty(), false, "Pushing new element, Queue is not empty", out);

	// ���� �� ������ �������
	q.pop();
	error_count += AssertInequality(q.empty(), true, "Deleting all elements, Queue is empty", out);

	// ���� �� ��������� ������� ����� ���������� ��������� ����� ���������
	for (int i = 5; i < 6000; i++) {
		q.push(i + 10);
	}
	error_count += AssertInequality(q.empty(), false, "Pushing many elements, Queue is not empty", out);

	// �������� ���� ������ ����������� ���������, ����� ������
	for (int i = 6; i < 6000; i++) {
		q.pop();
	}
	error_count += AssertInequality(q.empty(), false, "Deleting all elementq except one, Queue is not empty", out);

	// ������� ��������� �������
	q.pop();
	error_count += AssertInequality(q.empty(), true, "Deleting last element, Queue is empty", out);
	return error_count;
}

// ������ ������� ������������ ��� ����, ����� ���������� ��������� �������� � ������� �������.
// �� ��������� �������, ����� ���� ��������� ��������� �������� � ��������� ��������� �� ��� ���, ���� ������� �� ��������.
// � ���� ����� ����������� ��������, ��������� ����.
int QueueMainTest(ofstream& out) {
	Queue q = Queue(100);
	for (int i = 1; i <= 10; i++) {
		q.push(i);
	}
	int x = 1;
	while (!q.empty()) {
		if (AssertInequality(q.front(), string("front element is " + to_string(x)), "Front element is " + to_string(x), out)) {
			return 1;
		}
		q.pop();
		x++;
	}
	return 0;
}

// ������� ����������� �����
void queue_unit_test(ofstream& out) {
	TestRunner runner;
	runner.RunTest(QueuePushTest, "PushTest", out);
	runner.RunTest(QueuePopTest, "PopTest", out);
	runner.RunTest(QueueEmptyTest, "EmptyTest", out);
	runner.RunTest(QueueMainTest, "MainTest", out);
}
