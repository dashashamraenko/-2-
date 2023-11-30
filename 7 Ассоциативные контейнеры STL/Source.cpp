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
				cerr << "Критическая ошибка в потоке ввода. Программа завершена." << endl;
				exit(1);
			}
			cout << "Вводите только целые числа!" << endl;

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
		cout << "Введите название:" << endl;
		do
		{
			getline(cin, name);
		} while (name.empty());

		cout << "Введите количество:" << endl;
		count = InputInt(0, 1000000);
	}
	string getInfo()const
	{
		string info = name + " - " + to_string(count) + " шт.";

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

void MapMenu()//карта - ключ-значение уникальные
{
	map<string ,Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "1.Работа с контейнером map" << endl;
		cout << "==============================" << endl;
		
		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Вывод данных в файл" << endl;
		cout << "7.Выход" << endl;

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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)//автоматически объявляем переменную и определяем тип
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
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
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "Выберите элемент для редактирования:" << endl;
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
				cout << "Список пуст" << endl;
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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			cout << "Введите строку названия для поиска:" << endl;
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
				cout << "Ничего не найдено" << endl;
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
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "Список пуст" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.second.getInfo() << endl;
				}
				cout << "Запись добавлена в файл 'l7_map.txt'" << endl;
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

void MultimapMenu()//карта - ключ-значение есть повторения ключей
{
	multimap<string, Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "2.Работа с контейнером multimap" << endl;
		cout << "============================================" << endl;

		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Вывод данных в файл" << endl;
		cout << "7.Выход" << endl;

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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)//автоматически объявляем переменную и определяем тип
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
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
			for (auto vegetable : vegetables)//автоматически объявляем переменную и определяем тип
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "Выберите элемент для редактирования:" << endl;
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
				cout << "Список пуст" << endl;
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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			cout << "Введите строку названия для поиска:" << endl;
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
				cout << "Ничего не найдено" << endl;
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
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "Список пуст" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.second.getInfo() << endl;
				}
				cout << "Запись добавлена в файл 'l7_multimap.txt'" << endl;
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

void UnorderedMapMenu()//карта с уник ключами неупорядоч
{
	unordered_map<string, Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "3.Работа с контейнером unordered_map" << endl;
		cout << "============================================" << endl;
		
		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Вывод данных в файл" << endl;
		cout << "7.Выход" << endl;

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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
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
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "Выберите элемент для редактирования:" << endl;
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
				cout << "Список пуст" << endl;
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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			cout << "Введите строку названия для поиска:" << endl;
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
				cout << "Ничего не найдено" << endl;
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
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "Список пуст" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.second.getInfo() << endl;
				}
				cout << "Запись добавлена в файл 'l7_unordered_map.txt'" << endl;
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

void UnorderedMultimapMenu()//карта повтор ключей неупорядоч(хешированная)
{
	unordered_multimap<string, Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "4.Работа с контейнером unordered_multimap" << endl;
		cout << "============================================" << endl;

		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Вывод данных в файл" << endl;
		cout << "7.Выход" << endl;

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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			int i = 1;
			for (auto vegetable : vegetables)
			{
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
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
				cout << i++ << ". " << vegetable.second.getInfo() << endl;
			}

			cout << "Выберите элемент для редактирования:" << endl;
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
				cout << "Список пуст" << endl;
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
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			cout << "Введите строку названия для поиска:" << endl;
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
				cout << "Ничего не найдено" << endl;
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
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "Список пуст" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.second.getInfo() << endl;
				}
				cout << "Запись добавлена в файл 'l7_unordered_multimap.txt'" << endl;
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

void SetMenu()//набор содержит только ключи явл значениями
{
	set<Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "5.Работа с контейнером set" << endl;
		cout << "============================================" << endl;

		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Вывод данных в файл" << endl;
		cout << "7.Выход" << endl;

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

			cout << "Выберите элемент для редактирования:" << endl;
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

			cout << "Введите строку названия для поиска:" << endl;
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
				cout << "Ничего не найдено" << endl;
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
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "Список пуст" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.getInfo() << endl;
				}
				cout << "Запись добавлена в файл 'l7_set.txt'" << endl;
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

void MultisetMenu()//допускает совпадение значений
{
	multiset<Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "6.Работа с контейнером multiset" << endl;
		cout << "============================================" << endl;

		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Вывод данных в файл" << endl;
		cout << "7.Выход" << endl;

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

			cout << "Выберите элемент для редактирования:" << endl;
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

			cout << "Введите строку названия для поиска:" << endl;
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
				cout << "Ничего не найдено" << endl;
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
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "Список пуст" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.getInfo() << endl;
				}
				cout << "Запись добавлена в файл 'l7_multiset.txt'" << endl;
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
		cout << "7.Работа с контейнером unordered_set" << endl;
		cout << "============================================" << endl;

		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Вывод данных в файл" << endl;
		cout << "7.Выход" << endl;

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

			cout << "Выберите элемент для редактирования:" << endl;
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

			cout << "Введите строку названия для поиска:" << endl;
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
				cout << "Ничего не найдено" << endl;
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
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "Список пуст" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.getInfo() << endl;
				}
				cout << "Запись добавлена в файл 'l7_unordered_set.txt'" << endl;
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
		cout << "8.Работа с контейнером unordered_multiset" << endl;
		cout << "============================================" << endl;

		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Редактирование" << endl;
		cout << "4.Вывод на экран" << endl;
		cout << "5.Поиск" << endl;
		cout << "6.Вывод данных в файл" << endl;
		cout << "7.Выход" << endl;

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

			cout << "Выберите элемент для редактирования:" << endl;
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

			cout << "Введите строку названия для поиска:" << endl;
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
				cout << "Ничего не найдено" << endl;
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
				cout << "Ошибка открытия файла!" << endl;
				system("pause");
				break;
			}

			if (vegetables.empty())
			{
				fout << "Список пуст" << endl;
				system("pause");
			}
			else
			{
				int i = 1;
				for (auto vegetable : vegetables)
				{
					fout << i++ << ". " << vegetable.getInfo() << endl;
				}
				cout << "Запись добавлена в файл 'l7_unordered_multiset.txt'" << endl;
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
		cout << "1.Работа с контейнером map" << endl;
		cout << "2.Работа с контейнером multimap" << endl;
		cout << "3.Работа с контейнером unordered_map" << endl;
		cout << "4.Работа с контейнером unordered_multimap" << endl;
		cout << "5.Работа с контейнером set" << endl;
		cout << "6.Работа с контейнером multiset" << endl;
		cout << "7.Работа с контейнером unordered_set" << endl;
		cout << "8.Работа с контейнером unordered_multiset" << endl;
		cout << "9.Выход" << endl;

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