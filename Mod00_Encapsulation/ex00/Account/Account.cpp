#include "Account.hpp"

Account::Account(long givenValue, std::string givenBankId)
{
	DBG_MSG("Account constructor called");
	this->_id = generateRandomId();
	this->_value = givenValue;
	this->bankId = givenBankId;
}

Account::Account(const Account &obj)
{
	DBG_MSG("Account copy constructor called");
	if (this == &obj)
	{
		DBG_MSG("Me = me huh?");
		return;
	}
	this->_id = obj._id;
	this->_value = obj._value;
	this->bankId = obj.bankId;
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
	this->bankId = obj.bankId;

	return (*this);
}

std::string	Account::getId(std::string bankId) const
{
	if (bankId != this->bankId)
		throw AccountException("Unauthorized");
	return (this->_id);
}

long	Account::getValue(std::string bankId) const
{
	if (bankId != this->bankId)
		throw AccountException("Unauthorized");
	return (this->_value);
}

void	Account::setValue(long value, std::string bankId)
{
	if (bankId != this->bankId)
		throw AccountException("Unauthorized");
	this->_value += value;
}

std::ostream& operator<<(std::ostream& os, const Account& acc)
{
	os << "id: [" << acc._id << "] - value: [" << acc._value << "]";
	return (os);
}

void	Account::setBankId(std::string oldBankId, std::string newBankId)
{
	if (oldBankId != this->bankId)
		throw AccountException("Unauthorized");
	this->bankId = newBankId;
}
