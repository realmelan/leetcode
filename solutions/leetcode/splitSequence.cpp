//
//  splitSequence.cpp
//  leetcode
//
//  Created by  Song Ding on 12/11/17.
//  Copyright © 2017 Song Ding. All rights reserved.
//

#include "common.h"

using namespace std;

namespace splitSequence {
    class Solution {
    public:
        /**
         use a hashmap to record # of sequences ending at a certain number.
         */
        bool isPossible(vector<int>& nums) {
            int n = nums.size();
            unordered_map<int, multiset<int>> g;
            for (int i = 0; i < n; ++i) {
                int num = nums[i];
                auto it = g.find(num - 1);
                if (it == g.end()) {
                    g[num].insert(1);
                } else {
                    auto cit = it->second.begin();
                    int cnt = *cit;
                    // remove cit
                    it->second.erase(cit);
                    if (it->second.empty()) {
                        g.erase(it);
                    }
                    g[num].insert(cnt+1);
                }
            }
            for (auto& p : g) {
                if (*(p.second.begin()) < 3) {
                    return false;
                }
            }
            return true;
        }
        
        /**
         use multimap to record each sequence's end number and its # of elements.
         for a new num, find its position in the multimap using num-1.
         */
        bool isPossible3(vector<int>& nums) {
            int n = nums.size();
            multimap<int,int> g;
            for (int i = 0; i < n; ++i) {
                int num = nums[i];
                auto it = g.equal_range(num - 1);
                if (it.first == g.end() || it.first->first != num - 1) {
                    g.insert(make_pair(num, 1));
                } else {
                    // need to go to the short one
                    auto fit = it.first;
                    int cnt = fit->second;;
                    auto rit = fit++;
                    while (fit != it.second) {
                        if (cnt > fit->second) {
                            cnt = fit->second;
                            rit = fit;
                        }
                        ++fit;
                    }
                    g.erase(rit);
                    g.insert(make_pair(num, cnt+1));
                }
            }
            for (auto& p : g) {
                if (p.second < 3) {
                    return false;
                }
            }
            return true;
        }
        /**
         Starting from the first element, add it to concurrent
         sequence if current number follows the order;
         
         Otherwise start a new sequence, either a duplicate number
         or there is a gap between.
         
         Now when encountering a new number, check whether it fits
         one of the sequences; if not starting a new sequence;
         otherwise, favors the shortest sequence.
         */
        bool isPossible2(vector<int>& nums) {
            int len = nums.size();
            if (len < 3) {
                return false;
            }
            
            vector<vector<int>> seqs;
            vector<int> first{nums[0]};
            seqs.push_back(first);
            
            for (int i = 1; i < len; ++i) {
                int chosenSize = i + 2;
                int chosenIdx = -1;
                int vsize = seqs.size();
                for (int j = 0; j < vsize; ++j) {
                    if (nums[i] == seqs[j].back() + 1 && seqs[j].size() < chosenSize) {
                        chosenSize = seqs[j].size();
                        chosenIdx = j;
                    }
                }
                if (chosenIdx != -1) {
                    seqs[chosenIdx].push_back(nums[i]);
                } else {
                    seqs.push_back(vector<int>{nums[i]});
                }
            }
            for (const auto& s : seqs) {
                if (s.size() < 3) {
                    return false;
                }
            }
            return true;
        }
    };
}

/*
int main() {
    vector<int> nums{1,2,3,3,4,5};
    cout << splitSequence::Solution().isPossible(nums) << endl;
    return 0;
}
// */
