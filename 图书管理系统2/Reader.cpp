#include"_Head.h"
#include"SQLHead.h"
#define	SQLSUCCESS(rc) ((rc == SQL_SUCCESS) || (rc == SQL_SUCCESS_WITH_INFO))

void Reader::ReaderOperate() const 
{
	_interface inter;
	inter.ReaderInterface();	
	this->inter->ReaderChoose();
}

void Reader::ChangePassword() const
{
	std::string OldPassword;
	std::string first_NewPassword = "";
	std::string second_NewPassword = "";
	system("cls");
	printf("***ע��***\n����Ϊ6λ��\n\n");
	printf("������ԭʼ���룺");
	while (1)
	{
		std::getline(std::cin, OldPassword);
		if (OldPassword != UserInformation::m_Password)
		{
			printf("������������ԣ�");
		}
		else
		{
			break;
		}
	}
	while (1)
	{
		printf("�����������룺");
		std::getline(std::cin, first_NewPassword);
		/*����û������Ƿ�Ϊ6λ*/
		while (first_NewPassword.length()!=6)
		{
			printf("�����Ϊ6λ�ַ������������룺");
			std::getline(std::cin, first_NewPassword);
		}
		printf("���ٴ����������룺");
		std::getline(std::cin, second_NewPassword);
		if (first_NewPassword == second_NewPassword)
		{
			break;
		}
		printf("�������벻һ�£���������������");
	}
	/***�������ݿ������ӿ�***/
	DatabaseControl PW_con;
	short ret = 0;
	ret = PW_con.PasswordChange(second_NewPassword, PW_con);
	if (!SQLSUCCESS(ret))
	{
		std::cerr << "�޸�����ʧ�ܣ�����ϵ����Ա" << std::endl;
	}
	else
	{
		std::cout << "�޸ĳɹ���" << std::endl;
		UserInformation::m_Password = second_NewPassword;
		Sleep(1000);
	}
	system("cls");
	_interface::autoExit(1,1);

}


void Reader::BookSerch() const
{
	DatabaseControl BS_con;
	std::string BookName;
	std::string BookInformation;
	while (1)
	{
		printf("�����������ѯ��ͼ��ȫ����");
		std::getline(std::cin, BookName);
		/*Ҫʵ�ֲ�����Ҫ�������裺
			1.��������Ҫ��������
			2.ϵͳ��Database�е�ȡ�������Ϣ��������
			3.��system("pause")��ʾ�û���������������û�����������������ٴε�����ѯ����
			4.��Ҫ��exit������һ��Ŀ¼����*/

		_interface::Exit(1, 1, BookName);

		BS_con.SerchBookInformation(BookName, BS_con);
		system("pause");
		system("cls");
	}

}

void Reader::BorrowBook() const
{
	/*ʵ�ֽ��鹦�ܵļ������裺
		1.�û�����ISBN�ţ�ϵͳ��ѯ���鼮��
		2.��ѯʧ�ܷ���ʧ����Ϣ����ѯ�ɹ�ϵͳ���û�ȷ���Ƿ���ø��飻
		3.�û����򷵻ؽ�����棬�û�ȷ����ϵͳ�޸����ݿ���Ϣ�������û����������������û���������
			�޸��鼮״̬��Ϣ����ֹ�����û����ø��鼮���������������ͼ���һ����ֻ��һ����doge��
		4.������ʧ�ܣ��ж��������̲����ش�����Ϣ
		5.����ɹ��򷵻سɹ���Ϣ�����ص��������
		6.���������Ҫ��exit������һ��Ŀ¼����*/
	DatabaseControl borrow_con;
	std::string ISBN;
	while (1)
	{
		printf("���������������ISBN�ţ�");
		std::getline(std::cin, ISBN);
		std::string BookName;
		BOOL bl = 0;
		bl = borrow_con.Borrow(ISBN, borrow_con);
		if (0 ==bl)
		{
			continue;
		}
		
	}


}