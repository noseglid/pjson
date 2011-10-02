#ifndef _JSONEXCEPTION_H_
#define _JSONEXCEPTION_H_

namespace Json {

	/// Thrown when any JSON related error occured.
	/**
	 * A class to represent any exception which occured due to a JSON operation.
	 * This may be because JSON string being parsed is invalid (such as lack of
	 * enclosing characters or similar).
	 */
	class Exception
	{
		private:
			const char *cause;

		public:
			/**
			 * Initializes an exception which may be thrown.
			 *
			 * @param cause Description of what caused the exception.
			 */
			Exception(const char *cause)
			{
				this->cause = cause;
			};

			/**
			 * Fetches a short description of what caused this exception.
			 *
			 * @return Desciption of exception cause.
			 */
			const char *what() const throw()
			{
				return cause;
			};
	};
}

#endif
