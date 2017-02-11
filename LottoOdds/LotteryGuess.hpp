//
//  LotteryGuess.hpp
//  LottoOdds
//
//  Created by Chris Chaffey on 2017-02-11.
//  Copyright © 2017 Chris Chaffey. All rights reserved.
//

#ifndef LotteryGuess_hpp
#define LotteryGuess_hpp

#include "LottoGenerator.hpp"

namespace Lotto
{

class LotteryGuess: public LottoGenerator
{
public:
	LotteryGuess(int lottoSize = LOTTO_SIZE_DEFAULT, int maxNumber = LOTTO_MAX_NUMBER);
	void GenerateNewGuess();
	int GetGuessAtIndex(int index);
private:
	std::vector<int> mLottoNumbers;
	
};

} // Lotto namespace

#endif /* LotteryGuess_hpp */
