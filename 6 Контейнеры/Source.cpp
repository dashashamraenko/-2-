#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <array>
#include <algorithm>
#include <string>
#include <Windows.h>

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
				cerr << "Критическая ошибка в потоке ввода. Программа завершена." << endl;
				exit(1);
			}

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
	Vegetable() :name("-"), count(0) {}
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

	void input()
	{
		cout << "Введите название:" << endl;
		do
		{
			getline(cin, name);
		} while (name.empty());

		cout << "Введите количество:" << endl;
		count = InputInt(0, 10000000);
	}
	string getInfo()const
	{
		string info = name + " - " + to_string(count) + " шт.";

		return info;
	}
};

void VectorMenu()
{
	vector<Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Сортировка" << endl;
		cout << "7.Вывод данных в файл" << endl;
		cout << "8.Выход" << endl;

		switch (InputInt(1, 8))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables.push_back(vegetable);
			break;
		}
		case 2:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "Выберите элемент для удаления:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			vegetables.erase(vegetables.begin() + index);
			break;
		}
		case 3:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "Выберите элемент для редакттирования:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;
			vegetables[index].input();
			break;
		}
		case 4:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "Список пуст" << endl;
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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			cout << "Введите строку или подстроку названия для поиска:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			vector<Vegetable> found;
			for (auto vegetable : vegetables)
			{
				if (vegetable.getName().find(search) != -1)
					found.push_back(vegetable);
			}

			if (found.empty())
			{
				cout << "Ничего не найдено" << endl;
			}
			else
			{
				int i = 1;
				for (auto vegetable : found)
				{
					cout << i++ << ". " << vegetable.getInfo() << endl;
				}
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			sort(vegetables.begin(), vegetables.end());

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			ofstream fout("l6_vector.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "Список пуст" << endl;
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.getInfo() << endl;
				}
			}
			fout.close();
			break;
		}
		case 8:
		{
			isWork = false;
			break;
		}
		}
	}
}

void ListMenu()
{
	list<Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Сортировка" << endl;
		cout << "7.Вывод данных в файл" << endl;
		cout << "8.Выход" << endl;

		switch (InputInt(1, 8))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables.push_back(vegetable);
			break;
		}
		case 2:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "Выберите элемент для удаления:" << endl;
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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}

			cout << "Выберите элемент для редакттирования:" << endl;
			int index = InputInt(1, vegetables.size()) - 1;

			auto iter = vegetables.begin();
			while (index)
			{
				iter++;
				index--;
			}
			iter->input();

			break;
		}
		case 4:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "Список пуст" << endl;
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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			cout << "Введите строку или подстроку названия для поиска:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			vector<Vegetable> found;
			for (auto vegetable : vegetables)
			{
				if (vegetable.getName().find(search) != -1)
					found.push_back(vegetable);
			}

			if (found.empty())
			{
				cout << "Ничего не найдено" << endl;
			}
			else
			{
				int i = 1;
				for (auto vegetable : found)
				{
					cout << i++ << ". " << vegetable.getInfo() << endl;
				}
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			if (vegetables.empty())
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			vegetables.sort();

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			ofstream fout("l6_list.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "Список пуст" << endl;
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.getInfo() << endl;
				}
			}
			fout.close();
			break;
		}
		case 8:
		{
			isWork = false;
			break;
		}
		}
	}
}

void ArrayMenu()
{
	const int size = 20;
	array<Vegetable, size> vegetables;

	int count = 0;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Сортировка" << endl;
		cout << "7.Вывод данных в файл" << endl;
		cout << "8.Выход" << endl;

		switch (InputInt(1, 8))
		{
		case 1:
		{
			system("cls");
			if (count == size)
			{
				cout << "Больше нет места!" << endl;
				system("pause");
				break;
			}

			vegetables[count].input();
			count++;
			break;
		}
		case 2:
		{
			system("cls");
			if (count == 0)
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < count; ++i)
			{
				cout << i + 1 << ". " << vegetables[i].getInfo() << endl;
			}

			cout << "Выберите элемент для удаления:" << endl;
			int index = InputInt(1, count) - 1;

			for (int i = index; i < count - 1; ++i)
			{
				vegetables[i] = vegetables[i + 1];
			}
			count--;

			break;
		}
		case 3:
		{
			system("cls");
			if (count == 0)
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < count; ++i)
			{
				cout << i + 1 << ". " << vegetables[i].getInfo() << endl;
			}

			cout << "Выберите элемент для удаления:" << endl;
			int index = InputInt(1, count) - 1;
			vegetables[index].input();
			break;
		}
		case 4:
		{
			system("cls");
			if (count == 0)
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < count; ++i)
			{
				cout << i + 1 << ". " << vegetables[i].getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 5:
		{
			system("cls");
			if (count == 0)
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			cout << "Введите строку или подстроку названия для поиска:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			vector<Vegetable> found;
			for (int i = 0; i < count; ++i)
			{
				if (vegetables[i].getName().find(search) != -1)
					found.push_back(vegetables[i]);
			}

			if (found.empty())
			{
				cout << "Ничего не найдено" << endl;
			}
			else
			{
				int i = 1;
				for (auto vegetable : found)
				{
					cout << i++ << ". " << vegetable.getInfo() << endl;
				}
			}
			system("pause");
			break;
		}
		case 6:
		{
			system("cls");
			if (count == 0)
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			sort(vegetables.begin(), vegetables.begin() + count);

			for (int i = 0; i < count; ++i)
			{
				cout << i + 1 << ". " << vegetables[i].getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			ofstream fout("l6_array.txt", ios_base::trunc);
			if (!fout.is_open())
			{
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (count == 0)
			{
				fout << "Список пуст" << endl;
			}
			else
			{
				for (int i = 0; i < count; ++i)
				{
					fout << i + 1 << ". " << vegetables[i].getInfo() << endl;
				}
			}
			fout.close();
			break;
		}
		case 8:
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
		cout << "1.Vector" << endl;
		cout << "2.List" << endl;
		cout << "3.Array" << endl;
		cout << "4.Выход" << endl;

		switch (InputInt(1, 4))
		{
		case 1:
		{
			VectorMenu();
			break;
		}
		case 2:
		{
			ListMenu();
			break;
		}
		case 3:
		{
			ArrayMenu();
			break;
		}
		case 4:
		{
			isWork = false;
			break;
		}
		}
	}
}