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
#include <string>
#include <optional>
#include <set>
#include <unordered_set>

template<typename T>
class BaseFunctional
{
public:
	explicit BaseFunctional(const std::vector<T> &values, int count, std::optional<T> forbidden_first)
		: values_(std::unordered_set<T>(values.begin(), values.end())),
		  count_(count),
		  first_(forbidden_first)
	{
		if (values_.size() <= 0)
			throw std::invalid_argument("Values must have a some value");
		if (count_ <= 0)
			throw std::invalid_argument("Count must be > 0");
	};

	virtual ~BaseFunctional()
	{};

	virtual bool check(const std::vector<T> &vec);
	virtual std::vector<T> getPlayer(std::istream &in = std::cin);
	virtual std::vector<T> getRandom() = 0;
	virtual std::vector<std::vector<T>> getAllVariant() = 0;

protected:
	const std::unordered_set<T> values_;
	const int count_;
	const std::optional<T> first_;
};

template<typename T>
class RepeatSymbols: public BaseFunctional<T>
{
public:
	explicit RepeatSymbols(const std::vector<T> &values, int count, std::optional<T> forbidden_first)
		: BaseFunctional<T>(values, count, forbidden_first)
	{};
	~RepeatSymbols() override
	{};

	std::vector<T> getRandom() override;
	std::vector<std::vector<T>> getAllVariant();
private:
	std::vector<std::vector<T>> generator(int count, const std::vector<T> &arr);
};

template<typename T>
class IndividualSymbols: public BaseFunctional<T>
{
public:
	explicit IndividualSymbols(const std::vector<T> &values, int count, std::optional<T> forbidden_first)
		: BaseFunctional<T>(values, count, forbidden_first)
	{
		if (values.size() < count)
			throw std::invalid_argument("Count must be >= different values");
	};
	~IndividualSymbols() override
	{};

	bool check(const std::vector<T> &vec) override;
	std::vector<T> getRandom() override;
	std::vector<std::vector<T>> getAllVariant();
};

template<typename T>
bool BaseFunctional<T>::check(const std::vector<T> &vec)
{
	if (vec.size() == 0) return false;
	if (first_.has_value() && *vec.begin() == first_.value()) return false;
	for (const auto val : vec) {
		if (values_.find(val) == values_.end()) return false;
	}
	return true;
}

template<typename T>
std::vector<T> BaseFunctional<T>::getPlayer(std::istream &in)
{
	std::vector<T> res{};
	do {
		if (res.size()) {
			std::cerr << "Incorrect values! Please, try again";
		}
		res.clear();
		std::cout << "Input " << count_ << " symbols. From values: [";
		for (auto it = values_.begin(); it != values_.end();) {
			std::cout << *it;
			if (++it != values_.end()) std::cout << ", ";
		}
		std::cout << "]" << std::endl;
		for (int i = 0; i < count_; ++i) {
			T temp;
			in >> temp;
			res.push_back(temp);
		}
	}
	while (!check(res));

	return res;
}

template<typename T>
std::vector<T> RepeatSymbols<T>::getRandom()
{
	std::vector<T> res{};
	std::vector<T> temp{BaseFunctional<T>::values_.begin(), BaseFunctional<T>::values_.end()};
	auto random_gen = std::mt19937(std::random_device()());
	std::uniform_int_distribution<int> range(0, temp.size() - 1);

	for (int i = 0; i < BaseFunctional<T>::count_; ++i) {
		res.push_back(temp.at(range(random_gen)));
	}
	if (BaseFunctional<T>::first_.has_value() && *(res.begin()) == BaseFunctional<T>::first_.value()) {
		auto pos = range(random_gen);
		if (temp.at(pos) == BaseFunctional<T>::first_.value()) {
			if (pos >= temp.size() - 2) --pos;
			else ++pos;
		}
		res[0] = temp.at(pos);
	}
	return res;
}

template<typename T>
std::vector<std::vector<T>> RepeatSymbols<T>::getAllVariant()
{
	return generator(BaseFunctional<T>::count_,
					 std::vector<T>(BaseFunctional<T>::values_.begin(), BaseFunctional<T>::values_.end()));

}

template<typename T>
std::vector<std::vector<T>> RepeatSymbols<T>::generator(int count, const std::vector<T> &arr)
{
	std::vector<std::vector<T>> res{};
	if (count == 1) {
		for (const auto val : arr) {
			if (!BaseFunctional<T>::first_.has_value() || BaseFunctional<T>::first_.value() != val)
				res.emplace_back(std::vector<T>{val});
		}
		return res;
	}
	for (auto &r : generator(count - 1, arr)) {
		for (auto val : arr) {
			auto temp = r;
			temp.push_back(val);
			res.push_back(temp);
		}
	}
	return res;
}

template<typename T>
bool IndividualSymbols<T>::check(const std::vector<T> &vec)
{
	std::set<T> temp;
	if (!BaseFunctional<T>::check(vec)) return false;
	for (const auto &val : vec) {
		if (!temp.insert(val).second) return false;
	}
	return true;
}

template<typename T>
std::vector<T> IndividualSymbols<T>::getRandom()
{
	std::vector<T> res{BaseFunctional<T>::values_.begin(), BaseFunctional<T>::values_.end()};
	std::shuffle(res.begin(), res.end(), std::mt19937(std::random_device()()));
	res.resize(BaseFunctional<T>::count_);
	if (BaseFunctional<T>::first_.has_value() && *(res.begin()) == BaseFunctional<T>::first_.value()) {
		std::swap(res.at(0), res.at(std::rand() % (res.size() - 1) + 1));
	}
	return res;
}

template<typename T>
std::vector<std::vector<T>> IndividualSymbols<T>::getAllVariant()
{
	std::vector<std::vector<T>> res;
	std::vector<T> values{BaseFunctional<T>::values_.begin(), BaseFunctional<T>::values_.end()};
	std::sort(values.begin(), values.end());
	do {
		auto temp = std::vector<T>(values.begin(), values.begin() + BaseFunctional<T>::count_);
		if (check(temp) && (res.size() == 0 || temp != *(res.end() - 1))) res.push_back(temp);
	}
	while (std::next_permutation(values.begin(), values.end()));
	return res;
}

#endif //GENERATOR_H
