#ifndef STRINGUTILS_HPP
# define STRINGUTILS_HPP

# include <string>
# include <sstream>

template <typename T>
std::string toString(const T& value)
{
	std::ostringstream oss;
	oss << value;
	return (oss.str());
}

#endif
