#ifndef ACCOUNT_HPP
# define ACCOUNT_HPP

#include "../Includes/libs.h"

class Account
{
	private:

		int		_id;
		long	_value;

	public:

		Account(int id, long value);
		Account(const Account& other);
		~Account();
		Account& operator=(const Account& other);

		long	getValue() const;
		int		getId() const;

		class AccountException : public std::exception
		{
			private:
				std::string _msg;
			public:
				AccountException(std::string msg) : _msg(msg) {};
				virtual const char *what() const throw() {return (_msg.c_str());}
				~AccountException() throw() {};
		};
};

std::ostream& operator<<(std::ostream& os, const Account& acc);

#endif
