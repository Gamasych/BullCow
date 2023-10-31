//
// Created by fedorenko on 31.10.2023.
//

#include "bulls_cows.h"

std::ostream& operator<<(std::ostream &os, const BullsCows &counter)
{
	return os << "Bulls: " << counter.bulls() << ". Cows: " << counter.cows() << std::endl;
}

std::istream &operator>>(std::istream &in, BullsCows &counter)
{
	int bulls, cows;
	if (!(in >> bulls >> cows)) throw std::invalid_argument("Error! Insert bulls and cows");
	if (bulls < 0 || cows < 0) throw std::invalid_argument("Error! A negative number");
	counter.setBulls(bulls);
	counter.setCows(cows);
	return in;
}