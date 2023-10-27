//
// Created by fedorenko on 16.10.2023.
//
#ifndef COMMON_TYPES_H
#define COMMON_TYPES_H

#include <concepts>

constexpr int kWidthDivider {25};

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
