// fullJustify.cpp
// leetcode
//
// Created by  Song Ding on 7/8/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace fullJustify {
/*
// TODO: copy problem statement here
 68. Text Justification
 Hard
 
 374
 
 1048
 
 Favorite
 
 Share
 Given an array of words and a width maxWidth, format the text such that each line has exactly maxWidth characters and is fully (left and right) justified.
 
 You should pack your words in a greedy approach; that is, pack as many words as you can in each line. Pad extra spaces ' ' when necessary so that each line has exactly maxWidth characters.
 
 Extra spaces between words should be distributed as evenly as possible. If the number of spaces on a line do not divide evenly between words, the empty slots on the left will be assigned more spaces than the slots on the right.
 
 For the last line of text, it should be left justified and no extra space is inserted between words.
 
 Note:
 
 A word is defined as a character sequence consisting of non-space characters only.
 Each word's length is guaranteed to be greater than 0 and not exceed maxWidth.
 The input array words contains at least one word.
 Example 1:
 
 Input:
 words = ["This", "is", "an", "example", "of", "text", "justification."]
 maxWidth = 16
 Output:
 [
 "This    is    an",
 "example  of text",
 "justification.  "
 ]
 Example 2:
 
 Input:
 words = ["What","must","be","acknowledgment","shall","be"]
 maxWidth = 16
 Output:
 [
 "What   must   be",
 "acknowledgment  ",
 "shall be        "
 ]
 Explanation: Note that the last line is "shall be    " instead of "shall     be",
 because the last line must be left-justified instead of fully-justified.
 Note that the second line is also left-justified becase it contains only one word.
 Example 3:
 
 Input:
 words = ["Science","is","what","we","understand","well","enough","to","explain",
 "to","a","computer.","Art","is","everything","else","we","do"]
 maxWidth = 20
 Output:
 [
 "Science  is  what we",
 "understand      well",
 "enough to explain to",
 "a  computer.  Art is",
 "everything  else  we",
 "do                  "
 ]
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        return {};
    }

private:
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        vector<string> words;
        int maxWidth;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {{"This", "is", "an", "example", "of", "text", "justification."},16},
        {{"What","must","be","acknowledgment","shall","be"},16},
        {{"Science","is","what","we","understand","well","enough","to","explain",
            "to","a","computer.","Art","is","everything","else","we","do"},16}
    };

    vector< vector<string> > answers {
        {"This    is    an",
            "example  of text",
            "justification.  "},
        {"What   must   be",
            "acknowledgment  ",
            "shall be        "},
        {"Science  is  what we",
            "understand      well",
            "enough to explain to",
            "a  computer.  Art is",
            "everything  else  we",
            "do                  "}
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = fullJustify::Solution().fullJustify(dp.words, dp.maxWidth);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
