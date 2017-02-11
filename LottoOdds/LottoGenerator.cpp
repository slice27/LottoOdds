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
	for (int i = 0; i < mLottoSize; ++i)
	{
		distributions.push_back(std::uniform_int_distribution<>(1, mMaxNumber - i));
	}
	// Add a 0 to the list of numbers.  It will never be used, but makes the vector 1 indexed.
	for (int i = 0; i <= mMaxNumber; ++i)
	{
		lottoNumbers.push_back(i);
	}
}


void LottoGenerator::GenerateNewLotto()
{
	for (int i = 0; i < mLottoSize; ++i)
	{
		int pos = distributions[i](mRngEngine);
		int tmp = lottoNumbers[pos];
		lottoNumbers[pos] = lottoNumbers[mMaxNumber-i];
		lottoNumbers[mMaxNumber-i] = tmp;
	}
}

bool LottoGenerator::Compare(LottoGenerator &rhs)
{
	for (int i = mMaxNumber-mLottoSize; i < mMaxNumber; ++i)
	{
		if (lottoNumbers[i] != rhs.lottoNumbers[i])
		{
			return false;
		}
	}
	return true;
}
