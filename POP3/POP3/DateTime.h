#ifndef DATE
#define DATE
#include <string>
#include<iostream>
using namespace std;


class DateTime{

public:
	DateTime();
	DateTime(string Date);
	~DateTime();
	DateTime(const DateTime &source);
	DateTime& operator=(const DateTime &source);
	string getD(){return day ; }
	string getM(){ return month; }
	string getY(){ return year; }
	string getH(){ return hour; }
	string getMin(){ return minute; }
	string getS(){ return second; }

private:

	string day;
	string month;
	string year;
	string hour;
	string minute;
	string second;


};


#endif