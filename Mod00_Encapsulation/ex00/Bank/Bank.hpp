#ifndef BANK_HPP
# define BANK_HPP

#include "../Includes/libs.h"
#include "../Account/Account.hpp"

class Bank
{
	private:

		std::vector<Account *> Clients;

	public:

		Bank();
		Bank(const Bank& other);
		~Bank();
		Bank& operator=(const Bank& other);

		class BankException : public std::exception
		{
			private:
				std::string _msg;
			public:
				BankException(std::string msg) : _msg(msg) {};
				virtual const char *what() const throw() {return (_msg.c_str());}
				~BankException() throw() {};
		};
};

std::ostream& operator<<(std::ostream& os, const Account& acc);

#endif
