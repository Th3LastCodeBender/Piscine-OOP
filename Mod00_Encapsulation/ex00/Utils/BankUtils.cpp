#include "../Bank/Bank.hpp"

std::string generateRandomId()
{
	std::ifstream				urandom("/dev/urandom", std::ios::binary);
	std::vector<unsigned char>	buf(16);
	std::ostringstream			oss;

	if (!urandom.read(reinterpret_cast<char *>(&buf[0]), 16))
		throw std::runtime_error("Cannot read /dev/urandom");
	for (size_t i = 0; i < 16; ++i)
		oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(buf[i]);
	return (oss.str());
}

long	Bank::updateAverage(Bank::Account &acc, long amount)
{
	long	total;

	total = acc._averageBalance * acc._operations + amount;
	acc._operations++;
	acc._averageBalance = total / acc._operations;
	return (acc._averageBalance);
}
