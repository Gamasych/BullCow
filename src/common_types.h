//
// Created by fedorenko on 16.10.2023.
//
#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include "bulls_cows.h"
#include <concepts>
#include <vector>
#include <iostream>
#include <iomanip>
#include <utility>

constexpr int kWidthDivider{25};

const std::string answer =
	R"(####################)""\n"
	R"(# ^__^             #)""\n"
	R"(# (oo)\_______     #)""\n"
	R"(# (__)\       )\/\ #)""\n"
	R"(#     ||----w |    #)""\n"
	R"(#     ||     ||    #)""\n"
	R"(####################)""\n";

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &arr)
{
	os << "[";
	for (int i = 0; i < arr.size(); ++i) {
		os << arr[i];
		if (i < arr.size() - 1) os << ", ";
	}
	os << "]";
	return os;
}

template<typename T>
void printTable(const std::vector<std::vector<std::pair<T, BullsCows> > > &val, std::ostream &os = std::cout)
{
	const int addedWidth = 4;
	const std::string str_delimiter{"    |"};
	const std::string str_res{" => "};
	size_t numb{0};
	std::ostringstream value, result;
	value << val.begin()->begin()->first;
	result << val.begin()->begin()->second;
	size_t width
		{(value.str().size() + result.str().size() + str_res.size() + str_delimiter.size()) * val.begin()->size()
			 + addedWidth};
	os << std::setw(width) << std::setfill('-') << "\n" << std::setfill(' ');
	for (const auto &line : val) {
		os << '|' << ++numb << '|';
		for (const auto &column : line) {
			os << column.first << str_res << column.second << str_delimiter;
		}
		os << "\n" << std::setw(width) << std::setfill('-') << "\n" << std::setfill(' ');
	}
}

template<typename T>
concept Symbol = std::same_as<T, char> || std::is_convertible_v<T, int>;

template<class T>
concept Integer = requires(T a) {
	{ a } -> std::convertible_to<int>;
};

template<class T>
concept IntegerVec = requires(T a) {
	{ a[0] } -> std::convertible_to<int>;
	a.push_back(0);
};

template<class T>
concept MapTemplate = requires(T a) {
	{ a.begin()->first } -> std::convertible_to<int>;
	{ a.begin()->second } -> std::convertible_to<std::size_t>;
};

template<class T>
concept RandomIterator = requires(T a) {
	{ *(a + 1) } -> std::convertible_to<int>;
};

#endif //COMMON_TYPES_H
