// lengthLongestPath.cpp
// leetcode
//
// Created by  Song Ding on 1/15/20.
// Copyright © 2020 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace lengthLongestPath {
/*
// TODO: copy problem statement here
 388. Longest Absolute File Path
 Medium

 528

 1176

 Add to List

 Share
 Suppose we abstract our file system by a string in the following manner:

 The string "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext" represents:

 dir
     subdir1
     subdir2
         file.ext
 The directory dir contains an empty sub-directory subdir1 and a sub-directory subdir2 containing a file file.ext.

 The string "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext" represents:

 dir
     subdir1
         file1.ext
         subsubdir1
     subdir2
         subsubdir2
             file2.ext
 The directory dir contains two sub-directories subdir1 and subdir2. subdir1 contains a file file1.ext and an empty second-level sub-directory subsubdir1. subdir2 contains a second-level sub-directory subsubdir2 containing a file file2.ext.

 We are interested in finding the longest (number of characters) absolute path to a file within our file system. For example, in the second example above, the longest absolute path is "dir/subdir2/subsubdir2/file2.ext", and its length is 32 (not including the double quotes).

 Given a string representing the file system in the above format, return the length of the longest absolute path to file in the abstracted file system. If there is no file in the system, return 0.

 Note:
 The name of a file contains at least a . and an extension.
 The name of a directory or sub-directory will not contain a ..
 Time complexity required: O(n) where n is the size of the input string.

 Notice that a/aa/aaa/file1.txt is not the longest file path, if there is another path aaaaaaaaaaaaaaaaaaaaa/sth.png.
 */

class Solution {
public:
    /**
     * //TODO: explain algorithm here
     */
    int lengthLongestPath(string input) {
        int res = 0;
        vector<int> path;
        help(input, path, 0, 0, res);
        return res;
    }
    
    // iterative
    int lengthLongestPath2(string input) {
        vector<int> path;
        int i = 0;
        int res = 0;
        int curLen = 0;
        while (i < input.size()) {
            int indent = 0;
            int len = 0;
            bool file = false;
            while (i < input.size() && input[i] != '\n') {
                if (input[i] == '\t') {
                    ++indent;
                } else {
                    ++len;
                }
                if (input[i] == '.') {
                    file = true;
                }
                ++i;
            }
            if (indent >= path.size()) {
                if (!path.empty()) {
                    curLen += 1;
                }
                path.push_back(len);
                curLen += len;
            } else {
                while (indent < path.size()) {
                    curLen -= (path.back() + 1);
                    path.pop_back();
                }
                curLen += len + 1;
                path.push_back(len);
            }
            if (file) {
                res = max(res, curLen);
            }
            ++i;
        }
        return res;
    }

private:
    void help(const string& s, vector<int>& path, int curLen, int start, int& res) {
        int indent = 0;
        int len = 0;
        int i = start;
        while (i < s.size() && s[i] != '\n') {
            if (s[i] == '\t') {
                ++indent;
            } else {
                ++len;
            }
            ++i;
        }
        if (path.empty()) {
            path.push_back(len);
            curLen = len;
        } else if (indent >= path.size()) {
            path.push_back(len);
            curLen += len + 1;
        } else {
            curLen -= path.back();
            path.pop_back();
            path.push_back(len);
            curLen += len;
        }
        res = max(res, curLen);
        if (i+1 < s.size()) {
            help(s, path, curLen, i+1, res);
        }
    }
};

}

/*/
int main() {
    // TODO: define parameter type here
    struct d {
        string input;
    };
    // TODO: prepare parameters here
    vector<struct d> p {
        {"dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"},
        {"a\n\tb1\n\t\tf1.txt\n\taaaaa\n\t\tf2.txt"},
        {"a"},
    };

    vector< int > answers {
        32,
        14,
        0
    };

    // TODO: update paramters.
    for (auto& dp : p) {
        cout << endl;
        clock_t tstart = clock();
        auto res = lengthLongestPath::Solution().lengthLongestPath2(dp.input);
        cout << clock() - tstart << endl;
        cout << res << endl;
    }
    return 0;
}
//*/
