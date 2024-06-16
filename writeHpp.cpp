#include "generateClass.hpp"

std::string hppTemplate = R"(#ifndef {{CAPITALIZED_NAME}}_HPP
#define {{CAPITALIZED_NAME}}_HPP

class {{ClassName}} {
public:
    {{ClassName}} ({{ClassMembers}});
    {{ClassName}} (const {{ClassName}} &t_{{ClassName}});
    ~{{ClassName}} ();
    {{ClassName}}& operator = (const {{ClassName}} &t_{{ClassName}});

private:
    {{MemberDeclarations}}
};

#endif
)";

std::string generateMembersListHpp(const std::vector<std::tuple<std::string, std::string>>& classMembers) {
	std::string classMembersListStr;
	for (const std::tuple<std::string, std::string>& member : classMembers) {
		classMembersListStr += std::get<0>(member) + " " + std::get<1>(member) + ", ";
	}
	classMembersListStr = classMembersListStr.substr(0, classMembersListStr.length() - 2);
	return classMembersListStr;
}

std::string generateMemberDeclarationsHpp(const std::vector<std::tuple<std::string, std::string>>& classMembers) {
	std::string memberDeclarationsStr;
	if (classMembers.size() != 0) {
		for (const std::tuple<std::string, std::string>& member : classMembers) {
			memberDeclarationsStr += "\t" + std::get<0>(member) + " m_" + std::get<1>(member) + ";\n";
		}
	}
	else {
		memberDeclarationsStr = "";
	}
	return memberDeclarationsStr;
}

int writeHppFile(std::string className, std::vector<std::tuple<std::string, std::string>> classMembers) {
	std::ofstream hppFile;
	std::string hppName = className + ".hpp";
	std::string upperClassName = className;
	std::transform(upperClassName.begin(), upperClassName.end(), upperClassName.begin(), ::toupper);

	hppFile.open(hppName);
	if (!hppFile) {
		std::cout << "Failed to open file " << hppName << std::endl;
		return (1);
	}

	std::string classMembersListStr = generateMembersListHpp(classMembers);
	std::string memberDeclarationsStr = generateMemberDeclarationsHpp(classMembers);

	std::string finalStr = hppTemplate;
	replaceAll(finalStr, "{{CAPITALIZED_NAME}}", upperClassName);
	replaceAll(finalStr, "{{ClassName}}", className);
	replaceAll(finalStr, "{{ClassMembers}}", classMembersListStr);
	replaceAll(finalStr, "{{MemberDeclarations}}", memberDeclarationsStr);

	hppFile << finalStr;

	hppFile.close();
	return (0);
}


