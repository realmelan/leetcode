//
//  wiggleSort.cpp
//  leetcode
//
//  Created by  Song Ding on 1/16/18.
//  Copyright © 2018 Song Ding. All rights reserved.
//

#include "common.h"
using namespace std;

namespace wiggleSort {
    class Solution {
    public:
        /**
         * https://leetcode.com/problems/wiggle-sort-ii/discuss/77677/O(n)%2BO(1)-after-median-Virtual-Indexing
         * 1, use std::nth_element to partial sort array such that median element is at (n+1)/2
         * 2, use dutch national flag sort algorithm to move all larger elements to even positions and smaller elements to odd positions.
         *
         * Note, however, dutch national flag sort divides elements based on elements' relation with pivot element, that is, smaller ones go to
         * one end, and larger ones to the other end, and equal ones go in the middle.
         *
         * How can we use it for wiggle position?
         * Here is the catch: dutch national flag sort move larger elements to one end, say, to [0, k], we can map it to all odd indices of [1,2*k+1], by
         * let i=>1+2*i, then 0=>1, 1=>3, 2=>5,3=>7,... Also, we need to make it go back to the even positions. This can be done by %(n|1). (n|1) is
         * to change it to an odd number, such that, %(n|1) would change to even, starting from 0.
         */
        void wiggleSort(vector<int>& nums) {
            int n = nums.size();
            auto midptr = nums.begin() + n/2;
            std::nth_element(nums.begin(), midptr, nums.end());
            int mid = *midptr;
            
            // do dutch national flag sort
            int i = 0, j = 0, k = n-1;
            while (j <= k) {
                if (nums[wi(j,n)] > mid) {
                    swap(nums[wi(i,n)], nums[wi(j,n)]);
                    ++i;
                    ++j;
                } else if (nums[wi(j,n)] < mid) {
                    swap(nums[wi(j,n)], nums[wi(k,n)]);
                    --k;
                } else {
                    ++j;
                }
            }
        }
        int wi(int i, int n) {
            return (1+2*i)%(n|1);
        }
                    
        /**
         The final array is like a wave. Assume nums[0] is bottom.
         For a peak, compare current element with the previous one,
         switch them if current one is smaller; for a bottom, switch
         them if current one is larger.
         
         However, there might be cases that consecutive elements
         are the same. In this case, loop till find one number
         */
        /*
        void wiggleSort_wrong(vector<int>& nums) {
            int len = nums.size();
            // move min element to first
            // move max element to last
            if (len <= 1) {
                return;
            }
            int min = nums[0];
            int minidx = 0;
            int max = nums[len - 1];
            int maxidx = len - 1;
            for (int i = 1; i < len; ++i) {
                if (nums[i] < min) {
                    min = nums[i];
                    minidx = i;
                }
                if (nums[i] > max) {
                    max = nums[i];
                    maxidx = i;
                }
            }
            if (minidx != 0) {
                nums[minidx] = nums[0];
                nums[0] = min;
            }
            if (len % 2 == 0 && maxidx != len - 1) {
                nums[maxidx] = nums[len - 1];
                nums[len - 1] = max;
            }
            for (int i = 1; i < len; ++i) {
                if (i % 2) {
                    if (nums[i] == nums[i - 1]) {
                        // loop through next index to find one element
                        // which is larger than nums[i - 1]
                        int j = i + 1;
                        for (; j < len; ++j) {
                            if (nums[j] > nums[i - 1]) {
                                break;
                            }
                        }
                        // swap nums[i] and nums[j]
                        int t = nums[i];
                        nums[i] = nums[j];
                        nums[j] = t;
                    }
                    
                    if (nums[i] < nums[i - 1]) {
                        int t = nums[i];
                        nums[i] = nums[i - 1];
                        nums[i - 1] = t;
                    }
                } else {
                    if (nums[i] == nums[i - 1]) {
                        // loop through next index to find one element
                        // which is smaller than nums[i - 1]
                        int j = i + 1;
                        for (; j < len; ++j) {
                            if (nums[j] < nums[i - 1]) {
                                break;
                            }
                        }
                        // swap nums[i] and nums[j]
                        int t = nums[i];
                        nums[i] = nums[j];
                        nums[j] = t;
                    }
                    if (nums[i] > nums[i - 1]) {
                        int t = nums[i];
                        nums[i] = nums[i - 1];
                        nums[i - 1] = t;
                    }
                }
            }
            
        }*/
        /**
         * divide nums[left, right] into two halves, with the first half having
         * target number of elements.
         *
         * do it recursively.
         */
        void partition(vector<int>& nums, int left, int right, int target) {
            if (left == right) {
                return;
            }
            int mid = nums[(left + right) / 2];
            int i = left;
            int j = right;
            while (i < j) {
                while (nums[i] <= mid && i < j) {
                    ++i;
                }
                if (i >= j) {
                    break;
                }
                while (nums[j] >= mid && j > i) {
                    --j;
                }
                if (j <= i) {
                    break;
                }
                swap(nums[i], nums[j]);
                ++i;
                --j;
            }
            
            int cnt = i - left + 1;
            if (cnt == target) {
                return;
            } else if (cnt > target) {
                partition(nums, left, i, target);
            } else {
                partition(nums, j, right, target - cnt);
            }
        }
        void wiggle(vector<int>& nums, int half) {
            
        }
        /**
         * Step 1, Do a recursive partition until the array is
         * divided into two equal halves.
         *  this step may take O(n^2) in worst case, but average
         *  should be O(n).
         *
         * Step 2, interleave the first half and the second half.
         *  this step is O(n)
         */
        void wiggleSort_wrong(vector<int>& nums) {
            int n = nums.size();
            int half = (n + 1) / 2;
            partition(nums, 0, n - 1, half);
            wiggle(nums, half);
        }
        void wiggleSort2(vector<int>& nums) {
            int n = nums.size();
            
            // Find a median.
            int mid = nth_element(n / 2, nums);
            cout << nums << endl;
            
            // Index-rewiring.
#define A(i) nums[(1+2*(i)) % (n|1)]
            
            // 3-way-partition-to-wiggly in O(n) time with O(1) space.
            
            int i = 0, j = 0, k = n - 1;
            while (j <= k) {
                if (A(j) > mid) {
                    swap(A(i++), A(j++));
                } else if (A(j) < mid) {
                    swap(A(j++), A(k--));
                } else {
                    j++;
                }
                cout << nums << endl;
            }
        }
        int nth_element(int k, vector<int>& nums) {
            int left = 0, right = nums.size() - 1;
            //default_random_engine gen((random_device())());
            while (left <= right) {
                // Generates a random int in [left, right].
                //uniform_int_distribution<int> dis(left, right);
                int pivot_idx = left;
                int new_pivot_idx = PartitionAroundPivot(left, right, pivot_idx, nums);
                if (new_pivot_idx == k - 1) {
                    return nums[new_pivot_idx];
                } else if (new_pivot_idx > k - 1) {
                    right = new_pivot_idx - 1;
                } else {  // new_pivot_idx < k - 1.
                    left = new_pivot_idx + 1;
                }
            }
            return nums[left];
        }
        int PartitionAroundPivot(int left, int right, int pivot_idx, vector<int>& nums) {
            int pivot_value = nums[pivot_idx];
            int new_pivot_idx = left;
            swap(nums[pivot_idx], nums[right]);
            for (int i = left; i < right; ++i) {
                if (nums[i] > pivot_value) {
                    swap(nums[i], nums[new_pivot_idx++]);
                }
            }
            swap(nums[right], nums[new_pivot_idx]);
            return new_pivot_idx;
        }
        
    };
}
/*
int main() {
    //vector<int> nums{10,11,12,13,14,15,16,17,18,19};
    //vector<int> nums{1,5,1,1,6,4};
    vector<int> nums{1,1,2,1,2,2,1};
    wiggleSort::Solution().wiggleSort(nums);
    cout << nums << endl;
    return 0;
}
//*/
