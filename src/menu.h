//
// Created by fedorenko on 24.10.2023.
//

#ifndef MENU_H
#define MENU_H

namespace menu_settings
{
enum class TypeGame
{
	numb,
	word
};

enum class DifficultyGame
{
	easy,
	medium,
	hard
};

enum class OpponentGame
{
	onlyPlayer,
	onlyComputer,
	ComputerVsPlayer,
	PlayerVsPlayer
};

struct Settings
{
	TypeGame type{TypeGame::numb};
	DifficultyGame difficulty{DifficultyGame::easy};
	OpponentGame opponent{OpponentGame::ComputerVsPlayer};
	int numb{4};
	bool repeatSymbol{false};
};

Settings settings();

}// namespace menu_settings

#endif //MENU_H
