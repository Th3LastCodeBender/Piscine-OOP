#include "../Includes/libs.h"

std::string getTimeOfDay()
{
	struct timeval	tv;
	struct tm		*tm_info;
	char			buf[32];
	std::ostringstream	oss;

	if (gettimeofday(&tv, NULL) == -1)
		throw std::runtime_error("Cannot get time of day");
	tm_info = localtime(&tv.tv_sec);
	if (!tm_info)
		throw std::runtime_error("Cannot convert time");
	strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", tm_info);
	oss << buf << "." << std::setw(3) << std::setfill('0') << tv.tv_usec / 1000;
	return (oss.str());
}
