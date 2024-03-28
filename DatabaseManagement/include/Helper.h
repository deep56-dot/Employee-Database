#ifndef _HELPER_
#define _HELPER_

#include<iostream>
#include<filesystem>
#include<string>
#include<regex>
#include<optional>

namespace utility {

	inline std::optional<std::string> input(const std::string prompt, const std::regex& r, bool flag = false) {
		std::string input;
		auto cnt{ 0 };
		while (true) {
			if (cnt == 3) {
				break;
			}
			std::cout << prompt;
			std::getline(std::cin, input);

			if (input == "#" && flag == false) return "";
			else if (input == "#" && flag == true) return "0";
			if (!std::regex_match(input, r)) {
				std::cout << "\x1b[38;5;208mEnter valid input\x1b[0m\n";
				cnt++;
			}
			else {
				return input;
			}
		}
		return std::nullopt;
	}

	inline  std::string fun() {
		return "DEEP";
	}

	inline void waitMenu() {
		std::cout << "Press 0 to continue....\n";
		int i;
		std::cin >> i;
		std::cin.get();
	}
}

#endif