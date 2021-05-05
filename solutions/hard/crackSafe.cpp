//
//  crackSafe.cpp
//  leetcode
//
//  Created by  Song Ding on 1/30/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;
/**
 753. Cracking the Safe
 Hard

 322

 368

 Favorite

 Share
 There is a box protected by a password. The password is a sequence of n digits where each digit can be one of the first k digits 0, 1, ..., k-1.

 While entering a password, the last n digits entered will automatically be matched against the correct password.

 For example, assuming the correct password is "345", if you type "012345", the box will open because the correct password matches the suffix of the entered password.

 Return any password of minimum length that is guaranteed to open the box at some point of entering it.

  

 Example 1:

 Input: n = 1, k = 2
 Output: "01"
 Note: "10" will be accepted too.
 Example 2:

 Input: n = 2, k = 2
 Output: "00110"
 Note: "01100", "10011", "11001" will be accepted too.
  

 Note:

 n will be in the range [1, 4].
 k will be in the range [1, 10].
 k^n will be at most 4096.
 */
namespace crackSafe {
    class Solution {
    public:
        /**
         This is De Bruijn sequence, which has an iterative algorithm, a little complicated.
         Here we can construct a connected graph and find an Eulerian cycle.
         Vertex would be all n-1 code in base k, and the edge is 0 to k-1.
         
         Then the start string plus all edges would be the final result.
         When arriving at a vertex, find out what edges are left and choose one of them(either max
         or min) to get to next vertex.
         */
        string crackSafe(int n, int k) {
            string res;
            res.reserve(pow(k,n));
            for (int i = 1; i < n; ++i) {
                res.push_back('0');
            }
            
            unordered_map<string,int> edges;
            int edgeCnt = pow(k, n);
            int len = n-1;
            string cur(res);
            // when to stop?
            while (len < edgeCnt + n - 1) {
                int edge = getEdge(res.substr(len-n+1), edges, k);
                res.push_back('0' + edge);
                ++len;
            }
            return res;
        }
        int getEdge(const string& node, unordered_map<string, int>& edges, int k) {
            int res = k;
            auto it = edges.find(node);
            if (it == edges.end()) {
                edges[node] = k-2;
                res = k-1;
            } else if (it->second >= 0){
                res = it->second;
                --it->second;
            }
            return res;
        }
        
        /**
         Say for k = 6, n = 6, starting with 000000,
         move onto 0000001000002000003..., (0 being base digit)
         to 000005, now move onto 000005000011,
         gradually increase the number to 55, then increase
         number to 111, that is moving onto 00005500111.
         
         Finally it will go to 55554055555. Now increase
         the base digit to 1, that go to 55554055555111111.
         
         Now, do the above for another 4 round, till 55554455555.
         
         Add final '5', resulting in 555544555555
         
         At the very end, appending "50555500555000550000500000"
         to count for numbers that can't be reached.
         */
        string crackSafe2(int n, int k) {
            string res;
            res.reserve(4096);
            for (int base = 0; base < k - 1; ++base) {
                res.push_back('0' + base);
                if (n > 1) {
                    string bits;
                    for (int i = 0; i < n; ++i) {
                        bits.push_back('0' + base);
                    }
                    bits[n - 1] += 1;
                    res.append(bits);
                    
                    while (nextBits(bits, n, base, k)) {
                        res.append(bits);
                    }
                }
            }
            
            res.push_back('0' + k - 1);
            
                for (int i = 1; i < n - 1; ++i) {
                    for (int j = 0; j < i; ++j) {
                        res.push_back('0');
                    }
                    for (int j = i; j < n - 1; ++j) {
                        res.push_back('0' + k - 1);
                    }
                }
            return res;
        }
    private:
        bool nextBits(string& bits, int n, int base, int k) {
            int carry = 1;
            for (int i = n - 1; i >= 0; --i) {
                bits[i] += carry;
                carry = 0;
                if (bits[i] - '0' >= k) {
                    bits[i] = '0' + base + 1;
                    carry = 1;
                }
            }
            return bits[0] - '0' == base;
        }
    };
}
/*
int main() {
    int n = 3;
    int k = 5;
    cout << crackSafe::Solution().crackSafe(n, k) << endl;
    return 0;
}
// */
