#ifndef __PJTESTFRAMEWORK_HPP__
#define __PJTESTFRAMEWORK_HPP__

#include <vector>
#include <string>
#include <sstream>
#include <iostream>

static int testn    = 0;
static int successn = 0;

std::vector<std::string> failed;

typedef std::vector<std::string>::const_iterator failiter;

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

template <class T1, class T2> static void
pjassert_fail(T1 x, T2 y, const char *fnc, unsigned int line)
{
	std::cout << "!";
	std::stringstream ss;
	ss << "Failed test (#" << testn << ") - ";
	ss << "[" << fnc << ":" << line << "]" << std::endl;
	ss << ">    " << x << std::endl;
	ss << ":    " << y << std::endl;
	failed.push_back(ss.str());
}

static void
pjassert_throw_fail(const char *fnc, const unsigned int line)
{
	std::cout << "!";
	std::stringstream ss;
	ss << "Failed test (#" << testn << ") - ";
	ss << "[" << fnc << ":" << line << "]" << std::endl;
	ss << "> Did not throw expected exception." << std::endl;
	failed.push_back(ss.str());
}

static void
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

template <class T1, class T2> void
pjassert(T1 x, T2 y, const char *fnc, unsigned int line)
{
	if (x == y) pjassert_success();
	else pjassert_fail(x, y, fnc, line);
}

template <> void
pjassert(double x, double y, const char *fnc, unsigned int line)
{
	double delta = 0.001;
	double low  = x - delta;
	double high = y + delta;
	if(y >= low && y <= high) pjassert_success();
	else pjassert_fail(x, y, fnc, line);
}

std::string
pjreport()
{
	std::stringstream ss;
	ss << std::endl << std::endl;

	for (failiter it = failed.begin(); it != failed.end(); it++) {
		ss << *it << std::endl;
	}

	ss.precision(2);
	ss << "Result: " << successn << "/" << testn << " asserts passed "
	   << "[" << std::fixed << 100*successn/testn << "%]."
	   << std::endl << std::endl;

	return ss.str();
}

#endif
