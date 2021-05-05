// oddEvenJumps.cpp
// leetcode
//
// Created by  Song Ding on 9/15/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace oddEvenJumps {
/*
// TODO: copy problem statement here
 975. Odd Even Jump
 Hard
 
 410
 
 122
 
 Favorite
 
 Share
 You are given an integer array A.  From some starting index, you can make a series of jumps.  The (1st, 3rd, 5th, ...) jumps in the series are called odd numbered jumps, and the (2nd, 4th, 6th, ...) jumps in the series are called even numbered jumps.
 
 You may from index i jump forward to index j (with i < j) in the following way:
 
 During odd numbered jumps (ie. jumps 1, 3, 5, ...), you jump to the index j such that A[i] <= A[j] and A[j] is the smallest possible value.  If there are multiple such indexes j, you can only jump to the smallest such index j.
 During even numbered jumps (ie. jumps 2, 4, 6, ...), you jump to the index j such that A[i] >= A[j] and A[j] is the largest possible value.  If there are multiple such indexes j, you can only jump to the smallest such index j.
 (It may be the case that for some index i, there are no legal jumps.)
 A starting index is good if, starting from that index, you can reach the end of the array (index A.length - 1) by jumping some number of times (possibly 0 or more than once.)
 
 Return the number of good starting indexes.
 
 
 
 Example 1:
 
 Input: [10,13,12,14,15]
 Output: 2
 Explanation:
 From starting index i = 0, we can jump to i = 2 (since A[2] is the smallest among A[1], A[2], A[3], A[4] that is greater or equal to A[0]), then we can't jump any more.
 From starting index i = 1 and i = 2, we can jump to i = 3, then we can't jump any more.
 From starting index i = 3, we can jump to i = 4, so we've reached the end.
 From starting index i = 4, we've reached the end already.
 In total, there are 2 different starting indexes (i = 3, i = 4) where we can reach the end with some number of jumps.
 Example 2:
 
 Input: [2,3,1,1,4]
 Output: 3
 Explanation:
 From starting index i = 0, we make jumps to i = 1, i = 2, i = 3:
 
 During our 1st jump (odd numbered), we first jump to i = 1 because A[1] is the smallest value in (A[1], A[2], A[3], A[4]) that is greater than or equal to A[0].
 
 During our 2nd jump (even numbered), we jump from i = 1 to i = 2 because A[2] is the largest value in (A[2], A[3], A[4]) that is less than or equal to A[1].  A[3] is also the largest value, but 2 is a smaller index, so we can only jump to i = 2 and not i = 3.
 
 During our 3rd jump (odd numbered), we jump from i = 2 to i = 3 because A[3] is the smallest value in (A[3], A[4]) that is greater than or equal to A[2].
 
 We can't jump from i = 3 to i = 4, so the starting index i = 0 is not good.
 
 In a similar manner, we can deduce that:
 From starting index i = 1, we jump to i = 4, so we reach the end.
 From starting index i = 2, we jump to i = 3, and then we can't jump anymore.
 From starting index i = 3, we jump to i = 4, so we reach the end.
 From starting index i = 4, we are already at the end.
 In total, there are 3 different starting indexes (i = 1, i = 3, i = 4) where we can reach the end with some number of jumps.
 Example 3:
 
 Input: [5,1,3,4,2]
 Output: 3
 Explanation:
 We can reach the end from starting indexes 1, 2, and 4.
 
 
 Note:
 
 1 <= A.length <= 20000
 0 <= A[i] < 100000
 */

class Solution {
public:
    int oddEvenJumps(vector<int>& A) {
        return oddEvenJumps_monotonic(A);
    }
    //
    int oddEvenJumps_monotonic(vector<int>& A) {
        int n = A.size();
        vector<pair<int,int>> B;
        for (int i = 0; i < n; ++i) {
            B.emplace_back(A[i], i);
        }
        sort(begin(B), end(B));
        vector<int> odd(n+1,n), even(n+1,n);
        stack<int> oddq, evenq;
        for (int i = n-1; i >= 0; --i) {
            while (oddq.size() && B[i].second > oddq.top()) {
                oddq.pop();
            }
            if (oddq.size()) {
                odd[B[i].second] = oddq.top();
            }
            oddq.push(B[i].second);
        }
        sort(begin(B), end(B), [](const pair<int,int>&a, const pair<int,int>&b){
            return a.first != b.first ? a.first > b.first : a.second < b.second;
        });
        for (int i = n-1; i >= 0; --i) {
            while (evenq.size() && B[i].second > evenq.top()) {
                evenq.pop();
            }
            if (evenq.size()) {
                even[B[i].second] = evenq.top();
            }
            evenq.push(B[i].second);
        }
        int res = 1;
        vector<int> good(n, 0);
        good[n-1] = 1;
        even[n-1] = n-1;
        for (int i = n-2; i >= 0; --i) {
            res += (good[i] = good[even[odd[i]]]);
        }
        return res;
    }
    // starting from the end index, and expand odd list and even list
    int oddEvenJumps_bfs(vector<int>& A) {
        int n = A.size();
        vector<vector<int>> oddIn(n), evenIn(n);
        map<int, int> s1, s2;
        for (int i = n-1; i >= 0; --i) {
            auto it1 = s1.lower_bound(A[i]);
            if (it1 != s1.end()) {
                oddIn[it1->second].push_back(i);
            }
            s1[A[i]] = i;
            
            auto it2 = s2.lower_bound(-A[i]);
            if (it2 != s2.end()) {
                evenIn[it2->second].push_back(i);
            }
            s2[-A[i]] = i;
        }
        int res = 1;
        // starting from last index
        vector<vector<bool>> good(n, vector<bool>(2, false));
        good[n-1][0] = good[n-1][1] = true;
        queue<int> q1, q2;
        q1.push(n-1);
        q2.push(n-1);
        while (q1.size() || q2.size()) {
            int q1n = q1.size();
            int q2n = q2.size();
            while (q1n--) {
                int c1 = q1.front();
                q1.pop();
                for (auto i : oddIn[c1]) {
                    if (!good[i][1]) {
                        ++res;
                        good[i][1] = true;
                        q2.push(i);
                    }
                }
            }
            while (q2n--) {
                int c2 = q2.front();
                q2.pop();
                for (auto i : evenIn[c2]) {
                    if (!good[i][0]) {
                        good[i][0] = true;
                        q1.push(i);
                    }
                }
            }
        }
        return res;
    }
    // start from each index and see whether it can reach a good index
    int oddEvenJumps_dfs(vector<int>& A) {
        int n = A.size();
        int res = 0;
        // 1=>ok, -1=>bad, 0=>not set
        vector<vector<int>> good(n, vector<int>(2, 0));
        good[n-1][0] = good[n-1][1] = 1;
        vector<vector<int>> conn(2, vector<int>(n));
        map<int, int> s1, s2;
        for (int i = n-1; i >= 0; --i) {
            auto it1 = s1.lower_bound(A[i]);
            if (it1 != s1.end()) {
                conn[1][i] = it1->second;
                res += (good[i][1] = good[conn[0][it1->second]][1]);
            }
            s1[A[i]] = i;
            
            auto it2 = s2.lower_bound(-A[i]);
            if (it2 != s2.end()) {
                conn[0][i] = it2->second;
            }
            s2[-A[i]] = i;
        }
        return res;
    }
    int dfs(int c, int flag, vector<vector<vector<int>>>& conn, vector<vector<int>>& good) {
        if (good[c][flag]) {
            return good[c][flag];
        }
        good[c][flag] = -1;
        for (auto i : conn[flag][c]) {
            if (dfs(i, 1-flag, conn, good) == 1) {
                good[c][flag] = 1;
                break;
            }
        }
        return good[c][flag];
    }
    /**
     * Start from the right side:
     * For each position i, find its odd jump position j.
     * then for each position j, find its even jump position, k
     * then good(i) = good(k).
     *
     * How to find even(i) and odd(i)?
     * Use bucket sort because 0<=A[i]<=100000.
     *
     * Also, as the index array is sparse, some kind of linking is needed.
     * Always point
     *
     *
     */
    int oddEvenJumps_link(vector<int>& A) {
        int n = A.size();
        const int vn = 100000;
        // only need toe latest index of value
        vector<int> valToIndex(vn+1, 0);
        valToIndex[A[n-1]] = n-1;
        
        vector<int> good(n, 0);
        good[n-1] = 1;
        
        vector<int> even(n,0);
        even[n-1] = n-1;
        int res = 1;
        for (int i = n-2; i>=0; --i) {
            // now compute good[i] and even[i]
            // find index in valToIndex that has a value that's around A[i]
            
            
            // update A[i]
            valToIndex[A[i]] = i;
        }
        return res;
    }
    
    /**
     * Reverse. O(nlogn).
     * For each position i, find its odd jump position j.
     * then for each position j, find its even jump position, k
     * then good(i) = good(k).
     *
     * How to find even(i) and odd(i)?
     * Use bucket sort because 0<=A[i]<=100000.
     * However, we start from the right side to get the value to index mapping.
     *
     */
    int oddEvenJumps2(vector<int>& A) {
        int n = A.size();
        const int vn = 100000;
        // only need toe latest index of value
        map<int,int> valToIndex;
        valToIndex[A[n-1]] = n-1;
        
        vector<int> good(n, 0);
        good[n-1] = 1;
        
        vector<int> even(n,0);
        even[n-1] = n-1;
        int res = 1;
        for (int i = n-2; i>=0; --i) {
            // now compute odd[i] and even[i]
            // find index in valToIndex that has a value that's around A[i]
            auto it = valToIndex.lower_bound(A[i]);
            if (it != valToIndex.end()) {
                int k = even[it->second];
                if (k > 0) {
                    res += (good[i] = good[k]);
                }
                
                if (it->first == A[i]) {
                    even[i] = it->second;
                } else if (it != valToIndex.begin()) {
                    --it;
                    even[i] = it->second;
                }
            } else {
                even[i] = valToIndex.rbegin()->second;
            }
            valToIndex[A[i]] = i;
        }
        return res;
    }
    /**
     * Reverse. O(n)
     * For each position i, find its odd jump position j.
     * then for each position j, find its even jump position, k
     * then good(i) = good(k).
     *
     * How to find even(i) and odd(i)?
     * Use bucket sort because 0<=A[i]<=100000.
     *
     */
    int oddEvenJumps_wrong(vector<int>& A) {
        int n = A.size();
        const int vn = 100000;
        vector<vector<int>> valToIndex(vn + 1);
        for (int i = 0; i < n; ++i) {
            valToIndex[A[i]].push_back(i);
        }
        // index table for odd and even jump:
        // that is if odd[i] = k, then position i should jump to k for odd jump.
        vector<int> odd(n,0), even(n, 0);
        int j = 0;
        while (j <= vn && valToIndex[j].empty()) {
            ++j;
        }
        int i = j;
        ++j;
        while (j <= vn) {
            if (valToIndex[j].empty()) {
                ++j;
                continue;
            }
            
            // compare index at value i and j
            const auto& vi = valToIndex[i];
            const auto& vj = valToIndex[j];
            
            int idi = 0, idj = 0;
            while (idi < vi.size() && idj < vj.size()) {
                if (vi[idi] < vj[idj]) {
                    odd[idi] = idj;
                    ++idi;
                } else {
                    even[idj] = idi;
                    ++idj;
                }
            }
            
            i = j;
            ++j;
        }
        // override with same value index
        for (int i = 0; i <= vn; ++i) {
            for (int j = 1; j < valToIndex[i].size(); ++j) {
                odd[valToIndex[i][j-1]] = valToIndex[i][j];
                even[valToIndex[i][j-1]] = valToIndex[i][j];
            }
        }
        
        // now compute good(i) from n-2.
        int res = 1;
        vector<int> good(n, 0);
        good[n-1] = 1;
        for (int i = n-2; i >= 0; --i) {
            int oddi = odd[i];
            int eveni = even[oddi];
            res += (good[i] = good[eveni]);
        }
        return res;
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<int> A;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{50,28}},
        {{10,13,12,14,15}},
        {{2,3,1,1,4}},
        {{5,1,3,4,2}},
        {{1,2,3,2,1,4,4,5}},
    };

    vector< int > answers {
        1,
        2,
        3,
        3,
        6
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = oddEvenJumps::Solution().oddEvenJumps(dp.A);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
