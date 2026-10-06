#ifndef LIBS_H
# define LIBS_H

#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <climits>

#if defined(DEBUG) && DEBUG
  #define DBG_MSG(msg) (std::cout << (msg) << std::endl)
#else
  #define DBG_MSG(msg) ((void)0)
#endif

#endif
