#include "Bank.hpp"

Bank::Account::Account(int id, long value)
{
	DBG_MSG("Account constructor called");
	this->_id = id;
	this->_balance = value;
	this->_debtInfo.amount = 0;
	this->_debtInfo.interest = 0;
}

Bank::Account::Account(const Account &obj)
{
	DBG_MSG("Account copy constructor called");
	this->_id = obj._id;
	this->_balance = obj._balance;
	this->_debtInfo = obj._debtInfo;
}

Bank::Account::~Account()
{
	DBG_MSG("Account destructor called");
}

const int	&Bank::Account::getId() const
{
	return (this->_id);
}

const long	&Bank::Account::getValue() const
{
	return (this->_balance);
}

const s_debtInfo	&Bank::Account::getDebt() const
{
	return (this->_debtInfo);
}

std::ostream& operator<<(std::ostream& os, const Bank::Account& acc)
{
	os << "id: [" << acc.getId() << "] - value: [" << formatMoney(acc.getValue()) << "]";
	if (acc.getDebt().amount > 0)
		os << " - debt: [" << formatMoney(acc.getDebt().amount) << " since " << acc.getDebt().date << "]";
	return (os);
}
