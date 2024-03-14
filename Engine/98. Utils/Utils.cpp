#include "pch.h"
#include "Utils.h"

bool Utils::StartsWith(const string& str, const string& comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && index == 0)
		return true;

	return false;
}

bool Utils::StartsWith(const wstring& str, const wstring& comp)
{
	wstring::size_type index = str.find(comp);
	if (index != wstring::npos && index == 0)
		return true;

	return false;
}

std::wstring Utils::ToWString(const string& value)
{
	return wstring(value.begin(), value.end());
}

std::string Utils::ToString(const wstring& value)
{
	return string(value.begin(), value.end());
}

void Utils::makeUpperCase(string& str)
{
	for (auto& c : str)
		c = std::toupper(c);
}

void Utils::makeLowerCase(string& str)
{
	for (auto& c : str)
		c = std::tolower(c);
}

void Utils::splitString(const string& str, const char div, vector<string>& strings)
{
	if (str.empty())
		return;

	strings.clear();
	std::stringstream s(str);
	string temp;
	while (getline(s, temp, div))
		strings.push_back(temp);
}


