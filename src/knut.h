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
#include <exception>

namespace knut
{

template<typename T>
class KnutBase
{
public:
	KnutBase(const std::vector<std::vector<T> > &solutions)
		: currentSol_(*solutions.begin()),
		  remaining_(solutions),
		  solutions_(solutions)
	{ if (solutions.size() == 0) throw std::invalid_argument("Error! Vector solutions must be > 0 values"); }

	virtual std::vector<T> getSolutions() = 0;
	void eraseAllDiff(std::pair<int, int> bullsCows);

protected:
	std::vector<T> currentSol_;
	std::vector<std::vector<T>> remaining_;
	const std::vector<std::vector<T>> solutions_;
};

template<typename T>
class EasyKnut: public KnutBase<T>
{
public:
	EasyKnut(const std::vector<std::vector<T> > &solutions)
		: KnutBase<T>(solutions)
	{}
	std::vector<T> getSolutions() override;
};

template<typename T>
class MediumKnut: public KnutBase<T>
{
public:
	MediumKnut(const std::vector<std::vector<T> > &solutions)
		: KnutBase<T>(solutions)
	{}
	std::vector<T> getSolutions() override;
};

template<typename T>
class HardKnut: public KnutBase<T>
{
public:
	HardKnut(const std::vector<std::vector<T> > &solutions)
		: KnutBase<T>(solutions)
	{}
	std::vector<T> getSolutions() override;
};

template<typename T>
void KnutBase<T>::eraseAllDiff(std::pair<int, int> bullsCows)
{
	auto temp = currentSol_;
	remaining_.erase(std::remove_if(remaining_.begin(),
									 remaining_.end(),
									 [&bullsCows, &temp](const auto &first)
									 {
										 return (counter::countBullsCows(temp.cbegin(),
																		 temp.cend(),
																		 first.begin())
											 != bullsCows);
									 }), remaining_.end());
}

template<typename T>
std::vector<T> EasyKnut<T>::getSolutions()
{
	if (KnutBase<T>::remaining_.size() == 0) throw std::invalid_argument("No possible answers");
	auto random_gen = std::mt19937(std::random_device()());
	std::uniform_int_distribution<int> range(0, KnutBase<T>::solutions_.size() - 1);
	KnutBase<T>::currentSol_ = KnutBase<T>::solutions_.at(range(random_gen));
	return KnutBase<T>::currentSol_;
}

template<typename T>
std::vector<T> MediumKnut<T>::getSolutions()
{
	if (KnutBase<T>::remaining_.size() == 0) throw std::invalid_argument("No possible answers");
	auto random_gen = std::mt19937(std::random_device()());
	std::uniform_int_distribution<int> range(0, KnutBase<T>::remaining_.size() - 1);
	KnutBase<T>::currentSol_ = KnutBase<T>::remaining_.at(range(random_gen));
	return KnutBase<T>::currentSol_;
}

template<typename T>
std::vector<T> HardKnut<T>::getSolutions()
{
	if (KnutBase<T>::remaining_.size() == 0) throw std::invalid_argument("No possible answers");
	std::pair<int, bool> max_points{0, false};
	std::vector<T> currentVal{};
	int N = KnutBase<T>::solutions_[0].size();
	for (auto val_perm = KnutBase<T>::solutions_.begin(); val_perm != KnutBase<T>::solutions_.end(); ++val_perm) {
		std::map<std::pair<int, int>, int> points{};
		bool present{false};

		std::for_each(KnutBase<T>::remaining_.begin(), KnutBase<T>::remaining_.end(), [&](const std::vector<T> &first)
		{
			auto p = counter::countBullsCows(val_perm->begin(), val_perm->end(), first.begin());
			if (p.first == N) present = true;
			++points[p];
		});

		auto max = std::max_element(points.begin(), points.end(),
									[](const auto &a, const auto &b)
									{ return a.second < b.second; })->second;

		max = KnutBase<T>::remaining_.size() - max;
		if (max >= max_points.first && max_points.second < present) {
			max_points.first = max;
			max_points.second = present;
			currentVal = *val_perm;
		}
	}
	KnutBase<T>::currentSol_ = currentVal;
	return KnutBase<T>::currentSol_;
}
} // knut

#endif //KNUT_H
