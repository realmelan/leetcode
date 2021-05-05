//
//  minmaxGasDist.cpp
//  leetcode
//
//  Created by Song Ding on 2/20/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace minmaxGasDist {
/*
// TODO: copy problem statement here
 774. Minimize Max Distance to Gas Station
  

 On a horizontal number line, we have gas stations at positions stations[0], stations[1], ..., stations[N-1], where N = stations.length.

 Now, we add K more gas stations so that D, the maximum distance between adjacent gas stations, is minimized.

 Return the smallest possible value of D.

 Example:

 Input: stations = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], K = 9
 Output: 0.500000
 Note:

 stations.length will be an integer in range [10, 2000].
 stations[i] will be an integer in range [0, 10^8].
 K will be an integer in range [1, 10^6].
 Answers within 10^-6 of the true value will be accepted as correct.
*/
class Solution {
public:
    // TODO: copy function signature here
    /**
     do binary search on the min max distance between stations. say current target distance is mid,
     then from the first station, and its distance to next station is larger than mid, then insert a number
     of stations to make the distance smaller. if all gas station can be arranged, then min max distance
     can be smaller.
     */
    double minmaxGasDist(vector<int>& stations, int K) {
        sort(stations.begin(), stations.end());
        double right = 0;
        for (int i = 1; i < stations.size(); ++i) {
            if (stations[i] - stations[i-1] > right) {
                right = stations[i] - stations[i-1];
            }
        }
        double left = 0;
        while (right - left > 0.0000001) {
            double mid = left + (right - left) / 2;
            if (check(stations, K, mid)) {
                right = mid;
            } else {
                left = mid;
            }
        }
        return left;
    }
    
    bool check(vector<int>& stations, int K, double mid) {
        int need = 0;
        for (int i = 1; i < stations.size(); ++i) {
            int t = ceil((stations[i] - stations[i-1]) / mid) - 1;
            need += t;
        }
        return need <= K;
    }
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> stations;
        int K;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{1, 2, 3, 4, 5, 6, 7, 8, 9, 10},9},
        {{10, 19, 25, 27, 56, 63, 70, 87, 96, 97},3}
    };
    // TODO: provide expected results here
    vector<double> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = minmaxGasDist::Solution().minmaxGasDist(dp.stations, dp.K);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
