#include <iostream>
#include<stdio.h>
#include"_Head.h"
#include "Sign.h"
#include "_interface.h"
#include "DatabaseControl.h"
#include"SQLHead.h"
#include<string>
#include"UserInformation.h"

void Sign::AorB(std::string& choose)
{
	_interface face;
	/*ѡ����ߵ�¼���ǹ���Ա��¼*/
	while (1)
	{
		
		if (choose.find("A") != std::string::npos)
		{
			face.Reader_Sign_Interface();
			break;
		}
		else if (choose.find("B") != std::string::npos)
		{
			face.Administrator_Sign_Interface();
			break;
		}
		else
		{
			std::cout << "��ѡ��AB����һ����" << std::endl;
			std::cin >> choose;
			/*��ջ�����*/
			char c;
			while (c = getchar() != '\n') {}

		}

	}
}

/*�û�����ж�*/
short ClientJudgment(std::string& choose)
{
	if (choose.find("A") != std::string::npos)
	{
		/*����*/
		return 1;
	}
	else if (choose.find("B") != std::string::npos)
	{
		/*����Ա*/
		return 2;
	}
}

/*�����������жϺ���*/
void PasswordEnterAndCheck(int choose)
{
	char ID[100] = "";
	char password[100] = "";
	short i = 0, j = 0;
	DatabaseControl con;
	//Sign sign;
	switch (choose)
	{
	case 1:
	{
		printf("ѧ�ţ�");
		char* Realpassword = NULL;
		do
		{
			gets_s(ID);			//����10λѧ��
			do
			{
				/*��⵽�û�����exit�򷵻���һ��Ŀ¼*/
				_interface::Exit(1, ID);
			} while (0);
			/*��ȡ����*/
			Realpassword = con.PasswordSerch(choose, ID, con);
			if (Realpassword[0] != NULL)
			{
				break;
			}
			else
			{
				printf("����������ѧ�ţ�");
			}

		} while (1);
		printf("���룺");
		do
		{
			gets_s(password);	//����6λ����
			do
			{
				/*��⵽�û�����exit�򷵻���һ��Ŀ¼*/
				_interface::Exit(1, password);
			} while (0);
			/*����˶�*/
			int cnt = 0;
			for (int i = 0; i < 6;++i)
			{
				if (password[i] == Realpassword[i])
				{
					++cnt;
				}
			}
			if (cnt == 6 && password[6] == NULL)
			{
				printf("��½�ɹ���");
				delete Realpassword;
				//_interface inter;
				UserInformation::m_ID = ID;
				UserInformation::m_Password = password;
				Sleep(1000);
				system("cls");
				//inter.ReaderInterface();
				break;
			}
			else
			{
				printf("�������\n�������������룺");
			}
		} while (1);

		break;
	}
	case 2:
	{
		printf("���ţ�");
		int chances = 3;
		char* Realpassword = NULL;
		do
		{
			gets_s(ID);			//����10λ����
			do
			{
				/*��⵽�û�����exit�򷵻���һ��Ŀ¼*/
				_interface::Exit(1, ID);
			} while (0);
			/*��ȡ����*/
			Realpassword = con.PasswordSerch(choose, ID, con);
			if (Realpassword[0] != NULL)
			{
				break;
			}
			else
			{
				printf("���������빤�ţ�");
			}
		} while (1);
		printf("���룺");		//����Ա���������жϲ��ṩexit������һ������
		do
		{
			gets_s(password);	//����6λ����
			/*����˶�*/
			int cnt = 0;
			for (int i = 0; i < 6;++i)
			{
				if (password[i] == Realpassword[i])
				{
					++cnt;
				}
			}
			if (cnt == 6 && password[6] == NULL && chances > 0)
			{
				printf("��½�ɹ���");
				delete[]Realpassword;
				//_interface inter;
				UserInformation::m_ID = ID;
				UserInformation::m_Password = password;
				Sleep(1000);
				system("cls");
				//inter.AdministratorInterface();
				break;
			}
			else
			{
				--chances;
				if (0 == chances)
				{
					std::cerr << "�����������л��ᣬ������ϵͳ" << std::endl;
					Sleep(1000);
					exit(-1);
				}
				printf("�������������%d�λ���\n�������������룺",chances);
			}
		} while (1);
	}
	}

}

/*�����ж�������*/
void Sign::Password(std::string& choose)
{
	PasswordEnterAndCheck(ClientJudgment(choose));

}
