#pragma once



class UserInformation
{
	friend short ClientJudgment(std::string& choose);
	friend class Reader;
	friend void PasswordEnterAndCheck(int choose);
	friend class DatabaseControl;
public:
	UserInformation() { ; }

	~UserInformation() { ; }
	
private:
	static std::string m_ID;
	static std::string m_Password;
	static short ReOrAdmin;

};
