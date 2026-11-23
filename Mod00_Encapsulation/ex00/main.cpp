#include "Bank/Bank.hpp"

static int	g_ko = 0;

static void	check(const std::string &label, long got, long expected)
{
	if (got == expected)
		std::cout << "[OK] " << label << std::endl;
	else
	{
		std::cout << "[KO] " << label << " -> got " << formatMoney(got)
			<< ", expected " << formatMoney(expected) << std::endl;
		g_ko++;
	}
}

static void	title(const std::string &name)
{
	std::cout << std::endl << "===== " << name << " =====" << std::endl;
}

// Scenario originale: creazione, deposito, prestiti, cancellazione
static void	testBaseScenario()
{
	title("Base scenario");

	Bank	bank(99900, 5);
	int		a = bank.createAccount(10000);
	int		b = bank.createAccount(10000);

	std::cout << bank << std::endl;

	bank.deposit(a, 40000);
	bank.giveLoan(b, 20000);
	std::cout << bank << std::endl;

	std::cout << "Account " << a << ": " << bank[a] << std::endl;

	try { bank.giveLoan(a, 10000); }
	catch (const std::exception &e) { std::cerr << "Error: " << e.what() << std::endl; }

	try { bank.deleteAccount(b); }
	catch (const std::exception &e) { std::cerr << "Error: " << e.what() << std::endl; }

	try { bank.repayLoan(b, 21000); }
	catch (const std::exception &e) { std::cerr << "Error: " << e.what() << std::endl; }

	try { bank.deleteAccount(b); }
	catch (const std::exception &e) { std::cerr << "Error: " << e.what() << std::endl; }

	std::cout << bank << std::endl;

	try { std::cout << bank[b] << std::endl; }
	catch (const std::exception &e) { std::cerr << "Error: " << e.what() << std::endl; }
}

// Media alta (create 1000.00 -> saldo 950.00, media 475.00): niente POOR_FEE
static void	testRichNoPoorFee()
{
	title("Average: rich account, no POOR_FEE");

	Bank	bank(1000000, 5);
	int		id = bank.createAccount(100000);

	bank.withdraw(id, 1000);
	// 950.00 - 10.00 - 0.50 fee
	check("withdraw without POOR_FEE", bank[id].getValue(), 93950);
}

// Media bassa (create 100.00 -> saldo 95.00, media 47.50): POOR_FEE applicata
static void	testPoorFeeApplied()
{
	title("Average: poor account, POOR_FEE applied");

	Bank	bank(1000000, 5);
	int		id = bank.createAccount(10000);

	bank.withdraw(id, 1000);
	// 95.00 - 10.00 - 0.50 fee - 50.00 POOR_FEE
	check("withdraw with POOR_FEE", bank[id].getValue(), 3450);
}

// Un deposito grosso alza la media sopra la soglia
static void	testDepositRaisesAverage()
{
	title("Average: deposit raises average");

	Bank	bank(1000000, 5);
	int		id = bank.createAccount(10000);

	bank.deposit(id, 100000);
	// saldo 1045.00, media (47.50 * 2 + 1045.00) / 3 = 380.00
	bank.withdraw(id, 1000);
	check("no POOR_FEE after big deposit", bank[id].getValue(), 103450);
}

// Prelievi ripetuti abbassano la media finche' scatta la POOR_FEE
static void	testWithdrawLowersAverage()
{
	title("Average: withdrawals lower average");

	Bank	bank(1000000, 5);
	int		id = bank.createAccount(100000);

	bank.withdraw(id, 80000);
	check("after 800.00 withdraw", bank[id].getValue(), 11000);
	for (int i = 0; i < 4; i++)
		bank.withdraw(id, 1000);
	// media scesa a 199.27 (< 200.00)
	check("still no POOR_FEE (average >= 200.00)", bank[id].getValue(), 6800);
	bank.withdraw(id, 1000);
	check("POOR_FEE once average < 200.00", bank[id].getValue(), 750);
}

// Scelta di design: il prestito entra nella giacenza e alza la media
static void	testLoanRaisesAverage()
{
	title("Average: loan counts in average (design choice)");

	Bank	bank(1000000, 5);
	int		id = bank.createAccount(10000);

	bank.giveLoan(id, 100000);
	// saldo 1095.00, media (47.50 * 2 + 1095.00) / 3 = 396.66
	bank.withdraw(id, 1000);
	check("no POOR_FEE after loan", bank[id].getValue(), 108450);
}

// La POOR_FEE non dovrebbe mai generare debito
static void	testPoorFeeNoDebt()
{
	title("POOR_FEE must not create debt");

	Bank	bank(1000000, 5);
	int		id = bank.createAccount(10000);

	// saldo 95.00: 50.00 + 2.50 fee passa il controllo, ma + 50.00 POOR_FEE no
	try { bank.withdraw(id, 5000); }
	catch (const std::exception &e) { std::cerr << "Error: " << e.what() << std::endl; }
	check("no debt created by POOR_FEE", bank[id].getDebt().amount, 0);
	check("balance untouched", bank[id].getValue(), 9500);
}

int	main(void)
{
	void	(*tests[])() = {
		testBaseScenario,
		testRichNoPoorFee,
		testPoorFeeApplied,
		testDepositRaisesAverage,
		testWithdrawLowersAverage,
		testLoanRaisesAverage,
		testPoorFeeNoDebt
	};

	for (size_t i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
	{
		try
		{
			tests[i]();
		}
		catch (const std::exception &e)
		{
			std::cerr << "Unexpected error: " << e.what() << std::endl;
			g_ko++;
		}
	}
	std::cout << std::endl << (g_ko ? "Some tests failed: " : "All tests passed")
		<< (g_ko ? toString(g_ko) : "") << std::endl;
	return (g_ko != 0);
}
