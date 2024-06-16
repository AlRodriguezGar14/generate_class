#ifndef GENERATECLASS_HPP
#define GENERATECLASS_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <tuple>
#include <utility>


void replaceAll(std::string& str, const std::string& from, const std::string& to);
int writeCppFile(std::string className, std::vector<std::tuple<std::string, std::string>> classMembers);
int writeHppFile(std::string className, std::vector<std::tuple<std::string, std::string>> classMembers);

#endif
