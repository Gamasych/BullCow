//
// Created by fedorenko on 24.10.2023.
//

#include "menu.h"
#include <map>
#include <iostream>
#include <functional>
#include <iomanip>
#include <stdexcept>

namespace menu_settings
{
constexpr int kMaxCount = 8;

constexpr int kMinCount = 1;

const std::map<TypeGame, std::string> typeDefinition{
	{TypeGame::word, "use words"},
	{TypeGame::numb, "use numbers"}
};

const std::map<DifficultyGame, std::string> difficultDefinition{
	{DifficultyGame::easy, "easy level"},
	{DifficultyGame::medium, "medium level"},
	{DifficultyGame::hard, "hard level"}
};

const std::map<OpponentGame, std::string> opponentDefinition{
	{OpponentGame::onlyPlayer, "only player"},
	{OpponentGame::onlyComputer, "only computer"},
	{OpponentGame::ComputerVsPlayer, "computer vs player"},
	{OpponentGame::PlayerVsPlayer, "p2p"}
};

enum class SettingsNumb
{
	count,
	type,
	difficulty,
	opponent,
	repeat,
	read,
	exit
};

void setCount(Settings *param)
{
	int count;
	std::string str{"Value must be from "};
	str += std::to_string(kMinCount) + " to " + std::to_string(kMaxCount);
	std::cout << "Insert numbers of symbols in word (" << str << "): ";
	std::cin >> count;
	if (count > kMaxCount || count < kMinCount) {
		throw std::invalid_argument(str);
	}
	param->numb = count;
}

void setType(Settings *param)
{
	int count;
	for (const auto &val : typeDefinition) {
		std::cout << static_cast<int>(val.first) << " - to " << val.second << '\n';
	}
	std::cout << "Insert variant: ";
	std::cin >> count;
	if (count < static_cast<int>(typeDefinition.begin()->first)
		|| count > static_cast<int>((--typeDefinition.end())->first)) {
		throw std::invalid_argument(
			"Argument must be equal " + std::to_string(static_cast<int>(typeDefinition.begin()->first)) + " or "
				+ std::to_string(static_cast<int>((--typeDefinition.end())->first)));
	}
	param->type = static_cast<TypeGame>(count);
}

void setDifficulty(Settings *param)
{
	int count;
	for (const auto &val : difficultDefinition) {
		std::cout << static_cast<int>(val.first) << " - to " << val.second << '\n';
	}
	std::cout << "Insert variant: ";
	std::cin >> count;
	if (count < static_cast<int>(difficultDefinition.begin()->first)
		|| count > static_cast<int>((--difficultDefinition.end())->first)) {
		throw std::invalid_argument(
			"Argument must be equal " + std::to_string(static_cast<int>(difficultDefinition.begin()->first)) + " or "
				+ std::to_string(static_cast<int>((--difficultDefinition.end())->first)));
	}
	param->difficulty = static_cast<DifficultyGame>(count);
}

void setOpponent(Settings *param)
{
	int count;

	for (const auto &val : opponentDefinition) {
		std::cout << static_cast<int>(val.first) << " - to " << val.second << '\n';
	}
	std::cout << "Insert variant: ";
	std::cin >> count;
	if (count < static_cast<int>(opponentDefinition.begin()->first)
		|| count > static_cast<int>((--opponentDefinition.end())->first)) {
		throw std::invalid_argument(
			"Argument must be equal " + std::to_string(static_cast<int>(opponentDefinition.begin()->first)) + " or "
				+ std::to_string(static_cast<int>((--opponentDefinition.end())->first)));
	}
	param->opponent = static_cast<OpponentGame>(count);
}

void setRepeat(Settings *param)
{
	int count;

	std::cout << "Insert '0' - to disable repeat symbol, or '1' - to enable repeat symbol: ";
	std::cin >> count;

	param->repeatSymbol = count;
}

void readParams(Settings *param)
{
	try {
		const int max_length = 16;
		std::cout << std::setw(max_length) << "Numbers: " << param->numb << "\n";
		std::cout << std::setw(max_length) << "Type: " << typeDefinition.at(param->type) << "\n";
		std::cout << std::setw(max_length) << "Repeat symbols: " << (param->repeatSymbol ? "true" : "false") << "\n";
		std::cout << std::setw(max_length) << "Opponent: " << opponentDefinition.at(param->opponent) << "\n";
		std::cout << std::setw(max_length) << "Difficulty: " << difficultDefinition.at(param->difficulty) << "\n";
	}
	catch (std::exception& ex){
		std::cerr << "Error read settings" << ex.what();
	}
}

Settings settings()
{
	Settings res{};
	int com{0};
	const std::map<SettingsNumb, std::pair<std::string, std::function<void(Settings *)>>>
		kSettingsVal{{SettingsNumb::count, {"Number of symbols", setCount}},
					 {SettingsNumb::type, {"Type of symbols", setType}},
					 {SettingsNumb::difficulty, {"Game difficulty", setDifficulty}},
					 {SettingsNumb::opponent, {"Opponent in the game", setOpponent}},
					 {SettingsNumb::repeat, {"Possibility of character repetition", setRepeat}},
					 {SettingsNumb::read, {"Display current settings", readParams}},
					 {SettingsNumb::exit, {"Exit", [](Settings *v = nullptr)
					 { return; }}}};
	do {
		std::cout << std::setw(25) << std::setfill('-') << "\n";
		for (auto command : kSettingsVal) {
			std::cout << static_cast<int>(command.first) << " - " << command.second.first << std::endl;
		}
		std::cout << "Select an variant: ";
		std::cin >> com;
		std::cout << std::setw(25) << std::setfill('-') << "\n";
		std::cout << std::setfill(' ');
		try {
			kSettingsVal.at(static_cast<SettingsNumb>(com)).second(&res);
		}
		catch (std::exception &ex) {
			std::cout << "Error! Insert correct variant (" << ex.what() << ")" << std::endl;
		}
		std::cout << std::setw(25) << std::setfill('-') << "\n" << std::endl;
		std::cout << std::setfill(' ');
	}
	while (com != static_cast<int>(SettingsNumb::exit));
	return res;
}

}//namespace menu_settings