//
// Created by fedorenko on 25.10.2023.
//

#include "core.h"
#include "counter.h"
#include <iomanip>
#include <iostream>
#include <ctime>
#include <future>

namespace core
{
CoreGame::CoreGame()
	: commandMenu_({{CommandNumb::play, {"Start game", &CoreGame::playGame}},
					{CommandNumb::settings, {"Game settings", &CoreGame::settingsGame}},
					{CommandNumb::exit, {"Exit", &CoreGame::exitGame}}})
{
}

void CoreGame::start()
{
	int res{};
	do {
		std::cout << std::setw(kWidthDivider) << std::setfill('-') << "\n";
		std::cout << std::setfill(' ');
		for (auto command : commandMenu_) {
			std::cout << static_cast<int>(command.first) << " - " << command.second.first << std::endl;
		}
		std::cout << std::setw(kWidthDivider) << std::setfill('-') << "\n" << std::endl;
		std::cout << std::setfill(' ');
		std::cout << "Select an action: ";

		if (!(std::cin >> res)) {
			std::string temp;
			std::cin.clear();
			std::cin >> temp;
			continue;
		}

		try {
			(this->*(commandMenu_.at(static_cast<CommandNumb>(res)).second))();
		}
		catch (std::exception &ex) {
			std::cout << "Error! Insert correct variant (" << ex.what() << ")" << std::endl;
		}
	}
	while (res != static_cast<int>(CommandNumb::exit));
}

void CoreGame::playGame()
{
	const auto &params = settings_.getValue();
	std::shared_ptr<BaseFunctional<int> > gen
		{std::make_shared<IndividualSymbols<int> >(IndividualSymbols<int>({1, 2, 3, 4, 5, 6, 7, 8, 9, 0},
																		  4,
																		  std::optional<int>()))};
	std::shared_ptr<knut::KnutBase<int> > knut{
		std::make_shared<knut::HardKnut<int> >(knut::HardKnut<int>(gen->getAllVariant()))
	};
	std::cout << std::setw(kWidthDivider) << std::setfill('_') << "\n";
	std::cout << std::setfill(' ');
	player(gen);
	computer(knut);
	playerVsComputer(gen, knut);
	std::cout << std::setw(kWidthDivider) << std::setfill('_') << "\n";
	std::cout << std::setfill(' ');
}

void CoreGame::settingsGame()
{
	settings_.settings();
}

void CoreGame::exitGame()
{
	const int morning[]{8, 12};
	const int day[]{12, 16};
	const int evening[]{16, 22};
	time_t t1 = time(nullptr);
	tm t = *localtime(&t1);
	auto hours = t.tm_hour;
	std::cout << std::setw(kWidthDivider) << std::setfill('$') << "\n";
	std::cout << "Thanks for the game!\n";

	if (hours >= morning[0] && hours < morning[1])
		std::cout << "Have a nice morning!";
	else if (hours >= day[0] && hours < day[1])
		std::cout << "Have a nice day!";
	else if (hours >= evening[0] && hours < evening[1])
		std::cout << "Have a nice evening!";
	else
		std::cout << "Have a nice night!";

	std::cout << "\n" << std::setw(kWidthDivider) << std::setfill('#') << "\n" << std::endl;
	std::cout << std::setfill(' ');
}

template<Symbol T>
void CoreGame::player(std::shared_ptr<BaseFunctional<T> > generator)
{
	auto computer{generator->getRandom()};
	int count{1};
	std::cout << "The computer guessed a number. Try to guess it!\n";
	do {
		std::cout << "Insert numb: " << std::endl;
		auto player{generator->getPlayer()};
		auto res = counter::countBullsCows(computer.begin(), computer.end(), player.begin());
		std::cout << res;
		if (res.bulls() == player.size())
			break;
		++count;
	}
	while (true);
	std::cout << "You WIN!!! You have used " << count << " attempts!" << "\n";
}

template<Symbol T>
void CoreGame::computer(std::shared_ptr<knut::KnutBase<T>> knut)
{
	BullsCows bullsCows{0, 0};
	int count{1};
	std::cout << "Please guess the meaning. The computer will try to guess!\n";
	do {
		auto currentVal{knut->getSolutions()};
		std::cout << "The computer thinks the answer is: \n" << currentVal << "\nInsert Bulls cows\n";
		std::cin >> bullsCows;
		if (bullsCows.bulls() == currentVal.size())
			break;
		knut->eraseAllDiff(bullsCows);
		++count;
	}
	while (true);
	std::cout << "Computer WIN!!! They have used " << count << " attempts!" << "\n";
}

template<Symbol T>
void CoreGame::playerVsComputer(std::shared_ptr<BaseFunctional<T> > generator, std::shared_ptr<knut::KnutBase<T>> knut)
{
	auto computer{generator->getRandom()};
	int count{1};
	BullsCows res_computer{0, 0}, res_player{0,0};
	auto func = std::async(&knut::KnutBase<T>::getSolutions, knut);
	std::cout << "Please guess the meaning.\nThe computer guessed a number.\nBeat me!\n";
	do{
		std::cout << "Insert numb: " << std::endl;
		auto player{generator->getPlayer()};
		res_player = counter::countBullsCows(computer.begin(), computer.end(), player.begin());
		std::cout << res_player;

		auto currentVal{func.get()};
		std::cout << "The computer thinks the answer is: \n" << currentVal << "\nInsert Bulls cows\n";
		std::cin >> res_computer;
		knut->eraseAllDiff(res_computer);
		func = std::async(&knut::KnutBase<T>::getSolutions, knut);
		++count;
	}while(res_computer.bulls() != computer.size() && res_player.bulls() != computer.size());
}
} // core