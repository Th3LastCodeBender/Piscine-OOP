#include "Bank/Bank.hpp"

int main(void)
{
	try
	{
		Bank	bank(99900, 500);
		int		a = bank.createAccount(10000);
		int		b = bank.createAccount(10000);

		std::cout << bank << std::endl;

		bank.deposit(a, 40000);
		bank.giveLoan(b, 20000);
		std::cout << bank << std::endl;

		std::cout << "Account " << a << ": " << bank[a] << std::endl;

		try
		{
			bank.giveLoan(a, 999999999);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}

		try
		{
			bank.deleteAccount(b);
		}
		catch (const std::exception &e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}

		bank.repayLoan(b, 21000);
		bank.deleteAccount(b);
		std::cout << bank << std::endl;

		std::cout << bank[b] << std::endl;
	}
	catch (const std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
