//
//  Lottery.hpp
//  LottoOdds
//
//  Created by Chris Chaffey on 2017-02-11.
//  Copyright © 2017 Chris Chaffey. All rights reserved.
//

#ifndef Lottery_hpp
#define Lottery_hpp

#include "LottoGenerator.hpp"

namespace Lotto
{

class Lottery: public LottoGenerator
{
public:
    Lottery(int lottoSize = Lotto::LOTTO_SIZE_DEFAULT, int maxNumber = Lotto::LOTTO_MAX_NUMBER);
    bool Compare(const LottoGenerator &guess) const;
    virtual void GenerateNewLotto();

private:
    std::vector<bool> mLottoSelected;

};


} // Lotto namespace

#endif /* Lottery_hpp */
