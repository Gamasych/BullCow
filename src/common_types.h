//
// Created by fedorenko on 16.10.2023.
//
#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <concepts>
#include <vector>
#include <iostream>
#include <iomanip>

constexpr int kWidthDivider{25};

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &arr)
{
	os << "[";
	for (int i = 0; i < arr.size(); ++i)
	{
		os << arr[i];
		if(i < arr.size() - 1) os << ", ";
	}
	os << "]" << std::endl;
	return os;
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
