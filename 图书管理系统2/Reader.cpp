#include"_Head.h"

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
		printf("������������:");
		std::getline(std::cin, first_NewPassword);
		printf("���ٴ����������룺");
		std::getline(std::cin, second_NewPassword);
		if (first_NewPassword == second_NewPassword)
		{
			break;
		}
		printf("�������벻һ�£���������������");
	}
	longjmp(password_jump, 1);

}