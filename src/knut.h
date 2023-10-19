//
// Created by fedorenko on 18.10.2023.
//

#ifndef KNUT_H
#define KNUT_H

#include "counter.h"
#include <iostream>
#include <vector>
#include <functional>
#include <execution>
#include <chrono>
#include <map>

namespace knut
{


template<typename T>
std::vector<std::vector<T>>
allPermutation(std::vector<T> values, int N, std::function<bool(const std::vector<T> &)> func)
{
	std::vector<std::vector<T>> res;
	std::sort(values.begin(), values.end());
	do {
		auto temp = std::vector<T>(values.begin(), values.begin() + N);
		if (func(temp) && (res.size() == 0 || temp != *(res.end() - 1))) res.push_back(temp);
	}
	while (std::next_permutation(values.begin(), values.end()));
	return res;
}

template<typename T>
std::vector<T> choiceMiniMax(const std::vector<std::vector<T>> &multi,
							 const std::vector<std::vector<T>> &allPerm)
{
	std::pair<int, bool> max_points{0, false};
	std::vector<T> currentVal{};
	int N = allPerm[0].size();
	for (auto val_perm = allPerm.begin(); val_perm != allPerm.end(); ++val_perm) {
		std::map<std::pair<int, int>, int> points{};
		bool present{false};

		std::for_each(multi.begin(), multi.end(), [&](const std::vector<T> &first)
		{
			auto p = counter::countBullsCows(val_perm->begin(), val_perm->end(), first.begin());
			if (p.first == N) present = true;
			++points[p];
		});

		auto max = std::max_element(points.begin(), points.end(),
									[](const auto &a, const auto &b)
									{ return a.second < b.second; })->second;

		max = multi.size() - max;
		if (max >= max_points.first && max_points.second < present) {
			max_points.first = max;
			max_points.second = present;
			currentVal = *val_perm;
		}
	}
	return currentVal;
}

template<typename T>
void eraseAllDiff(const std::pair<int, int> &bullsCows, const std::vector<T> &currentVal, std::vector<std::vector<T>> *multi)
{
	multi->erase(std::remove_if(multi->begin(),
								multi->end(),
								[&](const auto &first)
								{
									return (counter::countBullsCows(currentVal.cbegin(),
																	currentVal.cend(),
																	first.begin())
										!= bullsCows);
								}), multi->end());
}

} // knut

#endif //KNUT_H
