#include "Account/Account.hpp"
#include "Bank/Bank.hpp"
#include "Includes/libs.h"

int main(void)
{
	Bank Banca;
	Account Conto(0, Banca.getId);
}
