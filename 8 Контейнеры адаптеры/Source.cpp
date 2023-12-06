#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <stack>
#include <queue>
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

void StackMenu()
{
	stack<Vegetable> vegetables;

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
			vegetables.push(vegetable);
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

			vegetables.pop();
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

			vegetables.top().input();
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
			stack<Vegetable> temp;
			while (!vegetables.empty())
			{
				cout << i++ << ". " << vegetables.top().getInfo() << endl;
				temp.push(vegetables.top());
				vegetables.pop();
			}
			while (!temp.empty())
			{
				vegetables.push(temp.top());
				temp.pop();
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

			int i = 1;
			stack<Vegetable> temp;
			bool isFound = false;
			while (!vegetables.empty())
			{
				if (vegetables.top().getName().find(search) != -1)
				{
					cout << i++ << ". " << vegetables.top().getInfo() << endl;
					isFound = true;
				}
				temp.push(vegetables.top());
				vegetables.pop();
			}
			while (!temp.empty())
			{
				vegetables.push(temp.top());
				temp.pop();
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
			if (vegetables.empty())
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			priority_queue<Vegetable> tempQ;
			while (!vegetables.empty())
			{
				tempQ.push(vegetables.top());
				vegetables.pop();
			}
			while (!tempQ.empty())
			{
				vegetables.push(tempQ.top());
				tempQ.pop();
			}

			int i = 1;
			stack<Vegetable> temp;
			while (!vegetables.empty())
			{
				cout << i++ << ". " << vegetables.top().getInfo() << endl;
				temp.push(vegetables.top());
				vegetables.pop();
			}
			while (!temp.empty())
			{
				vegetables.push(temp.top());
				temp.pop();
			}
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			ofstream fout("l7_stack.txt", ios_base::trunc);
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
				stack<Vegetable> temp;
				while (!vegetables.empty())
				{
					fout << i++ << ". " << vegetables.top().getInfo() << endl;
					temp.push(vegetables.top());
					vegetables.pop();
				}
				while (!temp.empty())
				{
					vegetables.push(temp.top());
					temp.pop();
				}
				cout << "Запись добавлена в файл 'l6_stack.txt'" << endl;
				system("pause");
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

void QueueMenu()
{
	queue<Vegetable> vegetables;

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
			vegetables.push(vegetable);
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

			vegetables.pop();
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

			vegetables.front().input();

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

			for (int i=0; i<vegetables.size(); i++)
			{
				cout << i + 1 << ". " << vegetables.front().getInfo() << endl;
				vegetables.push(vegetables.front());
				vegetables.pop();
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
			for (int i = 0; i < vegetables.size(); i++)
			{
				if (vegetables.front().getName().find(search) != -1)
					found.push_back(vegetables.front());
				vegetables.push(vegetables.front());
				vegetables.pop();
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

			priority_queue<Vegetable> tempQ;
			while (!vegetables.empty())
			{
				tempQ.push(vegetables.front());
				vegetables.pop();
			}
			while (!tempQ.empty())
			{
				vegetables.push(tempQ.top());
				tempQ.pop();
			}

			for (int i = 0; i < vegetables.size(); i++)
			{
				cout << i + 1 << ". " << vegetables.front().getInfo() << endl;
				vegetables.push(vegetables.front());
				vegetables.pop();
			}
			system("pause");
			break;
		}
		case 7:
		{
			system("cls");
			ofstream fout("l6_queue.txt", ios_base::trunc);
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
				for (int i = 0; i < vegetables.size(); i++)
				{
					fout << i + 1 << ". " << vegetables.front().getInfo() << endl;
					vegetables.push(vegetables.front());
					vegetables.pop();
				}
				cout << "Запись добавлена в файл 'l6_queue.txt'" << endl;
				system("pause");
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

void PriorityQueueMenu()
{
	priority_queue<Vegetable> vegetables;

	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "1.Добавление" << endl;
		cout << "2.Удаление" << endl;
		cout << "3.Вывод на экран" << endl;
		cout << "4.Поиск" << endl;
		cout << "5.Вывод данных в файл" << endl;
		cout << "6.Выход" << endl;

		switch (InputInt(1, 6))
		{
		case 1:
		{
			system("cls");
			Vegetable vegetable;
			vegetable.input();
			vegetables.push(vegetable);
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

			vegetables.pop();
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

			for (int i = 0; i < vegetables.size(); i++)
			{
				cout << i + 1 << ". " << vegetables.top().getInfo() << endl;
				vegetables.push(vegetables.top());
				vegetables.pop();
			}
			system("pause");
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

			cout << "Введите строку или подстроку названия для поиска:" << endl;
			string search;
			do
			{
				getline(cin, search);
			} while (search.empty());

			vector<Vegetable> found;
			for (int i = 0; i < vegetables.size(); i++)
			{
				if (vegetables.top().getName().find(search) != -1)
					found.push_back(vegetables.top());
				vegetables.push(vegetables.top());
				vegetables.pop();
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
		case 5:
		{
			system("cls");
			ofstream fout("l6_priority_queue.txt", ios_base::trunc);
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
				for (int i = 0; i < vegetables.size(); i++)
				{
					fout << i + 1 << ". " << vegetables.top().getInfo() << endl;
					vegetables.push(vegetables.top());
					vegetables.pop();
				}
				cout << "Запись добавлена в файл 'l6_priority_queue.txt'" << endl;
				system("pause");
			}
			fout.close();
			break;
		}
		case 6:
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
		cout << "1.Работа с контейнером Stack" << endl;
		cout << "2.Работа с контейнером Queue" << endl;
		cout << "3.Работа с контейнером PriorityQueue" << endl;
		cout << "4.Выход" << endl;

		switch (InputInt(1, 4))
		{
		case 1:
		{
			StackMenu();
			break;
		}
		case 2:
		{
			QueueMenu();
			break;
		}
		case 3:
		{
			PriorityQueueMenu();
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