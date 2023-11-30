#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <Windows.h>
#include <unordered_map>
#include <unordered_set>

using namespace std;

int InputInt()
{
	int result;

	bool isCorrect = cin.good();
	do {

		if (cin.fail() || cin.eof() || cin.bad())
		{
			cin.clear();
			cin.ignore(32767, '\n');

			if (cin.bad()) {
				cerr << "����������� ������ � ������ �����. ��������� ���������." << endl;
				exit(1);
			}
			cout << "������� ������ ����� �����!" << endl;

		}

		cin >> result;

		isCorrect = cin.good();


	} while (!isCorrect);

	return result;
}

int InputInt(int min, int max)
{
	int res;
	do
	{
		res = InputInt();
	} while (res < min || res > max);

	return res;
}

class Vegetable
{
	string name;
	int count;

public:
	Vegetable() {}
	Vegetable(const Vegetable& obj) : name(obj.name), count(obj.count) {}
	Vegetable(const string& name, int count) :name(name), count(count) {};

	void setName(const string& name) { this->name = name; }
	void setCount(int count) { this->count = count; }

	string getName()const { return name; }
	int getCount()const { return count; }

	bool operator>(const Vegetable& obj)const
	{
		return count > obj.count;
	}

	bool operator<(const Vegetable& obj)const
	{
		return count < obj.count;
	}

	bool operator==(const Vegetable& obj)const
	{
		return count == obj.count;
	}

	void input()
	{
		cout << "������� ��������:" << endl;
		do
		{
			getline(cin, name);
		} while (name.empty());

		cout << "������� ����������:" << endl;
		count = InputInt(0, 1000000);
	}
	string getInfo()const
	{
		string info = name + " - " + to_string(count) + " ��.";

		return info;
	}
};

namespace std
{
	template <>
	struct hash<Vegetable>
	{
		size_t operator()(const Vegetable& k) const
		{
			return ((hash<string>()(k.getName()) ^ (hash<int>()(k.getCount()) << 1)) >> 1);
		}
	};
}

void MapMenu()//����� - ����-�������� ����������
{
	map<string ,Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "1.������ � ����������� map" << endl;
		cout << "==============================" << endl;
		
		cout << "1.����������" << endl;
		cout << "2.��������" << endl;
		cout << "3.��������������" << endl;
		cout << "4.����� �� �����" << endl;
		cout << "5.�����" << endl;
		cout << "6.����� ������ � ����" << endl;
		cout << "7.�����" << endl;

		switch (InputInt(1, 7))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables[vegetable.getName()] = vegetable;
			break;
		}
		case 2:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)//������������� ��������� ���������� � ���������� ���
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			break;
		}
		case 3:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			Vegetable vegetable;
			vegetable.input();
			vegetables[vegetable.getName()] = vegetable;
			break;
		}
		case 4:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			cout << "������� ������ �������� ��� ������:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			auto iter = vegetables.find(search);
			if (iter != vegetables.end())
			{
				cout << iter->second.getInfo() << endl;
			}
			else
			{
				cout << "������ �� �������" << endl;
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			ofstream fout("l7_map.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "������ �������� �����!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "������ ����" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.second.getInfo() << endl;
				}
				cout << "������ ��������� � ���� 'l7_map.txt'" << endl;
				system("pause");
			}
			fout.close();
			break;
		}
		case 7:
		{
			isWork = false;
			break;
		}
		}
	}
}

void MultimapMenu()//����� - ����-�������� ���� ���������� ������
{
	multimap<string, Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "2.������ � ����������� multimap" << endl;
		cout << "============================================" << endl;

		cout << "1.����������" << endl;
		cout << "2.��������" << endl;
		cout << "3.��������������" << endl;
		cout << "4.����� �� �����" << endl;
		cout << "5.�����" << endl;
		cout << "6.����� ������ � ����" << endl;
		cout << "7.�����" << endl;

		switch (InputInt(1, 7))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(std::pair<string, Vegetable> (vegetable.getName(), vegetable));
			break;
		}
		case 2:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)//������������� ��������� ���������� � ���������� ���
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			break;
		}
		case 3:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)//������������� ��������� ���������� � ���������� ���
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(std::pair<string, Vegetable>(vegetable.getName(), vegetable));
			break;
		}
		case 4:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			cout << "������� ������ �������� ��� ������:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			auto iter = vegetables.find(search);
			if (iter != vegetables.end())
			{
				cout << iter->second.getInfo() << endl;
			}
			else
			{
				cout << "������ �� �������" << endl;
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			ofstream fout("l7_multimap.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "������ �������� �����!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "������ ����" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.second.getInfo() << endl;
				}
				cout << "������ ��������� � ���� 'l7_multimap.txt'" << endl;
				system("pause");
			}
			fout.close();
			break;
		}
		case 7:
		{
			isWork = false;
			break;
		}
		}
	}
}

void UnorderedMapMenu()//����� � ���� ������� ����������
{
	unordered_map<string, Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "3.������ � ����������� unordered_map" << endl;
		cout << "============================================" << endl;
		
		cout << "1.����������" << endl;
		cout << "2.��������" << endl;
		cout << "3.��������������" << endl;
		cout << "4.����� �� �����" << endl;
		cout << "5.�����" << endl;
		cout << "6.����� ������ � ����" << endl;
		cout << "7.�����" << endl;

		switch (InputInt(1, 7))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables[vegetable.getName()] = vegetable;
			break;
		}
		case 2:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			break;
		}
		case 3:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			Vegetable vegetable;
			vegetable.input();
			vegetables[vegetable.getName()] = vegetable;
			break;
		}
		case 4:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			cout << "������� ������ �������� ��� ������:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			auto iter = vegetables.find(search);
			if (iter != vegetables.end())
			{
				cout << iter->second.getInfo() << endl;
			}
			else
			{
				cout << "������ �� �������" << endl;
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			ofstream fout("l7_unordered_map.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "������ �������� �����!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "������ ����" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.second.getInfo() << endl;
				}
				cout << "������ ��������� � ���� 'l7_unordered_map.txt'" << endl;
				system("pause");
			}
			fout.close();
			break;
		}
		case 7:
		{
			isWork = false;
			break;
		}
		}
	}
}

void UnorderedMultimapMenu()//����� ������ ������ ����������(������������)
{
	unordered_multimap<string, Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "4.������ � ����������� unordered_multimap" << endl;
		cout << "============================================" << endl;

		cout << "1.����������" << endl;
		cout << "2.��������" << endl;
		cout << "3.��������������" << endl;
		cout << "4.����� �� �����" << endl;
		cout << "5.�����" << endl;
		cout << "6.����� ������ � ����" << endl;
		cout << "7.�����" << endl;

		switch (InputInt(1, 7))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(std::pair<string, Vegetable>(vegetable.getName(), vegetable));
			break;
		}
		case 2:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			break;
		}
		case 3:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(std::pair<string, Vegetable>(vegetable.getName(), vegetable));
			break;
		}
		case 4:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			cout << "������� ������ �������� ��� ������:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			auto iter = vegetables.find(search);
			if (iter != vegetables.end())
			{
				cout << iter->second.getInfo() << endl;
			}
			else
			{
				cout << "������ �� �������" << endl;
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			ofstream fout("l7_unordered_multimap.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "������ �������� �����!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "������ ����" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.second.getInfo() << endl;
				}
				cout << "������ ��������� � ���� 'l7_unordered_multimap.txt'" << endl;
				system("pause");
			}
			fout.close();
			break;
		}
		case 7:
		{
			isWork = false;
			break;
		}
		}
	}
}

void SetMenu()//����� �������� ������ ����� ��� ����������
{
	set<Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "5.������ � ����������� set" << endl;
		cout << "============================================" << endl;

		cout << "1.����������" << endl;
		cout << "2.��������" << endl;
		cout << "3.��������������" << endl;
		cout << "4.����� �� �����" << endl;
		cout << "5.�����" << endl;
		cout << "6.����� ������ � ����" << endl;
		cout << "7.�����" << endl;

		switch (InputInt(1, 7))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(vegetable);
			break;
		}
		case 2:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			break;
		}
		case 3:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(vegetable);
			break;
		}
		case 4:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			cout << "������� ������ �������� ��� ������:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			bool isFound = false;
			for (auto iter : vegetables)
			{
				if (iter.getName().find(search) != -1)
				{
					cout << iter.getInfo() << endl;
					isFound = true;
				}
			}
			if(!isFound)
			{
				cout << "������ �� �������" << endl;
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			ofstream fout("l7_set.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "������ �������� �����!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "������ ����" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.getInfo() << endl;
				}
				cout << "������ ��������� � ���� 'l7_set.txt'" << endl;
				system("pause");
			}
			fout.close();
			break;
		}
		case 7:
		{
			isWork = false;
			break;
		}
		}
	}
}

void MultisetMenu()//��������� ���������� ��������
{
	multiset<Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "6.������ � ����������� multiset" << endl;
		cout << "============================================" << endl;

		cout << "1.����������" << endl;
		cout << "2.��������" << endl;
		cout << "3.��������������" << endl;
		cout << "4.����� �� �����" << endl;
		cout << "5.�����" << endl;
		cout << "6.����� ������ � ����" << endl;
		cout << "7.�����" << endl;

		switch (InputInt(1, 7))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(vegetable);
			break;
		}
		case 2:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			break;
		}
		case 3:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(vegetable);
			break;
		}
		case 4:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			cout << "������� ������ �������� ��� ������:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			bool isFound = false;
			for (auto iter : vegetables)
			{
				if (iter.getName().find(search) != -1)
				{
					cout << iter.getInfo() << endl;
					isFound = true;
				}
			}
			if (!isFound)
			{
				cout << "������ �� �������" << endl;
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			ofstream fout("l7_multiset.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "������ �������� �����!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "������ ����" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.getInfo() << endl;
				}
				cout << "������ ��������� � ���� 'l7_multiset.txt'" << endl;
				system("pause");
			}
			fout.close();
			break;
		}
		case 7:
		{
			isWork = false;
			break;
		}
		}
	}
}

void UnorderedSetMenu()
{
	unordered_set<Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "7.������ � ����������� unordered_set" << endl;
		cout << "============================================" << endl;

		cout << "1.����������" << endl;
		cout << "2.��������" << endl;
		cout << "3.��������������" << endl;
		cout << "4.����� �� �����" << endl;
		cout << "5.�����" << endl;
		cout << "6.����� ������ � ����" << endl;
		cout << "7.�����" << endl;

		switch (InputInt(1, 7))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(vegetable);
			break;
		}
		case 2:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			break;
		}
		case 3:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(vegetable);
			break;
		}
		case 4:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			cout << "������� ������ �������� ��� ������:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			bool isFound = false;
			for (auto iter : vegetables)
			{
				if (iter.getName().find(search) != -1)
				{
					cout << iter.getInfo() << endl;
					isFound = true;
				}
			}
			if (!isFound)
			{
				cout << "������ �� �������" << endl;
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			ofstream fout("l7_unordered_set.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "������ �������� �����!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "������ ����" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.getInfo() << endl;
				}
				cout << "������ ��������� � ���� 'l7_unordered_set.txt'" << endl;
				system("pause");
			}
			fout.close();
			break;
		}
		case 7:
		{
			isWork = false;
			break;
		}
		}
	}
}

void UnorderedMultisetMenu()
{
	unordered_multiset<Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "8.������ � ����������� unordered_multiset" << endl;
		cout << "============================================" << endl;

		cout << "1.����������" << endl;
		cout << "2.��������" << endl;
		cout << "3.��������������" << endl;
		cout << "4.����� �� �����" << endl;
		cout << "5.�����" << endl;
		cout << "6.����� ������ � ����" << endl;
		cout << "7.�����" << endl;

		switch (InputInt(1, 7))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(vegetable);
			break;
		}
		case 2:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			break;
		}
		case 3:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "�������� ������� ��� ��������������:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			vegetables.erase(iter);
			Vegetable vegetable;
			vegetable.input();
			vegetables.insert(vegetable);
			break;
		}
		case 4:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "������ ����" << endl;
				system("pause");
				break;
			}

			cout << "������� ������ �������� ��� ������:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			bool isFound = false;
			for (auto iter : vegetables)
			{
				if (iter.getName().find(search) != -1)
				{
					cout << iter.getInfo() << endl;
					isFound = true;
				}
			}
			if (!isFound)
			{
				cout << "������ �� �������" << endl;
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			ofstream fout("l7_unordered_multiset.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "������ �������� �����!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "������ ����" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.getInfo() << endl;
				}
				cout << "������ ��������� � ���� 'l7_unordered_multiset.txt'" << endl;
				system("pause");
			}
			fout.close();
			break;
		}
		case 7:
		{
			isWork = false;
			break;
		}
		}
	}
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "1.������ � ����������� map" << endl;
		cout << "2.������ � ����������� multimap" << endl;
		cout << "3.������ � ����������� unordered_map" << endl;
		cout << "4.������ � ����������� unordered_multimap" << endl;
		cout << "5.������ � ����������� set" << endl;
		cout << "6.������ � ����������� multiset" << endl;
		cout << "7.������ � ����������� unordered_set" << endl;
		cout << "8.������ � ����������� unordered_multiset" << endl;
		cout << "9.�����" << endl;

		switch (InputInt(1, 9))
		{
		case 1:
		{
			MapMenu();
			break;
		}
		case 2:
		{
			MultimapMenu();
			break;
		}
		case 3:
		{
			UnorderedMapMenu();
			break;
		}
		case 4:
		{
			UnorderedMultimapMenu();
			break;
		}
		case 5:
		{
			SetMenu();
			break;
		}
		case 6:
		{
			MultisetMenu();
			break;
		}
		case 7:
		{
			UnorderedSetMenu();
			break;
		}
		case 8:
		{
			UnorderedMultisetMenu();
			break;
		}
		case 9:
		{
			isWork = false;
			break;
		}
		}
	}
}