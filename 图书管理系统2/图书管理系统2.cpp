#include "_Head.h"
extern jmp_buf home_page_jump;
extern jmp_buf secondary_inerface_jump;
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
	setjmp(home_page_jump);
	/*登录操作*/
	Enter();

	/*来自密码修改的返回*/
	setjmp(secondary_inerface_jump);
	/*来自图书查询的修改*/
	/*选择你要做的事情（暂时仅开放读者通道）*/
	Operate();

	return 0;
}


