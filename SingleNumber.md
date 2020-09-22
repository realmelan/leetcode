Given an array of integers, every element appears k times, except one appearing only p(p<k) times, find out this element.

Here is one solution.
```c++
int findNum(vector<int>& nums) {
  int x1 = 0, x2 = 0, x3 = 0, ..., xk = 0;
  for (auto i : nums) {
      int t = xk-1 | xk-2 | ... |x2 | x1;
      xk = (xk&~i) | (xk-1&i);
      xk-1 = (xk-1&~i) | (xk-2&i);
      ...
      x2 = (x2&~i) | (x1&i);
      x1 = (x1&~i) | ^t&i;
  }
  return xp;
}
```

xj = bit representation of 1's which appear y\*k+j(y>=0, j<=k) times. For instance if the 31th bit is 1 in xj,
then there are y\*k+j integers whose 31th bit is 1.

To update xj(j>0) when seeing a number i, first reset bits that
are 1 in both xj and k, as these bits appear y\*k+j+1 times now; then for bits that appear only y\*k+j-1 times, which
is represented by xj-1 and also appear in i, these bits appear y*k+j times now, so we get xj = (xj&~i) | (xj-1&i).

But x1 is different. If some bits appear k times, then 1 more appearance would come back to x1 again, so, bits that
appear 0 times or k times, and also appear in i, they appear 1 times now. 0 or k times is not (x1, x2, ..., xk-1) times,
so x1 = (x1&~i) | ^(x1|x2|x3|...|xk-2|xk-1)&i.

# Problems:
* https://leetcode.com/problems/single-number-ii/

# Reference:
* https://leetcode.com/problems/single-number-ii/discuss/43295/Detailed-explanation-and-generalization-of-the-bitwise-operation-method-for-single-numbers
* https://leetcode.com/problems/single-number-ii/discuss/43296/An-General-Way-to-Handle-All-this-sort-of-questions.
