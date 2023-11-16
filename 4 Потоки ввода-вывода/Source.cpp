#pragma once
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <locale>
using namespace std;

void exit_function();
void MyHandler();

double InputDouble()
{
	while (true) // ���� ������������ �� ��� ���, ���� ������������ �� ����� ���������� ��������
	{
		cout << "Enter a double value: ";
		double a;
		cin >> a;

		if (cin.fail()) // ���� ���������� ���������� ��������� ���������,
		{
			cin.clear(); // �� ���������� cin � '�������' ����� ������
			cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
		}
		else // ���� �� ������, �� ���������� a
			return a;
	}
}

int InputInt()
{
	int result;

	bool isCorrect = cin.good();
	do {

		if (cin.fail() || cin.eof())
		{
			std::cin.clear(); // �� ���������� cin � '�������' ����� ������
			std::cin.ignore(32767, '\n'); // � ������� �������� ����������� ����� �� �������� ������
		}

		cin >> result;

		isCorrect = cin.good();

	}while(!isCorrect);

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

class Convertation
{
protected:
	string filenameFrom;
	string filenameTo;

	double time;

public:
	Convertation() {};
	Convertation(int time) :Convertation()
	{
		if (time < 0)
			throw logic_error("����� ����������� �� ����� ���� �������������"); //������������ ������ ������ ������������
	};

	void Input()
	{
		cout << "������� �������� ��������������� �����" << endl;
		bool isCorrect;
		do
		{
			getline(ws(cin), this->filenameFrom);
			isCorrect = true;

			try
			{
				for (int i = 0; i < filenameFrom.length(); i++)
				{
					if (filenameFrom[i] == '?' || filenameFrom[i] == '*' || filenameFrom[i] == '#')
						throw filenameFrom[i]; //�� ����������� ����� ������
				}
			}
			catch (char ch)
			{
				isCorrect = false;
				cout << ch << " - ������ ��������� � �������� �����" << endl;
			}

			if (this->filenameFrom == "_") throw runtime_error("�������� ����� �� ������ ���� ������");//����������� ����� ������

		} while (!isCorrect);

		cout << "������� �������� ����� ����������" << endl;
		do
		{
			getline(ws(cin), this->filenameTo);
			isCorrect = true;

			try
			{
				for (int i = 0; i < filenameTo.length(); i++)
				{
					if (filenameTo[i] == '?' || filenameTo[i] == '*' || filenameTo[i] == '#')
						throw filenameTo[i]; //�� ����������� ����� ������
				}
			}
			catch (char ch)
			{
				isCorrect = false;
				cout << ch << " - ������ ��������� � �������� �����" << endl;
			}

			if (this->filenameTo == "_") throw runtime_error("�������� ����� �� ������ ���� ������");//����������� ����� ������

		} while (!isCorrect);

		cout << "������� ����� ����������� � ��������:" << endl;
		string val;
		getline(ws(cin), val);
		for (int i = 0; i < val.length(); ++i)
		{

			if (!(val[i] >= '0' && val[i] <= '9'))
				throw runtime_error("����� �� ����� ��������� ������ ������� ����� ����");
		}

		time = stoi(val);//������� �� ������ � �����
	}
	string GetFilenameFrom()const { return filenameFrom; }
	string GetFilenameTo()const { return filenameTo; }
	double GetTime()const { return time; }

	void SetFilenameFrom(string name) { filenameFrom = name; }
	void SetFilenameTo(string name) { filenameTo = name; }
	void SetTime(double time) { this->time = time; }

	virtual void Show() = 0;
	virtual void Init() = 0;


};

class TextConvertation : public Convertation
{
private:

	string codeFrom;
	string codeTo;

public:
	TextConvertation() {}
	~TextConvertation() {}
	string GetCodeFrom()const { return codeFrom; }
	string GetCodeTo()const { return codeTo; }

	void SetCodeFrom(string code) { codeFrom = code; }
	void SetCodeTo(string code) { codeTo = code; }

	virtual void Show() {
		cout << "��������� �����������. �� " << filenameFrom << " � ���������� " << codeFrom << " � " << filenameTo << " � ���������� " << codeTo << endl;
	}
	virtual void Init()
	{
		cout << "������� ������:" << endl;
		Input();
		cout << "������� ��������� ���������� �����:" << endl;
		getline(ws(cin), this->codeFrom);
		cout << "������� ��������� ��������� �����:" << endl;
		getline(ws(cin), this->codeTo);
	}


};

class BinaryConvertation : public Convertation
{
protected:

	bool isInverse;

public:
	BinaryConvertation() :Convertation(), isInverse(true) {}
	~BinaryConvertation() {}

	void SetInverse(bool s) { isInverse = s; }
	bool GetInverse() { return isInverse; }

	virtual void Show() { cout << "�������� ����������� �� " << filenameFrom << " � " << filenameTo << (isInverse ? " (��������������� ����)" : " (����������������� ����)") << endl; }

	virtual void Init()
	{
		cout << "������� ������:" << endl;
		Input();
		cout << "���� ���� �������������? (1/0)" << endl;
		string temp;
		getline(ws(cin), temp);
		isInverse = temp.empty() || temp[0] != '0';
	}

};

class FolderConvertation : public Convertation
{

protected:
	TextConvertation textConvertation; //����������
	BinaryConvertation binConvertation;

public:

	virtual void Show() {
		cout << "����������� ����� � ����� �������:" << endl;
		cout << "����� ������������� �� " << filenameFrom << " � " << filenameTo << endl;
		cout << "��������� ����� �����������: " << time << " ���" << endl;
	}

	virtual void Init()
	{
		cout << "������� ������ � ����������� �����:\n";
		cout << "������� �������� ��������� �����" << endl;
		getline(ws(cin), this->filenameFrom);

		try
		{
			for (int i = 0; i < filenameFrom.length(); i++)
			{
				if (filenameFrom[i] == '?' || filenameFrom[i] == '*' || filenameFrom[i] == '#')
					throw filenameFrom[i];
			}
		}
		catch (char ch) {
			cout << ch << " - ������ ��������� � �������� �����" << endl;
		}
		if (this->filenameFrom == "_") throw runtime_error("�������� ����� �� ������ ���� ������");

		cout << "������� �������� ����� ����������" << endl;
		getline(ws(cin), this->filenameTo);

		try
		{
			for (int i = 0; i < filenameTo.length(); i++)
			{
				if (filenameTo[i] == '?' || filenameTo[i] == '*' || filenameTo[i] == '#')
					throw filenameTo[i];
			}
		}
		catch (char ch) {
			cout << ch << " - ������ ��������� � �������� �����" << endl;
		}
		if (this->filenameTo == "_") throw runtime_error("�������� ����� �� ������ ���� ������");

		textConvertation.Init();
		binConvertation.Init();

		time = textConvertation.GetTime() + binConvertation.GetTime() + 1;
	}

};

class ConvertationOfFiles
{
private:
	vector<Convertation*> convertations;//aggregation

public:
	ConvertationOfFiles() {};

	void Show();
	void Input();

	int getCountOfConvertations()const { return convertations.size(); }
	bool isInclude(const string& filename)
	{
		for (auto convertation : convertations)
		{
			if (convertation->GetFilenameFrom() == filename ||
				convertation->GetFilenameTo() == filename)
				return true;
		}

		return false;
	}


};

class MyException
{
public:
	MyException()
	{
		cout << "!!!�����������!!!" << endl;
		throw* this; //����� ������ �� ������������
	};
	~MyException()
	{
		cout << "!!!����������!!!" << endl;
	};
};

void ConvertationOfFiles::Show()
{
	cout << "����������� ������:" << endl;
	if (convertations.empty())
	{
		cout << "�������������� ������ ���" << endl;
		return;
	}

	cout << "-----------------------------------------------------------" << endl;
	cout << "|  #  | �������� ���� | �������� ���� | ����� ����������� |" << endl;
	cout << "-----------------------------------------------------------" << endl;

	for (int i = 0; i < convertations.size(); i++)
	{
		cout << "|";
		cin.setf(ios::internal);
		cout << setw(5) << i + 1;
		cin.unsetf(ios::internal);
		cin.setf(ios::right);
		cout << "|";
		cout << setw(15) << convertations[i]->GetFilenameFrom();
		cout << "|";
		cout << setw(15) << convertations[i]->GetFilenameTo();
		cout << "|";
		cout << setw(12) << setfill('0') << convertations[i]->GetTime() << " ������";
		cout << setfill(' ');
		cout << "|";
		cout << endl;
		cin.unsetf(ios::right);

		cout << "-----------------------------------------------------------" << endl;
	}
}

void ConvertationOfFiles::Input()
{
	convertations.clear();

	bool exit = false;
	while (!exit)
	{
		try
		{
			Convertation* convertation = NULL;
			cout << "�������� ��� �����������:\n1.���������\n2.��������\n3.����������� �����" << endl;

			switch (InputInt(1,3))
			{
			case 1: convertation = new TextConvertation(); break;
			case 2: convertation = new BinaryConvertation(); break;
			case 3: convertation = new FolderConvertation(); break;
			}

			convertation->Init();

			convertations.push_back(convertation);//���������� ����� ����������� � ������
		}
		catch (runtime_error ex)
		{
			cout << ex.what() << endl;
		}
		catch (...)
		{
			cout << "�������������� ������" << endl;
		}
		cout << "������ ��������� ���� �����������? (1/0)"; cin >> exit;
	}
	cout << "������!" << endl;
}

void MyHandler()
{
	cout << "��� ����������: ";
	throw bad_alloc();
}

void exit_function() {
	cout << "���������� �������� ����� ����������� ���������";
	exit(-1);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	set_new_handler(MyHandler);

	cout << setprecision(2) << fixed;

	bool isWork = true;
	
	vector<ConvertationOfFiles> convertations;

	while (isWork)
	{
		system("cls");
		cout << "1.��������" << endl;
		cout << "2.���������" << endl;
		cout << "3.�������������" << endl;
		cout << "4.�������" << endl;
		cout << "5.����������" << endl;
		cout << "6.�����" << endl;
		cout << "7.�����" << endl;

		char ch;
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
		{
			ConvertationOfFiles c;
			c.Input();
			convertations.push_back(c);
			break;
		}
		case '2':
		{
			for (int i = 0; i < convertations.size(); i++)
			{
				cout << i + 1 << ".";
				convertations[i].Show();
				cout << endl;
			}
			system("pause");
			break;
		}
		case '3':
		{
			if (convertations.empty())
			{
				cout << "������ ����������� ����" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < convertations.size(); i++)
			{
				cout << i + 1 << ".";
				convertations[i].Show();
				cout << endl;
			}
			cout << "������� ����� ����������� ��� ��������������: " << endl;
			int index = InputInt(1, convertations.size()) - 1;
			convertations[index].Input();
			break;
		}
		case '4':
		{
			if (convertations.empty())
			{
				cout << "������ ����������� ����" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < convertations.size(); i++)
			{
				cout << i + 1 << ".";
				convertations[i].Show();
				cout << endl;
			}
			cout << "������� ����� ����������� ��� ��������: " << endl;
			int index = InputInt(1, convertations.size()) - 1;
			convertations.erase(convertations.begin() + index);
			break;
		}
		case '5':
		{
			if (convertations.empty())
			{
				cout << "������ ����������� ����" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < convertations.size(); i++)
			{
				for (int j = i; j < convertations.size(); j++)
				{
					if (convertations[i].getCountOfConvertations() > convertations[j].getCountOfConvertations())
						swap(convertations[i], convertations[j]);
				}
			}

			for (int i = 0; i < convertations.size(); i++)
			{
				cout << i + 1 << ".";
				convertations[i].Show();
				cout << endl;
			}
			system("pause");
			break;
		}
		case '6':
		{
			if (convertations.empty())
			{
				cout << "������ ����������� ����" << endl;
				system("pause");
				break;
			}

			cout << "������� �������� ����� ��� ����� ��� ������:" << endl;
			string search;
			while (search.empty())
				getline(cin, search);

			vector<ConvertationOfFiles> found;
			for (ConvertationOfFiles convertation : convertations)
			{
				if (convertation.isInclude(search))
					found.push_back(convertation);
			}

			system("cls");
			if (found.empty())
			{
				cout << "������ �� �������" << endl;
			}
			else
			{
				for (int i = 0; i < found.size(); i++)
				{
					cout << i + 1 << ".";
					found[i].Show();
					cout << endl;
				}
			}
			system("pause");
			break;
		}
		case '7':
		{
			isWork = false;
			break;
		}
		default:
		{
			cout << "������������ ����" << endl;
			system("pause");
			break;
		}
		}
	}

	return 0;
}