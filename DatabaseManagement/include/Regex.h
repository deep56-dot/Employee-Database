#ifndef _REG_
#define _REG_

#include<regex>

namespace utility {
	inline std::regex emailRegex(R"([a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,})");
	inline std::regex mobileRegex(R"([0-9]{10})");
	inline std::regex dateRegex(R"([0-3][0-9]-[01][0-9]-\d{4})");
	inline std::regex idRegex(R"(\b\d{1,3}\b)");
	inline std::regex alphaRegex(R"(^[a-zA-Z\s]*$)");
	inline std::regex digitRegex(R"(^[0-9]*$)");
	inline std::regex genderRegex(R"(^(Male|Female|Other)$)");
	inline std::regex salaryRegex(R"(^[0-9]+(\.[0-9]+)?$)");
	inline std::regex allRegex{ ".*" };
}


#endif