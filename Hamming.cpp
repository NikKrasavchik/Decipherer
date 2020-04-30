#include <iostream>

#include "Hamming.h"
#include "HammingPacket.h"

HammingPacket& Hamming::get_packet(int index) // Возвращает копию HammingPacket из вектора по индексу
{
	return text.at(index); // тоже самое что return HammingPacket(text.at(index))
}

std::string Hamming::get_clear_text()
{
	std::string str;
	for (auto & h : text) {
		str += h.clean_in_string();
	}
	return str;
}

bool check_user_input(std::string& str) {
	std::size_t pos = str.find_first_of(' ');
	while (pos != std::string::npos) {
		str.erase(pos, 1);
		pos = str.find_first_of(' ', pos);
	}

	for (auto &c : str) {
		if (c != '0' && c != '1') {
			return false;
		}
	}
	return true;
}

std::istream& operator>>(std::istream& in, Hamming& tmp) // inputs text with the Hamming encoding
{
	// getting user input
	std::string str;
	std::cout << "Put your input here (format: \"1100101 10101 101101\"): ";
	do {
		std::getline(in, str);
		if (!check_user_input(str)) {
			std::cerr << "Incorrect input found! Try again: ";
		}
	} while(!check_user_input(str));

	for (int i = 0; i < (int)str.size() / 15; ++i) {
		tmp.text.emplace_back(str.substr(0, 15).c_str()); // вызвать конструктор HammingPacket из строки в 15 символов
		str.erase(0, 15); // обрезать первые 15 символов
	}

	if (!str.empty())  // если есть лишние биты - дополнить
	{
		char s[16] = { '0' };
		strncpy(s, str.c_str(), str.length());
		tmp.text.emplace_back(s);
	}
	return in;
}

std::ostream& operator<<(std::ostream& out, const Hamming& tmp) // formatted text output in Hamming encoding
{
	std::cout << "Total of " << tmp.text.size() << " elements:" << std::endl;
	int i = 1;
	for (auto & h : tmp.text) {
		std::cout << i++ << " - " << h << std::endl;
	}
	return out;
}