#ifndef USER
#define USER
#include <iostream>
using namespace std;


class User
{
public:
	User(){};
	
	User(string userName,string password):userName(userName),password(password){};
	
	~User(){};
	
	User(const User &source):
	userName(source.userName),password(source.password){};
	
	string getUsername(){ return userName; };
	
	string getPassword(){ return password; };
	

	User& operator=(const User& source)
	{
		if (this != &source)
		{
			userName = source.userName;
			password = source.password;
		}
		return *this;
	};

private:
	string userName;
	string password;
};

#endif // !USER
