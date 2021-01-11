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
	printf("请输入原始密码：");
	while (1)
	{
		std::getline(std::cin, OldPassword);
		if (OldPassword != UserInformation::m_Password)
		{
			printf("密码错误！请重试：");
		}
		else
		{
			break;
		}
	}
	
	while (1)
	{
		printf("请输入新密码:");
		std::getline(std::cin, first_NewPassword);
		printf("请再次输入新密码：");
		std::getline(std::cin, second_NewPassword);
		if (first_NewPassword == second_NewPassword)
		{
			break;
		}
		printf("两次密码不一致！请重新设置密码");
	}
	longjmp(password_jump, 1);

}