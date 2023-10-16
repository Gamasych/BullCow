//
// Created by fedorenko on 16.10.2023.
//

#ifndef GENERATOR_H
#define GENERATOR_H

#include "common_types.h"
#include <random>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>

namespace generator
{
template<IntegerVec T>
T getRandom(int count = 4, int base = 10)
{
	std::vector<int> res{};

	if (count > base)
		throw std::invalid_argument("Count must be <= base");
	if (base <= 0)
		throw std::invalid_argument("Base must be > 0");
	if (count <= 0)
		throw std::invalid_argument("Count must be > 0");

	for (int i = 0; i < base; ++i) {
		res.push_back(i);
	}
	std::shuffle(res.begin(), res.end(), std::mt19937(std::random_device()()));
	if (res.at(0) == 0) std::swap(res.at(0), res.at(std::rand() % base + 1));
	res.resize(count);
	return res;
}

template<IntegerVec T>
T getPlayer(std::istream &in = std::cin, int count = 4, int base = 10)
{
	std::vector<int> res{};
	int temp{0};

	if (count > base)
		throw std::invalid_argument("Count must be <= base");
	if (base <= 0)
		throw std::invalid_argument("Base must be > 0");
	if (count <= 0)
		throw std::invalid_argument("Count must be > 0");

	in >> temp;
	if (temp <= 0)
		throw std::invalid_argument("Input numb must be > 0");

	for (; temp != 0; temp /= base) {
		res.push_back(temp % base);
	}

	if (res.size() != count) {
		std::string err_str = "Input numb must be = ";
		err_str.append(std::to_string(count));
		throw std::invalid_argument(err_str);
	}

	return res;
}

template<Integer T>
T getRandom(int count = 4, int base = 10)
{
	std::vector<int> temp{};
	T res{0};

	try {
		temp = getRandom<std::vector<int>>(count, base);
	}
	catch (std::exception &ex) {
		throw ex;
	}
	for (int i = 0; i < temp.size(); ++i) {
		res += temp.at(i) * std::pow(base, count - i - 1);
	}
	return res;
}

template<Integer T>
T getPlayer(std::istream &in = std::cin, int count = 4, int base = 10)
{
	std::vector<int> temp{};
	T res{0};

	try {
		temp = getPlayer<std::vector<int>>(in, count, base);
	}
	catch (std::exception &ex) {
		throw ex;
	}
	for (int i = 0; i < temp.size(); ++i) {
		res += temp.at(i) * std::pow(base, count - i);
	}
	return res;
}

template<MapTemplate T>
T getRandom(int count = 4, int base = 10)
{
	std::vector<int> temp{};
	T res;
	try {
		temp = getRandom<std::vector<int>>(count, base);
	}
	catch (std::exception &ex) {
		throw ex;
	}
	for (int i = 0; i < temp.size(); ++i) {
		res.insert({temp.at(i), i});
	}
	return res;
}

template<MapTemplate T>
T getPlayer(std::istream &in = std::cin, int count = 4, int base = 10)
{
	std::vector<int> temp{};
	T res;
	try {
		temp = getPlayer<std::vector<int>>(in, count, base);
	}
	catch (std::exception &ex) {
		throw ex;
	}
	for (int i = 0; i < temp.size(); ++i) {
		res.insert({temp.at(i), i});
	}
	return res;
}

template<class T, size_t N>
std::array<T, N> getRandom(int base = 10)
{
	std::vector<int> temp{};
	std::array<T, N> res;
	try {
		temp = getRandom<std::vector<int>>(res.size(), base);
	}
	catch (std::exception &ex) {
		throw ex;
	}
	for (int i = 0; i < temp.size(); ++i) {
		res[i] = temp.at(i);
	}
	return res;
}

template<class T, size_t N>
std::array<T, N> getPlayer(std::istream &in = std::cin, int base = 10)
{
	std::vector<int> temp{};
	std::array<T, N> res;
	try {
		temp = getPlayer<std::vector<int>>(in, res.size(), base);
	}
	catch (std::exception &ex) {
		throw ex;
	}
	for (int i = 0; i < temp.size(); ++i) {
		res.at(i) = temp.at(i);
	}
	return res;
}
} // generator

#endif //GENERATOR_H
