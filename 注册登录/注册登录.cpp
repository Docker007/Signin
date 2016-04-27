#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;

int CheckUserName(string UserName);
int CheckPassword(string Password);
int SaveUser(string UserName, string Password);
int CheckProfile(string UserName, string Password);

int main()	 
{
	int flag = 0;
	string UserName;
	string Password;
	cout << "1.Sign up." << endl;
	cout << "2.Sign in." << endl;
	cout << "Input UserName: " << endl;
	getline(cin, UserName);
	cout << "Input password: " << endl;
	getline(cin, Password);
	CheckProfile(UserName, Password);
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
	int upper_letter(0), lower_letter(0), number(0);
	for (unsigned  i = 0; i < Password.size(); i++)
	{
		if (Password[i] >= 'a' && Password[i] <= 'z')
			lower_letter++;
		if (Password[i] >= 'A'&&Password[i] <= 'Z')
			upper_letter++;
		if (Password[i] >= '0'&&Password[i] <= '9')
			number++;
		if(Password[i]==' ')
		{
			return 0;
		}
	}
	if (upper_letter == 0 || lower_letter == 0 || number == 0)
		return 0;
	return 1;
}

int SaveUser(string UserName, string Password)
{
	//vector<string> UserList;
	//vector<string> PsdList;
	ofstream outfileUserName("C:\\Users\\Hanxi\\Music\\login\\username.txt", ios_base::app);
	ofstream outfilePassword("C:\\Users\\Hanxi\\Music\\login\\password.txt", ios_base::app);
	outfileUserName << UserName << "\n";
	outfilePassword << Password << "\n";
	outfileUserName.close();
	outfilePassword.close();
	return 1;
}

int CheckProfile(string UserName, string Password)
{
	if (CheckUserName(UserName) == 0)
	{
		cout << "Username is invalid!" << endl;
	}
	else if (CheckPassword(Password) == 0)
	{
		cout << "Password is invalid!" << endl;
	}
	else
	{
		int SaveFileFlag = SaveUser(UserName, Password);
		if (SaveFileFlag = 1)
		{
			cout << "Sign up sucessfully!" << endl;
		}
		else cout << "Sign up failed..." << endl;
	}
	return 0;
}

