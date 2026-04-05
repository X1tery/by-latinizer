#include <print>
#include <iostream>
#include <unicode.hpp>
#include <cyrlat.hpp>

int main() {
	std::string str{};
	std::getline(std::cin, str);
	utf8str cyrstr{str};
	utf8str latstr{translateCyrLat(cyrstr)};
    std::println("{}", latstr.getstr());
	return 0;
}