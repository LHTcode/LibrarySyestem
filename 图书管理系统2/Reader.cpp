#include"_Head.h"
#include"SQLHead.h"
#define	SQLSUCCESS(rc) ((rc == SQL_SUCCESS) || (rc == SQL_SUCCESS_WITH_INFO))

void Reader::ReaderOperate()
{
	_interface inter;
	inter.ReaderInterface();	
	this->inter->ReaderChoose();
}

jmp_buf password_jump;
void Reader::ChangePassword()
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
	longjmp(password_jump, 1);

}
/****1��12���޸ģ�
�������תbug���⣬����˶��߶˵������޸�ģ��
��һ������ɹ���Ա�˵������޸�ģ�飬����ɶ��߲�ѯͼ��ģ��****/