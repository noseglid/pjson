#ifndef __PJTESTFRAMEWORK_HPP__
#define __PJTESTFRAMEWORK_HPP__

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

#define TEST_ASSERT(x, y) \
	do { \
		__pjtest(); \
		pjassert(x, y, __FUNCTION__, __LINE__); \
	} while (0)

#define TEST_THROWS(stmt, excp) \
	do { \
		__pjtest(); \
		bool caught = false; \
		try { stmt; } \
		catch (excp) { pjassert_success(); caught = true; } \
		if (!caught) pjassert_throw_fail(__FUNCTION__, __LINE__); \
	} while(0)

std::string
readfile(const char *file);

void
pjassert_throw_fail(const char *fnc, const unsigned int line);

void
pjassert_success();

void
__pjtest();

std::string
pjreport();

int
__gettestn();

std::vector<std::string>&
__getfailed();

#endif

template <class T1, class T2> void
pjassert_fail(T1 x, T2 y, const char *fnc, unsigned int line)
{
	std::cout << "!";
	std::stringstream ss;
	ss << "Failed test (#" << __gettestn() << ") - ";
	ss << "[" << fnc << ":" << line << "]" << std::endl;
	ss << ">    " << x << std::endl;
	ss << ":    " << y << std::endl;
	__getfailed().push_back(ss.str());
}

template <class T1, class T2> void
pjassert(T1 x, T2 y, const char *fnc, unsigned int line)
{
	if (x == y) pjassert_success();
	else pjassert_fail(x, y, fnc, line);
}
