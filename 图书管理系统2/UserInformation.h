#pragma once



class UserInformation
{
	friend class Reader;
	friend void PasswordEnterAndCheck(int choose);
public:
	UserInformation() { ; }

	~UserInformation() { ; }
	
private:
	static std::string m_ID;
	static std::string m_Password;

};
