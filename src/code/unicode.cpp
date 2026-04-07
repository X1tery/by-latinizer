#include <unicode.hpp>
#include <stdexcept>

std::string tobin(uint8_t n) {
	std::string out{};
	while (n > 0) {
		out.insert(0, 1, '0' + (n % 2));
		n /= 2;
	}
	return out;
}

utf8str::utf8str(std::string sstr) {
	std::vector<uint8_t> s{};
	for (char c : sstr) s.push_back(static_cast<uint8_t>(c));
	for (size_t i = 0; i < s.size(); i++) {
		if ((s[i] & 0x80) == 0x80) {
			if ((s[i] & 0x40) == 0x40) {
				if ((s[i] & 0x20) == 0x20) {
					if ((s[i] & 0x10) == 0x10) {
						if (i + 3 >= s.size()) throw std::runtime_error("invalid encoding4");
						data.push_back((s[i] << 030) + (s[++i] << 020) + (s[++i] << 010) + s[++i]);
					} else {
					if (i + 2 >= s.size()) throw std::runtime_error("invalid encoding3");
					data.push_back((s[i] << 020) + (s[++i] << 010) + s[++i]);
					}
				} else {
					if (i + 1 >= s.size()) throw std::runtime_error("invalid encoding2");
					data.push_back((s[i] << 010) + s[++i]);
				}
			} else {
				throw std::runtime_error("invalid encoding1");
			}
		} else {
			data.push_back(s[i]);
		}
	}
}

utf8str::utf8str(void) {
	data = {};
}

uint32_t& utf8str::operator[](size_t i) {
	return data[i];
}

const size_t utf8str::size() {
	return data.size();
}

void utf8str::push_back(uint32_t c) {
	data.push_back(c);
}

void utf8str::append(utf8str s) {
	for (size_t i = 0; i < s.size(); i++)
		data.push_back(s[i]);
}

void utf8str::append(std::string str) {
	utf8str s{str};
	for (size_t i = 0; i < s.size(); i++)
		data.push_back(s[i]);
}

void utf8str::insert(size_t pos, utf8str s) {
	data.insert_range(data.cbegin() + pos, s.getarr());
}

void utf8str::erase(size_t pos) {
	data.erase(data.begin() + pos);
}

std::vector<uint32_t> utf8str::getarr() {
	return data;
}

std::string utf8str::getstr() {
	std::string out{};
	for (size_t i = 0; i < data.size(); i++) {
		if ((data[i] & 0xff000000) > 0) {
			for (uint32_t j = 0; j < 4; j++) {
				out.push_back((data[i] & (0xff << (010 * (3 - j)))) >> 010 * (3 - j));
			}
		} else if ((data[i] & 0x00ff0000) > 0) {
			for (uint32_t j = 0; j < 3; j++) {
				out.push_back((data[i] & (0xff << (010 * (2 - j)))) >> 010 * (2 - j));
			}
		} else if ((data[i] & 0x0000ff00) > 0) {
			for (uint32_t j = 0; j < 2; j++) {
				out.push_back((data[i] & (0xff << (010 * (1 - j)))) >> 010 * (1 - j));
			}
		} else {
			out.push_back(data[i]);
		}
	}
	return out;
}