#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using namespace std;
int UserNumber = 0;

void ReadUserNumber(int &UserNumber);         //���ļ��ж�ȡ��ǰ�û���
void WriteUserNumber(int &UserNumber);        //����ǰ�û���д���ļ�
bool CheckUserName(string UserName);           //����û����ǺϷ�
bool CheckPassword(string Password);            //��������Ƿ�Ϸ�
bool SaveUser(string UserName, string Password);//���û��������뱣�����ļ�
bool CheckProfile(string UserName, string Password);//�����û�����麯���������麯������û���������
bool CheckRepetition(string UserName, string Password);//����û����Ƿ��ظ�

int main()	                                        //������
{
	int Select;
	string UserName;
	string Password;
	cout << "1.Sign up." << endl;                   //����ѡ��
	cout << "2.Sign in." << endl;
	cout << "3.Exit." << endl;
	cout << "Select a function: " << endl;
	cin >> Select;
	getchar();
	switch (Select)
	{
	case 1:
	{
		cout << "Input UserName: " << endl;
		getline(cin, UserName);
		cout << "Input password: " << endl;
		getline(cin, Password);
		CheckProfile(UserName, Password);
		break;
	}
	case 2:cout << "Sign in.........." << endl; break;
	case 3:return 0;
	default:
		cout << "��������У������ɡ�����" << endl; break;
	}
	
	return 0;
}

void ReadUserNumber(int &UserNumber)
{
	ifstream UserNumberFile("C:\\Users\\Hanxi\\Music\\login\\UserNumber.txt");
	UserNumberFile >> UserNumber;
	cout << "��ǰ����" << UserNumber << "���û���" << endl;
}

void WriteUserNumber(int& UserNumber)
{
	ofstream UserNumberFile("C:\\Users\\Hanxi\\Music\\login\\UserNumber.txt");
	UserNumberFile << UserNumber << endl;
	UserNumberFile.close();
	cout << "��ǰ����" << UserNumber << "���û���" << endl;
}

bool CheckUserName(string UserName)
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

bool CheckPassword(string Password)
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

bool SaveUser(string UserName, string Password)
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

bool CheckProfile(string UserName, string Password)
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
		int CheckPepFlag = CheckRepetition(UserName, Password);
		if (CheckPepFlag == 0)
		{
			cout << "�û����Ѵ���!" << endl;
			return 0;
		}
		int SaveFileFlag = SaveUser(UserName, Password);
		if (SaveFileFlag = 1)
		{
			cout << "��ע��ǰ";
			ReadUserNumber(UserNumber);
			cout << "Sign up sucessfully!" << endl;
			UserNumber++;
			WriteUserNumber(UserNumber);
			cout << "��ע���";
			ReadUserNumber(UserNumber);
			
		}
		else cout << "Sign up failed..." << endl;
	}
	return 0;
}

bool CheckRepetition(string UserName, string Password)
{
	ifstream inputUserList;
	int count = 0;
	inputUserList.open("C:\\Users\\Hanxi\\Music\\login\\username.txt"); //���ļ�
	vector<string> User;  //��ʱ�洢�û���
	string temp;
	while (getline(inputUserList,temp))  //���û������ļ���д����ʱvector��
	{
		User.push_back(temp);
		count++;
	}
	//for (int i = 0; i < count; i++)   //�������
	//{
	//	cout << User[i] << endl;
	//}
	inputUserList.close();              //�ر��ļ�
	for (int i = 0; i < count; i++)
	{
		if (UserName == User[i])
			return 0;
	}
	return 1;
}
