#include "_Head.h"
extern jmp_buf first_jump;
extern jmp_buf second_jump;
extern jmp_buf password_jump;
void Enter()
{
	
	_interface* inter = new _interface();
	Sign* sign = new Sign();
	std::string& choose = inter->FirstChoose();
	sign->AorB(choose);
	sign->Password(choose);
	delete sign;
	delete inter;
}

void Operate()
{
	Reader* re = new Reader();

	re->ReaderOperate();

	delete re;
}


int main()
{
	setjmp(first_jump);
	setjmp(second_jump);
	/*登录操作*/
	Enter();

	/*来自密码修改的返回*/
	setjmp(password_jump);
	/*选择你要做的事情（暂时仅开放读者通道）*/
	Operate();

	return 0;
}
