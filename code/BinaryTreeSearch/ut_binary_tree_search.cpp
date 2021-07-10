#include "ut_binary_tree_search.h"

using namespace std;

/* проверяет соответствует ли дерево критериям бинарного дерева поиска. 
 Мы проверяем, не превосходит ли левый потомок и не меньше ли правый потомок чем переданный узел. 
 Если нет, то мы рекурсивно запускаем функцию для потомков. Если все узлы выдали истину, то дерево валидно, иначе нет. */
bool is_valid(Node_bts* root) {
	bool answer = true;
	int worked = 0;
	if (root->left && root->left->val <= root->val) {
		answer *= is_valid(root->left);
		worked++;
	}
	if (root->right && root->val <= root->right->val) {
		answer *= is_valid(root->right);
		worked++;
	}
	if ((root->left != NULL) + (root->right != NULL) != worked) {
		return false;
	}
	else {
		return answer;
	}
}

// перегрузка вывода вектора в поток
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

int BinaryTreeSearchAddTest(ofstream& out) {
	int error_count = 0;
	BinaryTreeSearch bts = BinaryTreeSearch();
	// тест на добавление одного элемента
	bts.add(9);
	error_count += AssertInequality(bts.get_min()->val, 9, "Pushing element is 9", out);

	// добавляем два новых элемента, один меньше раннее добавленого, другой больше
	bts.add(8);
	bts.add(12);
	error_count += AssertInequality(bts.get_min()->val, 8, "Pushing new elements", out);
	error_count += AssertInequality(bts.get_max()->val, 12, "Pushing new elements", out);

	// добавляем еще несколько узлов и выполняем три основных вида обхода деревьев
	bts.add(15);
	bts.add(1);
	bts.add(14);
	bts.add(17);
	vector<int> v;
	bts.preorder(bts.get_head(), v);
	error_count += AssertInequality(v, {9, 8, 1, 12, 15, 14, 17}, "Preorder", out);
	v = {};
	bts.inorder(bts.get_head(), v);
	error_count += AssertInequality(v, {1, 8, 9, 12, 14, 15, 17}, "Inorder", out);
	v = {};
	bts.postorder(bts.get_head(), v);
	error_count += AssertInequality(v, {1, 8, 14, 17, 15, 12, 9}, "Postorder", out);

	// проверка полученного дерева на валидность
	error_count += AssertInequality(is_valid(bts.get_head()), true, "Check tree's valid", out);
	return error_count;
}

int BinaryTreeSearchRemoveTest(ofstream& out) {
	int error_count = 0;
	BinaryTreeSearch bts = BinaryTreeSearch();

	// удаление единственного элемента
	bts.add(1);
	error_count += AssertInequality(bts.remove(1), true, "Remove last element", out);

	// попытка удалить его еще раз
	error_count += AssertInequality(bts.remove(1), false, "Try remove element, that was previously in the binary tree search", out);

	// попытка удалить из пустого дерева элемент, никогда не бывавшего в дереве
	error_count += AssertInequality(bts.remove(2), false, "Remove element from empty tree", out);

	bts.add(4);
	bts.add(8);
	bts.add(5);
	bts.add(2);
	bts.add(6);
	bts.add(9);
	bts.add(2);
	bts.add(3);
	bts.add(7);
	bts.add(10);
	bts.add(1);
	bts.add(11);

	// пробуем трижды удалить элемент который содержится в дереве два раза
	error_count += AssertInequality(bts.remove(2), true, "Remove 2", out);
	error_count += AssertInequality(bts.remove(2), true, "Remove 2", out);
	error_count += AssertInequality(bts.remove(2), false, "Remove 2 from tree without 2", out);

	// удаление не существующего элемента
	error_count += AssertInequality(bts.remove(12), false, "Remove 12 from tree without 12", out);

	// разные виды удалений: листов с двумя потомакми и одним
	error_count += AssertInequality(bts.remove(10), true, "Remove 10", out);
	error_count += AssertInequality(bts.remove(8), true, "Remove 8", out);
	error_count += AssertInequality(bts.remove(7), true, "Remove 7", out);

	// проведем обходы полученного дерева
	vector<int> v;
	bts.preorder(bts.get_head(), v);
	error_count += AssertInequality(v, {4, 3, 1, 9, 5, 6, 11}, "Preorder", out);
	v = {};
	bts.inorder(bts.get_head(), v);
	error_count += AssertInequality(v, {1, 3, 4, 5, 6, 9, 11}, "Inorder", out);
	v = {};
	bts.postorder(bts.get_head(), v);
	error_count += AssertInequality(v, {1, 3, 6, 5, 11, 9, 4}, "Postorder", out);

	// проверка полученного дерева на валидность
	error_count += AssertInequality(is_valid(bts.get_head()), true, "Check tree's valid", out);
	return error_count;
}

int BinaryTreeSearchFindTest(ofstream& out) {
	int error_count = 0;
	BinaryTreeSearch bts = BinaryTreeSearch();
	bts.add(8);
	bts.add(22);
	bts.add(49);
	bts.add(320);
	bts.add(8);
	bts.add(14);
	
	// пробуем найти существующие и нет элементы
	error_count += AssertInequality(bts.find(22) != NULL, true, "Tree has 22", out);
	error_count += AssertInequality(bts.find(23) != NULL, false, "Tree hasn't 23", out);
	error_count += AssertInequality(bts.find(320) != NULL, true, "Tree has 320", out);
	error_count += AssertInequality(bts.find(0) != NULL, false, "Tree hasn't 0", out);
	error_count += AssertInequality(bts.find(8) != NULL, true, "Tree has 8", out);

	// удаляем элемент, который содержится в дереве дважды
	bts.remove(8);
	error_count += AssertInequality(bts.find(8) != NULL, true, "Tree has 8", out);

	// удаляем второй экземпляр раннее удаленного элемента, теперь мы не должны его найти
	bts.remove(8);
	error_count += AssertInequality(bts.find(8) != NULL, false, "Tree hasn't 8", out);

	// удаляем элемент из дерева
	bts.remove(22);
	error_count += AssertInequality(bts.find(22) != NULL, false, "Tree hasn't 22", out);

	// ищем не существующий элемент
	error_count += AssertInequality(bts.find(12) != NULL, false, "Tree hasn't 12", out);

	// проверка дерева на валидность
	error_count += AssertInequality(is_valid(bts.get_head()), true, "Check tree's valid", out);
	return error_count;
}

// функция запуска тестов
void binary_tree_search_unit_test(ofstream& out) {
	TestRunner runner;
	runner.RunTest(BinaryTreeSearchAddTest, "AddTest", out);
	runner.RunTest(BinaryTreeSearchRemoveTest, "RemoveTest", out);
	runner.RunTest(BinaryTreeSearchFindTest, "FindTest", out);
}
