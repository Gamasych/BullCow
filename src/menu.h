//
// Created by fedorenko on 24.10.2023.
//

#ifndef MENU_H
#define MENU_H

#include <map>
#include <string>

namespace menu_settings
{

class MenuSettings
{
public:
	enum class TypeGame
	{
		numb,
		symbol,
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
		Settings();
		TypeGame type;
		DifficultyGame difficulty;
		OpponentGame opponent;
		int numb;
		bool repeatSymbol;
	};

	MenuSettings(const Settings &params = Settings());

	const Settings& getValue() const
	{ return params_; };
	void setValue(const Settings &params);
	Settings settings();

private:
	void setCount();
	void setType();
	void setDifficulty();
	void setOpponent();
	void setRepeat();
	void readParams();

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

	const int maxCount_;
	const int minCount_ ;
	Settings params_;
	const std::map<TypeGame, std::string> typeDefinition_;
	const std::map<DifficultyGame, std::string> difficultDefinition_;
	const std::map<OpponentGame, std::string> opponentDefinition_;
	const std::map<SettingsNumb, std::pair<std::string, void(MenuSettings::*)()>> settingsVal_;
};
}// namespace menu_settings

#endif //MENU_H
