//
//  main.cpp
//  LottoOdds
//
//  Created by Chris Chaffey on 2017-02-11.
//  Copyright © 2017 Chris Chaffey. All rights reserved.
//

#include <iostream>
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

int main(int argc, const char * argv[])
{
    Lotto::Lottery lotto;
    int threads = std::thread::hardware_concurrency();
    std::cout << "Executing on " << threads << " threads." << std::endl;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::vector<std::future<uint64_t>> futures;
    for (int i = 0; i < threads; ++i)
    {
        std::packaged_task<uint64_t(const Lotto::Lottery&)> package { LotteryTask };
        futures.push_back(package.get_future());
        std::thread t { std::move(package), lotto };
        t.detach();
    }
    for(std::future<uint64_t> &f : futures)
    {
        f.wait();
    }
    auto diff = std::chrono::steady_clock::now() - start;
    std::cout << "Total time to run: " << std::chrono::duration_cast<std::chrono::milliseconds>(diff).count() << "ms" << std::endl;
    int threadNumber = 0;
    int64_t totalIterations = 0;
    for (std::future<uint64_t> &f : futures)
    {
        int64_t iterations = f.get();
        totalIterations += iterations;
        std::cout << "Thread " << ++threadNumber << " Iterations:" << iterations << std::endl;
    }
    std::cout << "Total iterations to find a match: " << totalIterations << std::endl << std::endl;
    return 0;

}
