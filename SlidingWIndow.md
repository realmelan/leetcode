# Sliding window
There are 2 different types of problems:
* Find a maximum, minimum  or nearest larger/smaller within a bounded range
* longest or shortest subarray/substring that matches certain constraints.

For type 1, Monotonic queue can be used, which achieves O(n) efficiency. 
A monotonic queue provides benefit that farther away useless elements are discarded
as they are inferior to the element that's closer to current position.

For type 2, use two pointer technique, right pointer to add counters and left pointer
to decrease counter. When conditions are met, left/right pointers form a valid range.

# Reference
* https://leetcode.com/problems/subarrays-with-k-different-integers/discuss/523136/JavaC%2B%2BPython-Sliding-Window
* https://github.com/xiaoylu/leetcode_category/blob/master/MonotonicQueue/Readme.md
