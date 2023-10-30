//
// Created by fedorenko on 24.10.2023.
//

#include "menu.h"
#include "common_types.h"
#include <iomanip>
#include <stdexcept>
#include <iostream>


//TODO Проверки на правильные входные данные
namespace menu_settings
{
MenuSettings::Settings::Settings()
	: type(TypeGame::numb),
	  difficulty(DifficultyGame::medium),
	  opponent(OpponentGame::ComputerVsPlayer),
	  numb(4),
	  repeatSymbol(false)
{

}

MenuSettings::MenuSettings(const Settings &params)
	: maxCount_(8),
	  minCount_(1),
	  params_(params),
	  typeDefinition_({{TypeGame::word, "use words"},
					   {TypeGame::symbol, "use symbols"},
					   {TypeGame::numb, "use numbers"}}),
	  difficultDefinition_({{DifficultyGame::easy, "easy level"},
							{DifficultyGame::medium, "medium level"},
							{DifficultyGame::hard, "hard level"}}),
	  opponentDefinition_({{OpponentGame::onlyPlayer, "only player"},
						   {OpponentGame::onlyComputer, "only computer"},
						   {OpponentGame::ComputerVsPlayer, "computer vs player"},
						   {OpponentGame::PlayerVsPlayer, "p2p"}}),
	  settingsVal_({{SettingsNumb::count, {"Number of symbols", &MenuSettings::setCount}},
					{SettingsNumb::type, {"Type of symbols", &MenuSettings::setType}},
					{SettingsNumb::difficulty, {"Game difficulty", &MenuSettings::setDifficulty}},
					{SettingsNumb::opponent, {"Opponent in the game", &MenuSettings::setOpponent}},
					{SettingsNumb::repeat, {"Possibility of character repetition", &MenuSettings::setRepeat}},
					{SettingsNumb::read, {"Display current settings", &MenuSettings::readParams}},
					{SettingsNumb::exit, {"Exit", &MenuSettings::readParams}}})
{

}

MenuSettings::Settings MenuSettings::settings()
{
	int com{0};
	do {
		std::cout << std::setw(kWidthDivider) << std::setfill('-') << "\n";
		for (auto command : settingsVal_) {
			std::cout << static_cast<int>(command.first) << " - " << command.second.first << std::endl;
		}
		std::cout << "Select an variant: ";
		std::cin >> com;
		std::cout << std::setw(kWidthDivider) << std::setfill('-') << "\n";
		std::cout << std::setfill(' ');
		try {
			(this->*(settingsVal_.at(static_cast<SettingsNumb>(com)).second))();
		}
		catch (std::exception &ex) {
			std::cout << "Error! Insert correct variant (" << ex.what() << ")" << std::endl;
		}
		std::cout << std::setw(kWidthDivider) << std::setfill('-') << "\n" << std::endl;
		std::cout << std::setfill(' ');
	}
	while (com != static_cast<int>(SettingsNumb::exit));
	return params_;
}

void MenuSettings::setValue(const MenuSettings::Settings &params)
{
	params_ = params;
}

void MenuSettings::setCount()
{
	int count;
	std::string str{"Value must be from "};
	str += std::to_string(minCount_) + " to " + std::to_string(maxCount_);
	std::cout << "Insert numbers of symbols in word (" << str << "): ";
	std::cin >> count;
	if (count > maxCount_ || count < minCount_) {
		throw std::invalid_argument(str);
	}
	params_.numb = count;
}

void MenuSettings::setType()
{
	int count;
	for (const auto &val : typeDefinition_) {
		std::cout << static_cast<int>(val.first) << " - to " << val.second << '\n';
	}
	std::cout << "Insert variant: ";
	std::cin >> count;
	if (count < static_cast<int>(typeDefinition_.begin()->first)
		|| count > static_cast<int>((--typeDefinition_.end())->first)) {
		throw std::invalid_argument(
			"Argument must be equal " + std::to_string(static_cast<int>(typeDefinition_.begin()->first)) + " or "
				+ std::to_string(static_cast<int>((--typeDefinition_.end())->first)));
	}
	params_.type = static_cast<TypeGame>(count);
}

void MenuSettings::setDifficulty()
{
	int count;
	for (const auto &val : difficultDefinition_) {
		std::cout << static_cast<int>(val.first) << " - to " << val.second << '\n';
	}
	std::cout << "Insert variant: ";
	std::cin >> count;
	if (count < static_cast<int>(difficultDefinition_.begin()->first)
		|| count > static_cast<int>((--difficultDefinition_.end())->first)) {
		throw std::invalid_argument(
			"Argument must be equal " + std::to_string(static_cast<int>(difficultDefinition_.begin()->first)) + " or "
				+ std::to_string(static_cast<int>((--difficultDefinition_.end())->first)));
	}
	params_.difficulty = static_cast<DifficultyGame>(count);
}

void MenuSettings::setOpponent()
{
	int count;

	for (const auto &val : opponentDefinition_) {
		std::cout << static_cast<int>(val.first) << " - to " << val.second << '\n';
	}
	std::cout << "Insert variant: ";
	std::cin >> count;
	if (count < static_cast<int>(opponentDefinition_.begin()->first)
		|| count > static_cast<int>((--opponentDefinition_.end())->first)) {
		throw std::invalid_argument(
			"Argument must be equal " + std::to_string(static_cast<int>(opponentDefinition_.begin()->first)) + " or "
				+ std::to_string(static_cast<int>((--opponentDefinition_.end())->first)));
	}
	params_.opponent = static_cast<OpponentGame>(count);
}

void MenuSettings::setRepeat()
{
	int count;

	std::cout << "Insert '0' - to disable repeat symbol, or '1' - to enable repeat symbol: ";
	std::cin >> count;

	params_.repeatSymbol = count;
}

void MenuSettings::readParams()
{
	try {
		const int max_length = 16;
		std::cout << std::setw(max_length) << "Numbers: " << params_.numb << "\n";
		std::cout << std::setw(max_length) << "Type: " << typeDefinition_.at(params_.type) << "\n";
		std::cout << std::setw(max_length) << "Repeat symbols: " << (params_.repeatSymbol ? "true" : "false") << "\n";
		std::cout << std::setw(max_length) << "Opponent: " << opponentDefinition_.at(params_.opponent) << "\n";
		std::cout << std::setw(max_length) << "Difficulty: " << difficultDefinition_.at(params_.difficulty) << "\n";
	}
	catch (std::exception &ex) {
		std::cerr << "Error read settings" << ex.what();
	}
}


}//namespace menu_settings