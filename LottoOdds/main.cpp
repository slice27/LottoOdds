//
//  main.cpp
//  LottoOdds
//
//  Created by Chris Chaffey on 2017-02-11.
//  Copyright © 2017 Chris Chaffey. All rights reserved.
//

#include <iostream>
#include "Lottery.hpp"
#include "LotteryGuess.hpp"

int main(int argc, const char * argv[])
{
	Lotto::Lottery lotto;
	Lotto::LotteryGuess guess;

	if (lotto.Compare(guess))
		std::cout << "Guess matched the lotto." << std::endl;
	else
		std::cout << "Guess did not match the lotto." << std::endl;
    return 0;
}
