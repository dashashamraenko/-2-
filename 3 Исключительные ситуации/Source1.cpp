#pragma once
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <locale>
using namespace std;

void exit_function();
void MyHandler();

class Convertation
{
protected:
	string filenameFrom;
	string filenameTo;
	int time;

public:
	Convertation(){};
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
	int GetTime()const { return time; }

	void SetFilenameFrom(string name) { filenameFrom = name; }
	void SetFilenameTo(string name) { filenameTo = name; }
	void SetTime(int time) { this->time = time; }

	virtual void Show() = 0;
	virtual void Init() = 0;

};

class TextConvertation : public Convertation
{
private:

	string codeFrom;
	string codeTo;

public:
	TextConvertation() :Convertation() {};
	~TextConvertation() {};

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
	BinaryConvertation() :Convertation(){}
	~BinaryConvertation() {}

	void SetInverse(bool s) { isInverse = s; }
	bool GetInverse() { return isInverse; }
	
	virtual void Init()
	{
		cout << "������� ������:" << endl;
		Input();
		cout << "���� ���� �������������? (1/0)" << endl;
		string temp;
		getline(ws(cin), temp);
		isInverse = temp.empty() || temp[0] != '0';
		
	}

	virtual void Show() { cout << "�������� ����������� �� " << filenameFrom << " � " << filenameTo << (isInverse ? " (��������������� ����)" : " (����������������� ����)") << endl;
	
	}

};

class FolderConvertation : public Convertation
{

protected:
	TextConvertation textConvertation; //����������
	TextConvertation binConvertation;

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
	~ConvertationOfFiles()
	{
		for (int i = 0; i < convertations.size(); i++)
		{
			delete convertations[i];
		}
	};

	void Show();
	void Input();


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
	for (auto i : this->convertations)
	{
		i->Show();
		cout << endl;
	}
}

void ConvertationOfFiles::Input()
{
	bool exit = false;
	while (!exit)
	{
		try
		{
			Convertation* convertation = NULL;
			cout << "�������� ��� �����������:\n1.���������\n2.��������\n3.����������� �����" << endl;

			int choise;
			cin >> choise;
			
			switch (choise)
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

	char* ptr;

	try {
		ptr = new char[~size_t(0) / 2];// ������������ ������ � ������� � ���������� new
		delete[] ptr;
	}
	catch (bad_alloc& e)
	{
		cout << e.what() << endl;
	}

	try
	{
		MyException IOEex;
	}
	catch (MyException)
	{
		cout << "������ ������������!" << endl;
	}



	bool isWork = true;
	ConvertationOfFiles build;
	while (isWork)
	{
		
		cout << "1.����" << endl;
		cout << "2.�����������" << endl;
		cout << "3.�����" << endl;

		char ch;
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
		{
			build.Input();
			break;
		}
		case '2':
		{
			build.Show();
			system("pause");
			break;
		}
		case '3':
		{
			exit_function();
			system("pause");
			break;
		}
		default:
		{
			cout << "������������ �����" << endl;
			system("pause");
			break;
		}
		}
	}

	return 0;
}