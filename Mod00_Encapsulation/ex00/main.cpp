#include "Bank/Bank.hpp"

int main(void)
{
	try
	{
		Bank	bank(99900, 5);
		int		a = bank.createAccount(10000);
		int		b = bank.createAccount(10000);

		std::cout << bank << std::endl;

		bank.deposit(a, 40000);
		bank.giveLoan(b, 20000);
		std::cout << bank << std::endl;

		std::cout << "Account " << a << ": " << bank[a] << std::endl;

		try
		{
			bank.giveLoan(a, 10000);
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
		
		try
		{
			bank.repayLoan(b, 21000);
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
