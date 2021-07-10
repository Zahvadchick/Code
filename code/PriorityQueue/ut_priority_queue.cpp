#include "ut_priority_queue.h"
#include "PriorityQueue.h"

using namespace std;
template<class T>
bool AssertInequality(const T& res, const T& ans,
	const string& hint, ofstream& out)
{
	// ���� ��������� � ����� �� �������, �� ����� ��������������� ���������
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
		// ��������� ���������� ���� � ������� ��������� � ����������� �� ���-�� ���������� ������
		int error_count = func(out);
		if (error_count == 0) {
			out << " OK\n";
		}
		else {
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

int PriorityQueuePushTest(ofstream& out) {
	int error_count = 0;
	PriorityQueue pq = PriorityQueue(10000);
	// ���� �� ���������� ������ ��������
	pq.push(9);
	error_count += AssertInequality(pq.top(), string("top element is 9, has max priority equal 9"), "Pushing element is 9", out);

	// ���� �� ������� ���������� ���������
	pq.push(5, 10);
	error_count += AssertInequality(pq.top(), string("top element is 5, has max priority equal 10"), "Pushing element is 5", out);
	pq.push(3);
	error_count += AssertInequality(pq.top(), string("top element is 5, has max priority equal 10"), "Pushing element is 3", out);

	// ���� �� ��������� ������� ����� ��������� ��������� ����� ���������
	for (int i = 0; i < 5000; i++) {
		pq.push(i * 2);
	}
	error_count += AssertInequality(pq.top(), string("top element is 9998, has max priority equal 9998"), "many pushing elements", out);
	return error_count;
}

int PriorityQueuePopTest(ofstream& out) {
	int error_count = 0;
	PriorityQueue pq = PriorityQueue(10000);
	// ���� �� �������� ������������ ��������
	pq.push(13);
	pq.pop();
	error_count += AssertInequality(pq.top(), string("Priority queue is empty"), "Deleting last element", out);

	// ���� �� ������� �������� (������ ��������� ������� c ��������� �����������)
	pq.push(13, 30);
	pq.push(14, 20);
	pq.push(17);
	pq.pop();
	error_count += AssertInequality(pq.top(), string("top element is 14, has max priority equal 20"), "After deleting element, last added element remains", out);

	// �������� �� ��������� ������� ��� ������������� ���������� � �������� ���������
	for (int i = 1001; i <= 10000; i++) {
		pq.push(i);
	}
	for (int i = 0; i < 8998; i++) {
		pq.pop();
	}
	error_count += AssertInequality(pq.top(), string("top element is 1002, has max priority equal 1002"), "Many pushing and deleting elements", out);
	pq.push(3);
	pq.pop();
	error_count += AssertInequality(pq.top(), string("top element is 1001, has max priority equal 1001"), "Many pushing and deleting elements", out);
	pq.pop();
	pq.pop();
	pq.pop();
	error_count += AssertInequality(pq.top(), string("top element is 3, has max priority equal 3"), "Many pushing and deleting elements", out);
	return error_count;
}

int PriorityQueueEmptyTest(ofstream& out) {
	int error_count = 0;
	PriorityQueue pq = PriorityQueue(10000);
	// ���� ��� �������������� �������. ��� ������ ���� ������
	error_count += AssertInequality(pq.empty(), true, "New Priority Queue is empty", out);

	// ���� �� �������� ������� � ����������� (�� ������ ��������)
	pq.push(5);
	error_count += AssertInequality(pq.empty(), false, "Pushing new element, Priority Queue is not empty", out);

	// ���� �� ������ ������� � �����������
	pq.pop();
	error_count += AssertInequality(pq.empty(), true, "Deleting all elements, Priority Queue is empty", out);

	// ���� �� ��������� ������� ����� ���������� ��������� ����� ���������
	for (int i = 5; i < 6000; i++) {
		pq.push(i + 10);
	}
	error_count += AssertInequality(pq.empty(), false, "Pushing many elements, Priority Queue is not empty", out);

	// �������� ���� ������ ����������� ���������, ����� ������
	for (int i = 6; i < 6000; i++) {
		pq.pop();
	}
	error_count += AssertInequality(pq.empty(), false, "Deleting all elementq except one, Priority Queue is not empty", out);

	// ������� ��������� �������
	pq.pop();
	error_count += AssertInequality(pq.empty(), true, "Deleting last element, Priority Queue is empty", out);
	return error_count;
}

// ������ ������� � ����������� ������������ ��� ����, ����� ���������� ��������� �������� � ������� �������� ����������.
// �� ��������� ������� � �����������, ����� ���� ��������� ��������� �������� � ���������, ������� ������ ��������� �� ��� ���,
// ���� ������� �� ��������. � ���� ����� ����������� ��������, ��������� ����.
int PriorityQueueMainTest(ofstream& out) {
	PriorityQueue pq = PriorityQueue(100);
	int prior = 99;
	for (int i = 1; i <= 10; i++) {
		pq.push(i, prior);
		prior--;
	}
	int x = 1;
	prior = 99;
	while (!pq.empty()) {
		if (AssertInequality(pq.top(), string("top element is " + to_string(x) + ", has max priority equal " + to_string(prior)), "Top element is " + to_string(x), out)) {
			return 1;
		}
		pq.pop();
		prior--;
		x++;
	}
	return 0;
}

// ������� ��� ������� ������
void priority_queue_unit_test(ofstream& out) {
	TestRunner runner;
	runner.RunTest(PriorityQueuePushTest, "PushTest", out);
	runner.RunTest(PriorityQueuePopTest, "PopTest", out);
	runner.RunTest(PriorityQueueEmptyTest, "EmptyTest", out);
	runner.RunTest(PriorityQueueMainTest, "MainTest", out);
}
