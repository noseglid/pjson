#ifndef _PJSONEXCEPTION_H_
#define _PJSONEXCEPTION_H_

#include <string>

using namespace std;

class PJsonException: public exception
{
	private:
		const char *cause;

	public:
		PJsonException(const char *cause)
		{
			this->cause = cause;
		};
		const char *what() const throw()
		{
			return cause;
		};
};

#endif
