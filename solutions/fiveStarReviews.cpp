//
//  fiveStarReviews.cpp
//  leetcode
//
//  Created by Song Ding on 11/10/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace fiveStarReviews {
/*
// TODO: copy problem statement here
 Platform: HackerRank
 Position: SDE2
 Date: SEP 2020
 Country: US

 Given the number of five-star and total reviews for each product a company sells, as well as the threshold percentage, what is the minimum number of additional five-star reviews the company needs to become five star seller.
 For ex, there are 3 products (n=3) with productRatings =[[4,4],[1,2],[3,6]], percentage rating threshold = 77.
 [1,2] indicates => [1 (five star reviews) ,2 (total reviews)].
 We need to get the seller reach the threshold with minimum number of additional five star reviews.

 Before we add more five star reviews, the percentage for this seller is ((4/4) + (1/2) + (3/6))/3 = 66.66%
 If we add a five star review to 2nd product, ((4/4) + (2/3) + (3/6))/3 = 72.22%
 If we add another five star review to 2nd product, ((4/4) + (3/4) + (3/6))/3 = 75%
 If we add a five star review to 3rd product, ((4/4) + (3/4) + (4/7))/3 = 77.38%
 At this point, 77% (threshold) is met. Therefore, answer is 3 (because that is the minimum five star reviews we need to add, to get the seller reach the threshold).

 public static int fiveStarReviews(List<List<Integer>> productRatings, int ratingsThreshold){
 }
 Constraints:
 1<= productRatings.size() <=200
 In product ratings, [fivestar, total], fivestar <=100, total<=100
 1<=ratingsThreshold< 100
 productRatings contains only non negative integers.
*/
class Solution {
public:
    // TODO: copy function signature here
    int fiveStarReviews(vector<vector<int>>& pr, int ratingsThreshold) {
        // use priority queue to find which product to choose from
        auto cmp = [&pr](const auto& a, const auto& b){
            return (double)(a[1]-a[0])/a[1]/(a[1]+1)
            < (double)(b[1]-b[0])/b[1]/(b[1]+1);
        };
        int res = 0;
        double rt = 0, target = (double)ratingsThreshold * pr.size() / 100;
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> q(cmp);
        for (auto& v : pr) {
            q.push(v);
            rt += (double)v[0]/v[1];
        }
        while (rt < target) {
            auto v = q.top(); q.pop();
            rt += (double)(v[1]-v[0])/v[1]/(v[1]+1);
            ++res;
            ++v[0];
            ++v[1];
            q.push(v);
        }
        return res;
    }
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<vector<int>> productRatings;
        int ratingsThreshold;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{{4,4},{1,2},{3,6}},77}
    };
    // TODO: provide expected results here
    vector<int> answers {
        3,
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = fiveStarReviews::Solution().fiveStarReviews(dp.productRatings, dp.ratingsThreshold);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
