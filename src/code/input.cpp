#include <input.hpp>
#include <print>
#include <iostream>
#include <fstream>

std::string handleInput(int argc, char** argv) {
    if (argc == 1) {
        std::string str{};
        std::getline(std::cin, str);
        return str;
    } else if (argc == 2) {
        std::ifstream file(argv[1]);
        if (!file.good()) {
            std::println(std::cerr, "Unknown file \"{}\"", argv[1]);
            file.close();
            exit(1);
        } else {
            std::string str{}, line{};
            while (std::getline(file, line))
                str.append(line + '\n');
            file.close();
            return str;
        }
    } else {
        std::println(std::cerr, "Usage: {} [file]", argv[0]);
        exit(1);
    }
}