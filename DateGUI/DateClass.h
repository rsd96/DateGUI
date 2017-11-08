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
	void setYear(int y);
	void setMonth(int m); 
	void setDay(int d); 
	void setDate(int,int,int);

	string DayOfWeek();
	int findDay();
	bool leapYear();
	bool operator<(DateClass &);
	bool operator==(DateClass &);
	friend ostream &operator << (ostream &, DateClass &);
	friend istream &operator >> (istream &, DateClass &);
	bool isMonthsOf30(); // checks if the month has 30 days or 31
	DateClass operator++();
	void incrementDay(int dayLimit);
	DateClass operator--();
	void decrementDay(int dayTo);
};


