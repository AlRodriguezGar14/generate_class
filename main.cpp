#include <iostream>
#include <fstream>
#include <sstream>
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
    hppFile << "class " << className << " {\n";
    hppFile << "public:\n";
    if (!classMembers.empty()) {
        hppFile << "\t" << className << " (";
        for (size_t i = 0; i < classMembers.size(); ++i) {
            hppFile << std::get<0>(classMembers[i]) << " t_" << std::get<1>(classMembers[i]);
            if (i != classMembers.size() - 1) {
                hppFile << ", ";
            }
        }
        hppFile << ");\n";
    } else {
        hppFile << "\t" << className << " ();\n";
    }
    hppFile << "\t" << className << " (const " << className << " &t_" << className << ");\n";
    hppFile << "\t~" << className << " ();\n";
    hppFile << "\t" << className << "& operator = (const " << className << " &t_" << className << ");\n\n";
    hppFile << "private:\n";
    for (std::tuple<std::string, std::string>& member : classMembers) {
        hppFile << "\t" << std::get<0>(member) << " m_" << std::get<1>(member) << ";\n";
    }
    hppFile << "};\n\n";
    hppFile << "#endif\n";

    hppFile.close();
    return (0);
}

std::string generateDefaultConstructor(const std::string& className, const std::vector<std::tuple<std::string, std::string>>& classMembers) {
    std::ostringstream constructor;

    constructor << className << "::" << className << " (";
    for (size_t i = 0; i < classMembers.size(); ++i) {
        constructor << std::get<0>(classMembers[i]) << " t_" << std::get<1>(classMembers[i]);
        if (i != classMembers.size() - 1) {
            constructor << ", ";
        }
    }
    constructor << ")";
	if (classMembers.size() != 0)
		constructor << " : ";
    for (size_t i = 0; i < classMembers.size(); ++i) {
        constructor << "m_" << std::get<1>(classMembers[i]) << "(t_" << std::get<1>(classMembers[i]) << ")";
        if (i != classMembers.size() - 1) {
            constructor << ", ";
        }
    }
    constructor << " {}\n\n";
    return constructor.str();
}

std::string generateCopyConstructor(const std::string& className, const std::vector<std::tuple<std::string, std::string>>& classMembers) {
    std::ostringstream constructor;

    constructor << className << "::" << className << " (const " << className << " &t_" << className << ") {\n";
    for (const std::tuple<std::string, std::string>& member : classMembers) {
        constructor << "\tm_" << std::get<1>(member) << " = t_" << className << ".m_" << std::get<1>(member) << ";\n";
    }
    constructor << "}\n\n";
    return constructor.str();
}

std::string generateDestructor(const std::string& className) {
    std::ostringstream destructor;

    destructor << className << "::~" << className << " () {\n\n";
    destructor << "}\n\n";
    return destructor.str();
}

std::string generateAssignmentOperator(const std::string& className, const std::vector<std::tuple<std::string, std::string>>& classMembers) {
    std::ostringstream assignmentOperator;

    assignmentOperator << className << "& " << className << "::operator = (const " << className << " &t_" << className << ") {\n";
    assignmentOperator << "\tif (this != &t_" << className << ") {\n";
    for (const std::tuple<std::string, std::string>& member : classMembers) {
        assignmentOperator << "\t\tm_" << std::get<1>(member) << " = t_" << className << ".m_" << std::get<1>(member) << ";\n";
    }
    assignmentOperator << "\t}\n";
    assignmentOperator << "\treturn (*this);\n";
    assignmentOperator << "}\n\n";
    return assignmentOperator.str();
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

    cppFile << generateDefaultConstructor(className, classMembers);
    cppFile << generateCopyConstructor(className, classMembers);
    cppFile << generateDestructor(className);
    cppFile << generateAssignmentOperator(className, classMembers);

    cppFile.close();
    return (0);
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
