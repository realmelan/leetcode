//
//  leastInterval.cpp
//  leetcode
//
//  Created by  Song Ding on 11/4/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;
namespace leastInterval {
    class Solution {
    public:
        /**
         Order the tasks based on the amount, and add all task types to
         an active list, and schedule the task with the largest amount,
         and move the task type to a waiting list. If at a time there is
         no task in the active list, add idle.
         
         At each step, check whether a task in waiting list can be moved
         back to active list.
         */
        int leastInterval(vector<char>& tasks, int n) {
            int taskSize = tasks.size();
            if (n <= 0) {
                return taskSize;
            }
            
            map<char, int> taskCount;
            for (auto c : tasks) {
                ++taskCount[c];
            }
            
            // the first element is the order of last time when the task is schduled;
            // the second element is the amount left for the task.
            auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
                if (a.first > b.first) {
                    return true;
                } else if (a.first < b.first) {
                    return false;
                } else {
                    return a.second < b.second;
                }
            };
            priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> active(cmp), waiting(cmp);
            
            for (auto const& kv: taskCount) {
                active.push(make_pair(0, kv.second));
            }
            
            int order = 0;
            int taskDone = 0;
            while (taskDone < taskSize) {
                // check whether the top task in waiting list
                // should be moved to active list.
                ++order;
                while (waiting.size()) {
                    auto kv = waiting.top();
                    if (order - kv.first >= n + 1) {
                        waiting.pop();
                        kv.first = 0;
                        active.push(kv);
                    } else {
                        break;
                    }
                }
                
                if (active.size()) {
                    ++taskDone;
                    auto kv = active.top();
                    active.pop();
                    
                    --kv.second;
                    if (kv.second > 0) {
                        kv.first = order;
                        waiting.push(kv);
                    }
                }
            }
            return order;
        }
    };
}
/*
int main() {
    string a("AAABBB");
    vector<char> tasks(a.begin(), a.end());
    cout << leastInterval::Solution().leastInterval(tasks, 2) << endl;
    return 0;
}
 */
