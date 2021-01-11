#include "_Head.h"
extern jmp_buf first_jump;
extern jmp_buf second_jump;
void Enter()
{
	_interface inter;
	Sign* sign = new Sign();
	setjmp(first_jump);
	setjmp(second_jump);/*这里出现了一个bug，用户操作界面exit返回后再次登录就出发断点，待解决1月11日*/
	std::string& choose = inter.FirstChoose();
	sign->AorB(choose);
	sign->Password(choose);
	delete sign;
}

void Operate()
{
	Reader* re = new Reader();
	/*来自密码修改的返回*/
	extern jmp_buf password_jump;
	setjmp(password_jump);
	re->ReaderOperate();

	delete re;
}


int main()
{
	/*登录操作*/
	Enter();
	
	/*选择你要做的事情（暂时仅开放读者通道）*/
	Operate();

	return 0;
}
