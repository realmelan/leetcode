// longestDecomposition.cpp
// leetcode
//
// Created by  Song Ding on 9/18/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace longestDecomposition {
/*
// TODO: copy problem statement here
 1147. Longest Chunked Palindrome Decomposition
 Hard
 
 80
 
 7
 
 Favorite
 
 Share
 Return the largest possible k such that there exists a_1, a_2, ..., a_k such that:
 
 Each a_i is a non-empty string;
 Their concatenation a_1 + a_2 + ... + a_k is equal to text;
 For all 1 <= i <= k,  a_i = a_{k+1 - i}.
 
 
 Example 1:
 
 Input: text = "ghiabcdefhelloadamhelloabcdefghi"
 Output: 7
 Explanation: We can split the string on "(ghi)(abcdef)(hello)(adam)(hello)(abcdef)(ghi)".
 Example 2:
 
 Input: text = "merchant"
 Output: 1
 Explanation: We can split the string on "(merchant)".
 Example 3:
 
 Input: text = "antaprezatepzapreanta"
 Output: 11
 Explanation: We can split the string on "(a)(nt)(a)(pre)(za)(tpe)(za)(pre)(a)(nt)(a)".
 Example 4:
 
 Input: text = "aaa"
 Output: 3
 Explanation: We can split the string on "(a)(a)(a)".
 
 
 Constraints:
 
 text consists only of lowercase English characters.
 1 <= text.length <= 1000
 */

class Solution {
public:
    int longestDecomposition(string text) {
        return longestDecomposition_recursive(text);
    }
    
    int longestDecomposition_recursive(string text) {
        for (int i = 1; i <= text.size()/2; ++i) {
            if (text.substr(0,i) == text.substr(text.size()-i)) {
                return 2 + longestDecomposition_recursive(text.substr(i, text.size() - i*2));
            }
        }
        return text.size() == 0 ? 0 : 1;
    }
    /**
     * use 2 pointer i=0, j=n-1
     *  if t[i]=t[j], then (t[i]) and (t[j]) is a pair
     *  else:
     *    loop until find next position from i, k, such that t[k]=t[j]
     *    and t[i..k] = t[j+i-k..j]
     */
    int longestDecomposition_greedy(string text) {
        int n = text.size();
        int stop = (n-1) / 2;
        int res = 0;
        int i = 0, j = n-1;
        while (i < j) {
            if (text[i] == text[j]) {
                res += 2;
                ++i;
                --j;
                continue;
            }
            
            int k = i+1;
            while (true) {
                while (k <= stop && (text[k] != text[j] || text[i] != text[i+j-k])) {
                    ++k;
                }
                if (k > stop) {
                    ++res;
                    return res;
                }
                // now check whether text[i..k]=text[j+i=k..j]
                int ci = i, cj = j+i-k;
                while (ci <= k && text[ci] == text[cj]) {
                    ++ci;
                    ++cj;
                }
                if (ci < k) {
                    ++k;
                } else {
                    j = j+i-k-1;
                    i = ci;
                    res += 2;
                    break;
                }
            }
        }
        if (i == j) {
            ++res;
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
        string text;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"ghiabcdefhelloadamhelloabcdefghi"},
        {"merchant"},
        {"antaprezatepzapreanta"},
        {"aaa"},
    };

    vector< int > answers {
        7,
        1,
        11,
        3,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = longestDecomposition::Solution().longestDecomposition(dp.text);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
