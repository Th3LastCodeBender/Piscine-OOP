#include "Bank.hpp"
#include <exception>
#include <linux/limits.h>
#include <sys/types.h>

Bank::Bank(long liquidity, int interest)
{
	DBG_MSG("Bank constructor called");
	if (liquidity < 0)
		throw BankException("Bank liquidity cannot be negative");
	if (interest < 0)
		throw BankException("Bank interest cannot be negative");
	this->_liquidity = liquidity;
	this->_interest = interest;
	this->_nextId = 0;
}

Bank::~Bank()
{
	DBG_MSG("Bank destructor called");
}

Bank::Account	&Bank::findClient(int id)
{
	std::map<int, Account>::iterator it = this->_Clients.find(id);

	if (it == this->_Clients.end())
		throw BankException("Client " + toString(id) + " is not registered to this bank");
	return (it->second);
}

const Bank::Account	&Bank::operator[](int id) const
{
	std::map<int, Account>::const_iterator it = this->_Clients.find(id);

	if (it == this->_Clients.end())
		throw BankException("Client " + toString(id) + " is not registered to this bank");
	return (it->second);
}

int	Bank::createAccount(long initialDeposit)
{
	if (initialDeposit < 0)
		throw BankException("Initial deposit cannot be negative");
	if (initialDeposit > MAX_START)
		throw BankException("Initial deposit exceeds max start amount " + formatMoney(MAX_START));

	int	id = this->_nextId;

	if (!this->_Clients.insert(std::make_pair(id, Account(id, 0))).second)
		throw BankException("Client " + toString(id) + " already registered");
	this->_nextId++;
	if (initialDeposit > 0)
		this->deposit(id, initialDeposit);
	return (id);
}

void	Bank::deleteAccount(int id)
{
	Account& Client = this->findClient(id);

	if (Client._debtInfo.amount > 0)
		throw BankException("The client: " + toString(id) + " you are trying to delete is still in debt\n Settle the debt before erasing the account!\n");
	if (Client._balance < DELETE_FEE)
		throw BankException("The client: " + toString(id) + " you are trying to delete has insufficent liquidity to pay the elimination fee!\n");

	this->_liquidity += Client._balance;
	Client._balance = 0;
	this->_Clients.erase(id);
}

void	Bank::deposit(int id, long amount)
{
	checkAmount(amount, CHK_POSITIVE | CHK_MAX, MAX_START, "Asked deposit amount not valid");

	Account &Client = this->findClient(id);
	long	rateFee = applyRate(amount, this->_interest);

	if (Client._balance + amount < rateFee)
		throw BankException("The Client: " + toString(id) + " balance is too low to pay the deposit fee, gimme more moneyH!\n");
	if (Client._balance + amount > MAX_START)
		throw BankException("Im afraid that would make your balance exceed the maximum allowed value...\n");

	this->_liquidity += rateFee;
	Client._balance += (amount - rateFee);

	std::cout << "Account " << id << " deposited a total of " << formatMoney(amount) << " minus the deposit fee that makes " << formatMoney(amount - rateFee) << std::endl;
}

void	Bank::withdraw(int id, long amount)
{
	Account &Client = this->findClient(id);
	long 	withdrawFee = applyRate(amount, this->_interest);

	if (Client._balance < withdrawFee)
		throw BankException("The Client:" + toString(id) + " tried to withdraw but does not have enough balance to pay the withdrawal fee\noups\n");
	else if (amount + withdrawFee > Client._balance)
		throw BankException("Cannot withdraw more than what you have, and never forget da fees!\n");
	else
	{
		this->_liquidity += withdrawFee;
		if (Client._averageBalance < 20000)
			Client._balance -= (amount + withdrawFee + POOR_FEE);
		else
			Client._balance -= (amount + withdrawFee);
		if (Client._balance < 0)
		{
			Client._debtInfo.amount += (Client._balance * -1);
			Client._balance = 0;
		}
	}

	std::cout << "Account " << id << " withdrew a total of " << formatMoney(amount) << " plus the withdrawal fee that makes " << formatMoney(amount + withdrawFee) << std::endl;
	if (Client._debtInfo.amount > 0)
		std::cout << "We see your debt balance is positive... Better give us back the money, never know when the boss wakes up and feels like increasing rates!\n:]" << std::endl;
}

void	Bank::giveLoan(int id, long amount)
{
	Account	&client = this->findClient(id);

	checkAmount(amount, CHK_POSITIVE | CHK_MAX, MAX_LOAN, "Loan amount");
	checkAmount(amount, CHK_MAX, this->_liquidity, "Bank liquidity check: loan");
	if (client._debtInfo.amount > 0)
		throw BankException("Please settle already existing debts before asking for new ones");

	client._debtInfo.amount = amount + applyRate(amount, this->_interest);
	client._debtInfo.interest = this->_interest;
	client._debtInfo.date = getTimeOfDay();
	client._balance += amount;
	this->_liquidity -= amount;

	std::cout << "Account " << id << " received a loan of " << formatMoney(amount) << " plus the loan interest that makes a debt of " << formatMoney(client._debtInfo.amount) << std::endl;
}

void	Bank::repayLoan(int id, long amount)
{
	Account &Client = this->findClient(id);
	long	debtFee = applyRate(Client._debtInfo.amount, Client._debtInfo.interest);

	if (Client._debtInfo.amount <= 0)
		throw BankException("Client: " + toString(id) + " has no debt balance");
	if (amount <= 0)
		throw BankException("Negative amounts are to accepted");
	if (amount > Client._debtInfo.amount)
		throw BankException("Client: " + toString(id) + " is trying to pay a greater loan than what owes the bank");
	if (Client._balance < amount + debtFee)
		throw BankException("Client: " + toString(id) + " is trying to pay a loan but has not enough funds to pay it");

	Client._debtInfo.amount -= amount;
	Client._balance -= amount + debtFee;
	this->_liquidity += amount;
}

const long	&Bank::getLiquidity() const
{
	return (this->_liquidity);
}

const int	&Bank::getInterest() const
{
	return (this->_interest);
}

std::ostream& operator<<(std::ostream& os, const Bank& bank)
{
	os << "Bank informations:" << std::endl;
	os << "Liquidity: " << formatMoney(bank._liquidity) << std::endl;
	for (std::map<int, Bank::Account>::const_iterator it = bank._Clients.begin(); it != bank._Clients.end(); ++it)
		os << "Account " << it->second << std::endl;
	return (os);
}
