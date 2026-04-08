#include <print>
#include <iostream>
#include <input.hpp>
#include <unicode.hpp>
#include <latcyr.hpp>

int main(int argc, char** argv) {
	std::string str{handleInput(argc, argv)};
	utf8str latstr{str};
	utf8str cyrstr{translateLatCyr(latstr)};
    std::println("{}", cyrstr.getstr());
	return 0;
}