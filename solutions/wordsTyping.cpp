// wordsTyping.cpp
// leetcode
//
// Created by  Song Ding on 10/29/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace wordsTyping {
/*
// TODO: copy problem statement here
 418. Sentence Screen Fitting

 Given a rows x cols screen and a sentence represented by a list of non-empty words, find how many times the given sentence can be fitted on the screen.

 Note:

 A word cannot be split into two lines.
 The order of words in the sentence must remain unchanged.
 Two consecutive words in a line must be separated by a single space.
 Total words in the sentence won\'t exceed 100.
 Length of each word is greater than 0 and won\'t exceed 10.
 1 ≤ rows, cols ≤ 20,000.
 Example 1:

 Input:
 rows = 2, cols = 8, sentence = ["hello", "world"]

 Output:
 1

 Explanation:
 hello---
 world---

 The character \'-\' signifies an empty space on the screen.
 Example 2:

 Input:
 rows = 3, cols = 6, sentence = ["a", "bcd", "e"]

 Output:
 2

 Explanation:
 a-bcd-
 e-a---
 bcd-e-

 The character \'-\' signifies an empty space on the screen.
 Example 3:

 Input:
 rows = 4, cols = 5, sentence = ["I", "had", "apple", "pie"]

 Output:
 1

 Explanation:
 I-had
 apple
 pie-I
 had--

 The character \'-\' signifies an empty space on the screen.
 */

class Solution {
public:
    /**
     * squeeze as many words into one line as possible, until starting at the 1st word at the 0-th column again.
     * then we know there is a duplication.
     * till now record # of times for each line.
     */
    int wordsTyping(vector<string>& sentence, int rows, int cols) {
        int n = sentence.size();
        vector<int> lens;
        for (auto& s : sentence) {
            lens.push_back(1+s.size()); // count space
        }
        
        vector<int> times;
        int wi = 0;
        int cnt = 0;
        while (times.size() < rows) {
            int ci = cols+1;
            while (ci >= lens[wi]) {
                ci -= lens[wi];
                ++wi;
                if (wi == n) {
                    ++cnt;
                    wi = 0;
                }
            }
            times.push_back(cnt);
            if (wi == 0) {
                break;
            }
        }
        
        // check how many duplication will be made for rows
        int res = 0;
        if (times.size() <= rows) {
            res += cnt * (rows / times.size());
            if (rows % times.size()) {
                res += times[rows%times.size() - 1];
            }
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
        vector<string> sentence;
        int rows;
        int cols;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"hello", "world"},2,8},
        {{"a", "bcd", "e"},3,6},
        {{"I", "had", "apple", "pie"},4,5},
    };

    vector< int > answers {
        1,
        2,
        1,
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = wordsTyping::Solution().wordsTyping(dp.sentence, dp.rows, dp.cols);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
