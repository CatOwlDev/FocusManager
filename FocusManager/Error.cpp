#include "Error.h"

Error::Error(
	const std::string& when,
	const std::string& where,
	const std::string& why
) : 
	mWhen{ when },
	mWhere{ where },
	mWhy{ why } {}

std::ostream& operator<<(std::ostream& out, const Error& e) {
	out << "Error: { When: " << e.mWhen 
		<< "; Why: " << e.mWhy 
		<< "; Where: " << e.mWhere << '\n';
	return out;
}

void writeErrorReport(const Error& error) {
	std::filesystem::path path{ "C:\\Users\\Dimo\\AppData\\Roaming\\FocusManager\\errorReport.txt" };
	std::ofstream fileErrorReport{ path, std::ios::app };

	if (!fileErrorReport) {
		return;
	}

	fileErrorReport << error;
}