// findMedianSortedArrays.cpp
// leetcode
//
// Created by  Song Ding on 1/8/19.
// Copyright © 2019 Song Ding. All rights reserved.
//
#include "common.h"
using namespace std;

namespace findMedianSortedArrays {
/**
 4. Median of Two Sorted Arrays
 Hard
 
 4456
 
 617
 
 Favorite
 
 Share
 There are two sorted arrays nums1 and nums2 of size m and n respectively.
 
 Find the median of the two sorted arrays. The overall run time complexity should be O(log (m+n)).
 
 You may assume nums1 and nums2 cannot be both empty.
 
 Example 1:
 
 nums1 = [1, 3]
 nums2 = [2]
 
 The median is 2.0
 Example 2:
 
 nums1 = [1, 2]
 nums2 = [3, 4]
 
 The median is (2 + 3)/2 = 2.5
 */
class Solution {
public:
    /**
     find a position in nums1, i, and thus a position in nums2, j, such that nums1[i-1] < nums2[j] and nums2[j-1] < nums1[i]
     and i+j => # of elements to bypass to get median.
     
     thanks to https://leetcode.com/problems/median-of-two-sorted-arrays/discuss/2471/Very-concise-O(log(min(MN)))-iterative-solution-with-detailed-explanation
     */
    double findMedianSortedArrays4(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        if (n1 > n2) {
            swap(nums1,nums2);
            swap(n1, n2);
        }
        int k = (n1+n2-1) / 2;
        int l = 0, r = n1-1;
        while (l <= r) {
            int m = l + (r-l) / 2;
            int m2 = k - m;
            int l1 = m > 0 ? nums1[m-1] : INT_MIN;
            int r1 = m < n1 ? nums1[m] : INT_MAX;
            int l2 = m2 > 0 ? nums2[m2-1] : INT_MIN;
            int r2 = m2 < n2 ? nums2[m2] : INT_MAX;
            if (l1 > r2) {
                r = m - 1;
            } else if (l2 > r1) {
                l = m + 1;
            } else {
                l = m;
                break;
            }
        }
        priority_queue<int, vector<int>, std::greater<int>> pq;
        int l2 = k - l;
        for (int i = 0; i < 2; ++i) {
            if (l < n1) {
                pq.push(nums1[l++]);
            }
            if (l2 < n2) {
                pq.push(nums2[l2++]);
            }
        }
        if ((n1+n2)%2) {
            return pq.top();
        } else {
            int f = pq.top(); pq.pop();
            return (f + pq.top()) / 2.0;
        }
    }
    /**
     test which first half (k/2) of both arrays should be removed
     */
    double findMedianSortedArrays3(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size(), n2 = nums2.size();
        int nremove = (n1+n2-1)/2;
        int k = nremove;
        int l1 = 0, l2 = 0;
        while (k && l1 < n1 && l2 < n2) {
            int nr = max(1, k / 2);
            int i1 = min(n1-1, l1+nr-1);
            int i2 = min(n2-1, l2+nr-1);
            if (nums1[i1] <= nums2[i2]) {
                k -= i1 - l1+1;
                l1 = i1+1;
            } else {
                k -= i2 - l2+1;
                l2 = i2 + 1;
            }
        }
        if (l1 >= n1) {
            int first = nums2[l2+k];
            if ((n1+n2)%2) {
                return first;
            } else {
                return (first + nums2[l2+k+1]) / 2.0;
            }
        } else if (l2 >= n2) {
            int first = nums1[l1+k];
            if ((n1+n2)%2) {
                return first;
            } else {
                return (first + nums1[l1+k+1]) / 2.0;
            }
        } else {
            priority_queue<int, vector<int>, std::greater<int>> pq;
            //priority_queue<int> pq;
            for (int i = 0; i < 2; ++i) {
                if (l1 < n1) {
                    pq.push(nums1[l1]);
                    ++l1;
                }
                if (l2 < n2) {
                    pq.push(nums2[l2]);
                    ++l2;
                }
            }
            if ((n1+n2)%2) {
                return pq.top();
            } else {
                int first = pq.top(); pq.pop();
                int second = pq.top(); pq.pop();
                return (first + second) / 2.0;
            }
        }
    }
    /**
     * given m=nums1.size() and n = nums2.size(), find k=(m+n-1)/2-th element.
     * let i=0, j = 0, and check nums1[i+k/2-1] and nums2[j+k/2-1], update i to i+k/2 if nums1[i+k/2-1] < nums2[j+k/2-1]
     * if i+k/2-1 >= m, then check m.
     */
    double findMedianSortedArrays2(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size(), k = (m+n-1)/2, i = 0, j = 0;
        while (i < m && j < n && k > 0) {
            int step = max(1, k/2);
            int ni = min(m-1, i+step-1);
            int nj = min(n-1, j+step-1);
            if (nums1[ni] < nums2[nj]) {
                k -= ni - i + 1;
                i = ni + 1;
            } else {
                k -= nj - j + 1;
                j = nj + 1;
            }
        }
        if (k > 0) {
            if (i < m) {
                i += k;
            } else {
                j += k;
            }
        }
        if ((m+n)%2) {
            if (i >= m) {
                return nums2[j];
            } else if (j >= n) {
                return nums1[i];
            } else {
                return min(nums1[i], nums2[j]);
            }
        } else {
            if (i >= m) {
                return ((double)nums2[j] + nums2[j+1])/2;
            } else if (j >= n) {
                return ((double)nums1[i] + nums1[i+1])/2;
            } else {
                return ((double)nums1[i] + nums2[j]) / 2;
            }
        }
    }
    /**
     * Try to remove tn = (n1+n2-1)/2 numbers in the first part of nums1 and nums2;
     * then the median number would be at the front of nums1 or nums2 or both.
     *
     * For each iteration, always remove tn/2 numbers.
     */
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int n1 = nums1.size();
        int n2 = nums2.size();
        int tn = (n1+n2-1) / 2; // # of elements to remove (just before median1)
        
        int l1 = 0, l2 = 0;
        int r1 = n1-1, r2 = n2-1;
        while (tn > 1) {
            int m = tn/2;
            m = min(min(m, r1-l1+1), r2-l2+1);
            if (m <= 0) {
                break;
            }
            
            tn -= m;
            if (nums1[l1+m-1] < nums2[l2+m-1]) {
                l1 = l1+m;
            } else {
                l2 = l2+m;
            }
            if (tn <= 1 || l1 > r1 || l2 > r2) {
                break;
            }
        }
        
        int m1 = 0;
        if (l1 > r1) {
            l2 += tn;
            m1 = nums2[l2++];
        } else if (l2 > r2) {
            l1 += tn;
            m1 = nums1[l1++];
        } else {
            if (tn == 1) {
                if (nums1[l1] < nums2[l2]) {
                    ++l1;
                } else {
                    ++l2;
                }
            }
            if (l1 > r1) {
                m1 = nums2[l2++];
            } else if (l2 > r2) {
                m1 = nums1[l1++];
            } else if (nums1[l1] < nums2[l2]) {
                m1 = nums1[l1++];
            } else {
                m1 = nums2[l2++];
            }
        }
        
        if ((n1+n2)%2) {
            return m1;
        } else {
            // find m2;
            int m2 = 0;
            if (l1 > r1) {
                m2 = nums2[l2];
            } else if (l2 > r2) {
                m2 = nums1[l1];
            } else {
                m2 = min(nums1[l1], nums2[l2]);
            }
            return ((double)m1 + m2)/ 2;
        }
    }

private:
};

}

/*/
 int main() {
 // TODO: define parameter type here
     struct d {
         vector<int> nums1;
         vector<int> nums2;
     };
     // TODO: prepare parameters here
     vector<struct d> p {
         {{2,3,4,5,6},{1}},
         {{1,3},{2}},
         {{1},{2,3}},
         {{1,2},{3,4}},
         {{3,4},{}},
         {{1,2,3,4,5},{}},
         {{1},{1}}
         
     
     };
     
     vector< double > answers {
         3.5,
         2.0,
         2.0,
         2.5,
         3.5,
         3.0,
         1.0
     };
     
     // TODO: update paramters.
     for (auto& dp : p) {
         cout << endl;
         clock_t tstart = clock();
         auto res = findMedianSortedArrays::Solution().findMedianSortedArrays4(dp.nums1, dp.nums2);
         cout << clock() - tstart << endl;
         cout << res << endl;
     }
     return 0;
 }
 //*/
