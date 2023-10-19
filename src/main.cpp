//
// Created by fedorenko on 13.10.2023.
//

#include "counter.h"
#include "generator.h"
#include <iostream>
#include <chrono>
#include <array>
#include <functional>
#include "knut.h"

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &arr)
{
	os << "[";
	for (const auto &v : arr) {
		os << v << ",";
	}
	os << "]" << std::endl;
	return os;
}

void player()
{
	auto computer{generator::getRandom<int, 4>()};
	int count{1};
	std::cout << "Insert numb \n";
	auto player{generator::getPlayer<int, 4>()};
	auto res = counter::countBullsCows(computer.begin(), computer.end(), player.begin());
	while (res.first != 4) {
		std::cout << "Bulls: " << res.first << "; Cows: " << res.second << "\n";
		player = generator::getPlayer<int, 4>();
		res = counter::countBullsCows(computer.begin(), computer.end(), player.begin());
		++count;
	}
	std::cout << "You WIN!!! You have used " << count << " attempts!" << "\n";
}

void computer()
{
	std::function<bool(const std::vector<int> &)> func = [](const std::vector<int> &arr)
	{
		return static_cast<bool>(arr[0]);
	};
	int count{1};
	const std::vector<std::vector<int>> allPerm{knut::allPermutation({1, 2, 3, 4, 5, 6, 7, 8, 9, 0}, 4, func)};
	std::vector<std::vector<int>> multi{allPerm};
	std::vector<int> currentVal{1,2,3,4};
	std::pair<int, int> bullsCows{0, 0};
	do {
		++count;
		std::cout << currentVal << "\nInsert Bulls cows\n";
		std::cin >> bullsCows.first >> bullsCows.second;

		knut::eraseAllDiff(bullsCows, currentVal, &multi);

		currentVal = knut::choiceMiniMax(multi, allPerm);

	}
	while (bullsCows.first != 4);
	std::cout << "Computer WIN!!! They have used " << count << " attempts!" << "\n";
}

int main()
{
	auto start = std::chrono::high_resolution_clock::now();
	player();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "Time to player: " << diff << ' s!\n';

	start = std::chrono::high_resolution_clock::now();
	computer();
	end = std::chrono::high_resolution_clock::now();
	diff = end - start;
	std::cout << "Time to computer: " << diff << ' s!\n';
	return 0;
}