#ifndef LIBS_H
# define LIBS_H

// IWYU pragma: begin_exports
#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <climits>
#include <cctype>
#include <sstream>
#include <stdexcept>
# include <fstream>
# include <iomanip>
# include <map>
# include <ctime>
# include <sys/time.h>

// ---------UTILS---------

#include "../Utils/StringUtils.hpp"
#include "../Includes/macro.h"

std::string generateRandomId();
std::string getTimeOfDay();
std::string formatMoney(long cents);
long        parseMoney(const std::string &str);
long        applyRate(long cents, int rateBp);

enum e_amountCheck
{
	CHK_POSITIVE	= 1 << 0,	// amount > 0
	CHK_NOT_NEG		= 1 << 1,	// amount >= 0
	CHK_MAX			= 1 << 2	// amount <= limit
};

void        checkAmount(long amount, int flags, long limit = 0, const std::string &label = "Amount");

// IWYU pragma: end_exports

#endif
