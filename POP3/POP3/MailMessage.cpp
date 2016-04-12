#include "MailMessage.h"

MailMessage::MailMessage(string ID,string From, string To, string Data, DateTime &ReciveDate,int size):
To(To),MailTime(ReciveDate), Data(Data), ID(ID), From(From), Size(size)
{
}

MailMessage::~MailMessage(){}
MailMessage::MailMessage(const MailMessage &source) : ID(source.ID), From(source.From), To(source.To),
Data(source.Data), Size(source.Size), MailTime(source.MailTime){}

MailMessage& MailMessage::operator=(const MailMessage &source){
	if (this != &source)
	{
		ID = source.ID;
		From = source.From;
		To = source.To;
		Data = source.Data;
		Size = source.Size;
		MailTime = source.MailTime;
	}
	return *this;
}