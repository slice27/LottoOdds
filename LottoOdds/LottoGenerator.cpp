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
}
