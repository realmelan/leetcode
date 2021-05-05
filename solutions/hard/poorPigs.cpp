// poorPigs.cpp
// leetcode
//
// Created by  Song Ding on 9/21/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace poorPigs {
/*
// TODO: copy problem statement here
 458. Poor Pigs
 Hard
 
 314
 
 741
 
 Favorite
 
 Share
 There are 1000 buckets, one and only one of them is poisonous, while the rest are filled with water. They all look identical. If a pig drinks the poison it will die within 15 minutes. What is the minimum amount of pigs you need to figure out which bucket is poisonous within one hour?
 
 Answer this question, and write an algorithm for the general case.
 
 
 
 General case:
 
 If there are n buckets and a pig drinking poison will die within m minutes, how many pigs (x) you need to figure out the poisonous bucket within p minutes? There is exactly one bucket with poison.
 
 
 
 Note:
 
 A pig can be allowed to drink simultaneously on as many buckets as one would like, and the feeding takes no time.
 After a pig has instantly finished drinking buckets, there has to be a cool down time of m minutes. During this time, only observation is allowed and no feedings at all.
 Any given bucket can be sampled an infinite number of times (by an unlimited number of pigs).
 */

class Solution {
public:
    /**
     * In the last round, we can feed pigs with bucket like this:
     *  1, a pig feed one exclusive bucket
     *  2, any 2 pigs feed one exclusive bucket
     *  3, any 3 pigs feed one exclusive bucket
     *  4, ...
     *  5, any x pigs feed one exclusive buckets
     * suppose there are x pigs, then total buckets = 2^x
     *
     * Let f(x,r) = maximum buckets that x pigs can test in r round
     *  then f(x,r) = f(x,r-1)*1+f(x-1,r-1)*C(x,1)+f(x-2,r-1)*C(x,2)+f(x-3,r-1)*C(x,3)+...
     *  and f(x,1) = 2^x.
     * it turns out that f(x,r)=(r+1)^x.
     *
     * Here is another way of interpretating f(x,r)=(r+1)^x.
     * let i-th pig feeds buckets whose (r+1) based form's i-th bit is r.
     * if x1 pig die, then x1 bit is set to r, and we have x-x1 pigs left and also x-x1 bits to test.
     * next round, we don't have to test bit r, but test bit r-1.
     * so on and so forth.
     *
     * Very simple reason:
     * Note that during t tests, each pig has exactly t+1 possible different statuses:
     * died at some Test#j (1<=j<=t) or still alive after all.
     * It means one pig can determins one position up to r+1 different values.
     * So the maximum number of possible statuses of n pigs with t tests is straightforward dp[n][t] = (t+1)^n.
     *
     */
    int poorPigs(int buckets, int minutesToDie, int minutesToTest) {
        int r = minutesToTest / minutesToDie;
        int x = log(buckets)/log(r+1);
        if (pow(r+1, x) < buckets) {
            return x+1;
        }
        return x;
    }
    /**
     * suppose for the last round, you have x4 pigs left, so max buckets to test is x4+1;
     * move back, say for the second to the last round, you have x3 pig left, then you can test
     * as many as (x4+1)*(x3+1)
     * so on so forth, the for 4 rounds, maximum buckets we can test is (x4+1)(x3+1)(x2+1)(x1+1).
     * Note, at each round at most 1 pig would die so basically x4=x3-1, x2=x1-1, etc
     *
     * suppose we have x pigs in the first round, and for 4 rounds, we can test maximum
     * (x-3+1)*(x-2+1)*(x-1+1)*(x+1)=(x-2)*(x-1)*x*(x+1) buckets.
     */
    int poorPigs_wrong(int buckets, int minutesToDie, int minutesToTest) {
        int rounds = minutesToTest / minutesToDie;
        int x = pow(buckets, 1.0/rounds)-1;
        while (true) {
            int p = 1;
            for (int i = 0; i < rounds; ++i) {
                p *= (x-i+1);
            }
            if (p >= buckets) {
                break;
            }
            ++x;
        }
        return x;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        int buckets;
        int minutesToDie;
        int minutesToTest;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {1000,15,60},
        {1000,15,15},
    };

    vector< int > answers {
        5,
        10,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = poorPigs::Solution().poorPigs(dp.buckets, dp.minutesToDie, dp.minutesToTest);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
