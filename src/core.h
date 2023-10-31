//
// Created by fedorenko on 25.10.2023.
//

#ifndef CORE_H
#define CORE_H

#include "menu.h"
#include "generator.h"
#include "knut.h"
#include "common_types.h"
#include <map>
#include <string>
#include <memory>

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

	template<Symbol T>
	void player(std::shared_ptr<BaseFunctional<T> > generator);
	template<Symbol T>
	void computer(std::shared_ptr<knut::KnutBase<T>> knut);
	template<Symbol T>
	void playerVsComputer(std::shared_ptr<BaseFunctional<T> > generator, std::shared_ptr<knut::KnutBase<T>> knut);

	enum class CommandNumb
	{
		play,
		settings,
		exit
	};

	const std::map<CommandNumb, std::pair<std::string, void (CoreGame::*)()>> commandMenu_;
	menu_settings::MenuSettings settings_;
};

} // core

#endif //CORE_H