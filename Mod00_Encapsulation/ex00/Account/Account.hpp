#ifndef ACCOUNT_HPP
# define ACCOUNT_HPP

#include "../Includes/libs.h"

class Account
{
	private:

		std::string	bankId;
		std::string	_id;
		long		_value;

	public:

		Account(long givenValue, std::string givenBankId);
		Account(const Account& other);
		~Account();
		
		Account& operator=(const Account& other);
		friend std::ostream& operator<<(std::ostream& os, const Account& acc);

		long		getValue(std::string bankId) const;
		std::string	getId(std::string bankId) const;
		void		setValue(long value, std::string bankId);
		void		setBankId(std::string oldBankId, std::string newBankid);

		class AccountException : public std::runtime_error
		{
			public:
				AccountException(const std::string &msg) : std::runtime_error(msg) {}
		};
};


#endif
