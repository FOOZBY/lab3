#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <windows.h>
#include <conio.h>
using namespace std;

struct Node
{
	Node* pNext;
	string data;
	string name, faculty, cafedra, group, stud_id, dob, tel_num, email;
	string temparr[8];
	Node(string data = string(), Node* pNext = nullptr)
	{
		this->data = data;
		this->pNext = pNext;
		int i = 0;
		char* pch = strtok(&data[0], ";");
		while (pch != NULL)                         // ���� ���� �������
		{
			temparr[i] = pch;
			pch = strtok(NULL, ";");
			i++;
		}
		this->name = this->temparr[0];
		this->faculty = this->temparr[1];
		this->cafedra = this->temparr[2];
		this->group = this->temparr[3];
		this->stud_id = this->temparr[4];
		this->dob = this->temparr[5];
		this->tel_num = this->temparr[6];
		this->email = this->temparr[7];
	}
};

struct List
{
	List();
	~List();

	//�������� ������� �������� � ������
	void pop_front();

	//���������� �������� � ����� ������
	void push_back(string data);

	// �������� ������
	void clear();

	// �������� ���������� ��������� � ������
	int GetSize() { return Size; }

	// ������������� �������� [] 
	string& operator[](int index);

	//���������� �������� � ������ ������
	void push_front(string data);

	//���������� �������� � ������ �� ���������� �������
	void insert(string data, int index);

	//�������� �������� � ������ �� ���������� �������
	void removeAt(int index);

	//�������� ���������� �������� � ������
	void pop_back();

	//����������� ������
	void showlist();

private:
	int Size;
	Node* head;
};

List::List()
{
	Size = 0;
	head = nullptr;
}

List::~List()
{
	clear();
}

void List::pop_front()
{
	Node* temp = head;

	head = head->pNext;

	delete temp;

	Size--;

}

void List::push_back(string data)
{
	if (head == nullptr)
	{
		head = new Node(data);
	}
	else
	{
		Node* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node(data);

	}

	Size++;
}

void List::clear()
{
	while (Size)
	{
		pop_front();
	}
}

string& List::operator[](int index)
{
	int counter = 0;
	if (index < 0)
		index = 0;
	if (index > Size)
		index = Size - 1;
	Node* current = this->head;

	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

void List::push_front(string data)
{
	head = new Node(data, head);
	Size++;
}

void List::insert(string data, int index)
{
	if (index < 1)
		push_front(data);
	else if (index > Size - 1)
		push_back(data);
	else
	{
		Node* previous = this->head;
		for (int i = 0; i < index - 1; i++)
			previous = previous->pNext;
		Node* newNode = new Node(data, previous->pNext);
		previous->pNext = newNode;
		Size++;
	}
}

void List::removeAt(int index)
{
	if (index < 1)
		pop_front();
	else
	{
		Node* previous = this->head;
		for (int i = 0; i < index - 1; i++)
			previous = previous->pNext;
		Node* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;
		delete toDelete;
		Size--;
	}
}

void List::pop_back()
{
	removeAt(Size - 1);
}

void List::showlist()
{
	{
		Node* current = head;
		int i = 0;
		while (current != nullptr)
		{
			cout << i << ")\n";
			cout << "���: " << setw(35) << current->name << endl;
			cout << "���������: " << setw(29) << current->faculty << endl;
			cout << "�������: " << setw(31) << current->cafedra << endl;
			cout << "������: " << setw(32) << current->group << endl;
			cout << "����� ����. ������: " << setw(20) << current->stud_id << endl;
			cout << "���� ��������: " << setw(25) << current->dob << endl;
			cout << "�������: " << setw(31) << current->tel_num << endl;
			cout << "��. �����: " << setw(29) << current->email << endl << endl;
			current = current->pNext;
			i++;
		}
	}
	system("pause");
}

void load_from_file(List &lst)
{
	cout << "������� �������� ����� ��� ������� ���� � ����: ";
	string prim_file, line, temp;
	while (true)
	{
		getline(cin, prim_file);
		ifstream in;
		in.open(prim_file);
		if (in.is_open())
		{
			while (!in.eof())
			{
				getline(in, line);
				lst.push_back(line);
			}
			break;
		}
		else
		{
			cout << "����������� ������� ��� ����� ��� ���� � �����." << endl;
			cout << "������� ������" << endl;
			cin.clear();
			cin.ignore(32767, '\n');
			system("cls");
		}
		cin.seekg(0, ios::end);
		cin.clear();
		in.close();
	}
}

void savetofile(List& lst)
{
	ofstream out;
	string file_name, temp;
	cout << "������ ��������� �����: ";
	getline(cin, file_name);
	out.open(file_name);
	for (int i = 0; i < lst.GetSize(); i++)
	{
		if (i != lst.GetSize())
			out << lst[i] << "\n";
		else
			out << lst[i];
	}
	out.close();
	cout << "���� �������\n";
	system("pause");
}

void MENU1(List& lst)//���������� �������� � ������
{
	int index;
	string data = "", temp;
	cout << "������� ������ �����, ���� ������ �������� �������: ";
	getline(cin, temp);
	if (temp == "")
		index == lst.GetSize();
	else
		index = stoi(temp);
	cout << "������� ��� ��������\n";
	getline(cin, temp); data += temp += ";";
	cout << "������� �������� ����������\n";
	getline(cin, temp); data += temp += ";";
	cout << "������� �������� �������\n";
	getline(cin, temp); data += temp += ";";
	cout << "������� ����� ������\n";
	getline(cin, temp); data += temp += ";";
	cout << "������� ����� ����. ������\n";
	getline(cin, temp); data += temp += ";";
	cout << "������� ���� ��������\n";
	getline(cin, temp); data += temp += ";";
	cout << "������� ����� ��������\n";
	getline(cin, temp); data += temp += ";";
	cout << "������� ����� ����������� �����\n";
	getline(cin, temp); data += temp += ";";
	lst.insert(data, index);
}