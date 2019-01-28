//

#include <iostream>
#include <locale.h>

using namespace std;

class Tree 
{
	struct node
	{
		int data; 
		node* left; //����� �������
		node* right; //������ �������
	};

	node* root; //������ ������

	node* insert(int x, node* temp) //������� 
	{
		if (temp == NULL)
		{
			temp = new node;
			temp->data = x;
			temp->left = temp->right = NULL;
		}
		else if (x <temp->data) //���� � ������ �������� , �� ��������� ������
			temp->left = insert(x, temp->left);
		else if (x > temp->data) //����� �������
			temp->right = insert(x, temp->right);
		return temp;
	}

	node* makeEmpty(node* data) //�������� 
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


	node* findMin(node* data) //������� ����������
	{
		if (data == NULL)
			return NULL;
		else if (data->left == NULL) //��� �����, ������� ���� ������ �� �����
			return data;
		else
			return findMin(data->left);
	}

	node* findMax(node* t) //������� ����������
	{
		if (t == NULL)
			return NULL;
		else if (t->right == NULL) //��� ������, ������� ���� ������� �� �����
			return t;
		else
			return findMax(t->right);
	}

	node* remove(int x, node* t) //�������� � �� ������
	{
		node* temp; //��������� �������
		if (t == NULL)
			return NULL;
		else if (x < t->data) //���� � ������ ����� �������� �������� - ���� ������
			t->left = remove(x, t->left);
		else if (x > t->data) // ����� �������
			t->right = remove(x, t->right);
		else if ((t->left != NULL) && (t->right != NULL)) //���� �� ����� ������ �������, �� � ���� ���� 2 �������
		{
			temp = findMin(t->right); //�� ������� ��������� �� ��������� �������
			t->data = temp->data;  //��������� ��������� ������� �� ����� ���������� 
			t->right = remove(t->data, t->right); //� ��� "���������" �������
		}
		else // ���� � �������� 1 �� ������ ������� ��
		{
			temp = t; //��������� ����
			if (t->left == NULL) //���� ���� ������ �������, �� �������� ��� ������� �� ����
				t = t->right;
			else if (t->right == NULL) // ���� ����� - �� �������������
				t = t->left;
			delete temp; //������������ ������ 
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

	bool find(node* t, int x) //����� �������� �� �����
	{
		if (t == NULL) //���� ������ ������
			return false;
		else if (x < t->data) //����� ���������� ���� � ���� ���� ������
			return find(t->left, x);
		else if (x > t->data) //��� �������
			return find(t->right, x);
		else //���� �� ������ �����
			return true;
	}

public:
	Tree(){ root = NULL; }
	~Tree(){ root = makeEmpty(root); }

	void insert(int x)    /// ���������� X
	{
		root = insert(x, root); 
	}

	void remove(int x)    /// �������� X
	{
		root = remove(x, root);
	}

	void display()  /// ����� ������
	{
		print_Tree(root, 10); cout << endl;
	}

	bool search(int x) // ����� X � ������
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
		cout << "1 ��� ���������� " << endl;
		cout << "2 ��� ��������  " << endl;
		cout << "3 ��� ������ ������ " << endl;
		cout << "4 ��� ������ �������� " << endl;
		cin >> a;
		switch (a)
		{
		case 1:
			cout << "������� �������� " << endl;
			cin >> x;
			BinTree.insert(x);
			break;
		case 2:
			cout << "������� �������� " << endl;
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
			cout << "������� �������� " << endl;
			cin >> x;
			if (BinTree.search(x))
				cout << "�������� " << x << " ����" << endl;
			else cout << "�������� " << x << " ���" << endl;
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