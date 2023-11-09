#include "Header.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	const int max = 4;
	int choice, budget_item = 0;
	BudgetItem* items[max];
	do
	{
		cout << "1. Добавить гос обеспечение." << endl;
		cout << "2. Добавить самообеспечение." << endl;
		cout << "3. Добавить льготное обеспечение." << endl;
		cout << "4. Просмотреть все объекта." << endl;
		cout << "5. Выход." << endl;
		cout << "Введите Ваш выбор:" << endl;
		while (true) {
			cin >> choice;
			if (cin.fail()) {
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				cout << "Ошибка, введите ещё раз" << endl;
				continue;
			}
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			if (cin.gcount() > 1) {
				cout << "Ошибка, введите ещё раз" << endl;
				continue;
			}
			if (choice <= 0 || choice > 5) {
				cout << "Ошибка, введите ещё раз" << endl;
				continue;
			}
			break;
		}
		switch (choice)
		{
		case 1:
		{
			system("cls");
			string name;
			float amount = 0;
			cout << "///Введите элемент гос обеспечение///" << endl;
			cout << "Максимальное количество элементов в системе - 10" << endl;
			cout << "Источник: " << endl;
			cin.ignore();
			getline(cin, name);
			cout << "Сумма:" << endl;
			amount = checkDouble(amount);
			items[budget_item] = new GovernmentSupport(name, amount);
			budget_item++;
			break;
		}
		case 2:
		{
			system("cls");
			string name;
			float number = 0;
			cout << "///Введите элемент самообеспечение///" << endl;
			cout << "Максимальное количество элементов в системе - 10" << endl;
			cout << "Источник:" << endl;
			cin.ignore();
			getline(cin, name);
			cout << "Cтавка налога:" << endl;
			number = checkDouble(number);
			items[budget_item] = new SelfSupport(name, number);
			budget_item++;
			break;
		}
		case 3:
		{
			system("cls");
			string name;
			float discount = 0;
			float number = 0, amount = 0;
			cout << "///Введите элемент льготное обеспечение///" << endl;
			cout << "Максимальное количество элементов в системе - 10" << endl;
			cout << "Источник:" << endl;
			cin.ignore();
			getline(cin, name);
			cout << "Сумма:" << endl;
			amount = checkDouble(amount);
			cout << "Cтавка налога:" << endl;
			number = checkDouble(number);
			cout << "Скидка:" << endl;
			discount = checkDouble(discount);
			items[budget_item] = new BenefitSupport(name, amount, number, discount);
			budget_item++;
			break;
		}
		case 4:
		{
			system("cls");
			for (int i = 0; i < budget_item; i++)
			{
				items[i]->display();
				cout << endl;
			}
			break;
		}
		case 5:
		{
			exit(0);
		}
		}
	} while (choice != 0 && budget_item != max);
	if (budget_item == max)
	{
		int choice2;
		cout << "Вы ввели предельно доступное число  элеметов..." << endl;
		cout << "Можете просмотреть список или выйти из программы..." << endl;
		cout << "1. Просмотреть список элементов." << endl;
		cout << "2. Выход." << endl;
		cin >> choice2;
		switch (choice2)
		{
		case 1:
		{
			system("cls");
			for (int i = 0; i < budget_item; i++)
			{
				items[i]->display();
				cout << endl;
			}
			exit(0);
		}
		case 2:
		{
			for (int i = 0; i < budget_item; i++)
			{
				delete items[i];
			}
			exit(0);
		}
		}
	}
	for (int i = 0; i < budget_item; i++)
	{
		delete items[i];
	}
	return 0;
}
