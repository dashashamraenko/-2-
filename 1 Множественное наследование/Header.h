#pragma once
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

float checkDouble(float a);

class BudgetItem
{
protected:
    string name;
public:
    BudgetItem() {}
    BudgetItem(const string name) : name(name) {}

    string getName();
    void setName(string name);
    BudgetItem(const BudgetItem& obj) {
        name = obj.name;
    }
    virtual void display() const = 0;
    ~BudgetItem()
    {
        cout << "Сработал деструктор класса BudgetItem" << endl;
    }
};

class GovernmentSupport : public virtual BudgetItem {
protected:
    float amount = 0;
public:
    GovernmentSupport() {}
    GovernmentSupport(const string name, float amount) : BudgetItem(name)
    {
        this->amount = amount;
    }
    ~GovernmentSupport()
    {
        cout << "Сработал деструктор класса GovernmentSupport" << endl;
    }
    void display() const override;
    GovernmentSupport(const GovernmentSupport& obj) {
        amount = obj.amount;
        name = obj.name;
    }


};

class SelfSupport : public virtual BudgetItem {
protected:
    float number = 0;
public:
    SelfSupport() {}
    SelfSupport(const string name, float number) : BudgetItem(name)
    {
        this->number = number;
    }
    ~SelfSupport()
    {
        cout << "Сработал деструктор класса SelfSupport" << endl;
    }
    void display() const override;
    SelfSupport(const SelfSupport& obj) {
        number = obj.number;
        name = obj.name;
    }
};

class BenefitSupport : public GovernmentSupport, public SelfSupport {
protected:
    float discount = 0;
public:
    BenefitSupport(const string name, float amount, float number, float discount) : BudgetItem(name), GovernmentSupport(name, amount), SelfSupport(name, number)
    {
        this->discount = discount;
    }
    ~BenefitSupport()
    {
        cout << "Сработал деструктор класса BenefitSupport" << endl;
    }
    void display() const override;
    BenefitSupport(const BenefitSupport& obj) {
        discount = obj.discount;
        name = obj.name;
    }
};








