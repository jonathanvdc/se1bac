#pragma once
#include <string>
#include <sstream>
#include <vector>

std::vector<std::string> Split(const std::string &s, char delim);
std::string AppendToFilename(const std::string& Name, const std::string& Extra);