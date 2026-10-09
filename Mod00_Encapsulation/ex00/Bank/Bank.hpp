#ifndef BANK_HPP
# define BANK_HPP

#include "../Includes/libs.h"

struct s_debtInfo
{
	std::string date;
	int		 	interest;
	long 		amount;
};

class Bank
{
	public:

		class Account
		{
			friend class Bank;

			private:

				int			_id;
				long		_balance;
				s_debtInfo	_debtInfo;

				Account(int id, long value);
				Account& operator=(const Account& other);

			public:

				Account(const Account& other);
				~Account();

				const int			&getId() const;
				const long			&getValue() const;
				const s_debtInfo	&getDebt() const;
		};

		class AccountException : public std::runtime_error
		{
			public:
				AccountException(const std::string &msg) : std::runtime_error(msg) {}
		};

	private:

		std::map<int, Account>	_Clients;
		long					_liquidity;
		int						_interest;
		int						_nextId;

		Bank(const Bank& other);
		Bank& operator=(const Bank& other);

		Account	&findClient(int id);

	public:

		Bank(long liquidity, int interest);
		~Bank();

		int		createAccount(long initialDeposit);
		void	deleteAccount(int id);
		void	deposit(int id, long amount);
		void	withdraw(int id, long amount);
		void	giveLoan(int id, long amount);
		void	repayLoan(int id, long amount);

		const long		&getLiquidity() const;
		const int		&getInterest() const;

		const Account	&operator[](int id) const;
		friend std::ostream& operator<<(std::ostream& os, const Bank& bank);

		class BankException : public std::runtime_error
		{
			public:
				BankException(const std::string &msg) : std::runtime_error(msg) {}
		};
};

std::ostream& operator<<(std::ostream& os, const Bank::Account& acc);

#endif
