#pragma once

class _interface
{
public:
	std::string& FirstChoose();

	void Reader_Sign_Interface();
	
	void Administrator_Sign_Interface();
	
	/*读者用户界面*/
	void ReaderInterface();
	
	/*管理员用户界面*/
	void AdministratorInterface();

	/*登陆后的用户选择*/
	void ReaderChoose();
	/*登陆后的用户选择*/
	void AdministratorChoose();

	/*返回上一级目录函数*/
	/*****我希望能够实现不分大小写的功能，寒假想想办法*****/
	static void Exit(short, std::string str);		//用于读者管理员界面选择退出
	static void Exit(short, short, std::string str);//用于用户登录界面退出
	static void Exit(short, short, short, std::string str);


};