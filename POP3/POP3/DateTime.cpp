#include "DateTime.h"

DateTime::DateTime(){}

DateTime::~DateTime(){}

DateTime::DateTime(const DateTime &source) : day(source.day), month(source.month), year(source.year),
hour(source.hour), minute(source.minute), second(source.second){}

DateTime& DateTime::operator=(const DateTime &source){
	if (this != &source)
	{
		day = source.day;
		month = source.month;
		year = source.year;
		hour = source.hour;
		minute = source.minute;
		second = source.second;
	}
	return *this;
}

DateTime::DateTime(string Date):day(Date.substr(0,2)),month(Date.substr(2,2))
, year(Date.substr(4, 4)), hour(Date.substr(8, 2)), minute(Date.substr(10,2)),
second(Date.substr(12,2))
{}