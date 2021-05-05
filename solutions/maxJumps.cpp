//
//  maxJumps.cpp
//  leetcode
//
//  Created by Song Ding on 8/10/20.
//  Copyright © 2020 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace maxJumps {
/*
// TODO: copy problem statement here
 1340. Jump Game V
 Hard

 225

 11

 Add to List

 Share
 Given an array of integers arr and an integer d. In one step you can jump from index i to index:

 i + x where: i + x < arr.length and 0 < x <= d.
 i - x where: i - x >= 0 and 0 < x <= d.
 In addition, you can only jump from index i to index j if arr[i] > arr[j] and arr[i] > arr[k] for all indices k between i and j (More formally min(i, j) < k < max(i, j)).

 You can choose any index of the array and start jumping. Return the maximum number of indices you can visit.

 Notice that you can not jump outside of the array at any time.

  

 Example 1:


 Input: arr = [6,4,14,6,8,13,9,7,10,6,12], d = 2
 Output: 4
 Explanation: You can start at index 10. You can jump 10 --> 8 --> 6 --> 7 as shown.
 Note that if you start at index 6 you can only jump to index 7. You cannot jump to index 5 because 13 > 9. You cannot jump to index 4 because index 5 is between index 4 and 6 and 13 > 9.
 Similarly You cannot jump from index 3 to index 2 or index 1.
 Example 2:

 Input: arr = [3,3,3,3,3], d = 3
 Output: 1
 Explanation: You can start at any index. You always cannot jump to any index.
 Example 3:

 Input: arr = [7,6,5,4,3,2,1], d = 1
 Output: 7
 Explanation: Start at index 0. You can visit all the indicies.
 Example 4:

 Input: arr = [7,1,7,1,7,1], d = 2
 Output: 2
 Example 5:

 Input: arr = [66], d = 1
 Output: 1
  

 Constraints:

 1 <= arr.length <= 1000
 1 <= arr[i] <= 10^5
 1 <= d <= arr.length
*/
class Solution {
public:
    // TODO: copy function signature here
    int maxJumps_topology2(vector<int>& arr, int d) {
        // construct jump connection using monotonic queue
        int n = arr.size();
        vector<int> starts;
        vector<vector<int>> conn(n);
        vector<int> indgr(n, 0);
        vector<int> bq; // as stack
        for (int i = 0; i < n; ++i) {
            while (bq.size() && arr[bq.back()] < arr[i]) {
                int b = bq.back();
                bq.pop_back();
                if (i-b <= d) {
                    ++indgr[b];
                    conn[i].push_back(b);
                }
            }
            bq.push_back(i);
        }
        bq.clear();
        for (int i = n-1; i >= 0; --i) {
            while (bq.size() && arr[bq.back()] < arr[i]) {
                int b = bq.back();
                bq.pop_back();
                if (b-i <= d) {
                    ++indgr[b];
                    conn[i].push_back(b);
                }
            }
            bq.push_back(i);
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (!indgr[i]) {
                q.push(i);
            }
        }
        int res = 0;
        while (q.size()) {
            ++res;
            int qn = q.size();
            while (qn--) {
                int cur = q.front();
                q.pop();
                for (auto nc : conn[cur]) {
                    if (--indgr[nc] == 0) {
                        q.push(nc);
                    }
                }
            }
        }
        return res;
    }
    
    int maxJumps_topology(vector<int>& arr, int d) {
        // construct jump connection
        int n = arr.size();
        vector<int> starts;
        vector<vector<int>> conn(n);
        vector<int> indgr(n, 0);
        for (int i = 0; i < n; ++i) {
            int blockh = 0;
            for (int j = 1; j <= d && i+j < n; ++j) {
                int k = i + j;
                if (arr[i] < arr[k] && blockh < arr[k]) {
                    conn[i].push_back(k);
                    ++indgr[k];
                } else if (arr[i] > arr[k] && arr[i] > blockh) {
                    conn[k].push_back(i);
                    ++indgr[i];
                }
                blockh = max(blockh, arr[k]);
            }
        }
        queue<int> q;
        for (int i = 0; i < n; ++i) {
            if (!indgr[i]) {
                q.push(i);
            }
        }
        int res = 0;
        while (q.size()) {
            ++res;
            int qn = q.size();
            while (qn--) {
                int cur = q.front();
                q.pop();
                for (auto nc : conn[cur]) {
                    if (--indgr[nc] == 0) {
                        q.push(nc);
                    }
                }
            }
        }
        return res;
    }
    // dfs: starting from all local bottoms and expand them
    // update each position's jump count if reached by a larger jump count.
    int maxJumps_dfs(vector<int>& arr, int d) {
        // construct jump connection
        int n = arr.size();
        vector<int> jcnts(n, 0);
        int res = 0;
        for (int i = 0; i < n; ++i) {
            res = max(res, dfs(i, d, arr, jcnts));
        }
        return res;
    }
    int dfs(int start, int d, vector<int>& arr, vector<int>& jcnts) {
        if (jcnts[start]) {
            return jcnts[start];
        }
        jcnts[start] = 1;
        for (int i = 1; i <= d && start-i >= 0 && arr[start-i] < arr[start]; ++i) {
            jcnts[start] = max(jcnts[start], 1+dfs(start-i, d, arr, jcnts));
        }
        for (int i = 1; i <= d && start+i < arr.size() && arr[start+i] < arr[start]; ++i) {
            jcnts[start] = max(jcnts[start], 1+dfs(start+i, d, arr, jcnts));
        }
        return jcnts[start];
    }
    // divide & conque
    int maxJumps_dc(vector<int>& arr, int d) {
        int n = arr.size();
        vector<int> jcnts(n, 1);
        recur(arr, 0, n-1, d, jcnts);
        return *max_element(begin(jcnts), end(jcnts));
    }
    void recur(vector<int>& arr, int l, int r, int d, vector<int>& jcnts) {
        if (l == r) {
            jcnts[l] = 1;
            return;
        }
        // find the maxi
        int maxi = l;
        for (int i = l; i <= r; ++i) {
            if (arr[maxi] < arr[i]) {
                maxi = i;
            }
        }
        if (l < maxi) {
            recur(arr, l, maxi-1, d, jcnts);
        }
        if (maxi < r) {
            recur(arr, maxi+1, r, d, jcnts);
        }
        
        for (int i = 1; i <= d && maxi-i>= l && arr[maxi-i] < arr[maxi]; ++i) {
            jcnts[maxi] = max(jcnts[maxi], 1+jcnts[maxi-i]);
        }
        for (int i = 1; i <= d && maxi+i <= r && arr[maxi+i] < arr[maxi]; ++i) {
            jcnts[maxi] = max(jcnts[maxi], 1+jcnts[maxi+i]);
        }
    }
    
private:
};
}

/*
int main() {
    // TODO: define parameter type here
    struct param {
        vector<int> arr;
        int d;
    };
    // TODO: prepare parameters here
    vector<struct param> params {
        {{3,3,3,3,3},3},
        {{6,4,14,6,8,13,9,7,10,6,12},2},
        {{37449,50826,48629,53457,86176,97983,30514,627,4435,2060,29389,61805,81013,77709,53595,70058,5069,64876,16877,86462,29078,40015,33538,76245,89300,82728,787,44496,10595,94004,22033,42312,49798,21686,91232,8272,63958,11193,18547,35163,29483,173,71856,39955,20475,85083,71039,98042,59518,61701,72475,17365,58597,82973,85426,62948,55685,17682,50585,96607,9603,18759,62694,59375,7470,75354,32727,93664,73526,70046,21251,58173,61504,8378,33884,39283,8689,84885,92640,10654,32983,2254,52601,52419,20809,21623,63763,34479,69429,18146,83143,96564,17384,98971,12456,81585,31227,22088,67361,26411,94406,78798,45898,31617,9400,40398,15790,36242,32237,84431,39759,69209,36354,25113,77450,10245,58021,99122,52202,35290,91451,84688,97832,95735,21995,89952,25394,51514,82576,16896,38207,43068,56094,35040,2018,67432,56389,55014,76849,69765,39357,31498,91292,51610,27699,50415,83988,70298,65469,30195,11643,82188,36491,89890,14208,22437,91121,2352,22067,33340,4728,11845,70960,2658,60952,98606,34672,88947,71973,23022,13549,71255,11015,99973,52568,5279,56706,26863,1202,1489,6356,90219,12738,5483,38469,91151,61572,3063,16464,65999,16224,49143,61152,38076,53195,87479,24751,77976,15029,44456,28904,67360,72300,93089,87011,19183,43587,39795,18713,95684,92147,19682,803,47293,34627,55103,41807,62202,54888,85754,30623,35768,59940,98546,57429,6523,33555,26230,72172,33994,31347,1609,80247,89388,37009,15703,23013,75390,34112,51860,64600,64667,81081,74253,59074,2701,48244,42148,56882,22527,82185,15911,49344,3471,77848,20316,32402,13019,41956,95396,42981,16807,73148,40632,86040,20419,48314,39262,72237,74545,25935,67363,51557,10146,98653,2230,38975,96955,10529,11005,30399,96496,26839,16194,13144,56444,10674,79233,86663,15913,74886,44431,94163,32735,85938,62949,78762,77235,41341,94316,44306,18218,82013,8362,53230,17999,29721,61252,54937,23496,84264,90326,58320,84225,30953,40659,83774,19586,86885,59322,93483,51776,5564,33257,88923,50295,70592,80526,24336,47628,83882,98169,88703,106,66220,45006,58509,81141,94412,66118,56382,48337,72129,13006,77211,15314,37452,50376,87922,16398,80299,72092,58636,20458,89500,19648,74595,24538,1668,89159,19896,39735,42861,27710,55931,31530,31413,35700,91816,52665,99708,86372,23211,46788,5519,13337,93757,36790,47676,3241,62023,14553,61904,23788,16192,48944,57217,348,55490,56590,19429,57804,73245,24216,64336,91729,33902,83639,66672,68688,75613,59632,31297,4600,87655,82579,72056,49072,73013,15651,30881,50431,478,28773,95946,88079,86656,12603,78007,81698,41759,13689,61100,8862,34022,13896,5440,72136,22702,30383,83519,32176,31262,54792,6724,8020,78067,14443,47181,4066,85515,38245,53818,9098,93970,45048,95608,15273,90554,70413,13297,95552,63566,49880,84064,61365,96238,87622,75755,30931,29077,39539,51470,36387,43578,97550,96289,74465,67023,96735,32580,1070,26819,85655,65675,22521,46583,58297,36805,60090,70400,79517,42405,39319,21826,10637,2741,59523,47521,79607,4108,73738,83182,64704,9522,19409,9665,33930,72285,71414,1337,13709,69633,28858,28531,61419,32597,71155,36837,35194,71706,96628,92304,93771,80016,43088,79217,15158,54800,91113,83692,71282,14448,94720,39445,24452,68626,703,48679,92539,61503,89226,12358,84643,43684,71258,37233,38282,27089,31387,57812,4861,14923,52580,55479,54656,26534,90430,74987,86232,18711,72811,48240,62705,21011,37945,24035,82796,71739,67807,94030,54749,95023,62118,31340,67596,52267,74468,20289,52988,85468,22678,10369,8575,88620,2280,90774,9937,46214,29669,87768,23679,33684,1364,40796,29850,81238,5718,83561,96586,68151,1731,14431,91326,96789,91893,51419,19949,68360,82859,75303,22351,93268,26816,52724,75794,15175,3024,69546,16836,92676,25457,24176,66897,93801,87130,78646,2110,80905,49714,12487,56422,92883,1796,96810,28584,27688,24114,11884,7949,37770,20658,90547,89481,21231,14164,41474,98077,47303,86161,89992,6256,98964,45778,93057,50081,79025,2067,33701,87505,86300,61209,78660,76381,84377,14182,41855,17622,68347,66496,79083,28786,38737,36173,42653,75924,17356,90963,45594,38441,51175,89862,4969,38974,79088,20481},349},
    };
    // TODO: provide expected results here
    vector<int> answers {
    };
    
    for (auto& dp : params) {
        cout << endl;
        clock_t tstart = clock();
        auto res = maxJumps::Solution().maxJumps_topology2(dp.arr, dp.d);
        cout << res << endl;
        cout << clock() - tstart << endl;
    }

    return 0;
}
//*/
