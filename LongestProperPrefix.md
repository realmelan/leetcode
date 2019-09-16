Longest proper prefix is also a suffix of str s[0..i], and the two don't overlap, that is s[0..k] = s[i-k,i](k!=i).
longest proper prefix is used in KMP search, by skipping the length of the longest proper prefix of pattern that last matches text.


# Ref
* https://www.geeksforgeeks.org/kmp-algorithm-for-pattern-searching/
