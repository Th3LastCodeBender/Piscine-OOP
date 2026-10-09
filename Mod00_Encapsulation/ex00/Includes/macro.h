#ifndef MACRO_H
#define 	MACRO_H

#define MAX_START 2000000000
#define MAX_LOAN 1000000
#define BANK_FEE 500
#define DELETE_FEE 5000

#if defined(DEBUG) && DEBUG
  #define DBG_MSG(msg) (std::cout << (msg) << std::endl)
#else
  #define DBG_MSG(msg) ((void)0)
#endif

#endif