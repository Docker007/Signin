#include<iostream>
#include<string>
using namespace std;

int CheckUserName(string UserName);
int CheckPassword(string Password);
//class SignUp
//{
//public:
//	SignUp();
//	~SignUp();
//	int sign_up();
//	int log_in();
//private:
//	string UserName;
//	string Password;
//};

int main()
{
	string UserName;
	string Password;
	cout << "Input UserName: " << endl;
	getline(cin, UserName);
	cout << "Input password: " << endl;
	getline(cin, Password);
	if (CheckUserName(UserName) == 0)
	{
		cout << "Username is invalid!" << endl;
	}
	else if (CheckPassword(Password) == 0)
	{
		cout << "Password is invalid!" << endl;
	}
	else
		cout << "Login successfully!" << endl;
	return 0;
}

int CheckUserName(string UserName)
{
	for (unsigned i = 0; i < UserName.size(); i++)
	{
		if (UserName[i]<48|| (UserName[i]>57&&UserName[i]<65)||
			(UserName[i]>90&&UserName[i]<95)||UserName[i]==96||UserName[i]>122)
		{
			return 0;
		}
	}
	return 1;
}

int CheckPassword(string Password)
{
	for (unsigned  i = 0; i < Password.size(); i++)
	{
		if(Password[i]==' ')
		{
			return 0;
		}
	}
	return 1;
}
