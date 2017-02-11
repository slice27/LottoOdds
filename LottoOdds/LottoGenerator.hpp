//
//  LottoGenerator.hpp
//  LottoOdds
//
//  Created by Chris Chaffey on 2017-02-11.
//  Copyright © 2017 Chris Chaffey. All rights reserved.
//

#ifndef LottoGenerator_hpp
#define LottoGenerator_hpp

#include <stdint.h>
#include <random>
#include <vector>

namespace Lotto
{

static const int LOTTO_SIZE_DEFAULT = 6;
static const int LOTTO_MAX_NUMBER   = 49;

class LottoGenerator
{
public:
	LottoGenerator(int lottoSize = LOTTO_SIZE_DEFAULT, int maxNumbers = LOTTO_MAX_NUMBER);
	virtual void GenerateNewLotto() = 0;

protected:
	int mLottoSize;
	int mMaxNumber;
	std::mt19937 mRngEngine;
	std::vector<std::uniform_int_distribution<>> distributions;

private:
	template<class T = std::mt19937, std::size_t N = T::state_size>
	auto ProperlySeededRandomEngine () -> typename std::enable_if<!!N, T>::type {
		typename T::result_type random_data[N];
		std::random_device source;
		std::generate(std::begin(random_data), std::end(random_data), std::ref(source));
		std::seed_seq seeds(std::begin(random_data), std::end(random_data));
		T seededEngine (seeds);
		return seededEngine;
	}
};

} // Lotto namespace

#endif /* LottoGenerator_hpp */
