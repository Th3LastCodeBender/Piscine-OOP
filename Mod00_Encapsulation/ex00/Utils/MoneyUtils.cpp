#include "../Includes/libs.h"

//Itoa per prendere un valore in palanche e convertirlo in stringa
std::string formatMoney(long cents)
{
	std::ostringstream	oss;
	unsigned long		abs;

	if (cents < 0)
	{
		oss << '-';
		abs = -static_cast<unsigned long>(cents);
	}
	else
		abs = static_cast<unsigned long>(cents);
	oss << abs / 100 << '.' << std::setw(2) << std::setfill('0') << abs % 100;
	return (oss.str());
}

//Atoi ma con il base in centesimi che sto usando per i valori dei conti
long parseMoney(const std::string &str)
{
	size_t	i = 0;
	bool	negative = false;
	long	units = 0;
	long	cents = 0;
	int		decimals = 0;

	if (i < str.size() && (str[i] == '-' || str[i] == '+'))
		negative = (str[i++] == '-');
	if (i >= str.size() || !std::isdigit(str[i]))
		throw std::invalid_argument("Invalid amount: \"" + str + "\"");
	while (i < str.size() && std::isdigit(str[i]))
	{
		if (units > (LONG_MAX / 100 - (str[i] - '0')) / 10)
			throw std::out_of_range("Amount too large: \"" + str + "\"");
		units = units * 10 + (str[i++] - '0');
	}
	if (i < str.size() && (str[i] == '.' || str[i] == ','))
	{
		i++;
		while (i < str.size() && std::isdigit(str[i]) && decimals < 2)
		{
			cents = cents * 10 + (str[i++] - '0');
			decimals++;
		}
		if (decimals == 0)
			throw std::invalid_argument("Invalid amount: \"" + str + "\"");
		if (decimals == 1)
			cents *= 10;
	}
	if (i != str.size())
		throw std::invalid_argument("Invalid amount: \"" + str + "\"");
	if (units > (LONG_MAX - cents) / 100)
		throw std::out_of_range("Amount too large: \"" + str + "\"");
	return (negative ? -(units * 100 + cents) : units * 100 + cents);
}

//Calcolo di interesse passato in percentuale convertito in rateBP, come fanno le banche vere MUHUHAHAHAHA
long applyRate(long cents, int rate)
{
	long	product;
	long	rateBp;

	if (rate != 0 && (cents > LONG_MAX / rate || cents < LONG_MIN / rate))
		throw std::out_of_range("Rate calculation overflow");
	rateBp = rate * 100;
	product = cents * rateBp;
	if (product >= 0)
		return ((product + 5000) / 10000);
	return ((product - 5000) / 10000);
}

//Controlla amount in base ai flag passati, lancia eccexion al primo controllo fallito
void	checkAmount(long amount, int flags, long limit, const std::string &label)
{
	if ((flags & CHK_POSITIVE) && amount <= 0)
		throw std::invalid_argument(label + " must be positive");
	if ((flags & CHK_NOT_NEG) && amount < 0)
		throw std::invalid_argument(label + " cannot be negative");
	if ((flags & CHK_MAX) && amount > limit)
		throw std::out_of_range(label + " exceeds limit " + formatMoney(limit));
}
