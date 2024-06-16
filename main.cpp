#include "generateClass.hpp"

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	size_t startPos = 0;
	while((startPos = str.find(from, startPos)) != std::string::npos) {
		str.replace(startPos, from.length(), to);
		startPos += to.length();
	}
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Wrong input. Try:" << std::endl;
        std::cout << "\t./newClass <ClassName> <\"type var\">..." << std::endl;
        return (1);
    }
    std::string className(argv[1]);
    if (!std::isupper(className[0]))
        className[0] = std::toupper(className[0]);

    std::vector<std::tuple<std::string, std::string>> classMembers;
    for (int i = 2; i != argc; i++) {
        std::string member(argv[i]);
        if (member.find(" ") == std::string::npos || member.find(" ") == member.size() - 1) {
            std::cout << "Wrong input. Try:" << std::endl;
            std::cout << "\t./newClass <ClassName> <\"type var\">..." << std::endl;
            return (1);
        }
        std::string type = member.substr(0, member.find(" "));
        std::string var = member.substr(member.find(" ") + 1);
        classMembers.push_back(std::make_tuple(type, var));
    }

	std::cout << "Building class " << className << "..." << std::endl;
    if (writeHppFile(className, classMembers)) {
        return (1);
    }
    if (writeCppFile(className, classMembers)) {
        return (1);
    }
	std::cout << className << ".hpp and " << className << ".cpp built successfully." << std::endl;

	return (1);
}
