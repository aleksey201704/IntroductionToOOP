#include <iostream>
#include <Windows.h>

using namespace std;
using std::cout;


int StringLength(const char* str);
class String;
String operator+(String left, String rigth);

//#define NULL_TERMINATED_LINES
//#define BASIC_CHECK

class String
{
	int size; // Размер строки
	
public:
	char* str; // Eуказатель на строку в динамическую память

	explicit String(int size = 80)
	{
		// Блвгодаря параметру size принимаем параметру мы можем создвавать строки
		// заданого размера
		this->size = size;
		this->str = new char[size] {};
		cout << "Default constractor: " << this << endl;
	}

	String(const char* str)
	{
		this->size = StringLength(str) + 1; // сохраняем размер в Байтах
		// с учетом
		this->str = new char[size] {};
		for (int i = 0; i < size; i++) this->str[i] = str[i];

	}

	String(const String& other)
	{
		this->size = other.size;
		this->str = new char [size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "Copy Constructor";
	}
	~String()
	{
		delete[] this->str; // Если конструторк выделяет память при помощи new
		// то деструтор обязателен должен особожждать эту память оператором delete
		// в противном случае будет возникать утечка памяти.
	}

				// Operators:
	String& operator=(const String& other)
	{
		if (this == &other) return *this; // если одинаковые значения

		delete[] this->str; // Затираем старое значение
		this->size = other.size;
		this->str = new char [size] {};
		for (int i = 0; i < size; i++)this->str[i] = other.str[i];
		cout << "Copy Assigment: \t";
		return *this;
	}
	
	void print()const
	{
		cout << "Size: " << size << endl;
		cout << "Str: " << str << endl;
	}
};

//String operator+(String left, String rigth)
//{
//	//return String(left,rigth);
//}


std::ostream& operator<<(std::ostream& os, const String& obj)
{
	
	//obj.print();
	cout << obj.str;
	return os;
}


void main()
{
	//setlocale(LC_ALL, "");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	
#ifdef NULL_TERMINATED_LINES
	/*char str[] = { 'H','r','e','\0'};
	char str1[] = "RTYR";
	cout << str1 << endl;

	char* str2 = "Wolrd";*/

	const int SIZE = 20;
	char str[SIZE] = {};

	cout << "Строку"; /*cin >> str;*/
	SetConsoleCP(1251);
	cin.getline(str, SIZE);
	SetConsoleCP(1251);
	cout << str << endl;
#endif // NULL_TNULL_TERMINATED_LINES

#ifdef BASIC_CHECK
	String str1;
	str1.print();

	// String str2=25; // Преобразование int в string запрещено
	String str2(25); // explicint конструтор можно вызвать только так
	str2.print();

	//cout << "StringLength:\t"  << StringLength("Hello");

	String str3 = "HEllo";
	str3.print();

	str3 = str3;

	String str4 = str3; // Вызывает Copy Constructor
	str4.print();

	String str5;
	str5 = str4; // CopyAssign
	str5.print();
#endif // BASIC_CHECK

	String str1 = "Hello";
	String str2 = "World";
	//String str3 = str1 + str2;
	//cout << str3 << endl; // HelloWorld
	cout << str2 + str1;

}

int StringLength(const char* str) 
{
	
	int t = 0;
	while (str[t] != 0)
	{
		t++;
	}
	
	return t;
}