#include<iostream>
using std::cin;
using std::cout;
using std::endl;

//#define DEBUG

class Fraction;	
Fraction operator*(Fraction left, Fraction right);
Fraction operator/(Fraction left, Fraction right);
Fraction operator+(Fraction left, Fraction right);
Fraction operator-(Fraction left, Fraction right);

class Fraction
{
	int integer;		
	int numerator;		
	int denominator;	
public:
	int get_integer()const
	{
		return integer;
	}
	int get_numerator()const
	{
		return numerator;
	}
	int get_denominator()const
	{
		return denominator;
	}
	void set_integer(int integer)
	{
		this->integer = integer;
	}
	void set_numerator(int numerator)
	{
		this->numerator = numerator;
	}
	void set_denominator(int denominator)
	{
		if (denominator <= 0)denominator = 1;
		this->denominator = denominator;
	}

	//				Constructors:
	Fraction()
	{
		this->integer = 0;
		this->numerator = 0;
		this->denominator = 1;
#ifdef DEBUG
		cout << "DefaultConstruct:\t" << this << endl;
#endif // DEBUG
	}
	explicit Fraction(int integer)
	{
		this->integer = integer;
		this->numerator = 0;
		this->denominator = 1;
#ifdef DEBUG
		cout << "1ArgConstructor:" << this << endl;
#endif // DEBUG
	}
	Fraction(int numerator, int denominator)
	{
		this->integer = 0;
		this->numerator = numerator;
		set_denominator(denominator);
#ifdef DEBUG
		cout << "Constructor\t" << this << endl;
#endif // DEBUG
	}
	Fraction(int integer, int numerator, int denominator)
	{
		this->integer = integer;
		this->numerator = numerator;
		set_denominator(denominator);
#ifdef DEBUG
		cout << "Constructor\t" << this << endl;
#endif // DEBUG
	}
	Fraction(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
#ifdef DEBUG
		cout << "CopyConstructor:" << this << endl;
#endif // DEBUG
	}
	~Fraction()
	{
#ifdef DEBUG
		cout << "Destructor\t" << this << endl;
#endif // DEBUG
	}

	//				Operators:
	Fraction& operator=(double ra)
	{
		int ost = (int)ra;
		int count = 0;
		double old_ra = ra;
		// The number to the right of the point
		while (ost != ra) {
			count++;
			ra *= 10;
			ost = (int)ra;
		}
		this->denominator = 1;

		for (int i = 0; i < count; i++) this->denominator *= 10;
		this->numerator = (old_ra - (int)old_ra) * denominator;
		this->integer = (int)old_ra;
		reduce();
		return *this;
	}
	Fraction& operator=(const Fraction& other)
	{
		this->integer = other.integer;
		this->numerator = other.numerator;
		this->denominator = other.denominator;
#ifdef DEBUG
		cout << "CopyAssignment:\t" << this << endl;
#endif // DEBUG
		return *this;
	}
	Fraction& operator*=(const Fraction& other)
	{
		return *this = *this * other;
	}
	Fraction& operator/=(const Fraction& other)
	{
		return *this = *this / other;
	}
	Fraction& operator+=(const Fraction& other)
	{	
		return *this = *this + other;
	}
	Fraction& operator-= (const Fraction& other)
	{
		return *this=*this-other;
	}
	Fraction& operator++()
	{
		integer++;
		return *this;
	}
	Fraction operator++(int)
	{
		Fraction old = *this;
		integer++;
		return old;
	}

	Fraction operator--()
	{
		if (integer != 0)  integer--;
		return *this;
	}
	Fraction operator--(int)
	{
		Fraction old=*this;
		if (integer != 0)  integer--;
		return old;
	}


	
	//				Type-cast operators:
	explicit operator int()const
	{
		return integer;
	}
	explicit operator double()const
	{
		return integer + (double)numerator / denominator;
	}

	//				Methods:
	Fraction& to_proper()
	{
		integer += numerator / denominator;
		numerator %= denominator;
		return *this;
	}
	Fraction& to_improper()
	{
		numerator += integer * denominator;
		integer = 0;
		return *this;
	}
	Fraction inverted()
	{
		to_improper();
		return Fraction(denominator, numerator);
	}
	Fraction& reduce()
	{
		int KratnoeS;
		KratnoeS = (denominator > numerator) ? denominator : numerator;
		for (int i = KratnoeS; i > 0; i--)
		{
			if (denominator % i == 0 && numerator % i == 0)
			{
				KratnoeS = i;
				break;
			}
		}
		numerator = numerator / KratnoeS;
		denominator = denominator / KratnoeS;
		return *this;

	}
	
	void print()const
	{
		if (integer)cout << integer;
		if (numerator)
		{
			if (integer)cout << "(";
			cout << numerator << "/" << denominator;
			if (integer)cout << ")";
		}
		else if (integer == 0)cout << 0;
		cout << endl;
	}
};

Fraction operator*(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	/*Fraction result
	(
		left.get_numerator()*right.get_numerator(),
		left.get_denominator()*right.get_denominator()
	);*/
	/*result.set_numerator(left.get_numerator()*right.get_numerator());
	result.set_denominator(left.get_denominator()*right.get_denominator());*/
	//result.to_proper();
	//return result;
	return Fraction		
	(
		left.get_numerator() * right.get_numerator(),
		left.get_denominator() * right.get_denominator()
	).to_proper();
}
Fraction operator/(Fraction left, Fraction right)
{
	return left * right.inverted();
}
Fraction operator+(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	int max;

	max = (left.get_denominator() > right.get_denominator() ) ? left.get_denominator() : right.get_denominator();
	
	do
	{
		if (max%left.get_denominator() == 0 && max%right.get_denominator()==0)
		{
			break;
		}
		else
		{
			++max;
		}

	} while (true);
	
	return Fraction
	((max/left.get_denominator()) * left.get_numerator()+
		(max/right.get_denominator()*right.get_numerator()) ,
		max
	).to_proper().reduce();
}
Fraction operator-(Fraction left, Fraction right)
{
	left.to_improper();
	right.to_improper();
	int max;

	max = (left.get_denominator() > right.get_denominator()) ? left.get_denominator() : right.get_denominator();

	do
	{
		if (max % left.get_denominator() == 0 && max % right.get_denominator() == 0)
		{
			break;
		}
		else
		{
			++max;
		}

	} while (true);

	
	return Fraction
	((max / left.get_denominator()) * left.get_numerator() -
		(max / right.get_denominator() * right.get_numerator()),
		max
	).to_proper().reduce();
}

bool operator==(Fraction& left, Fraction& right)
{
	bool result;
	
	left.to_improper();
	right.to_improper();
	result = (
		(double)left.get_numerator() / (double)left.get_denominator() ==
		(double)right.get_numerator() / (double)right.get_denominator()
			 ) ? true : false;
	
	return result;
}
bool operator!=(Fraction& left, Fraction& right)
{
	bool result;
	left.to_improper();
	right.to_improper();
	result = (
		(double)left.get_numerator() / (double)left.get_denominator() !=
		(double)right.get_numerator() / (double)right.get_denominator()
		) ? true : false;

	return result;
}
bool operator >(Fraction& left, Fraction& right) 
{
	bool result;
	left.to_improper();
	right.to_improper();
	result = (
		(double)left.get_numerator() / (double)left.get_denominator() >
		(double)right.get_numerator() / (double)right.get_denominator()
		) ? true : false;

	return result;
}
bool operator <(Fraction& left, Fraction& right) 
{
	bool result;
	left.to_improper();
	right.to_improper();
	result = (
		(double)left.get_numerator() / (double)left.get_denominator() <
		(double)right.get_numerator() / (double)right.get_denominator()
		) ? true : false;

	return result;
}



std::ostream& operator<<(std::ostream& os, const Fraction& obj)
{
	if (obj.get_integer())cout << obj.get_integer();
	if (obj.get_numerator())
	{
		if (obj.get_integer())cout << "(";
		cout << obj.get_numerator() << "/" << obj.get_denominator();
		if (obj.get_integer())cout << ")";
	}
	else if (obj.get_integer() == 0)cout << 0;
	return os;
}

std::istream& operator>>(std::istream& is, Fraction& obj) {
	/*INT INTEGER, NUMERATOR, DENOMINATOR;
	is >> INTEGER >> NUMERATOR >> DENOMINATOR;
	OBJ.SET_INTEGER(INTEGER);
	OBJ.SET_NUMERATOR(NUMERATOR);
	OBJ.SET_DENOMINATOR(DENOMINATOR);*/
	obj = Fraction(); // Обнуляем обьект - задаем ему значение по умолчание.
	const int SIZE = 256;
	char buffer[SIZE] = {};
	
	//is >> buffer;
	is.getline(buffer, SIZE); // Вводится строку с пробелами
	char delimiters[] = "/( )";

	char* number[3] = {}; // Сюда будут сохранятся числа из исходной строки (из буфера).
	int n = 0; // считает сколько чисел мы вытащили из исходной строки
	for (char *pch=strtok(buffer,delimiters);pch;pch=strtok(NULL,delimiters))
	{
		number[n++] = pch;
	}
	switch (n)
	{
	case 1: obj.set_integer(atoi(number[0])); break;
		// atoi ()  Принимает строку, и возвращает int - ое
		//значение числа хранещегося в строке
	case 2: obj.set_numerator(atoi(number[0]));
	obj.set_denominator(atoi(number[1]));
	break;
	case 3: 
		obj.set_integer(atoi(number[0]));
		obj.set_numerator(atoi(number[1]));
		obj.set_denominator(atoi(number[2]));
	}
	return is;
}
//#define CONSTRUCTORS_CHECK
#define OPERATORS_CHECK
//#define TYPE_CONVERSIONS_BASICS
//#define CONVERSIONS_FROM_OTHER_TYPES_TO_CLASS
//#define CONVERSIONS_FROM_CLASS_TO_OTHER_TYPES

void main()
{
	setlocale(LC_ALL, "");
#ifdef CONSTRUCTORS_CHECK
	Fraction A;		//Default constructor
	A.print();

	double b = 5;
	Fraction B = 5;	//Single-argument constructor
	B.print();

	Fraction C(1, 2);
	C.print();

	Fraction D(2, 3, 4);
	D.print();

	Fraction E = D;
	E.print();
#endif // CONSTRUCTORS_CHECK

#ifdef OPERATORS_CHECK
	int a=0,
		b=0;
	Fraction A(3, 3, 4);
	Fraction B(3, 4, 5);
	Fraction T;
	Fraction D;
	D = 2.75;
	D.print();
			cout << "Введите простую дробь : "; cin >> T; 

	/*T.set_numerator(a);
	T.set_denominator(b);
	cout << "T++ ; "; T++;*/
	T.print();
	
	cout << "--T ; "<<--T<<endl;
	//cout << a << " / " << b << endl;
	

	A.print();
	B.print();

	A.to_improper();
	B.to_improper();

	A.print();
	B.print();

	cout << "\n--------------------------\n";
	cout << "Сравнение == дробей  : ";
	(A == B) ? cout << "true" : cout << "false";
	cout << "\n--------------------------\n";
	cout << "Сравнение > дробей  : ";
	(A > B) ? cout << "true" : cout << "false";
	cout << "\n--------------------------\n";
	cout << "Сравнение < дробей  : "<<(double)A << " < " << (double)B<<endl;
	(A < B) ? cout << "true" : cout << "false";
	cout << "\n--------------------------\n";

	cout << "Умножение дробей : ";
	Fraction C = A * B;
	C.print();
	cout << "\n--------------------------\n";
	cout << "Сложение дробей : ";
	C = A + B;
	C.print();
	cout << "\n--------------------------\n";
	cout << "Деление дробей : ";
	C = A / B;
	C.print();
	cout << "\n--------------------------\n";
	cout << "Вычитание дробей : ";
	C = A - B;
	C.print();
	cout << "\n--------------------------\n";
	cout << "Присваивание += дробей : ";
	A += B;
	cout << A << endl;
	cout << "\n--------------------------\n";
	cout << "Присваивание -= дробей : ";
	A -= B;
	cout << A << endl;
	cout << "\n--------------------------\n";
	cout << "Присваивание *= дробей : ";
	A *= B;
	cout << A << endl;
	

#endif // OPERATORS_CHECK

#ifdef TYPE_CONVERSIONS_BASICS
			//Warning: conversion from type to type possible loss of data.
//		l-value = r-value;
	int a = 2;		//No conversion
	double b = 3;	//Conversion from less to more
	int c = b;		//Conversion from more to less without data loss
	int d = 5.2;	//Conversion from more to less with data loss
	char e = 515;	//Conversion from int to char. Truncation (Óñå÷åíèå, óðåçàíèå)
					//Arithmetical overflow
	cout << (int)e << endl;
#endif // TYPE_CONVERSIONS_BASICS

#ifdef CONVERSIONS_FROM_OTHER_TYPES_TO_CLASS
	//1. Single-argument constructor
	//2. Assignment operator

	//(type)value - C-Like notation
	//type(value) - Functional notation

	double a = 2;	//Conversion from 'int' to 'double'
	5;//×èñëîâàÿ êîíñòàíòà òèïà 'int'
	Fraction A = (Fraction)5;	//Conversion from 'int' to 'Fraction'
	A;//Ïåðåìåííàÿ òèïà 'Fraction'
	cout << A << endl;

	Fraction B;	//Default constructor
	cout << "\n--------------------------\n";
	B = Fraction(8);
	cout << "\n--------------------------\n";
	cout << B << endl;
#endif // CONVERSIONS_FROM_OTHER_TYPES_TO_CLASS

	
	/*Fraction A(5);
	int a = A;
	cout << a << endl;
	Fraction B(2, 1, 7);
	double b = B;
	cout << b << endl;*/

	//cout << ((double)Fraction(1, 2) == (double)Fraction(5, 10)) << endl;
	

}

