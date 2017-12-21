#include "FileNames.h"

#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> Split(const std::string &s, char delim)
{
	std::vector<std::string> elems;
	std::istringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		elems.push_back(item);
	}
	return elems;
}

std::string AppendToFilename(const std::string& Name, const std::string& Extra)
{
	auto items = Split(Name, '.');
	if (items.size() == 1)
	{
		return items[0] + Extra;
	}
	else
	{
		std::string result = "";
		for (int i = 0; i < items.size() - 1; i++)
		{
			if (i > 0)
			{
				result.append(".");
			}
			result.append(items[i]);
		}
		result.append(Extra);
		result.append(".");
		result.append(items[items.size() - 1]);
		return result;
	}
}