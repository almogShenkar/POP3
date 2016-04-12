#ifndef MAIL
#define MAIL
#include <iostream>
#include "DateTime.h"


class MailMessage
{
public:

	MailMessage():Size(0){};
	MailMessage(string ID,string From,string To,string Data,DateTime &ReciveDate,int size=0);
	~MailMessage();
	MailMessage(const MailMessage &source);
	MailMessage& operator=(const MailMessage &source);
	int getSize(){ return Size; };
	string getData(){ return Data; };
	string getID(){ return ID; };
	string getTo(){return To; };
	void setID(int id){ ID = to_string(id); }
	string getFrom(){return From; };
	DateTime getMailTime(){return MailTime; };
private:
	string ID;
	string From;
	string To;
	string Data;
	int  Size;
	DateTime MailTime;


};


#endif