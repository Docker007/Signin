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
bool CheckRepetition(string UserName);//����û����Ƿ��ظ�
bool CheckSigninPsd(string UserName, string Password); //����¼ʱ������ȷ�� 

int main()	                                        //������
{
	int Select;
	string UserName;
	string Password;
	cout << "1.ע��." << endl;                   //����ѡ��
	cout << "2.��¼." << endl;
	cout << "3.�˳�." << endl;
	cout << "ѡ��һ������: " << endl;
	cin >> Select;
	getchar();
	switch (Select)
	{
	case 1:
	{
		cout << "�����û���: " << endl;
		getline(cin, UserName);
		cout << "��������: " << endl;
		getline(cin, Password);
		CheckProfile(UserName, Password);
		break;
	}
	case 2: 
	{
		cout << "�����û���: ";
		getline(cin, UserName);
		cout << "��������: ";
		getline(cin, Password);
		int flag = CheckSigninPsd(UserName, Password);
		if (flag == 1)
			cout << "��¼�ɹ�." << endl;
		else if(flag == 0)
			cout << "��¼ʧ��" << endl;
		break;
	}
	case 3:return 0;
	default:
		cout << "��������У������ɡ�����" << endl; break;
	}
	system("pause");
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
		cout << "�û������Ϸ�!" << endl;
	}
	else if (CheckPassword(Password) == 0)
	{
		cout << "���벻�Ϸ�!" << endl;
	}
	else
	{
		int CheckPepFlag = CheckRepetition(UserName);
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
			cout << "ע��ɹ�!" << endl;
			UserNumber++;
			WriteUserNumber(UserNumber);
			cout << "��ע���";
			ReadUserNumber(UserNumber);
			
		}
		else cout << "ע��ʧ��" << endl;
	}
	return 0;
}

bool CheckRepetition(string UserName)
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

bool CheckSigninPsd(string UserName, string Password)
{
	int count = 0;
	int flag = 0;           //ID�Ƿ���ע��ı�־
	int countUser = 0;
	int countPsd = 0;
	ifstream inputUserList;
	ifstream inputPsdList;
	inputPsdList.open("C:\\Users\\Hanxi\\Music\\login\\password.txt");
	inputUserList.open("C:\\Users\\Hanxi\\Music\\login\\username.txt");
	vector<string> User;
	vector<string> Psd;
	string tempUser;
	string tempPsd;
	while (getline(inputUserList, tempUser))
	{
		User.push_back(tempUser);
		countUser++;
	}
	while (getline(inputPsdList, tempPsd))
	{
		Psd.push_back(tempPsd);
		countPsd++;
	}
	inputUserList.close();
	inputPsdList.close();
	for (int i = 0; i < countUser; i++)
	{
		if (UserName == User[i])
		{
			count = i;
			flag = 1;
			break;
		}
	}
	if (flag == 0)
	{
		cout << "����δע�ᣡ" << endl;
		return 0;
	}
	if (Password != Psd[count])
	{
		cout << "�������" << endl;
		return 0;
	}
	return 1;
}
