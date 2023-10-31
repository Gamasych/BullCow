//
// Created by fedorenko on 31.10.2023.
//

#ifndef BULLS_COWS_H
#define BULLS_COWS_H

#include <iostream>

class BullsCows
{
public:
	BullsCows(int bulls = 0, int cows = 0)
		: bullsCows_(std::make_pair(bulls,cows))
	{}
	int bulls() const
	{
		return bullsCows_.first;
	}
	int cows() const
	{
		return bullsCows_.second ;
	}
	void setBulls(int bulls)
	{
		bullsCows_.first = bulls;
	}
	void setCows(int cows)
	{
		bullsCows_.second = cows;
	}
	bool operator==(const BullsCows& other)const{
		return bullsCows_ == other.bullsCows_;
	}
	bool operator<(const BullsCows& other)const{
		return bullsCows_ < other.bullsCows_;
	}
private:
	std::pair<int, int> bullsCows_;
};

std::ostream& operator<<(std::ostream &os, const BullsCows &counter);
std::istream &operator>>(std::istream &in, BullsCows &counter);


#endif //BULLS_COWS_H
