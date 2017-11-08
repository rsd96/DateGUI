#include "stdafx.h"
#include "DateClass.h"
#include <algorithm>
#include <iterator>

DateClass::DateClass()
{
	year = 0;
	day = 0;
	month = 0;
}

DateClass::DateClass(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

DateClass::DateClass(DateClass &right) {
	day = right.day;
	month = right.month;
	year = right.year;
}

DateClass::~DateClass()
{
}

int DateClass::getYear() {
	return year;
}

int DateClass::getDay() {
	return day;
}

void DateClass::setYear(int y) {
	this->year = y; 
}

void DateClass::setMonth(int m) {
	this->month = m;
}

int DateClass::getMonth() {
	return month;
}

void DateClass::setDay(int d) {
	this->day = d; 
}

void DateClass::setDate(int day, int month, int year) {
	this->day = day;
	this->month = month;
	this->year = year;
}

bool DateClass::leapYear() {

	if ((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0))
		return true;
	else
		return false;
}

bool DateClass::operator<(DateClass &obj) {

	if (day < obj.day) {
		if (month < obj.month)
			if (year < obj.year)
				return true;
	}
	else
		return false;
}

bool DateClass::operator==(DateClass &obj) {

	if (day == obj.day) {
		if (month == obj.month)
			if (year == obj.year)
				return true;
	}
	else
		return false;
}

ostream &operator << (ostream &out, DateClass &right) {

	out << endl;
	out << "Date : " << right.day << "/" << right.month << "/" << right.year << endl;
	return out;
}

istream &operator >> (istream &in, DateClass &right) {

	cout << "Day - ";
	in >> right.day;
	cout << "Month - ";
	in >> right.month;
	cout << "Year - ";
	in >> right.year;
	return in;
}

bool DateClass::isMonthsOf30() {
	int mArray[7] = { 1,3,5,7,8,10,12 };
	return std::find(begin(mArray), std::end(mArray), month) != std::end(mArray);
}

DateClass DateClass::operator++() {

	++day;

	if (month == 2)
		leapYear() ? incrementDay(29) : incrementDay(28);
	else 
		isMonthsOf30() ? incrementDay(30) : incrementDay(31);

	return *this;
}

void DateClass::incrementDay(int dayLimit) {

	if (day > dayLimit) {
		day = 1;
		++month;
	}

	if (month > 12) {
		++year;
		month = 1;
	}
}

DateClass DateClass::operator--() {

	--day;

	if (month == 3)
		leapYear() ? decrementDay(29) : decrementDay(28);
	else 
		isMonthsOf30() ? decrementDay(31) : decrementDay(30);
	

	return *this;
}


void DateClass::decrementDay(int dayTo) {

	if (day < 1) {
		day = dayTo;
		--month;
	}

	if (month < 1) {
		--year;
		month = 12;
	}
}

int DateClass::findDay() {

	int m = month;
	int y = year;
	int d = day;

	m = (m + 9) % 12; // m = 11 d = 6 y = 2017
	y -= m / 10; //
	int dName = 365 * y + y / 4 - y / 100 + y / 400 + (m * 306 + 5) / 10 + (d - 1); //

	return dName;
}

string DateClass::DayOfWeek()
{
	string dayArray[] = {
		"Wednesday",
		"Thursday",
		"Friday",
		"Saturday",
		"Sunday",
		"Monday",
		"Tuesday"
	};

	int dName = findDay();

	return dayArray[dName % 7];
}