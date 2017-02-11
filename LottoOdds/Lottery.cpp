//
//  Lottery.cpp
//  LottoOdds
//
//  Created by Chris Chaffey on 2017-02-11.
//  Copyright © 2017 Chris Chaffey. All rights reserved.
//

#include "Lottery.hpp"
#include "LotteryGuess.hpp"

using namespace Lotto;

Lottery::Lottery(int lottoSize, int maxNumber):
	LottoGenerator(lottoSize, maxNumber)
{
	GenerateNewLotto();
}

void Lottery::GenerateNewLotto()
{
	for (int i = 0; i <= mMaxNumber; ++i)
	{
		mLottoNumbers.push_back(false);
	}

	for (int i = 0; i < mLottoSize; ++i)
	{
		mLottoNumbers[distributions[i](mRngEngine)] = true;
	}
}

bool Lottery::Compare(const LotteryGuess &guess)
{
	for (int i = 0; i < mLottoSize; ++i)
	{
		
	}
	return true;
}
