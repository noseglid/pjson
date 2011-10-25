#include "pjtestframework.hpp"

#include <vector>

static int testn    = 0;
static int successn = 0;

static std::vector<std::string> failed;
typedef std::vector<std::string>::const_iterator failiter;

void
pjassert_throw_fail(const char *fnc, const unsigned int line)
{
	std::cout << "!";
	std::stringstream ss;
	ss << "Failed test (#" << testn << ") - ";
	ss << "[" << fnc << ":" << line << "]" << std::endl;
	ss << "> Did not throw expected exception." << std::endl;
	failed.push_back(ss.str());
}

void
pjassert_success()
{
	successn++;
	std::cout << ".";
}

void
__pjtest()
{
	if (testn++ % 40 == 0) std::cout << std::endl;
}

int
__gettestn()
{
	return testn;
}

std::vector<std::string>&
__getfailed()
{
	return failed;
}

std::string
pjreport()
{
	std::stringstream ss;
	ss << std::endl;

	for (failiter it = failed.begin(); it != failed.end(); it++) {
		ss << *it << std::endl;
	}

	ss.precision(2);
	ss << "Result: " << successn << "/" << testn << " asserts passed "
	   << "[" << std::fixed << 100*successn/((testn == 0) ? 1 : testn) << "%]."
	   << std::endl << std::endl;

	failed.clear();
	testn    = 0;
	successn = 0;

	return ss.str();
}

