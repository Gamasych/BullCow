//
// Created by fedorenko on 25.10.2023.
//

#include "core.h"
#include "common_types.h"
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <ctime>

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
		std::cin >> res;
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
	std::cout << "PLAY";
	const auto& params = settings_.getValue();

}

void CoreGame::settingsGame()
{
	settings_.settings();
}

void CoreGame::exitGame()
{
	const int morning[] {8,12};
	const int day[] {12,16};
	const int evening[] {16,22};
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
} // core