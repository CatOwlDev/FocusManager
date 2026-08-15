#include "Error.h"

Error::Error(
	const std::string& when,
	const std::string& where,
	const std::string& why
) : 
	when{when},
	where{where},
	why{why} {}

std::ostream& operator<<(std::ostream& out, const Error& e) {
	out << "Error: { When: " << e.when 
		<< "; Why: " << e.why 
		<< "; Where: " << e.where << '\n';
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