#include "ut_xor_linked_list.h"
#include "XorLinkedList.h"

using namespace std;

// ������� ��� ������ �������
ostream& operator<<(ostream& out, const vector<int>& v) {
	for (size_t i = 0; i < v.size(); i++) {
		if (i != 0) {
			out << " ";
		}
		out << to_string(v[i]);
	}
	return out;
}

// ������� ������������ ��������� � �������.
template<class T>
bool AssertInequality(const T& res, const T& ans,
	const string& hint, ofstream& out)
{
	// ���� ��������� � ����� �� �������, �� ������� ��������� � �������� ������ � �������� ����
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
		// ��������� ���������� ����, � ������� ��������� � ����������� �� ���-�� ������
		int error_count = func(out);
		if (error_count == 0) {
			out << " OK" << '\n';
		}
		else {
			out << '\n' << test_name << " has " << to_string(error_count) << " wrong answers" << '\n';
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
	// ���������� ����������� ���� ������
	int fail_count = 0;
};

int XorLinkedListAddTest(ofstream& out) {
	int error_count = 0;
	XorLinkedList xl = XorLinkedList(10000);
	// ���� �� ���������� ������ ��������
	xl.add_back(9);
	error_count += AssertInequality(xl.get(0), string("in position 0 is 9"), "Pushing element is 9", out);

	// ���� �� ������� ���������� ���������
	xl.add(3, 0);
	error_count += AssertInequality(xl.get(0), string("in position 0 is 3"), "Pushing element is 3 on 0 position", out);
	xl.add_front(6);
	error_count += AssertInequality(xl.get(0), string("in position 0 is 6"), "Pushing front element is 6", out);
	xl.add(4, 2);
	xl.add_back(8);
	error_count += AssertInequality(xl.get(4), string("in position 4 is 8"), "Pushing back element is 8", out);
	xl.add_front(13);
	xl.add_back(1);
	error_count += AssertInequality(xl.get_all(), { 13, 6, 3, 4, 9, 8, 1 }, "", out);
	return error_count;
}

int XorLinkedListRemoveTest(ofstream& out) {
	int error_count = 0;
	XorLinkedList xl = XorLinkedList(10000);
	
	// �������� ������������� ��������
	xl.add_back(1);
	error_count += AssertInequality(xl.remove(1), true, "Remove 1", out);
	error_count += AssertInequality(xl.get(0), string("out of range"), "list is empty", out);

	xl.add_back(3);
	xl.add_back(4);
	xl.add_front(2);
	
	// ������� ������� �� ������������ �������
	error_count += AssertInequality(xl.remove(1), false, "Remove 1", out);
	error_count += AssertInequality(xl.get_all(), { 2, 3, 4 }, "Remove 1", out);
	
	// �������� ���������� ���������
	error_count += AssertInequality(xl.remove(3), true, "Remove 3", out);
	error_count += AssertInequality(xl.get_all(), { 2, 4 }, "Remove 3", out);
	
	error_count += AssertInequality(xl.remove(2), true, "Remove 2", out);
	error_count += AssertInequality(xl.get_all(), { 4 }, "Remove 2", out);
	return error_count;
}

int XorLinkedListCountTest(ofstream& out) {
	int error_count = 0;
	XorLinkedList xl = XorLinkedList(10000);

	// �������� �� ������� ������ ��� ���������� ����������� ������
	error_count += AssertInequality(xl.count(), 0, "list is empty", out);

	// ��������� 3 ��������
	xl.add_back(1);
	xl.add_back(2);
	xl.add_back(3);
	error_count += AssertInequality(xl.count(), 3, "add 3 new elements", out);

	// ��������� ��� 4 ��������
	xl.add_front(4);
	xl.add_back(5);
	xl.add(6, 3);
	xl.add(7, 3);
	error_count += AssertInequality(xl.count(), 7, "add 4 new elements", out);
	error_count += AssertInequality(xl.get_all(), { 4, 1, 2, 7, 6, 3, 5 }, "", out);
	error_count += AssertInequality(xl.reverse(), { 5, 3, 6, 7, 2, 1, 4 }, "", out);

	// ������� 2 ��������
	xl.remove(4);
	xl.remove(6);
	error_count += AssertInequality(xl.count(), 5, "remove 2 element", out);
	error_count += AssertInequality(xl.get_all(), { 1, 2, 7, 3, 5 }, "", out);
	return error_count;
}

int XorLinkedListContainsTest(ofstream& out) {
	int error_count = 0;
	XorLinkedList xl = XorLinkedList();
	// ��������� ������ � �������� ���������� ������������ � �� ������������ �������
	xl.add_back(5);
	xl.add_front(7);
	xl.add_back(8);
	xl.add_front(9);
	xl.add_back(9);
	error_count += AssertInequality(xl.contains(6), false, "list does not contain 6", out);
	error_count += AssertInequality(xl.contains(8), true, "list contain 8", out);

	// ������� ��� ��������: ���� ��� � ������������ ����������, � ������ � ����. �������� ���������� ���
	xl.remove(8);
	xl.remove(9);
	error_count += AssertInequality(xl.contains(8), false, "remove 8", out);
	error_count += AssertInequality(xl.contains(9), true, "list contained two copies 9, one of which was deleted", out);
	return error_count;
}

// ������� ������� ������
void xor_linked_list_unit_test(ofstream& out) {
	TestRunner runner;
	runner.RunTest(XorLinkedListAddTest, "AddTest", out);
	runner.RunTest(XorLinkedListRemoveTest, "RemoveTest", out);
	runner.RunTest(XorLinkedListCountTest, "CountTest", out);
	runner.RunTest(XorLinkedListContainsTest, "ContainsTest", out);
}
