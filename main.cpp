#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <tuple>

int writeHppFile(std::string className, std::vector<std::tuple<std::string, std::string>> classMembers) {
    std::ofstream hppFile;
    std::string hppName = className + ".hpp";
    std::string upperClassName = className;
    for (std::string::iterator it = upperClassName.begin(); it != upperClassName.end(); ++it) {
        *it = std::toupper(*it);
    }

    hppFile.open(hppName);
    if (!hppFile) {
        std::cout << "Failed to open file " << hppName << std::endl;
        return (1);
    }

    hppFile << "#ifndef " << upperClassName << "_HPP\n";
    hppFile << "#define " << upperClassName << "_HPP\n\n";
    hppFile << "class " << className << " {\n\n";
    hppFile << "public:\n\n";
    hppFile << "\t" << className << " ();\n";
    hppFile << "\t" << className << " (const " << className << " &t_" << className << ");\n";
    hppFile << "\t~" << className << " ();\n";
    hppFile << "\t" << className << "& operator = (const " << className << " &t_" << className << ");\n\n";
    hppFile << "private:\n";
    hppFile << "\n\n";
	for (std::tuple<std::string, std::string>& member : classMembers) {
		hppFile << "\t" << std::get<0>(member) << " m_" << std::get<1>(member) << ";\n";
	}
    hppFile << "};\n\n";
    hppFile << "#endif\n";

    hppFile.close();
    return (0);
}

int writeCppFile(std::string className, std::vector<std::tuple<std::string, std::string>> classMembers) {
    std::ofstream cppFile;
    std::string cppName = className + ".cpp";
    cppFile.open(cppName);
    if (!cppFile) {
        std::cout << "Failed to open file " << cppName << std::endl;
        return (1);
    }

    cppFile << "#include \"" << className << ".hpp\"\n\n";

	// Default Constructor
	cppFile << className << "::" << className << " (";
	for (size_t i = 0; i < classMembers.size(); ++i) {
		cppFile << std::get<0>(classMembers[i]) << " t_" << std::get<1>(classMembers[i]);
		if (i != classMembers.size() - 1) {
			cppFile << ", ";
		}
	}
	cppFile << ") : ";
	for (size_t i = 0; i < classMembers.size(); ++i) {
		cppFile << "m_" << std::get<1>(classMembers[i]) << "(t_" << std::get<1>(classMembers[i]) << ")";
		if (i != classMembers.size() - 1) {
			cppFile << ", ";
		}
	}
	cppFile << " {}\n\n";

	// Copy Constructor
    cppFile << className << "::" << className << " (const " << className << " &t_" << className << ") {\n";
	for (std::tuple<std::string, std::string>& member : classMembers) {
		cppFile << "\tm_" << std::get<1>(member) << " = t_" << className << ".m_" << std::get<1>(member) << ";\n";
	}
    cppFile << "}\n\n";

	// Destructor
    cppFile << className << "::~" << className << " () {\n\n";
    cppFile << "}\n\n";

	// Assignment Operator
    cppFile << className << "& " << className << "::operator = (const " << className << " &t_" << className << ") {\n";
    cppFile << "\tif (this != &t_" << className << ") {\n";
	for (std::tuple<std::string, std::string>& member : classMembers) {
		cppFile << "\t\tm_" << std::get<1>(member) << " = t_" << className << ".m_" << std::get<1>(member) << ";\n";
	}
	cppFile << "\t}\n";
    cppFile << "\treturn (*this);\n";
    cppFile << "}\n\n";

    cppFile.close();
    return (0);
}

int main(int argc, char **argv) {
    if (argc < 2) {
        std::cout << "Wrong input. Try:" << std::endl;
        std::cout << "\t./generate_class <ClassName> <\"type var\">..." << std::endl;
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
            std::cout << "\t./generate_class <ClassName> <\"type var\">..." << std::endl;
            return (1);
        }
        std::string type = member.substr(0, member.find(" "));
        std::string var = member.substr(member.find(" ") + 1);
        classMembers.push_back(std::make_tuple(type, var));
    }

    if (writeHppFile(className, classMembers) == 1) {
        return (1);
    }
    if (writeCppFile(className, classMembers) == 1) {
        return (1);
    }
}
