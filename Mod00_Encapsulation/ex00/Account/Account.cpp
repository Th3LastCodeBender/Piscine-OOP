#include "Account.hpp"

Account::Account(int id, long value)
{
	if (id < 0 || id > INT_MAX)
		throw AccountException("Given number id exeeds general Accounts limits");
	DBG_MSG("Account constructor called");
}

Account::Account(const Account &obj)
{
	DBG_MSG("Account copy constructor called");
	if (this == &obj)
	{
		DBG_MSG("Yes\n 2 = 2\n yes");
		return;
	}
}

Account::~Account()
{
	DBG_MSG("Account destructor called");
}	

Account &Account::operator=(const Account &obj)
{
	DBG_MSG("Account copy operator called");

	if (this == &obj)
		return(*this);

	this->_id = obj._id;
	this->_value = obj._value;

	return (*this);
}

std::ostream& operator << (std::ostream& os, const Account& acc)
{
	os << "[" << acc.getId() << "] - [" << acc.getValue() << "]";
	return (os);
}
