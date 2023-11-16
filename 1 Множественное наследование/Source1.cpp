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
		cout << "1. �������� ��� �����������." << endl;
		cout << "2. �������� ���������������." << endl;
		cout << "3. �������� �������� �����������." << endl;
		cout << "4. ����������� ��� �������." << endl;
		cout << "5. �����." << endl;
		cout << "������� ��� �����:" << endl;
		while (true) {
			cin >> choice;
			if (cin.fail()) {
				cin.clear();
				cin.ignore((numeric_limits<streamsize>::max)(), '\n');
				cout << "������, ������� ��� ���" << endl;
				continue;
			}
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			if (cin.gcount() > 1) {
				cout << "������, ������� ��� ���" << endl;
				continue;
			}
			if (choice <= 0 || choice > 5) {
				cout << "������, ������� ��� ���" << endl;
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
			cout << "///������� ������� ��� �����������///" << endl;
			cout << "������������ ���������� ��������� � ������� - 10" << endl;
			cout << "��������: " << endl;
			cin.ignore();
			getline(cin, name);
			cout << "�����:" << endl;
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
			cout << "///������� ������� ���������������///" << endl;
			cout << "������������ ���������� ��������� � ������� - 10" << endl;
			cout << "��������:" << endl;
			cin.ignore();
			getline(cin, name);
			cout << "C����� ������:" << endl;
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
			cout << "///������� ������� �������� �����������///" << endl;
			cout << "������������ ���������� ��������� � ������� - 10" << endl;
			cout << "��������:" << endl;
			cin.ignore();
			getline(cin, name);
			cout << "�����:" << endl;
			amount = checkDouble(amount);
			cout << "C����� ������:" << endl;
			number = checkDouble(number);
			cout << "������:" << endl;
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
		cout << "�� ����� ��������� ��������� �����  ��������..." << endl;
		cout << "������ ����������� ������ ��� ����� �� ���������..." << endl;
		cout << "1. ����������� ������ ���������." << endl;
		cout << "2. �����." << endl;
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
