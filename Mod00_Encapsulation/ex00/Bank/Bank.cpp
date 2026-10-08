#include "Bank.hpp"

Bank::Bank()
{
	DBG_MSG("Bank constructor called");
	this->_Id = generateRandomId();
	DBG_MSG("Bank id: " + this->_Id);
}

Bank::Bank(const Bank &obj)
{
	DBG_MSG("Bank copy constructor called");
	this->_Id = generateRandomId();
	this->_Clients = obj._Clients;
	this->_InDebt = obj._InDebt;
	for (std::vector<Account>::iterator it = this->_Clients.begin(); it != this->_Clients.end(); ++it)
		it->setBankId(obj._Id, this->_Id);
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
	this->_Clients = obj._Clients;
	this->_InDebt = obj._InDebt;
	for (std::vector<Account>::iterator it = this->_Clients.begin(); it != this->_Clients.end(); ++it)
		it->setBankId(obj._Id, this->_Id);
	return (*this);
}

void	Bank::addClient(const Account &Client, long reqMoney)
{
	std::string	newId = Client.getId(this->_Id);
	std::vector<Account>::const_iterator accountIter;

	for (accountIter = this->_Clients.begin(); accountIter != this->_Clients.end(); ++accountIter)
	{
		if (accountIter->getId(this->_Id) == newId)
			throw BankException("Client already registered");
	}
	this->_Clients.push_back(Client);
	if (reqMoney > MAX_START)
	{
		this->_Clients.back().setValue(MAX_START, this->_Id);
		std::cerr << "Requested value is out of acceptable range client: " + Client.getId(this->_Id) + " will start with a value of 1000000" << std::endl;
	}
}
