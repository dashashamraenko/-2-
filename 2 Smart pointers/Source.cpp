#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <fstream>

using namespace std;

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
				cerr << "Критическая ошибка в потоке ввода. Программа завершена." << endl;
				exit(1);
			}
			cout << "Вводите только целые числа!" << endl;
		}

		cin >> result;

		isCorrect = cin.good();


	} while (!isCorrect);

	return result;
}

class GraphicObject
{
public:

	GraphicObject();
	GraphicObject(const GraphicObject& obj);
	GraphicObject(int x, int y, int z);
	~GraphicObject() {};

public:

	int getX()const;
	int getY()const;
	int getZ()const;

	void setX(int x);
	void setY(int y);
	void setZ(int z);

	virtual string getInfo()const;
	virtual void input();

protected:
	int x;
	int y;
	int z;
};

class Ball : public GraphicObject
{
public:

	Ball();
	Ball(const Ball& obj);
	Ball(int x, int y, int z, int r);
	~Ball() {};

public:

	int getR()const;

	void setR(int r);

	string getInfo()const override;
	void input() override;

protected:
	int radius;
};

class Pyramid : public GraphicObject
{
public:

	Pyramid();
	Pyramid(const Pyramid& obj);
	Pyramid(int x, int y, int z, int c);
	~Pyramid() {};

public:

	int getCountOfFaces()const;

	void setCountOfFaces(int c);

	string getInfo()const override;
	void input() override;

protected:
	int countOfFaces;
};

class Parallelepiped : public GraphicObject
{
public:

	Parallelepiped();
	Parallelepiped(const Parallelepiped& obj);
	Parallelepiped(int x, int y, int z, bool isOrtogonal);
	~Parallelepiped() {};

public:

	bool getIsOrtogonal()const;

	void setIsOrtogonal(bool isOrtogonal);

	string getInfo()const override;
	void input() override;

protected:
	bool isOrtogonal;
};

class PolygonalFigure : public GraphicObject
{
public:

	PolygonalFigure();
	PolygonalFigure(const PolygonalFigure& obj);
	PolygonalFigure(int x, int y, int z, int countOfPolygons);
	~PolygonalFigure() {};

public:

	int getCountOfPolygons()const;

	void setCountOfPolygons(int countOfPolygons);

	string getInfo()const override;
	void input() override;

protected:
	int countOfPolygons;
};

template <class T>
struct PointerItem
{
	T* pointer;
	int count;
};

template<class T>
class SmartPointer
{
private:

	PointerItem<T>* pointer;

public:
	SmartPointer(T* obj);
	SmartPointer(const SmartPointer& obj);

public:
	~SmartPointer();

	SmartPointer& operator=(const SmartPointer& obj);

	PointerItem<T>* getPtr()const;
	int getCounter()const;

};

template<class T>
class Transaction
{protected:
	T* currentState;
	T* oldState;

public:
	Transaction();
	Transaction(const Transaction& obj);

public:
	~Transaction();

	Transaction& operator=(const Transaction& obj);

	void init(T* state);

	T* getCurrentState()const;
	T* getOldState()const;

	string getInfo();

	void begin(T* newState);
	void cancel();
	void commit();
};


PolygonalFigure::PolygonalFigure() :GraphicObject(), countOfPolygons(0) {}

PolygonalFigure::PolygonalFigure(const PolygonalFigure& obj) :GraphicObject(obj), countOfPolygons(obj.countOfPolygons) {}

PolygonalFigure::PolygonalFigure(int x, int y, int z, int countOfPolygons) :GraphicObject(x,y,z), countOfPolygons(countOfPolygons) {}

int PolygonalFigure::getCountOfPolygons() const
{
	return countOfPolygons;
}

void PolygonalFigure::setCountOfPolygons(int countOfPolygons)
{
	this->countOfPolygons = countOfPolygons;
}

string PolygonalFigure::getInfo() const
{
	string info = "Фигура произвольной формы.\n" + GraphicObject::getInfo() + "\n";
	info += "Кол-во полигонов: " + to_string(countOfPolygons);
	return info;
}

void PolygonalFigure::input()
{
	GraphicObject::input();

	do
	{
		cout << "Введите кол-во полигонов:" << endl;
		countOfPolygons = InputInt();

		if (countOfPolygons < 3)
		{
			cout << "Ошибка: количество полигонов должно быть не менее 3." << std::endl;
		}

	} while (countOfPolygons < 3);
}


Parallelepiped::Parallelepiped() :GraphicObject(), isOrtogonal(true) {}

Parallelepiped::Parallelepiped(const Parallelepiped& obj) :GraphicObject(obj), isOrtogonal(obj.isOrtogonal) {}

Parallelepiped::Parallelepiped(int x, int y, int z, bool isOrtogonal) :GraphicObject(x,y,z), isOrtogonal(isOrtogonal) {}

bool Parallelepiped::getIsOrtogonal() const
{
	return isOrtogonal;
}

void Parallelepiped::setIsOrtogonal(bool isOrtogonal)
{
	this->isOrtogonal = isOrtogonal;
}

string Parallelepiped::getInfo() const
{
	string info = "Параллелепипед.\n" + GraphicObject::getInfo() + "\n";
	info += isOrtogonal ? "Прямоугольный" : "Не прямоугольный";

	return info;
}

void Parallelepiped::input()
{
	GraphicObject::input();

	cout << "Параллелепипед прямоугольный?(1/0)" << endl;
	int temp;
	temp = InputInt();
	isOrtogonal = temp == 1;
}


Pyramid::Pyramid() :GraphicObject(), countOfFaces(0) {}

Pyramid::Pyramid(const Pyramid& obj) :GraphicObject(obj), countOfFaces(obj.countOfFaces) {}

Pyramid::Pyramid(int x, int y, int z, int c) :GraphicObject(x, y, z), countOfFaces(c) {}

int Pyramid::getCountOfFaces() const
{
	return countOfFaces;
}

void Pyramid::setCountOfFaces(int c)
{
	this->countOfFaces = c;
}

string Pyramid::getInfo() const
{
	string info = "Пирамида.\n" + GraphicObject::getInfo() + "\n";
	info += "Кол-во ребер: " + to_string(countOfFaces);
	return info;
}

void Pyramid::input()
{
	GraphicObject::input();

	do
	{
		cout << "Введите кол-во рёбер:" << endl;
		countOfFaces = InputInt(); 

		if (countOfFaces < 6)
		{
			cout << "Ошибка: количество рёбер должно быть не менее 6." << std::endl;
		}

	} while (countOfFaces < 6);
}


Ball::Ball() :GraphicObject(), radius(0){}

Ball::Ball(const Ball& obj) :GraphicObject(obj), radius(obj.radius){}

Ball::Ball(int x, int y, int z, int r) :GraphicObject(x, y ,z), radius(r){}

int Ball::getR() const
{
	return radius;
}

void Ball::setR(int r)
{
	this->radius = r;
}

std::string Ball::getInfo() const
{
	string info = "Шар.\n" +  GraphicObject::getInfo() + "\n";
	info += "Радиус: " + to_string(radius);
	return info;
}

void Ball::input()
{
	GraphicObject::input();
		cout << "Введите радиус:" << endl;
		radius = InputInt();

}


GraphicObject::GraphicObject() : x(0), y(0), z(0){}

GraphicObject::GraphicObject(const GraphicObject& obj): x(obj.x), y(obj.y), z(obj.z) {}

GraphicObject::GraphicObject(int x, int y, int z): x(x), y(y), z(z) {}

int GraphicObject::getX() const
{
	return x;
}

int GraphicObject::getY() const
{
	return y;
}

int GraphicObject::getZ() const
{
	return z;
}

void GraphicObject::setX(int x)
{
	this->x = x;
}

void GraphicObject::setY(int y)
{
	this->y = y;
}

void GraphicObject::setZ(int z)
{
	this->z = z;
}

string GraphicObject::getInfo() const
{
	return "Координаты: (" + to_string(x) + ", " + to_string(y) + ", " + to_string(z) + ")";
}

void GraphicObject::input()
{
	cout << "Введите x:" << endl;
	x =  InputInt();
	cout << "Введите y:" << endl;
	y = InputInt();
	cout << "Введите z:" << endl;
	z = InputInt();
}


template<class T>
SmartPointer<T>::SmartPointer(T* obj):pointer(NULL)
{
	if (!obj)
		return;

	pointer = new PointerItem<T>;
	pointer->count = 1;
	pointer->pointer = obj;
}

template<class T>
SmartPointer<T>::SmartPointer(const SmartPointer& obj):pointer(NULL)
{
	if (!obj.pointer)
		return;

	pointer = obj.pointer;
	pointer->count++;
}

template<class T>
SmartPointer<T>::~SmartPointer()
{
	if (!pointer)
		return;

	pointer->count--;
	if (pointer->count == 0)
	{
		delete pointer->pointer;
		delete pointer;
	}
}

template<class T>
SmartPointer<T>& SmartPointer<T>::operator=(const SmartPointer<T>& obj)
{
	if (pointer)
	{
		pointer->count--;
		if (pointer->count == 0)
		{
			delete pointer->pointer;
			delete pointer;
		}
	}

	pointer = obj.pointer;
	if(pointer)
		pointer->count++;

	return *this;
}

template<class T>
PointerItem<T>* SmartPointer<T>::getPtr() const
{
	return pointer;
}

template<class T>
int SmartPointer<T>::getCounter() const
{
	if (!pointer)
		return 0;
	return pointer->count;
}


template<class T>
Transaction<T>::Transaction():oldState(NULL), currentState(NULL){}

template<class T>
Transaction<T>::Transaction(const Transaction& obj): oldState(NULL), currentState(NULL)
{
	if (obj.currentState)
		currentState = new T(*obj.currentState);

	if (obj.oldState)
		oldState = new T(*obj.oldState);
}

template<class T>
Transaction<T>::~Transaction()
{
	if (oldState)
		delete oldState;

	if (currentState)
		delete currentState;
}

template<class T>
Transaction<T>& Transaction<T>::operator=(const Transaction& obj)
{
	if (oldState)
		delete oldState;

	if (currentState)
		delete currentState;

	if (obj.currentState)
		currentState = new T(*obj.currentState);
	else
		currentState = NULL;

	if (obj.oldState)
		oldState = new T(*obj.oldState);
	else
		oldState = NULL;

	return *this;
}

template<class T>
void Transaction<T>::init(T* state)
{
	if (currentState)
		delete currentState;

	currentState = state;
}

template<class T>
T* Transaction<T>::getCurrentState() const
{
	return currentState;
}

template<class T>
T* Transaction<T>::getOldState() const
{
	return oldState;
}

template<class T>
string Transaction<T>::getInfo()
{
	string info = "Current state: ";
	info += currentState ? currentState->getInfo() : "NULL";
	info += "\n";
	info += "Old state: ";
	info += oldState ? oldState->getInfo() : "NULL";

	return info;
}

template<class T>
void Transaction<T>::begin(T* newState)
{
	if (!newState)
		return;

	if (oldState)
		delete oldState;

	oldState = currentState;
	currentState = newState;
}

template<class T>
void Transaction<T>::cancel()
{
	if (!oldState)
		return;

	if (currentState)
		delete currentState;

	currentState = oldState;
	oldState = NULL;
}

template<class T>
void Transaction<T>::commit()
{
	if (!currentState)
		return;

	if (oldState)
		delete oldState;

	oldState = NULL;
}

void writeToFile(const vector<SmartPointer<Transaction<GraphicObject>>>& objects, const string& filename)
{
	ofstream fout(filename);

	if (!fout.is_open())
	{
		cerr << "Не удалось открыть файл для записи." << endl;
		return;
	}

	for (const auto& object : objects)
	{
		fout << object.getPtr()->pointer->getCurrentState()->getInfo() << endl;
	}

	fout.close();
	cout << "Данные успешно записаны в файл." << endl;
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	vector<SmartPointer<Transaction<GraphicObject>>> objects;
	vector<SmartPointer<Transaction<GraphicObject>>> additionalRefs;

	shared_ptr<GraphicObject> sp0 = 0;



	bool isWork = true;
	while (isWork)
	{
		system("cls");
		cout << "1.Добавить объект в список"<<endl;
		cout << "2.Просмотреть список объектов"<<endl;
		cout << "3.Просмотреть количество указателей на объект"<<endl;
		cout << "4.Добавить указатели на объект"<<endl;
		cout << "5.Удалить указатели на объект"<<endl;
		cout << "6.Работа с транзакциями"<<endl;
		cout << "7.Записать в файл"<<endl;
		cout << "8.Выход"<<endl;

		int ch;
		ch = InputInt();
		system("cls");
		switch (ch)
		{
		case 1: 
		{
			SmartPointer<Transaction<GraphicObject>> object(new Transaction<GraphicObject>);
			cout << "Выберите тип объекта:" << endl;
			cout << "1.Шар" << endl;
			cout << "2.Пирамида" << endl;
			cout << "3.Параллелепипед" << endl;
			cout << "4.Произвольная фигура" << endl;

			int choice;
			choice = InputInt();
			system("cls");
			switch (choice)
			{
			case 1:
			{
				object.getPtr()->pointer->init(new Ball);
				break;
			}
			case 2:
			{
				object.getPtr()->pointer->init(new Pyramid);
				break;
			}
			case 3:
			{
				object.getPtr()->pointer->init(new Parallelepiped);
				break;
			}
			case 4:
			{
				object.getPtr()->pointer->init(new PolygonalFigure);
				break;
			}
			default:
				cout << "Некорректный ввод!" << endl;
				system("pause");
				break;
			}

			if (ch >= '1' || ch <= '4')
			{
				object.getPtr()->pointer->getCurrentState()->input();
				objects.push_back(object);
			}

			break;
		}
		case 2:
		{
			if (objects.empty())
				cout << "Список пуст" << endl;

			for (int i = 0; i < objects.size(); i++)
			{
				cout << i + 1 << ". " << objects[i].getPtr()->pointer->getCurrentState()->getInfo() << endl;
			}
			system("pause");
			break;
		}
		case 3:
		{
			if (objects.empty())
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < objects.size(); i++)
			{
				cout << i + 1 << ". " << objects[i].getPtr()->pointer->getCurrentState()->getInfo() << endl;
			}
			cout << "Введите номер объекта для просмотра или любое другое число для выхода:" << endl;
			int index = 0;
			index = InputInt();
			index--;

			if (index >= 0 && index < objects.size())
			{
				cout << "Количество указателей на объект равно " << objects[index].getCounter() << endl;
				system("pause");
			}
			break;
		}
		case 4:
		{
			if (objects.empty())
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < objects.size(); i++)
			{
				cout << i + 1 << ". " << objects[i].getPtr()->pointer->getCurrentState()->getInfo() << endl;
			}
			cout << "Введите номер объекта для добавления ссылки:" << endl;
			int index = 0;
			index = InputInt();
			index--;

			if (index >= 0 && index < objects.size())
			{
				SmartPointer<Transaction<GraphicObject>> newPtr = objects[index];
				additionalRefs.push_back(newPtr);
			}
			break;
		}
		case 5:
		{
			if (objects.empty())
			{
				cout << "Список пуст" << endl;
				system("pause");
				break;
			}

			for (int i = 0; i < objects.size(); i++)
			{
				cout << i + 1 << ". " << objects[i].getPtr()->pointer->getCurrentState()->getInfo() << endl;
			}
			cout << "Введите номер объекта для удаления ссылки:" << endl;
			int index = 0;
			index = InputInt();
			index--;

			if (index >= 0 && index < objects.size())
			{
				if (objects[index].getCounter() > 1)
				{
					for (int i = 0; i < additionalRefs.size(); i++)
					{
						if (objects[index].getPtr() == additionalRefs[i].getPtr())
						{
							additionalRefs.erase(additionalRefs.begin() + i);
							break;
						}
					}
				}
				else
				{
					objects.erase(objects.begin() + index);
				}
			}
			break;
		}
		case 6:
		{
			bool work = true;
			while (work)
			{
				system("cls");
				cout << "1.Просмотреть состояние транзакции" << endl;
				cout << "2.Начать транзакцию" << endl;
				cout << "3.Отменить транзакцию" << endl;
				cout << "4.Подтвердить транзакцию" << endl;
				cout << "5.Выход" << endl;

				int c;
				c = InputInt();
				system("cls");
				switch (c)
				{
				case 1:
				{
					if (objects.empty())
					{
						cout << "Список пуст" << endl;
						system("pause");
						break;
					}

					for (int i = 0; i < objects.size(); i++)
					{
						cout << i + 1 << ". " << objects[i].getPtr()->pointer->getCurrentState()->getInfo() << endl;
					}
					cout << "Введите номер объекта для просмотра или любое другое число для вывода:" << endl;
					int index = 0;
					index = InputInt();
					index--;

					if (index >= 0 && index < objects.size())
					{
						cout << objects[index].getPtr()->pointer->getInfo() << endl;
						system("pause");
					}
					break;
				}
				case 2:
				{
					if (objects.empty())
					{
						cout << "Список пуст" << endl;
						system("pause");
						break;
					}

					for (int i = 0; i < objects.size(); i++)
					{
						cout << i + 1 << ". " << objects[i].getPtr()->pointer->getCurrentState()->getInfo() << endl;
					}
					cout << "Введите номер объекта или любое другое число для вывода:" << endl;
					int index = 0;
					index = InputInt();
					index--;

					if (index >= 0 && index < objects.size())
					{
						GraphicObject* object = NULL;
						cout << "Выберите тип объекта:" << endl;
						cout << "1.Шар" << endl;
						cout << "2.Пирамида" << endl;
						cout << "3.Параллелепипед" << endl;
						cout << "4.Произвольная фигура" << endl;

						int choice;
						choice = InputInt();
						system("cls");
						switch (choice)
						{
						case 1:
						{
							object = new Ball;
							break;
						}
						case 2:
						{
							object = new Pyramid;
							break;
						}
						case 3:
						{
							object = new Parallelepiped;
							break;
						}
						case 4:
						{
							object = new PolygonalFigure;
							break;
						}
						default:
							cout << "Некорректный ввод!" << endl;
							system("pause");
							break;
						}

						if (ch >= '1' || ch <= '4')
						{
							object->input();
							objects[index].getPtr()->pointer->begin(object);
						}
					}
					break;
				}
				case 3:
				{
					if (objects.empty())
					{
						cout << "Список пуст" << endl;
						system("pause");
						break;
					}

					for (int i = 0; i < objects.size(); i++)
					{
						cout << i + 1 << ". " << objects[i].getPtr()->pointer->getCurrentState()->getInfo() << endl;
					}
					cout << "Введите номер объекта или любое другое число для вывода:" << endl;
					int index = 0;
					index = InputInt();
					index--;

					if (index >= 0 && index < objects.size())
					{
						objects[index].getPtr()->pointer->cancel();
					}
					break;
				}
				case 4:
				{
					if (objects.empty())
					{
						cout << "Список пуст" << endl;
						system("pause");
						break;
					}

					for (int i = 0; i < objects.size(); i++)
					{
						cout << i + 1 << ". " << objects[i].getPtr()->pointer->getCurrentState()->getInfo() << endl;
					}
					cout << "Введите номер объекта или любое другое число для вывода:" << endl;
					int index = 0;
					index = InputInt();
					index--;

					if (index >= 0 && index < objects.size())
					{
						objects[index].getPtr()->pointer->commit();
					}
					break;
				}
				case 5:
				{
					work = false;
					break;
				}
				default:
					cout << "Некорректный ввод!" << endl;
					system("pause");
					break;
				}
			}
			break;
		}
		case 7:
		{
			if (objects.empty())
			{
				cout << "Список пуст. Запись в файл невозможна." << endl;
				system("pause");
				break;
			}
			string filename = "l2.txt";
			writeToFile(objects, filename);

			system("pause");
			break;
		}
		case 8:
		{
			isWork = false;
			break;
		}
		default:
		{
			cout << "Некорректный ввод!" << endl;
			system("pause");
			break;
		}
		
		}

	}
}
