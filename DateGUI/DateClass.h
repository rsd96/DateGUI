#pragma once
#include <iostream>
using namespace std;

class DateClass
{

private:
	int year;
	int month;
	int day;
	string dayName;
	//static const int mArray[];

public:
	DateClass();
	DateClass(int, int, int);
	DateClass(DateClass &);
	~DateClass();

	int getYear();
	int getMonth();
	int getDay();
	void setDate(int,int,int);

	string DayOfWeek();
	int findDay();
	bool leapYear();
	bool operator<(DateClass &);
	bool operator==(DateClass &);
	friend ostream &operator << (ostream &, DateClass &);
	friend istream &operator >> (istream &, DateClass &);
	DateClass operator++();
	void incrementDay(int dayLimit);
	DateClass operator--();
	void decrementDay(int dayTo);
};


