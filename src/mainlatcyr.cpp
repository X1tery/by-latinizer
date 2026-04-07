#include <print>
#include <iostream>
#include <unicode.hpp>
#include <latcyr.hpp>

int main() {
	std::string str{};
	std::getline(std::cin, str);
	utf8str latstr{str};
	utf8str cyrstr{translateLatCyr(latstr)};
    std::println("{}", cyrstr.getstr());
	return 0;
}