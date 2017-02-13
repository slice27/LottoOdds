//
//  LottoGenerator.cpp
//  LottoOdds
//
//  Created by Chris Chaffey on 2017-02-11.
//  Copyright © 2017 Chris Chaffey. All rights reserved.
//

#include "LottoGenerator.hpp"

using namespace Lotto;

LottoGenerator::LottoGenerator(int lottoSize, int maxNumber):
    mLottoSize(lottoSize),
    mMaxNumber(maxNumber),
    mRngEngine(ProperlySeededRandomEngine<>())
{
    for (int i = 1; i <= mMaxNumber; ++i)
    {
        mLottoNumbers.push_back(i);
    }
    for (int i = 0; i <= mLottoSize; ++i)
    {
        distributions.push_back(std::uniform_int_distribution<>(i, mMaxNumber-1));
    }
}

void LottoGenerator::GenerateNewLotto()
{
    for (int i = 0; i < mLottoSize; ++i)
    {
        int pos = distributions[i](mRngEngine);
        int tmp = mLottoNumbers[i];
        mLottoNumbers[i] = mLottoNumbers[pos];
        mLottoNumbers[pos] = tmp;
    }
}

int LottoGenerator::GetNumberAtIndex(int index) const
{
    if (index < 0 || index >= mLottoSize) return -1;
    return mLottoNumbers[index];
}
