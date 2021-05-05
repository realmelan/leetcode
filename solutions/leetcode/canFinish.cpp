//
//  canFinish.cpp
//  leetcode
//
//  Created by  Song Ding on 12/25/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace canFinish {
    class Solution {
    public:
        /**
         Topology sort
         */
        bool canFinish(int numCourses, vector<pair<int, int>>& prerequisites) {
            if (numCourses <= 0) {
                return true;
            }
            vector<int> finished(numCourses, 1);
            for (const auto& p : prerequisites) {
                finished[p.first] = 0;
            }
            
            while (true) {
                bool found = false;
                vector<int> pre(numCourses, 0);
                for (auto& p : prerequisites) {
                    if (finished[p.first] == 0 && finished[p.second] == 0) {
                        ++pre[p.first];
                    }
                }
                for (int i = 0; i < numCourses; ++i) {
                    if (finished[i] == 0 && pre[i] == 0) {
                        found = true;
                        finished[i] = 1;
                    }
                }
                if (!found) {
                    break;
                }
            }
            int c = 0;
            for (auto i : finished) {
                ++c;
            }
            return (c == numCourses);
        }
    };
}
/**
int main() {
    vector<pair<int, int>> courses{
        {0, 1}, {1, 0}
    };
    int numCourses = 2;
    cout << canFinish::Solution().canFinish(numCourses, courses) << endl;
    return 0;
}
*/
