//
// Created by fedorenko on 13.10.2023.
//
#include "counter.h"
#include "generator.h"
#include <iostream>


using namespace std;
int main() {
	auto computer{generator::getRandom<int, 4>()};
	int count {1};
	std::cout << "Insert numb \n";
	auto player{generator::getPlayer<int, 4>()};
	auto res = counter::countBullsCows(computer.begin(),computer.end(), player.begin());
	while(res.first != 4){
		std::cout << res.first << " " << res.second << "\n";
		player = generator::getPlayer<int, 4>();
		res = counter::countBullsCows(computer.begin(),computer.end(), player.begin());
		++count;
	}
	std::cout << "You WIN!!! You have used " <<  count << " attempts!"<< "\n";
	return 0;
}