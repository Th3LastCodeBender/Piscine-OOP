#ifndef MACRO_H
#define 	MACRO_H

#define MAX_START 1000000
#if defined(DEBUG) && DEBUG
  #define DBG_MSG(msg) (std::cout << (msg) << std::endl)
#else
  #define DBG_MSG(msg) ((void)0)
#endif

#endif