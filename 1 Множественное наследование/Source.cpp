#include "Header.h"

string BudgetItem::getName()
{
	return name;
}

void BudgetItem::setName(string name)
{
	this->name = name;
}

void GovernmentSupport::display() const
{
	cout << "Государственная обеспечение:" << endl;
	cout << "Источник:" << name << endl;
	cout << "Cумма:" << amount << endl;
}

void SelfSupport::display() const
{
	cout << "Самообеспечение:" << endl;
	cout << "Источник:" << name << endl;
	cout << "Cтавка налога: " << number << "%" << endl;
}

void BenefitSupport::display() const
{
	cout << "Льготное обеспечение:" << endl;
	cout << "Источник:" << name << endl;
	cout << "Cумма:" << amount << endl;
	cout << "Cтавка налога: " << number << "%" << endl;
	cout << "Скидка:" << discount << "%" << endl;
}

float checkDouble(float a) {
	while (true) {
		cin >> a;
		if (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "Ошибка, введите ещё раз" << endl;
			continue;
		}
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');

		if (a <= 0) {
			cout << "Ошибка, введите ещё раз" << endl;
			continue;
		}
		break;
	}
	return a;
}

