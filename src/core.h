//
// Created by fedorenko on 25.10.2023.
//

#ifndef CORE_H
#define CORE_H

#include "menu.h"
#include <map>
#include <string>

namespace core
{
class CoreGame
{
public:
	CoreGame();
	void start();

private:
	void playGame();
	void settingsGame();
	void exitGame();



	enum class CommandNumb
	{
		play,
		settings,
		exit
	};

	const std::map<CommandNumb, std::pair<std::string, void(CoreGame::*)()>> commandMenu_;
	menu_settings::MenuSettings settings_;
};

} // core

#endif //CORE_H
