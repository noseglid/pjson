#include "pjtestframework.hpp"

#include <vector>
#include <fstream>
#include <sstream>

static int testn    = 0;
static int successn = 0;

static std::vector<std::string> failed;
typedef std::vector<std::string>::const_iterator failiter;

std::string
readfile(const char *file)
{
	std::ifstream is;
	is.open(file, std::ios::binary);

	if (!is.good()) {
		std::cout << "Could not open file: " << file << std::endl;
		return std::string();
	}

	// get length of file:
	is.seekg(0, std::ios::end);
	int length = is.tellg();
	is.seekg(0, std::ios::beg);

	// allocate memory:
	char buffer[length];

	// read data as a block:
	is.read(buffer, length);
	is.close();

	return std::string(buffer, length);
}

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

