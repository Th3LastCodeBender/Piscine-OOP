#include "Bank.hpp"

Bank::Bank()
{
	DBG_MSG("Bank constructor called");
}

Bank::Bank(const Bank &obj)
{
	DBG_MSG("Bank copy constructor called");
	if (this == &obj)
		return;	
}

Bank::~Bank()
{
	DBG_MSG("Bank destructor called");
}

Bank &Bank::operator=(const Bank &obj)
{
	DBG_MSG("Bank copy operator called");
	if (this == &obj)
		return (*this);
	return (*this);
}

std::ostream& operator << (std::ostream& os, const Account& acc)
{
	// os << "[" << acc.getId() << "] - [" << acc.getValue() << "]";
	return (os);
}