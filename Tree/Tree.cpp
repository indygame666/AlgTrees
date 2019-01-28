//

#include <iostream>
#include <locale.h>

using namespace std;

class Tree 
{
	struct node
	{
		int data; 
		node* left; //левый потомок
		node* right; //правый потомок
	};

	node* root; //корень дерева

	node* insert(int x, node* temp) //вставка 
	{
		if (temp == NULL)
		{
			temp = new node;
			temp->data = x;
			temp->left = temp->right = NULL;
		}
		else if (x <temp->data) //если х меньше текущего , то переходим налево
			temp->left = insert(x, temp->left);
		else if (x > temp->data) //иначе направо
			temp->right = insert(x, temp->right);
		return temp;
	}

	node* makeEmpty(node* data) //удаление 
	{
		if (data == NULL)
			return NULL;
		{
			makeEmpty(data->left); 
			makeEmpty(data->right);
			delete data;
		}
		return NULL;
	}


	node* findMin(node* data) //находим наименьшее
	{
		if (data == NULL)
			return NULL;
		else if (data->left == NULL) //оно слева, поэтому идем налево до упора
			return data;
		else
			return findMin(data->left);
	}

	node* findMax(node* t) //находим наибольшее
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL) //оно справа, поэтому идем направо до упора
			return t;
		else
			return findMax(t->right);
	}

	node* remove(int x, node* t) //удаление х из дерева
	{
		node* temp; //временный элемент
		if (t == NULL)
			return NULL;
		else if (x < t->data) //если х меньше ключа текущего элемента - идем налево
			t->left = remove(x, t->left);
		else if (x > t->data) // иначе направо
			t->right = remove(x, t->right);
		else if ((t->left != NULL) && (t->right != NULL)) //если мы нашли нужный элемент, но у него есть 2 потомка
		{
			temp = findMin(t->right); //то находим следующий за удаляемым элемент
			t->data = temp->data;  //вставляем найденный элемент на место удаляемого 
			t->right = remove(t->data, t->right); //а тот "следующий" удаляем
		}
		else // если у элемента 1 ни одного потомка то
		{
			temp = t; //удаляемый узел
			if (t->left == NULL) //если есть правый потомок, то заменяем наш элемент на него
				t = t->right;
			else if (t->right == NULL) // если левый - то соответсвенно
				t = t->left;
			delete temp; //освоббождаем память 
		}

		return t;
	}

	void print_Tree(node* t, int level)
	{
		if (t)
		{
			print_Tree(t->left, level + 1);
			for (int i = 0; i< level; i++) cout << "   ";
			cout << t->data << endl;
			print_Tree(t->right, level + 1);
		}
	}

	bool find(node* t, int x) //поиск элемента по ключу
	{
		if (t == NULL) //если пустое дерево
			return false;
		else if (x < t->data) //инача сравниваем ключ и идем либо налево
			return find(t->left, x);
		else if (x > t->data) //или направо
			return find(t->right, x);
		else //пока не найдем нужно
			return true;
	}

public:
	Tree(){ root = NULL; }
	~Tree(){ root = makeEmpty(root); }

	void insert(int x)    /// добавление X
	{
		root = insert(x, root); 
	}

	void remove(int x)    /// удаление X
	{
		root = remove(x, root);
	}

	void display()  /// Вывод дерева
	{
		print_Tree(root, 10); cout << endl;
	}

	bool search(int x) // поиск X в дереве
	{
		return find(root, x);
	}
};

int main()
{
	Tree BinTree;
	int a, x;
	setlocale(LC_ALL, "Russian");
	for (;;)
	{
		system("cls");
		cout << "1 для добавления " << endl;
		cout << "2 для удаления  " << endl;
		cout << "3 для показа дерева " << endl;
		cout << "4 для поиска элемента " << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "Введите значение " << endl;
			cin >> x;
			BinTree.insert(x);
			break;
		case 2:
			cout << "Введите значение " << endl;
			cin >> x;
			BinTree.remove(x);
			break;
		case 3:
			cout << endl;
			BinTree.display();
			system("pause");
			break;
		case 4:
			cout << endl;
			cout << "Введите значение " << endl;
			cin >> x;
			if (BinTree.search(x))
				cout << "Значение " << x << " есть" << endl;
			else cout << "Значения " << x << " нет" << endl;
			system("pause");
			break;
		default:
			cout << "EXIT";
			abort();
		}
	}
	system("pause");
	return 0;
}