#include "Utilities.h"
#include <string>

namespace sdds
{
	char Utilities::m_delimiter = '\0';

	void Utilities::setFieldWidth(size_t newWidth)
	{
		this->m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const
	{
		return this->m_widthField;
	}

	std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
	{
		std::string token = "";

		//find the occurence of m_delimiter after the specified position "next_pos"
		size_t occurence = str.find(m_delimiter, next_pos);

		token = str.substr(next_pos, occurence - next_pos);
		std::string s = trimmer(token);

		if (s.length() > 0)
		{
			//update next_pos and more
			next_pos = occurence + 1;

			if (str.length() == 1 || next_pos == 0)
				more = false;
			else
				more = true;

			//set field width
			if (getFieldWidth() < s.length())
				setFieldWidth(s.length());

			return s;
		}
		else
		{
			more = false;
			s = "";
			throw 0;
		}

		return s;
	}

	void Utilities::setDelimiter(char newDelimiter)
	{
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter()
	{
		return m_delimiter;
	}

	std::string Utilities::trimmer(std::string str) const
	{
		std::string trimmed = "";

		if (str.length() > 0)
		{
			auto start = str.find_first_not_of(' ');
			auto end = str.find_last_not_of(' ');

			//trim only if string isn't empty
			if (end >= start)
			{
				trimmed = str.substr(start, (end - start) + 1);
			}
		}
		
		return trimmed;
	}
}