#include "generateClass.hpp"

std::string cppTemplate = R"(#include "{{ClassName}}.hpp"

{{ClassName}}::{{ClassName}}({{ClassMembers}}){{MemberInitializations}} {}

{{ClassName}}::{{ClassName}}(const {{ClassName}}& t_{{ClassName}}) {
{{CopyAssignmentsConstructor}}
}

{{ClassName}}::~{{ClassName}}() {}

{{ClassName}}& {{ClassName}}::operator=(const {{ClassName}}& t_{{ClassName}}) {
	if (this != &t_{{ClassName}}) {
{{CopyAssignmentsOperator}}
    }
	return *this;
}
)";

std::string generateMembersListCpp(const std::vector<std::tuple<std::string, std::string>>& classMembers) {
	std::string classMembersListStr;
	for (size_t i = 0; i < classMembers.size(); ++i) {
		classMembersListStr += std::get<0>(classMembers[i]) + " t_" + std::get<1>(classMembers[i]);
		if (i != classMembers.size() - 1) {
			classMembersListStr += ", ";
		}
	}
	return classMembersListStr;
}

std::string generateMemberInitializationsCpp(const std::vector<std::tuple<std::string, std::string>>& classMembers) {
	std::string memberInitializationsStr;
	for (size_t i = 0; i < classMembers.size(); ++i) {
		memberInitializationsStr += "m_" + std::get<1>(classMembers[i]) + "(t_" + std::get<1>(classMembers[i]) + ")";
		if (i != classMembers.size() - 1) {
			memberInitializationsStr += ", ";
		}
	}
	return memberInitializationsStr;
}

std::pair<std::string, std::string> generateCopyAssignmentsCpp(const std::vector<std::tuple<std::string, std::string>>& classMembers, const std::string& className) {
	if (classMembers.empty()) {
		return (std::make_pair("\t(void)t_" + className + + ";", "\t\t(void)t_" + className + + ";"));
	}
	std::string copyAssignmentsStrConstructor;
	std::string copyAssignmentsStrOperator;
	for (const std::tuple<std::string, std::string>& member : classMembers) {
		copyAssignmentsStrConstructor += "\tm_" + std::get<1>(member) + " = t_" + className + ".m_" + std::get<1>(member) + ";";
		copyAssignmentsStrOperator += "\t\tm_" + std::get<1>(member) + " = t_" + className + ".m_" + std::get<1>(member) + ";";
		if (member != classMembers.back()) {
			copyAssignmentsStrConstructor += "\n";
			copyAssignmentsStrOperator += "\n";
		}
	}
	return std::make_pair(copyAssignmentsStrConstructor, copyAssignmentsStrOperator);
}

int writeCppFile(std::string className, std::vector<std::tuple<std::string, std::string>> classMembers) {
	std::ofstream cppFile;
	std::string cppName = className + ".cpp";
	cppFile.open(cppName);
	if (!cppFile) {
		std::cout << "Failed to open file " << cppName << std::endl;
		return (1);
	}

	std::string classMembersListStr = generateMembersListCpp(classMembers);
	std::string memberInitializationsStr = generateMemberInitializationsCpp(classMembers);
	if (!memberInitializationsStr.empty()) {
		memberInitializationsStr = " : " + memberInitializationsStr;
	}
	std::pair<std::string, std::string> copyAssignmentsStr = generateCopyAssignmentsCpp(classMembers, className);

	std::string finalStr = cppTemplate;
	replaceAll(finalStr, "{{ClassName}}", className);
	replaceAll(finalStr, "{{ClassMembers}}", classMembersListStr);
	replaceAll(finalStr, "{{MemberInitializations}}", memberInitializationsStr);
	replaceAll(finalStr, "{{CopyAssignmentsConstructor}}", copyAssignmentsStr.first);
	replaceAll(finalStr, "{{CopyAssignmentsOperator}}", copyAssignmentsStr.second);

	cppFile << finalStr;

	cppFile.close();
	return (0);
}

