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
	while (true) // цикл продолжается до тех пор, пока пользователь не введёт корректное значение
	{
		cout << "Enter a double value: ";
		double a;
		cin >> a;

		if (cin.fail()) // если предыдущее извлечение оказалось неудачным,
		{
			cin.clear(); // то возвращаем cin в 'обычный' режим работы
			cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
		}
		else // если всё хорошо, то возвращаем a
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
			std::cin.clear(); // то возвращаем cin в 'обычный' режим работы
			std::cin.ignore(32767, '\n'); // и удаляем значения предыдущего ввода из входного буфера
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
	BinaryConvertation() :Convertation(), isInverse(true) {}
	~BinaryConvertation() {}

	void SetInverse(bool s) { isInverse = s; }
	bool GetInverse() { return isInverse; }

	virtual void Show() { cout << "Бинарная конвертация Из " << filenameFrom << " в " << filenameTo << (isInverse ? " (Инвертированные биты)" : " (Неинвертированные биты)") << endl; }

	virtual void Init()
	{
		cout << "Введите данные:" << endl;
		Input();
		cout << "Биты были инвертированы? (1/0)" << endl;
		string temp;
		getline(ws(cin), temp);
		isInverse = temp.empty() || temp[0] != '0';
	}

};

class FolderConvertation : public Convertation
{

protected:
	TextConvertation textConvertation; //композиция
	BinaryConvertation binConvertation;

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
	cout << "Конвертация файлов:" << endl;
	if (convertations.empty())
	{
		cout << "Конвертируемых файлов нет" << endl;
		return;
	}

	cout << "-----------------------------------------------------------" << endl;
	cout << "|  #  | Исходный файл | Конечный файл | Время конвертации |" << endl;
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
		cout << setw(12) << setfill('0') << convertations[i]->GetTime() << " секунд";
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
			cout << "Выберите тип конвертации:\n1.Текстовая\n2.Бинарная\n3.Конвертация папки" << endl;

			switch (InputInt(1,3))
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

	cout << setprecision(2) << fixed;

	bool isWork = true;
	
	vector<ConvertationOfFiles> convertations;

	while (isWork)
	{
		system("cls");
		cout << "1.Добавить" << endl;
		cout << "2.Распечать" << endl;
		cout << "3.Редактировать" << endl;
		cout << "4.Удалить" << endl;
		cout << "5.Сортировка" << endl;
		cout << "6.Поиск" << endl;
		cout << "7.Выход" << endl;

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
				cout << "Список конвертаций пуст" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < convertations.size(); i++)
			{
				cout << i + 1 << ".";
				convertations[i].Show();
				cout << endl;
			}
			cout << "Введите номер конвертации для редактирования: " << endl;
			int index = InputInt(1, convertations.size()) - 1;
			convertations[index].Input();
			break;
		}
		case '4':
		{
			if (convertations.empty())
			{
				cout << "Список конвертаций пуст" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < convertations.size(); i++)
			{
				cout << i + 1 << ".";
				convertations[i].Show();
				cout << endl;
			}
			cout << "Введите номер конвертации для удаления: " << endl;
			int index = InputInt(1, convertations.size()) - 1;
			convertations.erase(convertations.begin() + index);
			break;
		}
		case '5':
		{
			if (convertations.empty())
			{
				cout << "Список конвертаций пуст" << endl;
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
				cout << "Список конвертаций пуст" << endl;
				system("pause");
				break;
			}

			cout << "Введите название файла или папки для поиска:" << endl;
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
				cout << "Ничего не найдено" << endl;
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
			cout << "Неправильный ввод" << endl;
			system("pause");
			break;
		}
		}
	}

	return 0;
}