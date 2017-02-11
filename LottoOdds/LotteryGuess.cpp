//
//  LotteryGuess.cpp
//  LottoOdds
//
//  Created by Chris Chaffey on 2017-02-11.
//  Copyright © 2017 Chris Chaffey. All rights reserved.
//

#include "LotteryGuess.hpp"

using namespace Lotto;

LotteryGuess::LotteryGuess(int lottoSize, int maxNumber):
	LottoGenerator(lottoSize, maxNumber)
{
	for (int i = 1; i <= mMaxNumber; ++i)
	{
		mLottoNumbers.push_back(i);
	}
}

void LotteryGuess::GenerateNewGuess()
{
	for (int i = 0; i < mLottoSize; ++i)
	{
		int pos = distributions[i](mRngEngine);
		int tmp = mLottoNumbers[pos];
		mLottoNumbers[pos] = mLottoNumbers[mMaxNumber-i-1];
		mLottoNumbers[mMaxNumber-i-1] = tmp;
	}
}

int LotteryGuess::GetGuessAtIndex(int index)
{
	return mLottoNumbers[mMaxNumber-(mLottoSize+index)];
}
