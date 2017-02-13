//
//  Lottery.cpp
//  LottoOdds
//
//  Created by Chris Chaffey on 2017-02-11.
//  Copyright © 2017 Chris Chaffey. All rights reserved.
//

#include "Lottery.hpp"

using namespace Lotto;

Lottery::Lottery(int lottoSize, int maxNumber):
	LottoGenerator(lottoSize, maxNumber)
{
    GenerateNewLotto();
}

void Lottery::GenerateNewLotto()
{
    mLottoSelected.clear();
    for (int i = 0; i <= mMaxNumber; ++i)
    {
        mLottoSelected.push_back(false);
    }
    LottoGenerator::GenerateNewLotto();
    for (int i = 0; i < mLottoSize; ++i)
    {
        mLottoSelected[GetNumberAtIndex(i)] = true;
    }
}

bool Lottery::Compare(const LottoGenerator &guess) const
{
    for (int i = 0; i < mLottoSize; ++i)
    {
        if (!mLottoSelected[guess.GetNumberAtIndex(i)])
        {
            return false;
        }
    }
    return true;
}
