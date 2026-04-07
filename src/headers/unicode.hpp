#pragma once
#include <string>
#include <vector>
#include <cstdint>

std::string tobin(uint8_t n);
class utf8str {
	private:
		std::vector<uint32_t> data;
	public:
		utf8str(std::string sstr);
        utf8str(void);
        uint32_t& operator[](size_t i);
        const size_t size();
        void push_back(uint32_t c);
        void append(utf8str s);
        void append(std::string str);
        void insert(size_t pos, uint32_t c);
        void insert(size_t pos, utf8str s);
        void erase(size_t pos);
        std::vector<uint32_t> getarr();
        std::string getstr();
};