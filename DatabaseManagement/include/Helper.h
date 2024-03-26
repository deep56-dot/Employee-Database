#ifndef _HELPER_
#define _HELPER_

#include<iostream>
#include<filesystem>
#include<string>
#include<regex>

namespace utility {

	inline std::string input(const std::string prompt, const std::regex& r, bool flag = false) {
		std::string input;
		while (true) {
			std::cout << prompt;
			std::cin >> input;

			if (input == "#" && flag == false) return "";
			else if (input == "#" && flag == true) return "0";
			if (!std::regex_match(input, r)) {
				std::cout << "\x1b[31mEnter valid input\x1b[0m\n";
			}
			else {
				break;
			}
		}
		return input;
	}

	inline  std::string fun() {
		return "Deep";
	}

	inline void waitMenu() {
		std::cout << "Press 0 to continue....\n";
		int i;
		std::cin >> i;
	}
}

#endif