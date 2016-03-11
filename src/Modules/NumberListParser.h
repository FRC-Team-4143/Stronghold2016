#pragma once

#include <vector>
#include <regex>
#include <string>

class NumberListParser
{
public:
	NumberListParser();
	~NumberListParser();

	bool IsValid(std::string s);
	std::vector<double> Parse(std::string s);

protected:
	std::regex _GetNumberListRx();

private:
	std::regex _rxNumberList;
	bool _haveNumberListRx;
};
