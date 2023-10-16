//
// Created by fedorenko on 16.10.2023.
//

#ifndef COUNTER_H
#define COUNTER_H

#include "common_types.h"
#include <utility>
#include <algorithm>
#include <stdexcept>
#include <unordered_set>

namespace counter
{
template<Integer T>
std::pair<int, int> countBullsCows(T trust, T verifiable, int base = 10)
{
	int bulls{0}, cows{0};
	std::unordered_set<int> temp;

	if (base <= 0) throw std::invalid_argument("Base cant be < or = 0");

	for (auto t = trust; t != 0; t /= base)
		temp.insert(t % base);
	for (; verifiable != 0; verifiable /= base, trust /= base) {
		if (verifiable % base == trust % base)
			++bulls;
		else if (temp.find(verifiable % base) != temp.end())
			++cows;
	}
	return std::make_pair(bulls, cows);
}

template<MapTemplate T>
std::pair<int, int> countBullsCows(const T &trust, const T &verifiable)
{
	int bulls{0}, cows{0};

	for (const auto &v: verifiable) {
		auto it = trust.find(v.first);
		if (it != trust.end()) {
			if (it->second == v.second)
				++bulls;
			else
				++cows;
		}
	}
	return std::make_pair(bulls, cows);
}

template<RandomIterator It>
std::pair<int, int> countBullsCows(It first, It end, It first_verifiable)
{
	int bulls{0}, cows{0};

	for (auto first_temp{first}; first != end; ++first, ++first_verifiable) {
		if (*first == *first_verifiable)
			++bulls;
		else if (std::find(first_temp, end, *first_verifiable) != end)
			++cows;
	}
	return std::make_pair(bulls, cows);
}

} // counter

#endif //COUNTER_H
