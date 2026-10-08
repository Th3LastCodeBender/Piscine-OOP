#ifndef BANK_HPP
# define BANK_HPP

#include "../Includes/libs.h"
#include "../Account/Account.hpp"

struct s_debtInfo
{
	std::string date;
	int		 	interest;
	long 		amount;
};

class Bank
{
	private:

		std::vector<Account>			_Clients;
		std::map<Account, s_debtInfo>	_InDebt;
		std::string						_Id;

	public:

		Bank();
		Bank(const Bank& other);
		~Bank();

		Bank& operator=(const Bank& other);

		void	addClient(const Account &Client, long reqMoney);

		class BankException : public std::runtime_error
		{
			public:
				BankException(const std::string &msg) : std::runtime_error(msg) {}
		};
};

#endif
