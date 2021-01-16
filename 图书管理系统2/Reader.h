#pragma once

class Reader 
{
public:
	void ReaderOperate() const;

	void ChangePassword() const;

	void BookSerch() const;

	void BorrowBook() const;


private:
	_interface* inter;

	
};
