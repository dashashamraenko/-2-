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
	cout << "��������������� �����������:" << endl;
	cout << "��������:" << name << endl;
	cout << "C����:" << amount << endl;
}

void SelfSupport::display() const
{
	cout << "���������������:" << endl;
	cout << "��������:" << name << endl;
	cout << "C����� ������: " << number << "%" << endl;
}

void BenefitSupport::display() const
{
	cout << "�������� �����������:" << endl;
	cout << "��������:" << name << endl;
	cout << "C����:" << amount << endl;
	cout << "C����� ������: " << number << "%" << endl;
	cout << "������:" << discount << "%" << endl;
}

float checkDouble(float a) {
	while (true) {
		cin >> a;
		if (cin.fail()) {
			cin.clear();
			cin.ignore((numeric_limits<streamsize>::max)(), '\n');
			cout << "������, ������� ��� ���" << endl;
			continue;
		}
		cin.ignore((numeric_limits<streamsize>::max)(), '\n');

		if (a <= 0) {
			cout << "������, ������� ��� ���" << endl;
			continue;
		}
		break;
	}
	return a;
}

