#pragma once
#include <windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <locale>
using namespace std;

void exit_function();
void MyHandler();

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
				cerr << "����������� ������ � ������ �����. ��������� ���������." << endl;
				exit(1);
			}
			cout << "������� ������ ����� �����!" << endl;
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

			if (this->filenameFrom == "_") throw runtime_error("�������� ����� �� ������ ���� ������");

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
						throw filenameTo[i];
				}
			}
			catch (char ch)
			{
				isCorrect = false;
				cout << ch << " - ������ ��������� � �������� �����" << endl;
			}

			if (this->filenameTo == "_") throw runtime_error("�������� ����� �� ������ ���� ������");

		} while (!isCorrect);

		cout << "������� ����� ����������� � ��������:" << endl;
		string val;
		getline(ws(cin), val);
		for (int i = 0; i < val.length(); ++i)
		{

			if (!(val[i] >= '0' && val[i] <= '9'))
				throw runtime_error("����� �� ����� ��������� ������ ������� ����� ����");
		}

		time = stoi(val);
	}
	string GetFilenameFrom()const { return filenameFrom; }
	string GetFilenameTo()const { return filenameTo; }
	double GetTime()const { return time; }

	void SetFilenameFrom(string name) { filenameFrom = name; }
	void SetFilenameTo(string name) { filenameTo = name; }
	void SetTime(double time) { this->time = time; }

	virtual void Show() = 0;
	virtual void Init() = 0;

	virtual string GetType() = 0;

	friend ostream& operator<<(ostream& out, const Convertation& obj);
	friend istream& operator>>(istream& in, Convertation& obj);
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

	string GetType()override { return "TEXT"; }

	friend ostream& operator<<(ostream& out, const TextConvertation& obj);
	friend istream& operator>>(istream& in, TextConvertation& obj);

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

	string GetType()override { return "BINARY"; }

	friend ostream& operator<<(ostream& out, const BinaryConvertation& obj);
	friend istream& operator>>(istream& in, BinaryConvertation& obj);
};

class FolderConvertation : public Convertation
{

protected:
	TextConvertation textConvertation; 
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

	string GetType()override { return "FOLDER"; }

	friend ostream& operator<<(ostream& out, const FolderConvertation& obj);
	friend istream& operator>>(istream& in, FolderConvertation& obj);

};

class ConvertationOfFiles
{
private:
	vector<Convertation*> convertations;

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

	friend ostream& operator<<(ostream& out,const ConvertationOfFiles& obj);
	friend istream& operator>>(istream& in, ConvertationOfFiles& obj);

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
		cout << "|";
		cin.setf(ios::right);
		cout << setw(15) << convertations[i]->GetFilenameFrom();
		cout << "|";
		cout << setw(15) << convertations[i]->GetFilenameTo();
		cout << "|";
		cout << setw(12) << convertations[i]->GetTime() << " ������";
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

			switch (InputInt(1, 3))
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

vector<ConvertationOfFiles> Load();
void Save(const vector<ConvertationOfFiles>& convertations);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	set_new_handler(MyHandler);

	cout << setprecision(2) << fixed;

	bool isWork = true;

	while (isWork)
	{
		system("cls");
		cout << "1.���������� ����������� � ����" << endl;
		cout << "2.�������� ����������� �� �����" << endl;
		cout << "3.�������������� ����������� � �����" << endl;
		cout << "4.�������� ����������� �� �����" << endl;
		cout << "5.����� ����������� � �����" << endl;
		cout << "6.�����" << endl;

		char ch;
		cin >> ch;
		system("cls");
		switch (ch)
		{
		case '1':
		{
			auto convertations = Load();
			ConvertationOfFiles c;
			c.Input();
			convertations.push_back(c);
			Save(convertations);
			break;
		}
		case '2':
		{
			auto convertations = Load();
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
			auto convertations = Load();
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
			Save(convertations);
			break;
		}
		case '4':
		{
			auto convertations = Load();
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
			Save(convertations);
			break;
		}
		case '5':
		{
			auto convertations = Load();
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
		case '6':
		{
			exit_function();
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

ostream& operator<<(ostream& out, const Convertation& obj)
{
	out << obj.time << endl;
	out << obj.filenameFrom << endl;
	out << obj.filenameTo;

	return out;
}

istream& operator>>(istream& in, Convertation& obj)
{
	in >> obj.time;
	getline(in, obj.filenameFrom);
	getline(in, obj.filenameFrom);
	getline(in, obj.filenameTo);

	return in;
}

ostream& operator<<(ostream& out, const TextConvertation& obj)
{
	out << (Convertation&)obj << endl;
	out << obj.codeFrom << endl;
	out << obj.codeTo;

	return out;
}

istream& operator>>(istream& in, TextConvertation& obj)
{
	in >> (Convertation&)obj;
	getline(in, obj.codeFrom);
	getline(in, obj.codeTo);

	return in;
}

ostream& operator<<(ostream& out, const BinaryConvertation& obj)
{
	out << (Convertation&)obj << endl;
	out << obj.isInverse? 1: 0;

	return out;
}

istream& operator>>(istream& in, BinaryConvertation& obj)
{
	in >> (Convertation&)obj;
	int temp;
	in >> temp;
	obj.isInverse = temp == 1;

	return in;
}

ostream& operator<<(ostream& out, const FolderConvertation& obj)
{
	out << (Convertation&)obj << endl;

	return out;
}

istream& operator>>(istream& in, FolderConvertation& obj)
{
	in >> (Convertation&)obj;

	return in;
}

ostream& operator<<(ostream& out, const ConvertationOfFiles& obj)
{
	out << obj.convertations.size() << endl;
	for (int i = 0; i < obj.convertations.size(); i++)
	{
		out << obj.convertations[i]->GetType() << endl;
		out << *obj.convertations[i] << endl;
	}

	return out;
}

istream& operator>>(istream& in, ConvertationOfFiles& obj)
{
	obj.convertations.clear();

	int size = 0;
	in >> size;
	for (int i = 0; i < size; i++)
	{
		Convertation* convertation = NULL;

		string type;
		in >> type;
		if (type == "TEXT")
			convertation = new TextConvertation;
		else if (type == "BINARY")
			convertation = new BinaryConvertation;
		else if (type == "FOLDER")
			convertation = new FolderConvertation;

		in >> *convertation;

		obj.convertations.push_back(convertation);
	}

	return in;
}

vector<ConvertationOfFiles> Load()
{
	vector<ConvertationOfFiles> convertations;

	ifstream fin;
	fin.open("l5.txt", ios_base::in);
	if(!fin.is_open())
		return convertations;

	int size = 0;
	fin >> size;

	try
	{

		for (int i = 0; i < size; i++)
		{
			if (!fin.good())
			{
				if (fin.eof())
					throw "EOF error";
				else if (fin.fail())
					throw "Incorrect data in file";
				else if (fin.bad())
					throw "Unknown error";
			}
			ConvertationOfFiles convertation;
			fin >> convertation;
			convertations.push_back(convertation);
		}
	}
	catch (const string& str)
	{
		system("cls");
		cout << str << endl;
		cout << fin.tellg() << "chars readed" << endl;
		fin.seekg(0, ios::end);
		system("pause");
	}

	fin.close();

	return convertations;
}

void Save(const vector<ConvertationOfFiles>& convertations)
{
    ofstream fout("l5.txt", ios_base::trunc);
	if (!fout.is_open())
		return;

	fout << convertations.size() << endl;

	for (int i = 0; i < convertations.size(); i++)
	{
		fout << convertations[i] << endl;
		if (fout.bad())
		{
			fout.seekp(ios::end);
			break;
		}
	}

	fout.close();
}
