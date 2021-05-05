// circularArrayLoop.cpp
// leetcode
//
// Created by  Song Ding on 9/13/18.
// Copyright © 2018 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace circularArrayLoop {
/**
 457. Circular Array Loop
 Medium

 192

 1051

 Favorite

 Share
 You are given a circular array nums of positive and negative integers. If a number k at an index is positive, then move forward k steps. Conversely, if it's negative (-k), move backward k steps. Since the array is circular, you may assume that the last element's next element is the first element, and the first element's previous element is the last element.

 Determine if there is a loop (or a cycle) in nums. A cycle must start and end at the same index and the cycle's length > 1. Furthermore, movements in a cycle must all follow a single direction. In other words, a cycle must not consist of both forward and backward movements.

  

 Example 1:

 Input: [2,-1,1,2,2]
 Output: true
 Explanation: There is a cycle, from index 0 -> 2 -> 3 -> 0. The cycle's length is 3.
 Example 2:

 Input: [-1,2]
 Output: false
 Explanation: The movement from index 1 -> 1 -> 1 ... is not a cycle, because the cycle's length is 1. By definition the cycle's length must be greater than 1.
 Example 3:

 Input: [-2,1,-1,-2,-2]
 Output: false
 Explanation: The movement from index 1 -> 2 -> 1 -> ... is not a cycle, because movement from index 1 -> 2 is a forward movement, but movement from index 2 -> 1 is a backward movement. All movements in a cycle must follow a single direction.
  

 Note:

 -1000 ≤ nums[i] ≤ 1000
 nums[i] ≠ 0
 1 ≤ nums.length ≤ 5000
 */

class Solution {
public:
    bool circularArrayLoop(vector<int>& nums) {
        int n = nums.size();
        if (n <= 0) {
            return false;
        }
        
        for (int i = 0; i < n; ++i) {
            int cnt = 0;
            int j = i;
            while (nums[i] * nums[j] > 0 && (j + nums[j] + n)%n != j) {
                if (cnt > n) {
                    return true;
                }
                j = (j + nums[j] + n) % n;
                ++cnt;
            }
        }
        return false;
    }
    /**
     * Use 0 to mark a visited node.
     */
    bool circularArrayLoop2(vector<int>& nums) {
        int n = nums.size();
        if (n <= 0) {
            return false;
        }
        
        for (auto& i : nums) {
            int j = i % n;
            if (i % n == 0) {
                if (i > 0) {
                    i = n;
                } else {
                    i = -n;
                }
            } else {
                i = j;
            }
        }
        
        int start = 0;
        while (start < n) {
            int j = 0;
            while (j < n) {
                if (nums[j] == 0) {
                    nums[j] = n * 2;
                }
                ++j;
            }
            
            ++start;
            while(start < n && nums[start] == n*2) {
                ++start;
            }
            if (start >= n) {
                return false;
            }
            
            int i = start;
            int type = nums[i];
            int last = i;
            while (true) {
                int v = nums[i];
                if (v == 0) {
                    cout << start << endl;
                    return true;
                }
            
                if (type > 0 && v < 0) {
                    break;
                } else if (type < 0 && v > 0) {
                    break;
                } else {
                    nums[i] = 0;
                    last = i;
                    i += v;
                    i %= n;
                    if (i < 0) {
                        i += n;
                    }
                    if (last == i) {
                        break;
                    }
                }
            }
        }
        return false;
    }
    
    /**
     * starting from each position, and walk the link and see until a change of direction is met or a revisit
     * of position, or result in a bad position.
     * if a change of direction is met, then all elements till the change of direction will not be in a proper cycle.
     * thus they can be skipped as the starting position.
     */
    bool circularArrayLoop3(vector<int>& nums) {
        int n = nums.size();
        // 0 => not set
        // 1 => visiting
        // 2 => bad
        vector<int> st(n, 0);
        for (int i = 0; i < n; ++i) {
            if (st[i]) {
                continue;
            }
            // walk the link
            st[i] = 1;
            int j = next(i, nums);
            while (st[j] == 0 && nums[i] * nums[j] > 0) {
                st[j] = 1;
                j = next(j, nums);
            }
            if (st[j] == 1) {
                // test whether length is 1
                int nj = next(j, nums);
                if (nj == j) {
                    st[j] = 2;
                    st[i] = 2;
                    int k = next(i, nums);
                    while (k != j) {
                        st[k] = 2;
                        k = next(k, nums);
                    }
                } else {
                    return true;
                }
            } else {
                st[i] = 2;
                int k = next(i, nums);
                while (k != j) {
                    st[k] = 2;
                    k = next(k, nums);
                }
            }
        }
        return false;
    }

private:
    int next(int i, vector<int>& nums) {
        int n = nums.size();
        int j = i + nums[i];
        if (j >= n) {
            j %= n;
        } else {
            while (j < 0) {
                j += n;
            }
        }
        return j;
    }
};

}

/*/
int main() {
    // TODO: prepare parameters here
    struct d {
        vector<int> nums;
    };
    vector<struct d> p {
        {{-2,-3,-9}},
        {{2,-1,1,-2,-2}},
        {{2, -1, 1, 2, 2}},
        {{-1, 2}},
        {{-1,-2,-3,-4,-5}},
        {{3,1,2}},
        {{1, -1, 1,1,1,1,1,1,1,5}},
    };
    
    vector< bool > answers {
        false,
        true,
        false,
        false,
        true,
        true,
    };

    // TODO: add return type and paramters.
    for (auto& dp : p) {
        clock_t start = clock();
        auto res = circularArrayLoop::Solution().circularArrayLoop3(dp.nums);
        cout << "time=" << clock() - start << endl;
        cout << res << endl << endl;
    }
    return 0;
}
//*/
