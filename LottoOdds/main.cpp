//
//  main.cpp
//  LottoOdds
//
//  Created by Chris Chaffey on 2017-02-11.
//  Copyright © 2017 Chris Chaffey. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <thread>
#include <atomic>
#include <future>
#include "Lottery.hpp"

static std::atomic<bool> found{false};

uint64_t LotteryTask(const Lotto::Lottery &lotto)
{
    Lotto::LottoGenerator guess;
    uint64_t iterations = 0;
    while (!found)
    {
        ++iterations;
        guess.GenerateNewLotto();
        if (lotto.Compare(guess))
        {
            found = true;
        }
    }
    return iterations;
}

uint64_t ExecuteLottery(const Lotto::Lottery &lotto, int threads, uint32_t &duration)
{
    found = false;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::vector<std::future<uint64_t>> futures;
    for (int i = 0; i < threads; ++i)
    {
        std::packaged_task<uint64_t(const Lotto::Lottery&)> package { LotteryTask };
        futures.push_back(package.get_future());
        std::thread t { std::move(package), lotto };
        t.detach();
    }
    uint64_t totalIterations = 0;
    for(std::future<uint64_t> &f : futures)
    {
        totalIterations += f.get();
    }
    auto diff = std::chrono::steady_clock::now() - start;
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
    return totalIterations;
}

int main(int argc, const char * argv[])
{
    Lotto::Lottery lotto;
    int threads = std::thread::hardware_concurrency();
    std::cout << "LottoOdds: Executing on " << threads << " threads." << std::endl;
    uint64_t totalIterations = 0;
    uint64_t totalExecutes = 100;
    std::vector<uint64_t> numIterations;
    std::vector<uint32_t> durations;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    for (int i = 0; i < totalExecutes; ++i)
    {
        lotto.GenerateNewLotto();
        uint32_t duration = 0;
        uint64_t numIteration = ExecuteLottery(lotto, threads, duration);
        totalIterations += numIteration;
        numIterations.push_back(numIteration);
        durations.push_back(duration);
    }

    auto diff = std::chrono::steady_clock::now() - start;
    std::cout << "Total time to run: " << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << "ms" << std::endl << std::endl;
    std::cout << "Average number of iterations: " << totalIterations / totalExecutes << std::endl;
    std::cout << "Per execution statistics:" << std::endl;
    for (int i = 0; i < totalExecutes; ++i)
    {
        std::cout << "\tExecution: " << std::setw(8) << i+1 << "\tNum of iterations: " << std::setw(10) << numIterations[i] <<  "\tDuration: " << durations[i]  << " ms" << std::endl;
    }
    
    std::cout << "Total iterations to find a match: " << totalIterations << std::endl << std::endl;
    return 0;

}
