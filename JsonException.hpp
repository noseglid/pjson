#ifndef _JSONEXCEPTION_H_
#define _JSONEXCEPTION_H_

namespace Json {
	class Exception
	{
		private:
			const char *cause;

		public:
			Exception(const char *cause)
			{
				this->cause = cause;
			};
			const char *what() const throw()
			{
				return cause;
			};
	};
}

#endif
