#include <print>
#include <iostream>
#include <input.hpp>
#include <unicode.hpp>
#include <cyrlat.hpp>

int main(int argc, char** argv) {
	std::string str{handleInput(argc, argv)};
	utf8str cyrstr{str};
	utf8str latstr{translateCyrLat(cyrstr)};
    std::println("{}", latstr.getstr());
	return 0;
}