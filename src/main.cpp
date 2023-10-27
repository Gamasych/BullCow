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
#include <future>
#include "menu.h"
#include "core.h"

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
/*
void player()
{
	auto computer{getRandom<int, 4>()};
	int count{1};
	std::cout << "Insert numb \n";
	auto player{getPlayer<int, 4>()};
	auto res = counter::countBullsCows(computer.begin(), computer.end(), player.begin());
	while (res.first != 4) {
		std::cout << "Bulls: " << res.first << "; Cows: " << res.second << "\n";
		player = getPlayer<int, 4>();
		res = counter::countBullsCows(computer.begin(), computer.end(), player.begin());
		++count;
	}
	std::cout << "You WIN!!! You have used " << count << " attempts!" << "\n";
}

void computer(const std::vector<int> &player = {})
{
	std::function<bool(const std::vector<int> &)> func = [](const std::vector<int> &arr)
	{
		return static_cast<bool>(arr[0]);
	};
	int count{1};
	const std::vector<std::vector<int>> allPerm{knut::allPermutation({1, 2, 3, 4, 5, 6, 7, 8, 9, 0}, 4, func)};
	std::vector<std::vector<int>> multi{allPerm};
	std::vector<int> currentVal{knut::choiceMiniMax(multi, allPerm)};
	std::pair<int, int> bullsCows{0, 0};
	do {
		++count;
		std::cout << currentVal << "\nInsert Bulls cows\n";
		if (player.size() == 0)
			std::cin >> bullsCows.first >> bullsCows.second;
		else
			bullsCows = counter::countBullsCows(currentVal.cbegin(), currentVal.cend(), player.cbegin());

		knut::eraseAllDiff(bullsCows, currentVal, &multi);

		currentVal = knut::choiceMiniMax(multi, allPerm);

	}
	while (bullsCows.first != 4);
	std::cout << "Computer WIN!!! They have used " << count << " attempts!" << "\n";
}

void compVSPlayer()
{
	std::function<bool(const std::vector<int> &)> func = [](const std::vector<int> &arr)
	{
		return static_cast<bool>(arr[0]);
	};
	std::vector<int> temp{1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	auto ll = std::async(&knut::allPermutation<int>, temp, 4, func);

	auto computer{getRandom<std::vector<int>>()};
	int count{1};
	std::cout << "Insert numb \n";
	auto player{getPlayer<std::vector<int>>()};
	auto res = counter::countBullsCows(computer.begin(), computer.end(), player.begin());
	std::cout << "Bulls: " << res.first << " Cows: " << res.second << "\n";
	const std::vector<std::vector<int>> allPerm{ll.get()};
	std::vector<std::vector<int>> multi{allPerm};
	std::vector<int> currentVal{multi.at(0)};
	std::pair<int, int> bullsCows{0, 0};
	while (res.first != 4 || bullsCows.first != 4) {
		std::cout << currentVal << "\nInsert Bulls cows\n";
		std::cin >> bullsCows.first >> bullsCows.second;
		knut::eraseAllDiff(bullsCows, currentVal, &multi);
		auto f = std::async(&knut::choiceMiniMax<int>, multi, allPerm);
		std::cout << "\nInsert numb \n";
		player = getPlayer<std::vector<int>>();
		res = counter::countBullsCows(computer.begin(), computer.end(), player.begin());
		std::cout << "Bulls: " << res.first << " Cows: " << res.second << "\n";
		currentVal = f.get();
	}
}*/


#include <memory>

int main()
{
	/*auto start = std::chrono::high_resolution_clock::now();
	//player();
	//computer();
	//compVSPlayer();
	auto end = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> diff = end - start;
	std::cout << "Time to player: " << diff << ' s!\n';*/

	/*core::CoreGame core;
	core.start();*/

	std::unique_ptr<BaseFunctional<int>> gen =
		std::make_unique< RepeatSymbols<int> >(std::vector<int>({1,2,3,4,5,5,6,7,8,9,0}), 4, std::optional<int>(0));
	auto rr = gen->getAllVariant();
	std::cout << rr;
	/*for(int i =0; i < 100; ++i){
		auto vect = gen->getRandom();
		bool res = gen->check(vect);
		if(res)
			std::cout << vect << "\n";
		else
			std::cerr << vect << "\n";
	}*/


	//menu();
	//menu_settings::settings();
	//system("pause");
	return 0;
}