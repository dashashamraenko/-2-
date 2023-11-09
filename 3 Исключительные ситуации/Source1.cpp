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
			throw logic_error("Время конвертации не может быть отрицательным"); //Пробрасывает ошибку внутри конструктора
	};

	void Input()
	{
		cout << "Введите название конвертируемого файла" << endl;
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
						throw filenameFrom[i]; //Не прерывающая метод ошибка
				}
			}
			catch (char ch)
			{
				isCorrect = false;
				cout << ch << " - нельзя указывать в названии файла" << endl;
			}

			if (this->filenameFrom == "_") throw runtime_error("Название файла не должно быть пустым");//Прерывающая метод ошибка

		} while (!isCorrect);

		cout << "Введите название файла результата" << endl;
		do
		{
			getline(ws(cin), this->filenameTo);
			isCorrect = true;

			try
			{
				for (int i = 0; i < filenameTo.length(); i++)
				{
					if (filenameTo[i] == '?' || filenameTo[i] == '*' || filenameTo[i] == '#')
						throw filenameTo[i]; //Не прерывающая метод ошибка
				}
			}
			catch (char ch)
			{
				isCorrect = false;
				cout << ch << " - нельзя указывать в названии файла" << endl;
			}

			if (this->filenameTo == "_") throw runtime_error("Название файла не должно быть пустым");//Прерывающая метод ошибка

		} while (!isCorrect);

		cout << "Введите время конвертации в секундах:" << endl;
		string val;
		getline(ws(cin), val);
		for (int i = 0; i < val.length(); ++i)
		{

			if (!(val[i] >= '0' && val[i] <= '9'))
				throw runtime_error("Число не может содержать другие символы кроме цифр");
		}

		time = stoi(val);//перевод из строки в число
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
		cout << "Текстовая конвертация. Из " << filenameFrom << " с кодировкой " << codeFrom << " в " << filenameTo << " с кодировкой " << codeTo << endl;
			
	}
	virtual void Init()
	{
		cout << "Введите данные:" << endl;
		Input();
		cout << "Введите кодировку начального файла:" << endl;
		getline(ws(cin), this->codeFrom);
		cout << "Введите кодировку выходного файла:" << endl;
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
		cout << "Введите данные:" << endl;
		Input();
		cout << "Биты были инвертированы? (1/0)" << endl;
		string temp;
		getline(ws(cin), temp);
		isInverse = temp.empty() || temp[0] != '0';
		
	}

	virtual void Show() { cout << "Бинарная конвертация Из " << filenameFrom << " в " << filenameTo << (isInverse ? " (Инвертированные биты)" : " (Неинвертированные биты)") << endl;
	
	}

};

class FolderConvertation : public Convertation
{

protected:
	TextConvertation textConvertation; //композиция
	TextConvertation binConvertation;

public:

	virtual void Show() {
		cout << "Конвертация папки с двумя файлами:" << endl;
		cout << "Папка переименована из " << filenameFrom << " в " << filenameTo << endl;
		cout << "Суммарное время конвертации: " << time << " сек" << endl;
	}

	virtual void Init()
	{
		cout << "Введите данные о конвертации папки:\n";
		cout << "Введите название начальной папки" << endl;
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
			cout << ch << " - нельзя указывать в названии папки" << endl;
		}
		if (this->filenameFrom == "_") throw runtime_error("Название папки не должно быть пустым");

		cout << "Введите название папки результата" << endl;
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
			cout << ch << " - нельзя указывать в названии папки" << endl;
		}
		if (this->filenameTo == "_") throw runtime_error("Название папки не должно быть пустым");

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
		cout << "!!!Конструктор!!!" << endl;
		throw* this; //вызов ошибки из конструктора
	};
	~MyException()
	{
		cout << "!!!Деструктор!!!" << endl;
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
			cout << "Выберите тип конвертации:\n1.Текстовая\n2.Бинарная\n3.Конвертация папки" << endl;

			int choise;
			cin >> choise;
			
			switch (choise)
			{
				case 1: convertation = new TextConvertation(); break;
				case 2: convertation = new BinaryConvertation(); break;
				case 3: convertation = new FolderConvertation(); break;
					
			}
			

			convertation->Init();

			convertations.push_back(convertation);//добавление новой конвертации в список
		}
		catch (runtime_error ex)
		{
			cout << ex.what() << endl;
		}
		catch (...)
		{
			cout << "Непредвиденная ошибка" << endl;
		}
		cout << "Хотите закончить ввод конвертаций? (1/0)"; cin >> exit;
	}
	cout << "Готово!" << endl;
}

void MyHandler()
{
	cout << "Мой обработчик: ";
	throw bad_alloc();
}

void exit_function() {
	cout << "Выполнение действий перед завершением программы";
	exit(-1);
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	set_new_handler(MyHandler);

	char* ptr;

	try {
		ptr = new char[~size_t(0) / 2];// демонстрация работы с ошибкой и оператором new
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
		cout << "Ошибка конструктора!" << endl;
	}



	bool isWork = true;
	ConvertationOfFiles build;
	while (isWork)
	{
		
		cout << "1.Ввод" << endl;
		cout << "2.Распечатать" << endl;
		cout << "3.Выход" << endl;

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
			cout << "Некорректный вывод" << endl;
			system("pause");
			break;
		}
		}
	}

	return 0;
}